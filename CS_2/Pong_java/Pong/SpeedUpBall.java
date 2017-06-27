//© A+ Computer Science  -  www.apluscompsci.com
//Name -
//Date -
//Lab  - Speed Up Ball

package Pong;
import Pong.Block;
import Pong.Paddle;
import Pong.Ball;

import java.awt.Color;
import java.awt.Graphics;

public class SpeedUpBall extends Ball implements Collidable
{
	public SpeedUpBall()
	{
		super(0,0,5,5,Color.white);
		randomSpeed();
	}

	public SpeedUpBall(int x , int y , int w , int h , Color col)
	{
		super(x,y,w,h,col);
		super.randomSpeed();
	}

	public void speedUp()
	{
		if(getXSpeed() <0)
		{
			setXSpeed(getXSpeed()-1);
		}
		if(getXSpeed()>0)
		{
			setXSpeed(getXSpeed()+1);
		}
		if(getYSpeed() <0)
		{
			setYSpeed(getYSpeed()-1);
		}
		if(getYSpeed()>0)
		{
			setYSpeed(getYSpeed()+1);
		}
	}

	public void speedUp(int x)
	{
		if(getXSpeed() <0)
		{
			setXSpeed(getXSpeed()-x);
		}
		if(getXSpeed()>0)
		{
			setXSpeed(getXSpeed()+x);
		}
		if(getYSpeed() <0)
		{
			setYSpeed(getYSpeed()-x);
		}
		if(getYSpeed()>0)
		{
			setYSpeed(getYSpeed()+x);
		}
	}
}