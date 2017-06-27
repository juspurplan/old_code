//© A+ Computer Science  -  www.apluscompsci.com
//Name -
//Date -
//Lab  - Blinky Ball

package Pong;
import Pong.Block;
import Pong.Paddle;
import Pong.Ball;

import java.awt.Color;
import java.awt.Graphics;

public class BlinkyBall extends Ball implements Collidable
{
	public BlinkyBall()
	{
		super(0,0,5,5,Color.white);
		randomSpeed();
	}

	public BlinkyBall(int x , int y , int w , int h , Color col)
	{
		super(x,y,w,h,col);
		super.randomSpeed();
	}

    public void changeColor()
    {
		//overwrite method to do nothing
    }
}