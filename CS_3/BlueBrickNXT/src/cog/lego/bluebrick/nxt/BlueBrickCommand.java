package cog.lego.bluebrick.nxt;

import lejos.nxt.comm.Bluetooth;
import lejos.nxt.comm.NXTConnection;
import lejos.nxt.comm.USB;

public class BlueBrickCommand {
	public static void main(String args[]){
		System.out.println("Waiting for usb...");
		NXTConnection usbCon = USB.waitForConnection(0, NXTConnection.RAW);
		System.out.println("Waiting for bluetooth...");
		NXTConnection bluetoothCon = Bluetooth.connect("NXT", NXTConnection.RAW);
		while(true){
			byte buffer[] = new byte[usbCon.available()];
			usbCon.read(buffer, usbCon.available());
			String input = new String(buffer);			
			System.out.println("Received: " + input);
			
			bluetoothCon.write(buffer, buffer.length);
			System.out.println("Sent: " + input);		
		}
		
		
	}
}
