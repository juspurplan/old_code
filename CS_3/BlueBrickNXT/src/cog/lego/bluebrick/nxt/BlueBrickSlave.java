package cog.lego.bluebrick.nxt;

import lejos.nxt.Motor;
import lejos.nxt.comm.Bluetooth;
import lejos.nxt.comm.NXTConnection;

public class BlueBrickSlave {
	public static void main(String args[]){
		System.out.println("Waiting for bluetooth...");
		NXTConnection con = Bluetooth.waitForConnection(0, NXTConnection.RAW);
		
		while(true){
			byte buffer[] = new byte[con.available()];
			con.read(buffer, con.available());
			String input = new String(buffer);
			
			if (input.equals("stop") || input.equals("0")) {
				Motor.A.stop();Motor.B.stop();
			} else if (input.equals("forward") || input.equals("1")) {
				Motor.A.forward();Motor.B.forward();
			} else if (input.equals("backward") || input.equals("2")) {
				Motor.A.backward();Motor.B.backward();
			} else {
				System.out.println("Invalid Command; " + input);
			}
			
		}
		
		
	}
	
	
}
