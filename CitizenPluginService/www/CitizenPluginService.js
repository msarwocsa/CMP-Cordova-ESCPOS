var CitizenEscpPrinter = function () { };

CitizenEscpPrinter.prototype.getPairedBT = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "getPairedBT", []);
}

CitizenEscpPrinter.prototype.connect = function (successCallback, errorCallback, address) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "connect", [address]);
}

CitizenEscpPrinter.prototype.setCharacterSet = function (successCallback, errorCallback, iCharSet) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "setCharacterSet", [iCharSet]);
};
	
CitizenEscpPrinter.prototype.getStatus = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "getStatus", []);
}

CitizenEscpPrinter.prototype.printNormal = function (successCallback, errorCallback, data) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "printNormal", [data]);
}
	
CitizenEscpPrinter.prototype.printText = function (successCallback, errorCallback, data, alignment, attribute, textSize) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "printText", [data, alignment, attribute, textSize]);
}
	
CitizenEscpPrinter.prototype.printBarCode = function (successCallback, errorCallback, data, symbology, height, width, alignment, hri) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "printBarCode", [data, symbology, height, width, alignment, hri]);
}
	
CitizenEscpPrinter.prototype.printQRCode = function (successCallback, errorCallback, data, dataSize, cellSize, iECL, alignment) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "printQRCode", [data, dataSize, cellSize, iECL, alignment]);
}
	
CitizenEscpPrinter.prototype.printPDF417 = function (successCallback, errorCallback, pdfData, dataSize, numberOfColumn, cellWidth, alignment) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "printPDF417", [pdfData, dataSize, numberOfColumn, cellWidth, alignment]);
}
	
CitizenEscpPrinter.prototype.printImage = function (successCallback, errorCallback, imagePath, alignment, size) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "printImage", [imagePath, alignment, size]);
}
	
CitizenEscpPrinter.prototype.lineFeed = function (successCallback, errorCallback, iLine) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "lineFeed", [iLine]);
}
	
CitizenEscpPrinter.prototype.swipeMSR = function (successCallback, errorCallback, selTrack) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "swipeMSR", [selTrack]);
}
	
CitizenEscpPrinter.prototype.cancelMSR = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "cancelMSR", []);
}
	
CitizenEscpPrinter.prototype.disconnect = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "disconnect", []);
}
	
CitizenEscpPrinter.prototype.searchBT = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "searchBT", []);
}
	
CitizenEscpPrinter.prototype.getCountBT = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "getCountBT", []);
}
	
CitizenEscpPrinter.prototype.getListBTAddress = function (successCallback, errorCallback) {
    return cordova.exec(successCallback, errorCallback, "CitizenEscpPrinter", "getListBTAddress", []);
}

module.exports = new CitizenEscpPrinter;

