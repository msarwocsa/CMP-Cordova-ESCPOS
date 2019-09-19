//
//  CPCLPrinter.h
//  iOS
//
//  Created by leesk on 12. 1. 10..
//  Copyright 2012. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

// CPCL Status
#define STS_CPCL_BATTERY_LOW	  8 
#define STS_CPCL_COVER_OPEN		  4 
#define STS_CPCL_PAPER_EMPTY	  2 
#define STS_CPCL_BUSY 			  1 
#define STS_CPCL_NORMAL			  0 

// Unit
#define CPCL_INCH    0 
#define CPCL_CENTI   1 
#define CPCL_MILLI   2 
#define CPCL_DOTS    3 

// Justification
#define CPCL_LEFT     0 
#define CPCL_CENTER   1 
#define CPCL_RIGHT    2 

// Text Rotation
#define CPCL_NO_ROTATION    0 
#define CPCL_0_ROTATION     0 
#define CPCL_90_ROTATION    1 
#define CPCL_180_ROTATION   2 
#define CPCL_270_ROTATION   3 

// Concatenation
/** It concatenates text as horizontal */
#define CPCL_CONCAT    0  
/** It concatenates text as vertical */
#define CPCL_VCONCAT   1 

// Media Type
/**  Label with Gap. */
#define CPCL_LABEL 		  0 
/**  Label with Black Mark. */
#define CPCL_BLACKMARK    1 
/**  Continuous Label. */
#define CPCL_CONTINUOUS   2 

// Ratio
/** Set up width ratio */
#define CPCL_TXT_1WIDTH		1 
#define CPCL_TXT_2WIDTH		2 
#define CPCL_TXT_3WIDTH		3 
#define CPCL_TXT_4WIDTH		4 
#define CPCL_TXT_5WIDTH		5 
#define CPCL_TXT_6WIDTH		6 
#define CPCL_TXT_7WIDTH		7 
#define CPCL_TXT_8WIDTH		8 
#define CPCL_TXT_9WIDTH		9 
#define CPCL_TXT_10WIDTH    10 
#define CPCL_TXT_11WIDTH    11 
#define CPCL_TXT_12WIDTH    12 
#define CPCL_TXT_13WIDTH    13 
#define CPCL_TXT_14WIDTH    14 
#define CPCL_TXT_15WIDTH    15 
#define CPCL_TXT_16WIDTH    16  

// Height Ratio
/** Set up height ratio */
#define CPCL_TXT_1HEIGHT	1 
#define CPCL_TXT_2HEIGHT	2 
#define CPCL_TXT_3HEIGHT	3 
#define CPCL_TXT_4HEIGHT	4 
#define CPCL_TXT_5HEIGHT	5 
#define CPCL_TXT_6HEIGHT	6 
#define CPCL_TXT_7HEIGHT	7 
#define CPCL_TXT_8HEIGHT	8 
#define CPCL_TXT_9HEIGHT	9 
#define CPCL_TXT_10HEIGHT   10 
#define CPCL_TXT_11HEIGHT   11 
#define CPCL_TXT_12HEIGHT   12 
#define CPCL_TXT_13HEIGHT   13 
#define CPCL_TXT_14HEIGHT   14 
#define CPCL_TXT_15HEIGHT   15 
#define CPCL_TXT_16HEIGHT   16 

// Barcode Types
extern NSString * const CPCL_BCS_39;
extern NSString * const CPCL_BCS_39C; 
extern NSString * const CPCL_BCS_39F;  	
extern NSString * const CPCL_BCS_39FC;  	
extern NSString * const CPCL_BCS_93; 	
extern NSString * const CPCL_BCS_128; 	
extern NSString * const CPCL_BCS_EAN128;  
extern NSString * const CPCL_BCS_CODABAR;  
extern NSString * const CPCL_BCS_CODABARC;  
extern NSString * const CPCL_BCS_EAN8; 
extern NSString * const CPCL_BCS_EAN82; 
extern NSString * const CPCL_BCS_EAN85;  
extern NSString * const CPCL_BCS_EAN13;  
extern NSString * const CPCL_BCS_EAN132;  
extern NSString * const CPCL_BCS_EAN135;  
extern NSString * const CPCL_BCS_I2OF5;  
extern NSString * const CPCL_BCS_POSTNET;  
extern NSString * const CPCL_BCS_UPCA; 
extern NSString * const CPCL_BCS_UPCA2;  
extern NSString * const CPCL_BCS_UPCA5;  
extern NSString * const CPCL_BCS_UPCE;  
extern NSString * const CPCL_BCS_UPCE2;  
extern NSString * const CPCL_BCS_UPCE5;  
extern NSString * const CPCL_BCS_MSI; 
extern NSString * const CPCL_BCS_MSI1C;  
extern NSString * const CPCL_BCS_MSI2C;
extern NSString * const CPCL_BCS_MSI11C;  

// Barcode Ratio
/** Set up the barcode ratio as 1.5 : 1. */
#define CPCL_BCS_0RATIO   0  
/** Set up the barcode ratio as 2.0 : 1. */
#define CPCL_BCS_1RATIO   1  
/** Set up the barcode ratio as 2.5 : 1. */
#define CPCL_BCS_2RATIO   2  
/** Set up the barcode ratio as 3.0 : 1. */
#define CPCL_BCS_3RATIO   3  
/** Set up the barcode ratio as 3.5 : 1. */
#define CPCL_BCS_4RATIO   4  
/** Set up the barcode ratio as 2.0 : 1. */
#define CPCL_BCS_20RATIO   20
/** Set up the barcode ratio as 2.1 : 1. */
#define CPCL_BCS_21RATIO   21
/** Set up the barcode ratio as 2.2 : 1. */
#define CPCL_BCS_22RATIO   22
/** Set up the barcode ratio as 2.3 : 1. */
#define CPCL_BCS_23RATIO   23
/** Set up the barcode ratio as 2.4 : 1. */
#define CPCL_BCS_24RATIO   24
/** Set up the barcode ratio as 2.5 : 1. */
#define CPCL_BCS_25RATIO   25
/** Set up the barcode ratio as 2.6 : 1. */
#define CPCL_BCS_26RATIO   26
/** Set up the barcode ratio as 2.7 : 1. */
#define CPCL_BCS_27RATIO   27
/** Set up the barcode ratio as 2.8 : 1. */
#define CPCL_BCS_28RATIO   28
/** Set up the barcode ratio as 2.9 : 1. */
#define CPCL_BCS_29RATIO   29
/** Set up the barcode ratio as 3.0 : 1. */
#define CPCL_BCS_30RATIO   30  

// Pattern
/** Filled(Black/default value) */
#define CPCL_DEFAULT_PATTERN    100  
/** It prints the pattern as a horizontal line. */
#define CPCL_HORIZON_PATTERN    101 
/** It prints the pattern as a vertical line. */
#define CPCL_VERTICAL_PATTERN   102 
/** It prints the diagonal pattern to the right. */
#define CPCL_RDIAGON_PATTERN    103 
/** It prints the diagonal pattern to the left. */
#define CPCL_LDIAGON_PATTERN    104 
/** It prints the pattern as a square. */
#define CPCL_SQUARE_PATTERN     105 
/** It prints the pattern as a diagonal line to right and left. */
#define CPCL_CROSS_PATTERN      106 

// Tone
/** Set up as default. */
#define CPCL_CONT_DEFAULT  	  0 
/** Print as middle brightness. */
#define CPCL_CONT_MEDIUM  	  1  
/** Print as dark. */
#define CPCL_CONT_DARK 		  2 
/** Print as very dark. */
#define CPCL_CONT_VERY_DARK   3 

// 2D Barcode
extern NSString * const CPCL_BCS_PDF417; 
extern NSString * const CPCL_BCS_MAXICODE;
extern NSString * const CPCL_BCS_QRCODE;
extern NSString * const CPCL_BCS_DATAMATRIX;

extern NSString * const CPCL_BCS_RSS14;
extern NSString * const CPCL_BCS_RSS14STACK;
extern NSString * const CPCL_BCS_RSS14STACK_OMNI;
extern NSString * const CPCL_BCS_RSS_LTD;
extern NSString * const CPCL_BCS_RSS_EXP;
extern NSString * const CPCL_BCS_RSS_EXPSTACK;

// Text Font
#define CPCL_FONT_0   0 
#define CPCL_FONT_1   1 
#define CPCL_FONT_2   2 
#define CPCL_FONT_4   4 
#define CPCL_FONT_5   5 
#define CPCL_FONT_6   6 	
#define CPCL_FONT_7   7 

// Country Command Parameters.
extern NSString * const CPCL_COUNTRY_USA;
extern NSString * const CPCL_COUNTRY_GERMANY;
extern NSString * const CPCL_COUNTRY_FRANCE;
extern NSString * const CPCL_COUNTRY_SWEDEN; 
extern NSString * const CPCL_COUNTRY_SPAIN;
extern NSString * const CPCL_COUNTRY_NORWAY;
extern NSString * const CPCL_COUNTRY_ITALY;
extern NSString * const CPCL_COUNTRY_UK;
extern NSString * const CPCL_COUNTRY_CP850;
extern NSString * const CPCL_COUNTRY_LATIN9;



@interface CPCLPrinter : NSObject 
{
	NSStringEncoding encoding;
}

@property (nonatomic) NSStringEncoding encoding;

- (long) openPort:(NSString*)portName withPortParam:(int) port;
- (long) closePort;

// CPCL Command methods.
- (long) setForm:(int) horizonOffset withResX:(int) resolX withResY:(int) resolY withLabelHeight:(int) labelHeight withQuantity:(int) quantity;
- (long) printForm;
- (long) printerCheck;
- (long) status;
- (long) setMeasure:(int) measure;
- (long) setJustification:(int) justify;

- (long) printCPCLText:(int) rotation withFontType:(int) fontType withFontSize:(int) fontSize withPrintX:(int) printX withPrintY:(int) printY
			 withData:(NSString *) data withCount:(int) count;

- (long) setConcat:(int) contcatMode withPrintX:(int) printX withPrintY:(int) printY;
- (long) concatText:(int) fontType withFontSize:(int) fontSize withOffset:(int) offset withData:(NSString *) data;
- (long) resetConcat;
- (long) setMultiLine:(int) lineHeight;
- (long) multiLineText:(int) rotation withFontType:(int) fontType withFontSize:(int) fontSize withPrintX:(int) printX withPrintY:(int) printY;
- (long) multiLineData:(NSString *) data;
- (long) resetMultiLine;
- (long) setMagnify:(int) width withHeight:(int) height;
- (long) resetMagnify;

- (long) printCPCLBarcode:(int) rotation withBarcodeType:(NSString *) barcodeType withNarrowBar:(int) NB withRatio:(int) ratio
		   withBarHeight:(int) barHeight withPrintX:(int) printX withPrintY:(int) printY withData:(NSString *) data withCount:(int) count;

- (long) printBox:(int) xs withYs:(int) ys withXx:(int) xx withYX:(int) yx withThickness:(int) thickness;
- (long) printLine:(int) xs withYs:(int) ys withXx:(int) xx withYx:(int) yx withThickness:(int) thickness;
- (long) inverseLine:(int) xs withYs:(int) ys withXx:(int) xx withYx:(int) yx withThickness:(int) thickness;
- (long) setPattern:(int) patternNum;
- (long) printBitmap:(NSString *) filePath withPrintX:(int) printX withPrintY:(int) printY withBrightness:(int) bright;
- (long) setContrast:(int) darkness;
- (long) setPageWidth:(int) pageWidth;
- (long) printCPCLImage:(NSString *) imageName withPrintX:(int) printX withPrintY:(int) printY;
- (long) setSpeed:(int) speed;
- (long) setTone:(int) tone;
- (long) setCPCLBarcode:(int) fontNum withFontSize:(int) fontSize withOffset:(int) offset;
- (long) resetCPCLBarcode; // Added in 1.61

- (long) setMedia:(int) mode;
- (long) setCountry:(NSString *) country;
- (long) resetCountry;

// 2D Barcode
- (void) printPDF417:(int) rotation withPrintX:(int) printX withPrintY:(int) printY withUnitWidth:(int) unitWidth withUnitHeight:(int) unitHeight 
	withNumOfColumns:(int) column withSecurityLevel:(int) securityLevel withData:(NSString *) data;

- (void) printDATAMATRIX:(int) rotation withPrintX:(int) printX withPrintY:(int) printY withECCLevel:(int) eccLevel withCellSize:(int) cellSize 
				withData:(NSString *) data;

- (void) printQRCODE:(int) rotation withPrintX:(int) printX withPrintY:(int) printY withVersion:(int) version withECLevel:(int) ecLevel 
	  withModuleSize:(int) moduleSize withMaskNo:(int) maskNo withData:(NSString *) data;

- (void) printGS1:(int) rotation withType:(NSString *) type withModuleWidth:(int) moduleWidth withHeight:(int) height withPrintX:(int) printX withPrintY:(int) printY 
		 withData:(NSString *) data;

// Added in 1.71 for web printing
- (long) printImage:(UIImage *) imgApp withPrintX:(int) printX withPrintY:(int) printY withBrightness:(int) bright;
- (long) printNormalWeb:(NSString *) normalData;
//////////////////////////////////

// Added in 1.71 for iOS font.
- (long) printIOSFont:(int) rotation withPrintX:(int) printX withPrintY:(int) printY withFontName:(NSString *)fontName withBold:(int)bold withItalic:(int)italic withUnderline:(int)underline withData:(NSString *)data withMaxWidth:(int)maxWidth withFontSize:(int)fontdotsize withReverse:(int)reverse;

// bluetooth only.
- (long) searchPrinter:(NSString*)portName withPortParam:(int) port;
- (long) closePortReset;
- (long) printData:(unsigned char *)data withLength:(int) length;

// Added in 1.75b to get/set printer's info.
// Wi-Fi only.
- (long) getPrinterInfo:(unsigned char *)SendBuf charsToSend:(int)wLength withRecvBuf:(unsigned char *)RecvBuf;
- (long) setPrinterInfo:(unsigned char *)SendBuf charsToSend:(int)wLength;

@end
