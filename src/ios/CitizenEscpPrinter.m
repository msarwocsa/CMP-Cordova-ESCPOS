//
//  CitizenEscpPrinter.m
//  CitizenEscpPrinter
//
//  Created by Seok on 7/3/19.
//

#import "CitizenEscpPrinter.h"

#define DEBUG   1

@implementation CitizenEscpPrinter
@synthesize successCallback;
@synthesize failCallback;

- (void)pluginInitialize
{
    //
    // Plugin initialize.
    //
#ifdef DEBUG
    NSLog(@"[ Plugin Initialize ]\n");
#endif
    escp = [[ESCPOSPrinter alloc] init];
    isConnected = 0;
    iInterface = -1; // Unknown interface
    currentStatus = 0; // No error.
}

// Blueooth receive function
- (void) statusCheckReceived:(NSNotification *) notification
{
#ifdef DEBUG
    NSString * result;
#endif
    long bytesAvailable = 0;
    long readLength = 0;
    unsigned char buf[8] = {0,};
    EABluetoothPort * sessionController = (EABluetoothPort *)[notification object];
    NSMutableData * readData = [[NSMutableData alloc] init];
    while((bytesAvailable = [sessionController readBytesAvailable]) > 0)
    {
        NSData * data = [sessionController readData:bytesAvailable];
        if(data)
        {
            [readData appendData:data];
            readLength = readLength + bytesAvailable;
        }
    }
    if(readLength > sizeof(buf))
    readLength = sizeof(buf);
    [readData getBytes:buf length:readLength];
    
    int sts = buf[readLength - 1];
    
#ifdef DEBUG
    NSLog(@"readLength=%ld ===== Status Check START ===== %d", readLength, sts);
#endif
    
    if(sts == STS_NORMAL)
    {
        currentStatus = 0;
#ifdef DEBUG
        NSLog(@"No errors");
#endif
    }
    else
    {
        if((sts & STS_COVEROPEN) > 0)
        {
            currentStatus = 1;
#ifdef DEBUG
            NSLog(@"Cover Open");
#endif
        }
        if((sts & STS_PAPEREMPTY) > 0)
        {
            currentStatus = 2;
#ifdef DEBUG
            NSLog(@"Paper Empty");
#endif
        }
        if((sts & STS_BATTERY_LOW) > 0)
        {
            currentStatus = 8;
#ifdef DEBUG
            NSLog(@"Battery low");
#endif
        }
    }
    
    if(bCheckPrinterEnd) bCheckPrinterEnd = NO;

#ifdef DEBUG
    NSLog(@"===== Status Check EXIT =====");
#endif
}

- (void)getPairedBT:(CDVInvokedUrlCommand *)command
{
#ifdef DEBUG
    NSLog(@"getPairedBT");
#endif

    if(escp != nil) escp = [[ESCPOSPrinter alloc] init];
    
    [self.commandDelegate runInBackground:^{
        int i;
        CDVPluginResult *pluginResult;
        NSString *javaScriptString;
        
        NSArray * array = [self->escp getConnectedPrinter];
        // NSLog(@"array.count=%lu", (unsigned long)array.count);
        if(array.count > 0)
        {
            NSString *keys[array.count];
            NSString *values[array.count];
            for(i=1; i<= array.count; i++)
            {
                keys[i-1] = [NSString stringWithFormat:@"Address%d", i];
                values[i-1] = [NSString stringWithFormat:@"bluetooth"];
            }
            
            NSDictionary *jsonInfo =  [NSDictionary dictionaryWithObjects:values forKeys:keys count:array.count];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: jsonInfo];
        } else {
            javaScriptString = [NSString stringWithFormat:@"There are no printers"];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
        }
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)connect:(CDVInvokedUrlCommand *)command
{
    NSLog(@"command.arguments.count = %d", command.arguments.count);

    NSLog(@"connect(connect) called = %d", isConnected);
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        // Call your function or whatever work that needs to be done on a background thread
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            long ret;
            CDVPluginResult* pluginResult = nil;
            
            NSLog(@"connect() called = %d", self->isConnected);
            NSString* message = [command.arguments objectAtIndex:0];
            NSLog(@"message=%@", message);
            
            if(self->isConnected == 1)
            {
                NSString *javaScriptString = [NSString stringWithFormat:@"Connected status"];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
                
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                return;
            }
            if(self->escp == nil) self->escp = [[ESCPOSPrinter alloc] init];
#ifdef DEBUG
            NSLog(@"Start connect call\r\n");
#endif
            if(![message isEqualToString:@"bluetooth"])
            { // tcpip
                self->iInterface = 1;
                ret = [self->escp openPort:message withPortParam:9100];
            } else { // bluetooth.
                self->iInterface = 0;
                ret = [self->escp openPort:message withPortParam:0];
            }
#ifdef DEBUG
            NSLog(@"Connect BT Ret %ld",ret);
#endif
            if (ret < 0)
            {
                NSString *javaScriptString = [NSString stringWithFormat:@"Fail"];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
            } else {
                if(self->iInterface == 0)
                {
                    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(statusCheckReceived:) name:EADSessionDataReceivedNotification object:nil];
                    [[EAAccessoryManager sharedAccessoryManager] registerForLocalNotifications];
                }
                
                NSString *javaScriptString = [NSString stringWithFormat:@"Success"];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:javaScriptString];
                self->isConnected = 1;
            }
            
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            
//            NSLog(@"connect(?) called = %d", self->isConnected);
        });
    });
}

- (void)disconnect:(CDVInvokedUrlCommand *)command
{
#ifdef DEBUG
    NSLog(@"Start disconnect call\r\n");
    NSLog(@"disconnect() called = %d", isConnected);
#endif
    
    if(isConnected == 1)
    {
        [escp closePort];
        escp = nil;
        if(iInterface == 0)
        {
            [[NSNotificationCenter defaultCenter] removeObserver:self name:EADSessionDataReceivedNotification object:nil];
        }
        iInterface = -1;
        isConnected = 0;
        
        CDVPluginResult* pluginResult = nil;
        NSString *javaScriptString = [NSString stringWithFormat:@"Success"];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:javaScriptString];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)setCharacterSet:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];

    [escp setCharacterSet:[arg1 intValue]];
}

- (void)printNormal:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];

    [escp printNormal:arg1];
}

- (void)printText:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];
    NSString* arg2 = [command.arguments objectAtIndex:1];
    NSString* arg3 = [command.arguments objectAtIndex:2];
    NSString* arg4 = [command.arguments objectAtIndex:3];
    
    [escp printText:arg1 withAlignment:[arg2 intValue] withOption:[arg3 intValue] withSize:[arg4 intValue]];
}

- (void)printBarCode:(CDVInvokedUrlCommand *)command
{
    int symbology;
    NSString* arg1 = [command.arguments objectAtIndex:0];
    NSString* arg2 = [command.arguments objectAtIndex:1];
    NSString* arg3 = [command.arguments objectAtIndex:2];
    NSString* arg4 = [command.arguments objectAtIndex:3];
    NSString* arg5 = [command.arguments objectAtIndex:4];
    NSString* arg6 = [command.arguments objectAtIndex:5];
    
    symbology = [arg2 intValue];
    
    int symbol;
    switch(symbology)
    {
        case 101:
        symbol = 65;
        break;
        case 102:
        symbol = 66;
        break;
        case 103:
        symbol = 68;
        break;
        case 104:
        symbol = 67;
        break;
        case 105:
        symbol = 68;
        break;
        case 106:
        symbol = 67;
        break;
        case 107:
        symbol = 70;
        break;
        case 108:
        symbol = 71;
        break;
        case 109:
        symbol = 69;
        break;
        case 110:
        symbol = 72;
        break;
        case 111:
        symbol = 73;
        break;
    }

    [escp printBarCode:arg1 withSymbology:symbol withHeight:[arg3 intValue] withWidth:[arg4 intValue] withAlignment:[arg5 intValue] withHRI:[arg6 intValue]];
}

- (void)printQRCode:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];
    NSString* arg2 = [command.arguments objectAtIndex:1];
    NSString* arg3 = [command.arguments objectAtIndex:2];
    NSString* arg4 = [command.arguments objectAtIndex:3];
    NSString* arg5 = [command.arguments objectAtIndex:4];
    
    [escp printQRCode:arg1 withLength:[arg2 intValue] withModuleSize:[arg3 intValue] withECLevel:[arg4 intValue] withAlignment:[arg5 intValue]];
}

- (void)printPDF417:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];
    NSString* arg2 = [command.arguments objectAtIndex:1];
    NSString* arg3 = [command.arguments objectAtIndex:2];
    NSString* arg4 = [command.arguments objectAtIndex:3];
    NSString* arg5 = [command.arguments objectAtIndex:4];
        
    [escp printPDF417:arg1 withLength:[arg2 intValue] withColumns:[arg3 intValue] withCellWidth:[arg4 intValue] withAlignment:[arg5 intValue]];
}

- (void)printImage:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];
    NSString* arg2 = [command.arguments objectAtIndex:1];
    NSString* arg3 = [command.arguments objectAtIndex:2];
    
    [escp printBitmap:arg1 withAlignment:[arg2 intValue] withSize:[arg3 intValue] withBrightness:5];
}


- (void)lineFeed:(CDVInvokedUrlCommand *)command
{
    NSString* arg1 = [command.arguments objectAtIndex:0];
    
    [escp lineFeed:[arg1 intValue]];
}

- (void)getStatus:(CDVInvokedUrlCommand *)command
{
    int returnValue, waitTimeout = 0;
    CDVPluginResult* pluginResult = nil;
    NSString *javaScriptString;
    
    if(iInterface == 0)
    {
        bCheckPrinterEnd = YES;
        [escp printerCheck];
        while (bCheckPrinterEnd) {
            [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1.0]];    // wait 1.0 sec
            waitTimeout++;
            if(waitTimeout > 4)
            {
                javaScriptString = [NSString stringWithFormat:@"No response"];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
                return;
            }
        }
        
        if( (currentStatus == 0) || (currentStatus == 8) ) // No error or Battery low.
        {
            switch(currentStatus)
            {
                case 0:
                    javaScriptString = [NSString stringWithFormat:@"Success"];
                    break;
                case 8:
                    javaScriptString = [NSString stringWithFormat:@"Battery low"];
                    break;
            }
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:javaScriptString];
        } else {
            switch(currentStatus)
            {
            case 1:
                javaScriptString = [NSString stringWithFormat:@"Cover Open"];
                break;
            case 2:
                javaScriptString = [NSString stringWithFormat:@"Paper Empty"];
                break;
            }
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
        }
    } else {
        returnValue = (int)[escp printerCheck];
        if(returnValue == 0)
        {
            javaScriptString = [NSString stringWithFormat:@"Success"];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:javaScriptString];
        } else {
            switch(returnValue)
            {
                case 1:
                javaScriptString = [NSString stringWithFormat:@"Cover Open"];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
                break;
                case 2:
                javaScriptString = [NSString stringWithFormat:@"Paper Empty"];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:javaScriptString];
                break;
            }
        }
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
