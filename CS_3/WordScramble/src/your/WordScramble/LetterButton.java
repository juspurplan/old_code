package your.WordScramble;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.util.AttributeSet;
import android.widget.Button;

public class LetterButton extends Button
{
	private char letter;
	private boolean used;

	public LetterButton(Context context)
	{
		super(context);
	}
	public LetterButton(Context context, AttributeSet attrs)
	{
		super(context, attrs);
	}
	public LetterButton(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
	}
	public LetterButton(Context context, char letter)
	{
		super(context);
		this.letter = letter;
		used = false;
	}
	
	public boolean isUsed()
	{
		return used;
	}
	public void setUsed(boolean used)
	{
		this.used = used;
	}
	public char getLetter()
	{
		return letter;
	}

	public void setLetter(char letter)
	{
		this.letter = letter;
	}
	@Override
	protected void onDraw(Canvas canvas)
	{
		// TODO Auto-generated method stub
		if(!isUsed())
		{
			super.onDraw(canvas);
			Paint p = new Paint();
			p.setARGB(255,0,0,0);
			p.setTextAlign(Align.CENTER);
			p.setTextSize(50);
			canvas.drawText(letter+"", this.getWidth()/2, this.getHeight()/2 +50/3, p);
		}
	}
}
