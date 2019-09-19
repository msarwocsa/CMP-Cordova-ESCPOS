package com.citizen.service.plugin;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Iterator;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.citizen.jpos.command.ESCPOSConst;
import com.citizen.jpos.printer.ESCPOSPrinter;
import com.citizen.jpos.printer.CMPPrint;
import com.citizen.port.android.BluetoothPort;
import com.citizen.request.android.AndroidMSR;
import com.citizen.request.android.RequestHandler;
import com.citizen.port.android.WiFiPort;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

/**
 * This class performs sum called from JavaScript.
 */
public class CitizenEscpPrinter extends CordovaPlugin {
	private BluetoothAdapter mBluetoothAdapter;
	private BluetoothPort bluetoothPort;
	private WiFiPort wifiPort;
	private ESCPOSPrinter posPtr;
	private Thread handlerThread;

    private static final int REQUEST_ENABLE_BT = 2;
    private static final int BT_PRINTER_LIST = 20;
	private BroadcastReceiver discoveryResult = null;
	private Context context;
	String btAddressData[] = new String[BT_PRINTER_LIST];
	private static int btCounter = 0;

	private static int interfaceType = 0; // Bluetooth default
	
	private int msrMode;
	private static int userMsrSwipeEnd = 0;
	private AndroidMSR androidMSR;
	static String [] track;
	
	// Connect, Print, Disconnect. 
	static final String GET_PAIRED_BT = "getPairedBT";
	static final String CONNECT = "connect";
	static final String GET_STATUS = "getStatus";
	static final String SET_CHARACTER_SET = "setCharacterSet";
	static final String PRINT_NORMAL = "printNormal";
	static final String PRINT_TEXT = "printText";
	static final String PRINT_BARCODE = "printBarCode";
	static final String PRINT_QRCODE = "printQRCode";
	static final String PRINT_PDF417 = "printPDF417";
	static final String PRINT_IMAGE = "printImage";
	static final String LINE_FEED = "lineFeed";
	static final String SWIPE_MSR = "swipeMSR";
	static final String CANCEL_MSR = "cancelMSR";
	static final String DISCONNECT = "disconnect";

	// Search bluetooth printer.
	static final String SEARCH_BT_PRINTER = "searchBT";
	static final String GET_COUNT_BT = "getCountBT";
	static final String GET_SEARCHED_LIST = "getListBTAddress";

	@Override
    public boolean execute(String action, JSONArray args, final CallbackContext callbackContext) throws JSONException
	{
//		Log.e("CitizenEscpPrinter", "Enter execute = " + action);
		
		// Get paired bluetooth device list
		if (action.equals(GET_PAIRED_BT))
		{
			class GetPairedBT implements Runnable
			{
				CitizenEscpPrinter citizenPlugin;
				JSONArray arguments;
				CallbackContext callbackId;

				public GetPairedBT(CitizenEscpPrinter z, JSONArray args, CallbackContext cbid) { this.citizenPlugin = z; this.arguments = args; this.callbackId = cbid; }
				public void run() { try {
					citizenPlugin.getPairedBT(this.arguments,this.callbackId);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}}
			}
			new GetPairedBT(this,args,callbackContext).run();

			return true;
		} else if (action.equals(CONNECT))
		{
			class Connect implements Runnable
			{
				CitizenEscpPrinter citizenPlugin;
				JSONArray arguments;
				CallbackContext callbackId;

				public Connect(CitizenEscpPrinter z, JSONArray args, CallbackContext cbid) { this.citizenPlugin = z; this.arguments = args; this.callbackId = cbid; }
				public void run() { citizenPlugin.connect(this.arguments,this.callbackId);}

			}
			new Connect(this,args,callbackContext).run();
			return true;
		} else if (action.equals(SET_CHARACTER_SET))
    	{
			this.setCharacterSet(args, callbackContext);
            return true;
		} else if (action.equals(GET_STATUS))
    	{
			try {
				this.getStatus(args, callbackContext);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
            return true;
		} else if (action.equals(PRINT_NORMAL))
    	{
			this.printNormal(args, callbackContext);
            return true;
		} else if (action.equals(PRINT_TEXT))
    	{
			this.printText(args, callbackContext);
            return true;
		} else if (action.equals(PRINT_BARCODE))
    	{
			this.printBarCode(args, callbackContext);
            return true;
		} else if (action.equals(PRINT_QRCODE))
    	{
			this.printQRCode(args, callbackContext);
            return true;
		} else if (action.equals(PRINT_PDF417))
    	{
			this.printPDF417(args, callbackContext);
            return true;
		} else if (action.equals(PRINT_IMAGE))
    	{
			try {
				this.printImage(args, callbackContext);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
            return true;
		} else if (action.equals(LINE_FEED))
    	{
			this.lineFeed(args, callbackContext);
            return true;
		} else if (action.equals(SWIPE_MSR))
		{
			class SwipeMSR implements Runnable
			{
				CitizenEscpPrinter citizenPlugin;
				JSONArray arguments;
				CallbackContext callbackId;

				public SwipeMSR(CitizenEscpPrinter z, JSONArray args, CallbackContext cbid) { this.citizenPlugin = z; this.arguments = args; this.callbackId = cbid; }
				public void run() { try {
					citizenPlugin.swipeMSR(this.arguments,this.callbackId);
				} catch (UnsupportedEncodingException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}}
			}
			new SwipeMSR(this,args,callbackContext).run();

    		return true;
		} else if (action.equals(CANCEL_MSR))
		{
			class CancelMSR implements Runnable
			{
				CitizenEscpPrinter citizenPlugin;
				JSONArray arguments;
				CallbackContext callbackId;

				public CancelMSR(CitizenEscpPrinter z, JSONArray args, CallbackContext cbid) { this.citizenPlugin = z; this.arguments = args; this.callbackId = cbid; }
				public void run() { try {
					citizenPlugin.cancelMSR(this.arguments,this.callbackId);
				} catch (UnsupportedEncodingException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}}
			}
			new CancelMSR(this,args,callbackContext).run();

			return true;
		} else if (action.equals(DISCONNECT))
    	{
            this.disconnect(callbackContext);
            return true;
    	} else if (action.equals(GET_COUNT_BT))
    	{
            callbackContext.success(btCounter);
    		return true;
    	} else if (action.equals(GET_SEARCHED_LIST))
    	{
    		int ni = 0;
    		JSONArray deviceArray = new JSONArray();
    		JSONObject bluetoothinfo = new JSONObject();
   			if(btCounter > 0)
   			{
   				for(ni=0; ni<btCounter; ni++)
   				{
   					bluetoothinfo.put("Address" + (ni+1), btAddressData[ni]);
					deviceArray.put(bluetoothinfo);
   				}
   				callbackContext.success(bluetoothinfo);
   			} else {
   				callbackContext.success("There are no printers");
   			}
   			return true;
    	} else if (action.equals(SEARCH_BT_PRINTER))
    	{
			class Discover implements Runnable
			{
				CitizenEscpPrinter z;
				JSONArray arguments;
				CallbackContext callbackId;

				public Discover(CitizenEscpPrinter z, JSONArray args, CallbackContext cbid) { this.z = z; this.arguments = args; this.callbackId = cbid; }
				public void run() { z.discover(this.arguments,this.callbackId); /*Looper.myLooper().quit();*/ }

			}
			try
			{
				new Discover(this,args,callbackContext).run();
			}
			catch(Throwable t)
			{
				t.printStackTrace();
			}
			return true;
		} else {
			return false;
		}
    }

    public void onDestroy()
    {
        // Log.e("CitizenEscpPrinter", "onDestroy"); 
        removeBluetoothListener(); 
    } 
 
    public void getPairedBT(JSONArray args, CallbackContext callbackContext) throws JSONException
    {
		int ni = 1;
		JSONArray deviceArray = new JSONArray();
		JSONObject bluetoothinfo = new JSONObject();

		bluetoothPort = BluetoothPort.getInstance();
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

		BluetoothDevice pairedDevice;
		Iterator<BluetoothDevice> iter = (mBluetoothAdapter.getBondedDevices()).iterator();
		while(iter.hasNext())
		{
			pairedDevice = iter.next();
			bluetoothinfo.put("Address" + ni++, pairedDevice.getAddress());
			deviceArray.put(bluetoothinfo);
		}
		
		if(ni == 1)
		{
			callbackContext.success("There are no printers");
		} else {
			callbackContext.success(bluetoothinfo);
		}
    }

    public void connect(JSONArray args, CallbackContext callbackContext)
    {
		String connetAddress = null;
		try {
			connetAddress = args.getString(0);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		if(connetAddress != null)
		{
			try {
				// posPtr = new ESCPOSPrinter("EUC-KR"); // Korean.
				// posPtr = new ESCPOSPrinter("Shift_JIS"); // Japanese.

				posPtr = new ESCPOSPrinter();

				if (connetAddress.contains(".")) // Network(xxx.xxx.xxx.xxx)
				{
					wifiPort = WiFiPort.getInstance();
					interfaceType = 1;
					wifiPort.connect(connetAddress);
				} else { // Bluetooth(xx:xx:xx:xx:xx:xx or xxxxxxxxxxxx)
					bluetoothPort = new BluetoothPort();
					interfaceType = 0;
					bluetoothPort.connect(connetAddress);
				}

				RequestHandler rh = new RequestHandler();				
				handlerThread = new Thread(rh);
				handlerThread.start();

				callbackContext.success("Success");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				callbackContext.error("Connection failed.");
			}
		} else {
			callbackContext.error("Expected one string arguments.");
		}
    }

	public void setCharacterSet(JSONArray args, CallbackContext callbackContext)
    {
		int iCharSet = 0;
		try {
			iCharSet = args.getInt(0);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(iCharSet != 0)
        {
			posPtr.setCharacterSet(iCharSet);
			callbackContext.success("Success");
        } else {
			callbackContext.error("Fail");
        }
    }

    public void getStatus(JSONArray args, CallbackContext callbackContext) throws UnsupportedEncodingException
    {
    	int returnValue;

    	// MSR Mode warning.
    	if( userMsrSwipeEnd == 1 )
    	{
    		callbackContext.success("MSR Read mode");
    		return;
    	}
    	returnValue = posPtr.printerCheck();
		if(ESCPOSConst.CMP_SUCCESS == returnValue)
		{
			returnValue = posPtr.status();
			if(ESCPOSConst.CMP_STS_NORMAL == returnValue)
			{ // No errors
		        callbackContext.success("Success");
			} else {
				// Cover open error.
				if((ESCPOSConst.CMP_STS_COVER_OPEN & returnValue) > 0)
				{
			           callbackContext.error("Cover open");
				}
				// Paper empty error.
				if((ESCPOSConst.CMP_STS_PAPER_EMPTY & returnValue) > 0)
				{
			           callbackContext.error("Paper empty");
				}
				// Battery low warning.
				if((ESCPOSConst.CMP_STS_BATTERY_LOW & returnValue) > 0)
				{
			           callbackContext.success("Battery low");
				}
			}
		} else { // Error(CMP_FAIL, CMP_STS_PRINTEROFF, CMP_STS_TIMEOUT)
			if((returnValue & ESCPOSConst.CMP_STS_PRINTEROFF) > 0)
		        callbackContext.error("Printer Power OFF\r\nReconnect and print");
			if((returnValue & ESCPOSConst.CMP_STS_TIMEOUT) > 0)
		        callbackContext.error("Timeout error");
			if((returnValue & ESCPOSConst.CMP_FAIL) > 0)
		        callbackContext.error("No response");
		};
    }

    public void printNormal(JSONArray args, CallbackContext callbackContext)
    {
		String data = null;
		try {
			data = args.getString(0);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(data != null)
        {
    		try {
				posPtr.printNormal(data);
    		} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			};
        } else {
            callbackContext.error("Expected one string arguments.");
        }
    }

    public void printText(JSONArray args, CallbackContext callbackContext)
    {
		String data = null;
		int iAlign = 0, iAttribute = 0, iSize = 0;
		try {
			data = args.getString(0);
			iAlign = args.getInt(1);
			iAttribute = args.getInt(2);
			iSize = args.getInt(3);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(data != null)
        {
    		try {
				posPtr.printText(data, iAlign, iAttribute, iSize);
    		} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			};
        } else {
            callbackContext.error("Expected one string arguments.");
        }
    }

    public void printBarCode(JSONArray args, CallbackContext callbackContext)
    {
		String data = null;
		int iSymbol = 0, iHeight = 0, iWidth = 0, iAlign = 0, iHRI = 0;
		try {
			data = args.getString(0);
			iSymbol = args.getInt(1);
			iHeight = args.getInt(2);
			iWidth = args.getInt(3);
			iAlign = args.getInt(4);
			iHRI = args.getInt(5);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(data != null)
        {
    		try {
				posPtr.printBarCode(data, iSymbol, iHeight, iWidth, iAlign, iHRI);
    		} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			};
        } else {
            callbackContext.error("Expected one string arguments.");
        }
    }

    public void printQRCode(JSONArray args, CallbackContext callbackContext)
    {
		String data = null;
		int iLen = 0, iCellSize = 0, iECL = 0, iAlign = 0;
		try {
			data = args.getString(0);
			iLen = args.getInt(1);
			iCellSize = args.getInt(2);
			iECL = args.getInt(3);
			iAlign = args.getInt(4);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(data != null)
        {
			try {
				posPtr.printQRCode(data, iLen, iCellSize, iECL, iAlign);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			};
        } else {
            callbackContext.error("Expected one string arguments.");
        }
    }

    public void printPDF417(JSONArray args, CallbackContext callbackContext)
    {
		String data = null;
		int iLen = 0, iNumberOfColumns = 0, iCellWidth = 0, iAlign = 0;
		try {
			data = args.getString(0);
			iLen = args.getInt(1);
			iNumberOfColumns = args.getInt(2);
			iCellWidth = args.getInt(3);
			iAlign = args.getInt(4);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(data != null)
        {
			try {
				posPtr.printPDF417(data, iLen, iNumberOfColumns, iCellWidth, iAlign);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			};
        } else {
            callbackContext.error("Expected one string arguments.");
        }
    }

    public void printImage(JSONArray args, CallbackContext callbackContext) throws UnsupportedEncodingException
    {
		String strPath = null;
		int iAlign = 0, iSize = 0;
		try {
			strPath = args.getString(0);
			iAlign = args.getInt(1);
			iSize = args.getInt(2);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		try {
			posPtr.printBitmap(strPath, iAlign, iSize);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
    
    public void lineFeed(JSONArray args, CallbackContext callbackContext)
    {
		int iCount = 0;
		try {
			iCount = args.getInt(0);
//			Log.e("CitizenEscpPrinter", "(iCount)=" + iCount);
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(iCount != 0)
        {
			posPtr.lineFeed(iCount);;
        }
    }

    // ================================================================================================ //
    // Track Data Update Handler. - Read Complete.
    // ================================================================================================ //
    final static Handler msrHandler = new MSRHandler();
    static class MSRHandler extends Handler
	{
    	private Context mContext;
    	@Override
		public void handleMessage(Message msg)
		{
    		super.handleMessage(msg);
    		Bundle bundle = (Bundle) msg.obj;
			Log.d("CitizenEscpPrinter", "bundle.size() = "+bundle.size());
    		if(bundle.size() > 1)
    		{
    			// rawData - MSR Data.
    			byte [] rawData = bundle.getByteArray("RawData");
    			int rawLength = bundle.getInt("RawDataSize");
    			track = parsingMSRData(rawData);
    			if(track.length >= 3)
    			{
        			Log.i("CitizenEscpPrinter", "track[0]= " + track[0]);
        			Log.i("CitizenEscpPrinter", "track[1]= " + track[1]);
        			Log.i("CitizenEscpPrinter", "track[2]= " + track[2]);
    			}
    			Log.i("CitizenEscpPrinter", "RawDATA == "+new String(rawData));
    			Log.i("CitizenEscpPrinter", "RawDATA Buffer Size == "+rawData.length);
        		Log.i("CitizenEscpPrinter", "RawDATA Size == "+ rawLength);

        		userMsrSwipeEnd = 2;
    		}
    		else
    		{
    			// Fail to read MSR(Invalid MSR data).
        		userMsrSwipeEnd = 3;
//    			Log.e("CitizenEscpPrinter","RawDATA == "+new String(bundle.getByteArray("RawData")));
    		}	
    	}
	}
    
	/**
	 * STX FS [Track1] FS [Track2] FS [Track3] ETX DATAEND 0x02 0x1C [0-76
	 * Bytes] 0x1C [0-37 Bytes] 0x1C [0-106 Bytes] 0x03 0x0D 0x0A 0x00
	 */
	private static String[] parsingMSRData(byte[] rawData)
	{
		final byte[] FS = { (byte) 0x1C };
		final byte[] ETX = { (byte) 0x03 };

		String temp = new String(rawData);
		String trackData[] = new String[3];

		// ETX , FS
		String[] rData = temp.split(new String(ETX));
		temp = rData[0];
		String[] tData = temp.split(new String(FS));

		switch (tData.length)
		{
			case 1:
				break;
			case 2:
				trackData[0] = tData[1];
				break;
			case 3:
				trackData[0] = tData[1];
				trackData[1] = tData[2];
				break;
			case 4:
				trackData[0] = tData[1];
				trackData[1] = tData[2];
				trackData[2] = tData[3];
				break;
		}
		return trackData;
	}

    public void onReset()
    { 
//        Log.e("CitizenEscpPrinter", "onReset"); 
    	removeBluetoothListener(); 
    } 

    public void swipeMSR(JSONArray args, final CallbackContext callbackContext) throws UnsupportedEncodingException
    {
		try {
			msrMode = args.getInt(0);
		} catch (JSONException e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		} // Get track info
		Log.i("CitizenEscpPrinter", "msrMode=" + msrMode);
		
		androidMSR = AndroidMSR.getInstance();
		androidMSR.setHandler(msrHandler);
		try
		{
			if(androidMSR.readMSR(msrMode) == CMPPrint.CMP_STS_MSR_READ)
			{
				userMsrSwipeEnd = 1;
				cordova.getThreadPool().execute(new Runnable() {
	                public void run() {
	                	// Waiting for stripe the card
	                	while(userMsrSwipeEnd == 1)
	                	{
	                		try {
	            				// Log.e("CitizenEscpPrinter", "while userMsrSwipeEnd=" + userMsrSwipeEnd);
								Thread.sleep(1000);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
	                	}
	                	
	        			if(userMsrSwipeEnd == 2)
	        			{
	            			int ni = 1;
	            			JSONArray deviceArray = new JSONArray();
	                		JSONObject msrTrancInfo = new JSONObject();

	                    	try {
	        					msrTrancInfo.put("Track1", track[0]);
	        	    			deviceArray.put(msrTrancInfo);
	        	            	msrTrancInfo.put("Track2", track[1]);
	        	    			deviceArray.put(msrTrancInfo);
	        	            	msrTrancInfo.put("Track3", track[2]);
	        	    			deviceArray.put(msrTrancInfo);
	        				} catch (JSONException e) {
	        					// TODO Auto-generated catch block
	        					e.printStackTrace();
	        				}
	        		
	        				Log.i("CitizenEscpPrinter", "Track1=" + track[0]);
	        				Log.i("CitizenEscpPrinter", "Track2=" + track[1]);
	        				Log.i("CitizenEscpPrinter", "Track3=" + track[2]);
	                    	track[0] = null;
	                    	track[1] = null;
	                    	track[2] = null;
	        				Log.i("CitizenEscpPrinter", "result=" + msrTrancInfo.toString());
	        				callbackContext.success(msrTrancInfo);
	        			} else {
	        				if(userMsrSwipeEnd == 0) callbackContext.error("canceled by user");
	        				if(userMsrSwipeEnd == 3) callbackContext.error("Invalid data");
	        			}
	                }
	            });
			}
			else
			{
				callbackContext.error("Fail to change MSR mode");
			}
		}
		catch(InterruptedException e1)
		{
			Log.e("CitizenEscpPrinter", "msrTestListener "+e1.getMessage());
		}
		catch(IOException e2)
		{
			Log.e("CitizenEscpPrinter", "msrTestListener "+e2.getMessage());
		}
    }

    public void cancelMSR(JSONArray args, final CallbackContext callbackContext) throws UnsupportedEncodingException
    {
		if(userMsrSwipeEnd == 1)
		{
			try {
//				Log.e("CitizenEscpPrinter", "cancelMSR:cancelMSR");
				userMsrSwipeEnd = 0; // initialize
				androidMSR.cancelMSR();
            	callbackContext.success("Cancel success");
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else {
			callbackContext.error("Not msr mode");
		}
    }
    public void disconnect(CallbackContext callbackContext)
    {
    	try {
			switch(interfaceType)
			{
			case 0: // Bluetooth.
				bluetoothPort.disconnect();
				break;
			case 1: // Network.
				wifiPort.disconnect();
				break;
			}

			if((handlerThread != null) && (handlerThread.isAlive()))
	           	handlerThread.interrupt();

	       	callbackContext.success("Success");
    	} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }

    /** 
     * Stop Bluetooth receiver. 
     */ 
    private void removeBluetoothListener()
    { 
        if (this.discoveryResult != null)
        { 
            try { 
                webView.getContext().unregisterReceiver(this.discoveryResult); 
                this.discoveryResult = null; 
            } catch (Exception e) { 
//                Log.e("CitizenEscpPrinter", "Error unregistering bluetooth receiver: " + e.getMessage(), e); 
            } 
        } 
    } 

	public void discover(JSONArray arguments, CallbackContext cid)
	{
		btCounter = 0;
		context = this.cordova.getActivity().getApplicationContext(); 
		// UI - Event Handler.
		// Search device, then add List.
		bluetoothPort = BluetoothPort.getInstance();
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		if (mBluetoothAdapter == null) 
		{
			// Device does not support Bluetooth
			cid.error("Device does not support Bluetooth.");
		}
		if (!mBluetoothAdapter.isEnabled()) 
		{
			this.cordova.startActivityForResult(this, 
					new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), 
					this.REQUEST_ENABLE_BT);
			while(true)
			{
				try {
					Thread.sleep(1000);
					if( mBluetoothAdapter.isEnabled() ) break;
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}

		// We need to listen to power events to update bluetooth status 
		IntentFilter intentFilter = new IntentFilter(); 
		intentFilter.addAction(BluetoothDevice.ACTION_FOUND); 
		if (this.discoveryResult == null)
		{
//			Log.e("CitizenEscpPrinter", "discoveryResult is null");
			this.discoveryResult = new BroadcastReceiver()
			{ 
				@Override 
				public void onReceive(Context context, Intent intent)
				{ 
					String key;
					String finalKey = null;
					BluetoothDevice remoteDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
					if(remoteDevice != null)
					{
						if(remoteDevice.getBondState() != BluetoothDevice.BOND_BONDED)
						{
							key = remoteDevice.getName() +"\n["+remoteDevice.getAddress()+"]";
						}
						else
						{
							key = remoteDevice.getName() +"\n["+remoteDevice.getAddress()+"] [Paired]";
						}

						btAddressData[btCounter] = remoteDevice.getAddress();
   						btCounter++;
//		 				Log.e("onReceive", key);
//    					Log.e("onReceive", "Status=" + mBluetoothAdapter.getState());
					}
				} 
			};
			webView.getContext().registerReceiver(this.discoveryResult, intentFilter); 
		} else {
//			Log.e("CitizenEscpPrinter", "discoveryResult is not null");
			removeBluetoothListener(); 
			this.discoveryResult = new BroadcastReceiver()
			{ 
				@Override 
				public void onReceive(Context context, Intent intent)
				{
					String key;
					String finalKey = null;
					BluetoothDevice remoteDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
					if(remoteDevice != null)
					{
						if(remoteDevice.getBondState() != BluetoothDevice.BOND_BONDED)
						{
							key = remoteDevice.getName() +"\n["+remoteDevice.getAddress()+"]";
						}
						else
						{
							key = remoteDevice.getName() +"\n["+remoteDevice.getAddress()+"] [Paired]";
						}
   						btAddressData[btCounter] = remoteDevice.getAddress();
   						btCounter++;
//    					Log.e("onReceive", key);
//    					Log.e("onReceive", mBluetoothAdapter.ACTION_DISCOVERY_FINISHED);
//    					Log.e("onReceive", "Status=" + mBluetoothAdapter.getState());
					}
				} 
			}; 

			webView.getContext().registerReceiver(this.discoveryResult, intentFilter); 
		}

		mBluetoothAdapter.cancelDiscovery();
		if ( !mBluetoothAdapter.startDiscovery() )
		{ 
			String msg = "Unable to start discovery"; 
			cid.sendPluginResult( new PluginResult(PluginResult.Status.ERROR, msg)); 
		} else {
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
