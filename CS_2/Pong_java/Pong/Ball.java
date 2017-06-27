//© A+ Computer Science  -  www.apluscompsci.com
//Name -
//Date -
//Lab  - Ball

package Pong;
import Pong.Block;
import Pong.Paddle;

import java.awt.Color;
import java.awt.Graphics;

public class Ball extends Block implements Collidable
{
	private int xSpeed;
	private int ySpeed;

	private int r;
	private int g;
	private int b;
	private int rTarg;
	private int gTarg;
	private int bTarg;

	public Ball()
	{
		super(200,200);
		randomSpeed();
	}
	//add the other Ball constructors
	public Ball(int x , int y , int w , int h , Color col)
	{
		super(x,y,w,h,col);
		randomSpeed();
		r = col.getRed();
		g = col.getGreen();
		b = col.getBlue();
		rTarg=0255;
		gTarg=0255;
		bTarg=0255;
	}

	public Ball(int s)
	{
		super(100,100);
		randomSpeed();
	}

    //add the set methods
    public void setXSpeed(int s)
    {
    	xSpeed = s;
    }
    public void setYSpeed(int s)
    {
   		ySpeed = s;
    }

    public void setSize(int w , int h)
    {
    	setWidth(w);
    	setHeight(h);
    }

   public void moveAndDraw(Graphics window)
   {
   		//draw a bakground colored ball at old ball location
    	draw(window,Color.black);
		//draw the ball at its new location
		setX(getX()+xSpeed);
		setY(getY()+ySpeed);
		draw(window);
   }

	public boolean equals(Object obj)
	{
		Ball b = (Ball) obj;
		if( this.getHeight() == b.getHeight() && this.getWidth() == b.getWidth() &&
				this.getXSpeed() == b.getXSpeed() && this.getYSpeed() == b.getYSpeed() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    //add the get methods
    public int getXSpeed()
    {
    	return xSpeed;
    }

    public int getYSpeed()
    {
    	return ySpeed;
    }

    //add a toString() method
    public String toString()
    {
   		return super.toString()+"\n"+"xSpeed = "+xSpeed+"\n"+"ySpeed = "+ySpeed;
    }

    public boolean didCollideLeft(Locatable obj)
   	{
   		Paddle p = (Paddle) obj;
   		if( this.getX() <= p.getX() + p.getWidth() + Math.abs(this.getXSpeed()) && (this.getX() >= p.getX()) &&
			( this.getY() >= p.getY() && this.getY() <= p.getY()+p.getHeight() ) )
		{
			return true;
		}
		else
		{
			return false;
		}
    }

    public boolean didCollideRight(Locatable obj)
    {
    	Paddle p = (Paddle) obj;
    	if((this.getX() >= p.getX() - Math.abs(this.getXSpeed()) && (this.getX() <= p.getX()+p.getWidth())) &&
    		(this.getY() >= p.getY() && this.getY() <= p.getY()+p.getHeight())  )
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }

    public boolean didCollideUp(Locatable obj)
    {
    	Paddle p = (Paddle) obj;
    	if(this.getY() < p.getY()+Math.abs(this.getYSpeed()) && this.getY()>=p.getY() && this.getX() >= p.getX() && this.getX() <= p.getX()+p.getWidth())
		{
			return true;
		}
		else
		{
			return false;
		}
    }

    public boolean didCollideDown(Locatable obj)
    {
    	Paddle p = (Paddle) obj;
    	if(this.getY()>=p.getY()-p.getHeight()-Math.abs(this.getYSpeed()) && (this.getX()>= p.getX() && this.getX() <= p.getX()+p.getWidth()) )
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }

    public void respawn(int w , int h)
    {
    	setX( w );
    	setY( h );
    	randomSpeed();
    }

    public void respawn(int w , int h , int a , int b)
    {
    	setX( w );
    	setY( h );
    	randomSpeed(a,b);
    }

    public void randomSpeed()
    {
		do
		{
			xSpeed = (int) (8*Math.random()+0);
    		ySpeed = (int) (8*Math.random()+0);
		}while(xSpeed==0 || ySpeed==0 || Math.abs(xSpeed-ySpeed) >5 || Math.abs(ySpeed/xSpeed)>.5 );

		if(xSpeed>8|| ySpeed >8)
		{
			xSpeed = (int) ((double)xSpeed/1.25);
			ySpeed = (int) ((double)ySpeed/1.25);
		}

		if( (int) (2*Math.random())==0 )
		{
			xSpeed = (-1)*xSpeed;
		}

		if( (int) (2*Math.random())== 0 )
		{
			ySpeed = (-1)*ySpeed;
		}
    }

    public void randomSpeed(int  a , int  b)
    {
    	do
		{
			xSpeed = (int) (8*Math.random()+0);
    		ySpeed = (int) (8*Math.random()+0);
		}while(xSpeed==0 || ySpeed==0  || Math.abs(xSpeed-ySpeed) >5|| Math.abs(ySpeed/xSpeed)>.5);

		if(xSpeed>8 || ySpeed >8)
		{
			xSpeed = (int) ((double)xSpeed/1.25);
			ySpeed = (int) ((double)ySpeed/1.25);
		}

		if(a<0)
		{
			xSpeed = (-1)*xSpeed;
		}
		if(b<0)
		{
			ySpeed = (-1)*ySpeed;
		}
		if(a==0)
		{
			if( (int) (2*Math.random())==0 )
			{
				xSpeed = (-1)*xSpeed;
			}
		}
		if(b==0)
		{
			if( (int) (2*Math.random())== 0 )
			{
				ySpeed = (-1)*ySpeed;
			}
		}
    }

    public void changeColor()
    {
    	int rdiff = rTarg-r;
    	int gdiff = gTarg-g;
    	int bdiff = bTarg-b;
    	int rtemp=0;
    	int gtemp=0;
    	int btemp=0;
    	if(rdiff<0)
    	{
    		rtemp = r-3;
    		r = rtemp;
    		rdiff+=3;
    	}
    	if(gdiff<0)
    	{
    		gtemp = g-3;
    		g= gtemp;
    		gdiff+=3;
    	}
    	if(bdiff<0)
    	{
    		btemp = b-3;
    		b = btemp;
    		bdiff+=3;
    	}
    	if(rdiff>0)
    	{
    		rtemp = r+3;
    		r= rtemp;
    		rdiff-=3;
    	}
    	if(gdiff>0)
    	{
    		gtemp = g+3;
    		g= gtemp;
    		gdiff-=3;
    	}
    	if(bdiff>0)
    	{
    		btemp = b+3;
    		b= btemp;
    		bdiff-=3;
    	}
    	setColor(new Color(rtemp, gtemp, btemp));
    }

    public void setColorTarget(Color col)
    {
    	rTarg = col.getRed();
    	gTarg = col.getGreen();
    	bTarg = col.getBlue();
    }

    public void randomColorChange()
    {
    	int rtemp = (int) (155*Math.random()+100);
    	int gtemp = (int) (155*Math.random()+100);
    	int btemp = (int) (155*Math.random()+100);
    	Color asdf =new Color (rtemp,gtemp,btemp);
    	setColorTarget( asdf);
    }
}