//
//  CitizenEscpPrinter.h
//  CitizenEscpPrinter
//
//  Created by Seok on 7/3/19.
//

//#import <Cordova/Cordova.h>
#import <Cordova/CDV.h>
#import "ESCPOSPrinter.h"
#import "CallbackData.h"
#import "EABluetoothPort.h"

NS_ASSUME_NONNULL_BEGIN

@interface CitizenEscpPrinter : CDVPlugin
{
    ESCPOSPrinter *escp;
    NSString* successCallback;
    NSString* failCallback;
    BOOL bCheckPrinterEnd;
    int isConnected;
    int iInterface;
    int currentStatus;
    NSMutableData *stsData;
}

- (void)getPairedBT:(CDVInvokedUrlCommand*)command;
- (void)connect:(CDVInvokedUrlCommand*)command;
- (void)setCharacterSet:(CDVInvokedUrlCommand*)command;
- (void)getStatus:(CDVInvokedUrlCommand*)command;
- (void)printNormal:(CDVInvokedUrlCommand*)command;
- (void)printText:(CDVInvokedUrlCommand*)command;
- (void)printBarCode:(CDVInvokedUrlCommand*)command;
- (void)printQRCode:(CDVInvokedUrlCommand*)command;
- (void)printPDF417:(CDVInvokedUrlCommand*)command;
- (void)printImage:(CDVInvokedUrlCommand*)command;
- (void)lineFeed:(CDVInvokedUrlCommand*)command;
- (void)disconnect:(CDVInvokedUrlCommand*)command;

@property (nonatomic, retain) NSString* successCallback;
@property (nonatomic, retain) NSString* failCallback;

@end

NS_ASSUME_NONNULL_END
