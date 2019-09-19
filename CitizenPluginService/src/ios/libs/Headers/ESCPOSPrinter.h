//
//  ESCPOSPrinter.h
//  iOS
//
//  Modified by sooh on 2016. 12. 12..
//  Copyright 2011. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#define ENABLE_MSR

// Alignment
#define ALIGNMENT_LEFT				0
#define ALIGNMENT_CENTER			1
#define ALIGNMENT_RIGHT				2

// Font properties
#define FNT_DEFAULT					0
#define FNT_FONTB					1
#define FNT_BOLD					8
#define FNT_UNDERLINE				128
#define FNT_UNDERLINE2              256

// Font size
#define TXT_1HEIGHT					0
#define TXT_2HEIGHT					1
#define TXT_3HEIGHT					2
#define TXT_4HEIGHT					3
#define TXT_5HEIGHT					4
#define TXT_6HEIGHT					5
#define TXT_7HEIGHT					6
#define TXT_8HEIGHT					7

#define TXT_1WIDTH					0
#define TXT_2WIDTH					16
#define TXT_3WIDTH					32
#define TXT_4WIDTH					48
#define TXT_5WIDTH					64
#define TXT_6WIDTH					80
#define TXT_7WIDTH					96
#define TXT_8WIDTH					112

// Barcode symbol
#define BCS_UPCA					65
#define BCS_UPCE					66
#define BCS_EAN13					67
#define BCS_JAN13					67
#define BCS_EAN8					68
#define BCS_JAN8					68
#define BCS_CODE39					69
#define BCS_ITF						70
#define BCS_CODABAR					71
#define BCS_CODE93					72
#define BCS_CODE128					73

// Barcode width. (Default 3) 
#define BCS_2WIDTH					2
#define BCS_3WIDTH					3
#define BCS_4WIDTH					4
#define BCS_5WIDTH					5
#define BCS_6WIDTH					6

// Barcode Text Position
#define HRI_TEXT_NONE				0
#define HRI_TEXT_ABOVE				1
#define HRI_TEXT_BELOW				2

// Bitmap image size 0 - 3
#define BITMAP_NORMAL				0
#define BITMAP_DOUBLE_WIDTH			1
#define BITMAP_DOUBLE_HEIGHT		2
#define BITMAP_QUADRUPLE			3

// QRCode Error Correction Level.
#define QRCODE_EC_LEVEL_L			0
#define QRCODE_EC_LEVEL_M			1
#define QRCODE_EC_LEVEL_Q			2
#define QRCODE_EC_LEVEL_H			3

// Print direction
#define DIRECTION_LEFT_RIGHT		0
#define DIRECTION_BOTTOM_TOP		1
#define DIRECTION_RIGHT_LEFT		2
#define DIRECTION_TOP_BOTTOM		3


// POSPrinter Only.
#ifdef ENABLE_POS
// Cashdrawer status
#define STS_CD_OPEN					0
#define STS_CD_CLOSE				1
// Cashdrawer pin
#define CD_PIN_TWO					0
#define CD_PIN_FIVE					1
#endif

// Printer Status
#define STS_PRINTEROFF				128
#define STS_MSR_READ				64
#define STS_PAPEREMPTY				32
#define STS_COVEROPEN				16
#define STS_BATTERY_LOW				8
#define STS_PAPERNEAREMPTY			4
#define STS_NORMAL					0

// MSR
#define MSR_TRACK_1					49
#define MSR_TRACK_2					50
#define MSR_TRACK_12				51
#define MSR_TRACK_3					52
#define MSR_TRACK_23				54

// Dithering type
#define THRESHOLDING_DITHERING		0
#define ERROR_DIFFUSION_DITHERING 	1
#define ORDERED_2x2_DITHERING       2
#define ORDERED_4x4_DITHERING       3
#define ORDERED_8x8_DITHERING       4
#define ORDERED_12x12_DITHERING     5


@interface ESCPOSPrinter : NSObject 
{
	BOOL asbMode;
	BOOL msrDataMode;
	NSStringEncoding encoding;
    int ditherType;
}
@property (nonatomic) BOOL asbMode;
@property (nonatomic) BOOL msrDataMode;
@property (nonatomic) NSStringEncoding encoding;
@property (nonatomic) int ditherType;


- (long) openPort:(NSString*)portName withPortParam:(int) port;
- (long) closePort;

- (long) printText:(NSString *) data withAlignment:(int) align withOption:(int) option withSize:(int) size;
- (long) printString:(NSString*) data;
- (long) printData:(unsigned char *) data withLength:(int) length;
- (long) printNVBitmap:(int) imageNumber withAlignment:(int) align withSize:(int) size;
- (long) printBitmap:(NSString *) filePath withAlignment:(int) align withSize:(int) size withBrightness:(int) bright;
- (long) printBarCode:(NSString*) data withSymbology:(int) symbol withHeight:(int) height withWidth:(int) width withAlignment:(int) align withHRI:(int) textPos;
- (long) printPDF417:(NSString *) data withLength:(int) dataLength withColumns:(int) columns withCellWidth:(int) cWidth withAlignment:(int) align;
- (long) printQRCode:(NSString*) data withLength:(int) dataLength withModuleSize:(int) moduleSize withECLevel:(int) ECLevel withAlignment:(int) align;

- (long) asbOn;
- (long) asbOff;
- (void) registerCallback:(id) object withSelctor:(SEL) selector;
- (void) unregisterCallback;

- (long) printPageModeData;
- (long) clearPageModeData;
- (long) setPageMode:(BOOL) pagemode;
- (long) setPrintDirection:(int) direction;
- (long) setPrintingArea:(int) startX withStartY:(int) startY withWidth:(int) width withHeight:(int) height;
- (long) setMotionUnit:(int) hUnit withVUnit:(int) vUnit;
- (long) setAbsoluteVertical:(int) absolutePosition;
- (long) setRelativeVertical:(int) relativePosition;
- (long) lineFeed:(int) lfConunt;

// MSR function.
- (long) readMSR:(int) mode;
- (long) cancelMSR;

- (long) printerCheck;

// Added in 1.71 for web printing
- (long) printImage:(UIImage *) imgApp withAlignment:(int) align withSize:(int) size withBrightness:(int) bright;
- (long) printNormalWeb:(NSString *) normalData;
//////////////////////////////////

// Added in 1.71 for font
- (long) printIOSFont:(NSString *)fontName withBold:(int)bold withItalic:(int)italic withUnderline:(int)underline
             withData:(NSString *)data withMaxWidth:(int)maxWidth withFontSize:(int)fontdotsize withAlgin:(int)alignment withReverse:(int)reverse;
// Added in 1.71 for dithering
- (long) setDithering:(int) iDither;
// Added in 1.75 for OLE POS Command
- (long) printNormal:(NSString *) Data;
// Added in 1.75 for CharacterSet
- (long) setCharacterSet:(int) iCharSet;


// bluetooth only.
- (long) searchPrinter:(NSString*)portName withPortParam:(int) port;
- (long) closePortReset;
// Added in 1.75 for connected Printer by cordova
- (NSArray *) getConnectedPrinter;

// Added in 1.75b to get/set printer's info.
// Wi-Fi only.
- (long) getPrinterInfo:(unsigned char *)SendBuf charsToSend:(int)wLength withRecvBuf:(unsigned char *)RecvBuf;
- (long) setPrinterInfo:(unsigned char *)SendBuf charsToSend:(int)wLength;

@end
