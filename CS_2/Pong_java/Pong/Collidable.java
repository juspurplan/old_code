package Pong;

public interface Collidable
{
	public boolean didCollideLeft(Locatable obj);
	public boolean didCollideRight(Locatable obj);
	public boolean didCollideUp(Locatable obj);
	public boolean didCollideDown(Locatable obj);
}