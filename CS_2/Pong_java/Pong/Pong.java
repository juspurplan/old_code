//© A+ Computer Science  -  www.apluscompsci.com
//Name -
//Date -
//Lab  - Pong

package Pong;
import Pong.Block;
import Pong.Paddle;
import Pong.Ball;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Canvas;
import java.awt.event.ActionEvent;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import static java.lang.Character.*;
import java.awt.image.BufferedImage;
import java.awt.event.ActionListener;

public class Pong extends Canvas implements KeyListener, Runnable
{
	private Ball ball;
	private Paddle leftPaddle;
	private Paddle rightPaddle;
	private Paddle ceil;
	private Paddle floor;
	private boolean[] keys;
	private BufferedImage back;
	private int p1score;
	private int p2score;
	private boolean ballreleased;
	private Ball lazer1;
	private Ball lazer2;


	public Pong()
	{
		//set up all variables related to the game
		ball = new Ball(400,300,5,5,Color.white);
		leftPaddle = new Paddle(31 , 300-25 , 2 , 100 , 20 , Color.blue);
		rightPaddle = new Paddle(750 , 300-25 , 2 , 100 , 20 , Color.GREEN);
		ceil = new Paddle(0 , 15 , 800 ,1 , Color.gray);
		floor = new Paddle(0 , 535 , 800 , 1 , Color.gray);
		keys = new boolean[8];
		p1score = 0;
		p2score = 0;
		ballreleased=false;
		lazer1 = new Ball(900,300,10,2,new Color(200,0,0));
		lazer2 = new Ball(-900,300,10,2,new Color(200,0,0));
		lazer1.setXSpeed(20);
		lazer1.setYSpeed(0);
		lazer2.setXSpeed(-20);
		lazer2.setYSpeed(0);

		//choose who serves 1st
		if( (int) (2*Math.random()) == 0 )
		{
			ball.setX(19);
		}
		else
		{
			ball.setX(761);
		}

    	setBackground(Color.black);
		setVisible(true);

		new Thread(this).start();
		addKeyListener(this);		//starts the key thread to log key strokes
	}

    public void update(Graphics window)
    {
	   paint(window);
    }

    public void paint(Graphics window)
    {
		//set up the double buffering to make the game animation nice and smooth
		Graphics2D twoDGraph = (Graphics2D)window;

		//take a snap shop of the current screen and save it as an image
		//that is the exact same width and height as the current screen
		if(back==null)
		{
			back = (BufferedImage)(createImage(getWidth(),getHeight()));
		}

		//create a graphics reference to the back ground image
		//we will draw all changes on the background image
		Graphics graphToBack = back.createGraphics();

		//see if ball hits left wall or right wall
		if(!(ball.getX()>=15 && ball.getX()<=760))
		{
			ball.setXSpeed(0);
			ball.setYSpeed(0);
			if(ball.getX() <400 && ballreleased)
			{
				p2score++;
			}
			if(ball.getX() >400 && ballreleased)
			{
				p1score++;
			}
			ballreleased = false;
		}

		//see if the ball hits the top wall
		if(ball.didCollideUp(ceil))
		{
			ball.setYSpeed((-1) * ball.getYSpeed());
			ball.setYSpeed(ball.getYSpeed()+1);
			ball.randomColorChange();
		}

		//see if the ball hits the left paddle
		if(ball.didCollideLeft(leftPaddle))
		{
			ball.setXSpeed( (-1) * ball.getXSpeed());
			ball.setXSpeed(ball.getXSpeed()+1);
			int x = (((rightPaddle.getY()+rightPaddle.getHeight())/2)-ball.getY())/50;
			ball.setYSpeed(ball.getYSpeed() + (((rightPaddle.getY()+rightPaddle.getHeight())/2)-ball.getY())/70 );
			ball.randomColorChange();
		}

		//see if the ball hits the right paddle
		if(ball.didCollideRight(rightPaddle))
		{
			ball.setXSpeed( (-1) * ball.getXSpeed());
			ball.setXSpeed(ball.getXSpeed()-1);
			int x = (((rightPaddle.getY()+rightPaddle.getHeight())/2)-ball.getY())/50;
			ball.setYSpeed(ball.getYSpeed() + (((rightPaddle.getY()+rightPaddle.getHeight())/2)-ball.getY())/70 );
			ball.randomColorChange();
		}

		//see if ball hits bottom
		if(ball.didCollideDown(floor))
		{
			ball.setYSpeed((-1) * ball.getYSpeed());
			ball.setYSpeed(ball.getYSpeed()-1);
			ball.randomColorChange();
		}

		//see if the paddles need to be moved
		if(keys[0] && leftPaddle.getY() > 16)
		{
			leftPaddle.moveUpAndDraw(graphToBack);
		}
		if(keys[1] && leftPaddle.getY() < 530-leftPaddle.getHeight())
		{
			leftPaddle.moveDownAndDraw(graphToBack);
		}
		if(keys[2] && rightPaddle.getY() > 16)
		{
			rightPaddle.moveUpAndDraw(graphToBack);
		}
		if(keys[3] && rightPaddle.getY() < 530-rightPaddle.getHeight())
		{
			rightPaddle.moveDownAndDraw(graphToBack);
		}

		//loser respawns ball whenever he/she wants
		if(ball.getX() < 800/2 && ball.getXSpeed() == 0 && ball.getYSpeed() == 0)
		{
			graphToBack.setColor(Color.red);
			graphToBack.fillOval(310,547,5,5);
			if(keys[4])
			{
				graphToBack.setColor(Color.black);
				graphToBack.fillRect(ball.getX(),ball.getY(),ball.getWidth(),ball.getHeight());
				ballreleased = true;
				ball.respawn(leftPaddle.getX()+10,leftPaddle.getY()+(leftPaddle.getHeight()/2) , 1 , 0);
				graphToBack.clearRect(310,547,5,5);
			}
		}
		if(ball.getX() > 800/2 && ball.getXSpeed() == 0 && ball.getYSpeed() == 0)
		{
			graphToBack.setColor(Color.red);
			graphToBack.fillOval(495,547,5,5);
			if(keys[5])
			{
				graphToBack.setColor(Color.black);
				graphToBack.fillRect(ball.getX(),ball.getY(),ball.getWidth(),ball.getHeight());
				ballreleased = true;
				ball.respawn(rightPaddle.getX()-10,rightPaddle.getY()+(rightPaddle.getHeight()/2) , -1 , 0 );
				graphToBack.clearRect(495,547,5,5);
			}
		}

		//shoot lazers, and move/draw lazers
		lazer1.moveAndDraw(graphToBack);
		lazer2.moveAndDraw(graphToBack);
		if(keys[6] && lazer1.getX()>800)
		{
			lazer1.setX(leftPaddle.getX());
			lazer1.setY(leftPaddle.getY()+(leftPaddle.getHeight()/2));
		}
		if(keys[7] && lazer2.getX()<0)
		{
			lazer2.setX(rightPaddle.getX());
			lazer2.setY(rightPaddle.getY()+(rightPaddle.getHeight()/2));
		}

		//see if lazers hit sumthing
		if(lazer1.didCollideRight(rightPaddle))
		{
			rightPaddle.stun();
		}
		if(lazer2.didCollideLeft(leftPaddle))
		{
			leftPaddle.stun();
		}

		ball.moveAndDraw(graphToBack);
		leftPaddle.draw(graphToBack);
		rightPaddle.draw(graphToBack);

		ball.changeColor();

		floor.draw(graphToBack);
		ceil.draw(graphToBack);
		graphToBack.clearRect(320,541,175,100);
		graphToBack.setColor(Color.blue);
		graphToBack.drawString("Player 1 = "+p1score , 330,555);
		graphToBack.setColor(Color.green);
		graphToBack.drawString("Player 2 = "+p2score , 420,555);

		twoDGraph.drawImage(back, null, 0, 0);
  	}

 	public void keyPressed(KeyEvent e)
 	{
		switch(toUpperCase(e.getKeyChar()))
	 	{
			case 'Q' : keys[0]=true; break;
			case 'A' : keys[1]=true; break;
			case 'U' : keys[2]=true; break;
			case 'J' : keys[3]=true; break;
			case 'Z' : keys[4]=true; break;
			case 'M' : keys[5]=true; break;
			case 'S' : keys[6]=true; break;
			case 'K' : keys[7]=true; break;
		}
	}

	public void keyReleased(KeyEvent e)
	{
		switch(toUpperCase(e.getKeyChar()))
		{
			case 'Q' : keys[0]=false; break;
			case 'A' : keys[1]=false; break;
			case 'U' : keys[2]=false; break;
			case 'J' : keys[3]=false; break;
			case 'Z' : keys[4]=false; break;
			case 'M' : keys[5]=false; break;
			case 'S' : keys[6]=false; break;
			case 'K' : keys[7]=false; break;
		}
	}

	public void keyTyped(KeyEvent e){}

    public void run()
    {
   		try
   		{
   			while(true)
   			{
   		   		Thread.currentThread().sleep(15);

				//cooldown
				leftPaddle.coolDown(15);
				rightPaddle.coolDown(15);

            	repaint();
         	}
      	}catch(Exception e)
      	{
      	}
  	}
}