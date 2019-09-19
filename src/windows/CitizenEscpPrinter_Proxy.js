var citizenAPI = CitizenPlugin.Citizen;
var init = new CitizenPlugin.Citizen();

var CMP_SUCCESS = 0;
var CMP_FAIL = -1;
var CMP_STS_NORMAL = 0;
var CMP_STS_COVER_OPEN = 16;
var CMP_STS_PAPER_EMPTY = 32;
var CMP_STS_BATTERY_LOW = 8;
var CMP_STS_MSR_READ = 64;
var CMP_IMAGE_PROCESS_ERROR = 1;
var CMP_FILE_IS_NOT_EXIST = 2;
var CMP_FILE_IS_NOT_BITMAP = 3;
var CMP_FILE_IS_UNSUPPORTED = 4;

var msg_no_printer = "There are no printers";
var msg_fail_connect = "Connection failed";
var msg_cover_open = "Cover open";
var msg_paper_empty = "Paper empty";
var msg_battery_low = "Battery low";
var msg_msr_read = "MSR Read mode";
var msg_process_error = "File Error";
var msg_not_exist = "File is not exist";
var msg_not_bitmap = "File is not a bitmap";
var msg_unsupported = "File is unsupported file";
var msg_select_track_fail = "Fail to change MSR mode";
var msg_canceled_msr = "canceled by user";
var msg_cancel_success = "Cancel success";
var msg_success = "Success";
var msg_not_supported = "Not Supported";


cordova.commandProxy.add("CitizenEscpPrinter", {
    getPairedBT: function (successCallback, errorCallback) {
        citizenAPI.getPairedBluetooth().then(
            function (msg) {
                if (msg != CMP_FAIL)
                    successCallback(msg);
                else
                    errorCallback(msg_no_printer);
            },
            function (msg) {
                errorCallback(msg);
            }
        );
    }
    ,
    connect: function (successCallback, errorCallback, args) {

        citizenAPI.connectDevice(args[0]).then(
            function (msg) {
                if (msg == CMP_SUCCESS)
                    successCallback(msg_success);
                else
                    errorCallback(msg_fail_connect);
            },
            function (msg) {
                errorCallback(msg);
            }
        );
    }
    ,
    setCharacterSet: function (successCallback, errorCallback, args) {

        citizenAPI.setCharacterSet(args[0]);
    }
    ,
    getStatus: function (successCallback, errorCallback) {

        var msg = citizenAPI.getStatus();

        if (msg == CMP_STS_NORMAL) {
            successCallback(msg_success);
        }
        else {
            switch (msg) {
                case CMP_STS_BATTERY_LOW: msg = msg_battery_low; break;
                case CMP_STS_COVER_OPEN: msg = msg_cover_open; break;
                case CMP_STS_PAPER_EMPTY: msg = msg_paper_empty; break;
                case CMP_STS_MSR_READ: msg = msg_msr_read; break;
                default: msg = "Error"; break;
            }

            errorCallback(msg);
        }
    }
    ,
    printNormal: function (successCallback, errorCallback, args) {

        var msg = citizenAPI.printNormal(args[0]);

        if (msg != CMP_SUCCESS) {
            errorCallback(msg);
        }
    }
    ,
    printText: function (successCallback, errorCallback, args) {

        var msg = citizenAPI.printText(args[0], args[1], args[2], args[3]);

        if (msg != CMP_SUCCESS) {
            errorCallback(msg);
        }
    }
    ,
    printBarCode: function (successCallback, errorCallback, args) {

        var msg = citizenAPI.printText(args[0], args[1], args[2], args[3], args[4], args[5]);

        if (msg != CMP_SUCCESS) {
            errorCallback(msg);
        }
    }
    ,
    printQRCode: function (successCallback, errorCallback, args) {

        var msg = citizenAPI.printQRCode(args[0], args[1], args[2], args[3], args[4]);

        if (msg != CMP_SUCCESS) {
            errorCallback(msg);
        }
    }
    ,
    printPDF417: function (successCallback, errorCallback, args) {

        var msg = citizenAPI.printPDF417(args[0], args[1], args[2], args[3], args[4]);

        if (msg != CMP_SUCCESS) {
            errorCallback(msg);
        }
    }
    ,
    printImage: function (successCallback, errorCallback, args) {

        citizenAPI.printImage(args[0], args[1], args[2]).then(
            function (msg) {
                if (msg != CMP_SUCCESS) {
                    switch (msg) {
                        case CMP_IMAGE_PROCESS_ERROR: msg = msg_process_error; break;
                        case CMP_FILE_IS_NOT_EXIST: msg = msg_not_exist; break;
                        case CMP_FILE_IS_NOT_BITMAP: msg = msg_not_bitmap; break;
                        case CMP_FILE_IS_UNSUPPORTED: msg = msg_unsupported; break;
                        default: msg = "Error"; break;
                    }

                    errorCallback(msg);
                }
            },
            function (msg) {
                errorCallback(msg);
            }
        );
    }
    ,
    lineFeed: function (successCallback, errorCallback, args) {

        var msg = citizenAPI.lineFeed(args[0]);

        if (msg != CMP_SUCCESS) {
            errorCallback(msg);
        }
    }
    ,
    swipeMSR: function (successCallback, errorCallback, args) {

        citizenAPI.setMSRMode(args[0]).then(
            function (msg) {
                if (msg == CMP_SUCCESS) {

                    citizenAPI.readMSR().then(
                        function (msg) {
                            if (msg != CMP_FAIL)
                                successCallback(msg);
                            else
                                errorCallback(msg_canceled_msr);
                        },
                        function (msg) {
                            errorCallback(msg);
                        }
                    );
                }
                else {
                    errorCallback(msg_select_track_fail);
                }
            },
            function (msg) {
                errorCallback(msg);
            }
        );
    }
    ,
    cancelMSR: function (successCallback, errorCallback) {

        citizenAPI.cancelMSR().then(
            function (msg) {
                if (msg == CMP_SUCCESS)
                    successCallback(msg_cancel_success);
                else
                    errorCallback(msg);
            },
            function (msg) {
                errorCallback(msg);
            }
        );
    }
    ,
    disconnect: function (successCallback, errorCallback) {

        citizenAPI.disConnectDevice().then(
            function (msg) {
                if (msg == CMP_SUCCESS)
                    successCallback(msg_success);
                else
                    errorCallback(msg);
            },
            function (msg) {
                errorCallback(msg);
            }
        );
    }
    ,
    searchBT: function (successCallback, errorCallback) {
        var msg = msg_not_supported;
        errorCallback(msg);
    }
    ,
    getCountBT: function (successCallback, errorCallback) {
        var msg = msg_not_supported;
        errorCallback(msg);
    }
    ,
    getListBTAddress: function (successCallback, errorCallback) {
        var msg = msg_not_supported;
        errorCallback(msg);
    }
});




