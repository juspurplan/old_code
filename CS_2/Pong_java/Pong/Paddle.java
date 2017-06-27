//© A+ Computer Science  -  www.apluscompsci.com
//Name -
//Date -
//Lab  - Paddle

package Pong;
import Pong.Block;

import java.awt.Color;
import java.awt.Graphics;

public class Paddle extends Block
{
    //instance variables
    private int speed;
    private int stunMillis;

    public Paddle()
    {
		super(10,10,10,10);
      	speed =5;
    }

    //add the other Paddle constructors
	public Paddle (int x , int y , int w , int h , Color col)
	{
		super(x , y , w , h , col);
		speed = 5;
	}

	public Paddle(int x , int y , int w , int h ,  int s , Color col)
	{
		super( x , y , w, h , col);
		speed = s;
	}

	//add set methods
	public void setSpeed(int s)
	{
		speed = s;
	}

    public void moveUpAndDraw(Graphics window)
    {
    	if(stunMillis <=0)
    	{
    		draw(window,Color.black);
			setY(getY()-speed);
			draw(window);
    	}
    }

    public void moveDownAndDraw(Graphics window)
    {
    	if(stunMillis <=0)
    	{
    		draw(window,Color.black);
			setY(getY()+speed);
			draw(window);
    	}
    }

    //add get methods
    public int getSpeed()
    {
    	return speed;
    }

    //add a toString() method
    public String toString()
    {
    	return super.toString()+"\n"+"Speed = "+speed;
    }

    public void stun()
    {
    	stunMillis = 500;
    }

    public void coolDown(int millis)
    {
    	stunMillis-=millis;
    }
}