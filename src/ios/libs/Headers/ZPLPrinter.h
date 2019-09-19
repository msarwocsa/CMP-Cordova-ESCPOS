//
//  ZPLPrinter.h
//  iOS
//
//  Created by Sang-ok OH on 16. 1. 12..
//  Copyright 2016. All rights reserved.
//

#import <Foundation/Foundation.h>

// ZPL Status
#define STS_ZPL_NORMAL          0
#define STS_ZPL_SUCCESS         0
#define STS_ZPL_BUSY            1
#define STS_ZPL_PAPER_EMPTY     2
#define STS_ZPL_COVER_OPEN      4
#define STS_ZPL_BATTERY_LOW     8

// Rotation
extern NSString * const ZPL_ROTATION_0; 
extern NSString * const ZPL_ROTATION_90;
extern NSString * const ZPL_ROTATION_180;
extern NSString * const ZPL_ROTATION_270;

// Media
extern NSString * const ZPL_SENSE_CONTINUOUS; 
extern NSString * const ZPL_SENSE_GAP;
extern NSString * const ZPL_SENSE_WEB;
extern NSString * const ZPL_SENSE_BLACKMARK;

// Device Font (Bitmap)
extern NSString * const ZPL_FONT_A; 
extern NSString * const ZPL_FONT_B; 
extern NSString * const ZPL_FONT_C; 
extern NSString * const ZPL_FONT_D; 
extern NSString * const ZPL_FONT_E; 
extern NSString * const ZPL_FONT_F; 
extern NSString * const ZPL_FONT_G; 
extern NSString * const ZPL_FONT_H; 

extern NSString * const ZPL_FONT_0; 
extern NSString * const ZPL_FONT_1; 
extern NSString * const ZPL_FONT_2; 
extern NSString * const ZPL_FONT_3; 
extern NSString * const ZPL_FONT_4; 
extern NSString * const ZPL_FONT_5; 
extern NSString * const ZPL_FONT_6; 
extern NSString * const ZPL_FONT_7; 
extern NSString * const ZPL_FONT_8; 
extern NSString * const ZPL_FONT_9; 

extern NSString * const ZPL_FONT_P; 
extern NSString * const ZPL_FONT_Q; 
extern NSString * const ZPL_FONT_R; 
extern NSString * const ZPL_FONT_S; 
extern NSString * const ZPL_FONT_T; 
extern NSString * const ZPL_FONT_U; 
extern NSString * const ZPL_FONT_V; 

// Barcode Types
extern NSString * const ZPL_BCS_Code11;
extern NSString * const ZPL_BCS_Interleaved_2OF5; 
extern NSString * const ZPL_BCS_Code39;  	
extern NSString * const ZPL_BCS_Code49;  	
extern NSString * const ZPL_BCS_PlanetCode; 	
extern NSString * const ZPL_BCS_PDF417; 	
extern NSString * const ZPL_BCS_EAN8;  
extern NSString * const ZPL_BCS_UPCE;  
extern NSString * const ZPL_BCS_Code93;  
extern NSString * const ZPL_BCS_CODABLOCK; 
extern NSString * const ZPL_BCS_Code128; 
extern NSString * const ZPL_BCS_UPSMAXICODE;  
extern NSString * const ZPL_BCS_EAN13;  
extern NSString * const ZPL_BCS_MicroPDF417;  
extern NSString * const ZPL_BCS_Industrial_2OF5;  
extern NSString * const ZPL_BCS_Standard_2OF5;  
extern NSString * const ZPL_BCS_Codabar;  
extern NSString * const ZPL_BCS_LOGMARS; 
extern NSString * const ZPL_BCS_MSI;  
extern NSString * const ZPL_BCS_Aztec;  
extern NSString * const ZPL_BCS_Plessey;  
extern NSString * const ZPL_BCS_QRCode;  
extern NSString * const ZPL_BCS_RSS;  
extern NSString * const ZPL_BCS_UPCEANEXT; 
extern NSString * const ZPL_BCS_TLC39;  
extern NSString * const ZPL_BCS_UPCA;
extern NSString * const ZPL_BCS_DataMatrix;  
extern NSString * const ZPL_BCS_POSTNET;  

// QR Code ECL
extern NSString * const ZPL_QR_ECL_H; 
extern NSString * const ZPL_QR_ECL_Q;
extern NSString * const ZPL_QR_ECL_M;
extern NSString * const ZPL_QR_ECL_L;

// DataMatrix Quality
#define ZPL_DM_QUALITY_0		0
#define ZPL_DM_QUALITY_50	50
#define ZPL_DM_QUALITY_80	80
#define ZPL_DM_QUALITY_100	100
#define ZPL_DM_QUALITY_140	140
#define ZPL_DM_QUALITY_200	200 

// Graphic color
extern NSString * const ZPL_LINE_COLOR_W;
extern NSString * const ZPL_LINE_COLOR_B;

// Graphic Direction of Diagonal
extern NSString * const ZPL_DIAGONAL_R;
extern NSString * const ZPL_DIAGONAL_L; 


@interface ZPLPrinter : NSObject 
{
	BOOL startXA;
	NSStringEncoding encoding;
}

@property (nonatomic) BOOL startXA;
@property (nonatomic) NSStringEncoding encoding;

- (long) openPort:(NSString*)portName withPortParam:(int) port;
- (long) closePort;

// ZPL Command methods.
- (long) setInternationalFont:(int) internationalFont;
- (long) startPage;
- (long) endPage:(int) quantity;
- (long) setSpeed:(int) speed;
- (long) setDarkness:(int) darkness;
- (long) setupPrinter:(NSString *) orientation withmTrack:(NSString *) mTrack withWidth:(int) width withHeight:(int) height;
- (long) printTextFormat:(NSString *) deviceFont withOrientation:(NSString *) orientation withWidth:(int) width withHeight:(int) height
	withPrintX:(int) printX withPrintY:(int) printY withData:(NSString *) data withFormat:(NSString *) format withIncrement:(NSString *) increment;
- (long) printText:(NSString *) deviceFont withOrientation:(NSString *) orientation withWidth:(int) width withHeight:(int) height
	withPrintX:(int) printX withPrintY:(int) printY withData:(NSString *) data;
- (long) setBarcodeField:(int) moduleWidth withRatio:(NSString *) ratio withBarHeight:(int) barHeight;
- (long) printBarcode:(NSString *) barcodeType withBarcodeProp:(NSString *) barcodeProp withPrintX:(int) printX withPrintY:(int) printY withData:(NSString *) data;
- (long) printImage:(NSString *) filePath withPrintX:(int) printX withPrintY:(int) printY withBrightness:(int) bright;
- (long) printDiagonalLine:(int) printX withPrintY:(int) printY withWidth:(int) width withHeight:(int) height withThickness:(int) thickness
	withLineColor:(NSString *) lineColor withDirection:(NSString *) direction;
- (long) printCircle:(int) printX withPrintY:(int) printY withDiameter:(int) diameter withThickness:(int) thickness withLineColor:(NSString *) lineColor;
- (long) printEllipse:(int) printX withPrintY:(int) printY withWidth:(int) width withHeight:(int) height withThickness:(int) thickness
	withLineColor:(NSString *) lineColor;
- (long) printRectangle:(int) printX withPrintY:(int) printY withWidth:(int) width withHeight:(int) height withThickness:(int) thickness
	withLineColor:(NSString *) lineColor withRounding:(int) rounding;
// 2D Barcode
- (long) printPDF417:(int) printX withPrintY:(int) printY withOrientation:(NSString *) orientation withCellWidth:(int) cellWidth withSecurity:(int) security	withNumOfRow:(int) numOfRow withTruncate:(NSString *) truncate withData:(NSString *) data;
- (long) printDataMatrix:(int) printX withPrintY:(int) printY withOrientation:(NSString *) orientation withCellWidth:(int) cellWidth withQuality:(int) quality withData:(NSString *) data;
- (long) printQRCODE:(int) printX withPrintY:(int) printY withOrientation:(NSString *) orientation withModel:(int) model withCellWidth:(int) cellWidth withData:(NSString *) data;
- (long) directCommand:(NSString *) command;
- (long) printString:(NSString*) data;
- (long) printData:(unsigned char *) data withLength:(int) length;

// Check the printer status.
- (long) printerCheck;
- (long) status; // Wi-Fi Only. Bluetooth not supported.

// Added in 1.75b to get/set printer's info.
// Wi-Fi only.
- (long) getPrinterInfo:(unsigned char *)SendBuf charsToSend:(int)wLength withRecvBuf:(unsigned char *)RecvBuf;
- (long) setPrinterInfo:(unsigned char *)SendBuf charsToSend:(int)wLength;

@end