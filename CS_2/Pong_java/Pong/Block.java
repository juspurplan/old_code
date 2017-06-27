//© A+ Computer Science  -  www.apluscompsci.com
//Name -
//Date -
//Lab  - Block

package Pong;
import Pong.Locatable;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Canvas;

public class Block implements Locatable
{
	private int width;
	private int height;

	private int xPos;
	private int yPos;

	private Color color;

	public Block()
	{
		width = 100;
		height = 100;
		xPos = 0;
		yPos = 0;
		color = Color.black;
	}

	//add other Block constructors
	public Block(int x , int y , int w , int h)
	{
		width = w;
		height = h;
		xPos = x;
		yPos = y;
		color = Color.black;
	}

	public Block(int x , int y , int w , int h, Color col)
	{
		width = w;
		height = h;
		xPos = x;
		yPos = y;
		color = col;
	}

	public Block(Color col)
	{
		width = 100;
		height = 100;
		xPos = 0;
		yPos = 0;
		color = col;
	}

	public Block(int w , int h)
	{
		width = w;
		height = h;
		xPos = 0;
		yPos = 0;
		color = Color.black;
	}

	public Block (int w , int h , Color col)
	{
		width = w;
		height = h;
		xPos = 0;
		yPos = 0;
		color = col;
	}

    //add the other set methods
   	public void setColor(Color col)
   	{
   		color = col;
	}

	public void setWidth(int w)
	{
		width = w;
	}

	public void setHeight(int h)
	{
		height = h;
	}

	public void setX(int x)
	{
		xPos = x;
	}

	public void setY(int y)
	{
		yPos = y;
	}

	public void setPos(int x , int y)
	{
		xPos = x;
		yPos = y;
	}

	public void draw(Graphics window)
	{
		//uncomment after you write the set and get methods
	   window.setColor(color);
	   window.fillRect(getX(), getY(), getWidth(), getHeight());
	}

	public void draw(Graphics window, Color col)
	{
		window.setColor(col);
		window.fillRect(getX(), getY(), getWidth(), getHeight());
	}

	public boolean equals(Object obj)
	{
		return false;
	}

	//add the other get methods
	public Color getColor()
   	{
   		return color;
	}

	public int getWidth()
	{
		return width;
	}

	public int getHeight()
	{
		return height;
	}

	public int getX()
	{
		return xPos;
	}

	public int getY()
	{
		return yPos;
	}

	//add a toString() method
	public String toString()
	{
		return "Color = "+color+"\n"+"xPos"+xPos+"\n"+"yPos"+yPos+"\n"+"Width = "+width+"\n"+"Height = "+height;
	}
}

class BlockTestTwo extends Canvas
{
	public BlockTestTwo()
	{
		setBackground(Color.white);
	}

	public void paint(Graphics window)
	{
		Block one = new Block();
		one.draw(window);

		Block two = new Block(50,50,30,30);
		two.draw(window);

		Block three = new Block(350,350,15,15,Color.red);
		three.draw(window);

		//two.draw(window, Color.white);

		Block four = new Block(450,50,20,60, Color.green);
		four.draw(window);

		//add more test cases
	}
}

class a
{
	public static void main (String[] args)
	{
		BlockTestTwo b = new BlockTestTwo();
		b.setVisible(true);
	}
}