import java.io.File;

import javax.microedition.lcdui.Graphics;

import lejos.*;
import lejos.robotics.navigation.DifferentialPilot;
import lejos.util.*;
import lejos.nxt.*;
import lejos.nxt.ColorSensor.Color;

public class WAVTest 
{
	public static void main(String[]a)
	{
		String s = Integer.toString(Sound.playSample( new File("creeper_sss_5.wav") ,100 ));
		System.out.println(s);
		Button.waitForPress();
	}
}