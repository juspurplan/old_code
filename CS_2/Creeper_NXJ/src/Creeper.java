import java.io.File;

import javax.microedition.lcdui.Graphics;

import lejos.*;
import lejos.robotics.navigation.DifferentialPilot;
import lejos.util.*;
import lejos.nxt.*;
import lejos.nxt.ColorSensor.Color;

public class Creeper 
{
	public static void main(String[] args) 
	{
		Thread main = new Thread(new MainThread());
		main.start();
	}
}

class MainThread implements Runnable
{
	private MotorThread motor;
	private SensorThread sensor;
	private LCDThread lcd;
	private State state;
	public MainThread()
	{
		motor= new MotorThread(this);
		sensor = new SensorThread(this);
		lcd = new LCDThread(this);
		state = State.MOVING;
	}
	public void run()
	{
		motor.start();
		lcd.start();
		sensor.start();
	}
	public synchronized State getState()
	{
		return state;
	}
	public synchronized void changeState(State s)
	{
		/*if(state != s)
			Sound.beep();*/
		this.state = s;
	}
}
class MotorThread implements Runnable
{
	private Thread t;
	private MainThread mainthread;
	
	public MotorThread(MainThread mt)
	{
		this.mainthread = mt;
		t= new Thread(this);
	}
	public void start()
	{
		t.start();
	}
	public void run()
	{
		DifferentialPilot dp = new DifferentialPilot(56,26, Motor.C, Motor.A);
		dp.setTravelSpeed(400);
		dp.setRotateSpeed(400);
		dp.setAcceleration(400);
		run: while (true)
		{
			switch (mainthread.getState())
			{
				case MOVING:
					Thread.yield();
					int rand = (int)(Math.random()*3);
					switch (rand) 
					{
						case 0:
							dp.travel(200);
							break;
						case 1:
							dp.arc(30, 400);
							break;
						case 2:
							dp.arc(-30, -400);
							break;
					}
					break;
				case ENCOUNTERED_WALL:
					dp.rotate(600);
					break;
				case ENCOUNTERED_TARGET:
				case EXITING:
					break run;
			}
			try
			{
				Thread.sleep(10);
			}
			catch(InterruptedException e)
			{
			}
		}
	}
}
class SensorThread implements Runnable
{
	private MainThread mainthread;
	private Thread t;
	public SensorThread(MainThread mt)
	{
		this.mainthread = mt;
		t = new Thread(this);
	}
	public void start()
	{
		t.start();
	}
	public void run()
	{
		UltrasonicSensor us = new UltrasonicSensor(SensorPort.S1);
		us.continuous();
		ColorSensor cs = new ColorSensor(SensorPort.S4);
		int dist;
		int colorid;
		Color color;
		run: while (true)
		{
			switch (mainthread.getState())
			{
				case MOVING:
				case ENCOUNTERED_WALL:
					us.ping();
					dist = us.getDistance();
					color = cs.getColor();
					colorid = cs.getColorID();
					/*debug*/
					System.out.println("d = "+dist);
					System.out.println("c = "+colorid);
					System.out.println("RGB = "+color.getColor()+" "+color.getRed()+" "+color.getGreen()+" "+color.getBackground());
					/**/
					if(compare(color) && dist< 50)
					{
						mainthread.changeState(State.ENCOUNTERED_TARGET);
					}
					else if(dist< 50)
					{
						mainthread.changeState(State.ENCOUNTERED_WALL);
					}
					else
					{
						mainthread.changeState(State.MOVING);
					}
					break;
				case ENCOUNTERED_TARGET:
					//Sound.systemSound(true, 3);
					//Sound.systemSound(true, 2);
					Sound.playSample(new File("explode_pcm.wav"), 100);
					mainthread.changeState(State.EXITING);
					break;
				case EXITING:
					Sound.playSample(new File("explode_pcm.wav"), 100);
					break run;
			}
		}
	}
	public boolean compare(Color c)
	{
		//returns true if c is close to target
		int r = 255;
		int g = 0;
		int b = 0;
		int cr = c.getRed();
		int cg = c.getGreen();
		int cb = c.getBlue();
		if(Math.abs(cr-r) <= 50 && Math.abs(cg-g) <= 50 && Math.abs(cb-b) <= 50 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	public boolean analyze(Color c)
	{
		//returns true to say the color is a target, false otherwise
		//random algorithm goes here.
		return true;
	}
}
class LCDThread implements Runnable
{
	private MainThread mainthread;
	private Thread t;
	public LCDThread(MainThread mt)
	{
		this.mainthread = mt;
		t=new Thread(this);
	}
	public void start()
	{
		t.start();
	}
	public void run()
	{
		run: while(true)
		{
			//creeper sss sound
			if(mainthread.getState()==State.ENCOUNTERED_WALL)
			{
				Sound.playSample(new File("creeper_sss_pcm.wav"), 100); 
				try{Thread.sleep(1000);}catch(InterruptedException e){}
			}
			

			Graphics g = new Graphics();
			//eyes
			g.fillRect(20, 0, 20, 20 );
			g.fillRect(60,0,20,20);
			//nose
			g.fillRect(40,20,20,30);
			//mouth
			g.fillRect(30,30,10,30);
			g.fillRect(60,30,10,30);
			try{Thread.sleep(1000);}catch(InterruptedException e){}
			if(mainthread.getState()==State.EXITING)
				break run;
		}
	}
}
enum State
{
	MOVING,
	ENCOUNTERED_WALL,
	ENCOUNTERED_TARGET,
	EXITING
}