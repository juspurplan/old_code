package scrabble;
import java.util.Queue;
import java.util.LinkedList;
import java.util.ArrayList;
public class Bag
{
    public Queue<Letter> letters;

    public Bag()
    {
        ArrayList<Letter> temp=new ArrayList<Letter>();
        letters=new LinkedList<Letter>();
        for(char x='A';x<='Z';x++)
        {
            if(x=='J' || x=='K' || x=='Q' || x=='X' || x=='Z')
            {
                temp.add(new Letter(x));
            }
            if(x=='B' || x=='C' || x=='F' || x=='H' || x=='M' || x=='P' ||
                x=='V' || x=='W' || x=='Y')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
            if(x=='G')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
            if(x=='D' || x=='L' || x=='S' || x=='U')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
            if(x=='N' || x=='R' || x=='T')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
            if(x=='O')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
            if(x=='A' || x=='I')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
            if(x=='E')
            {
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
                temp.add(new Letter(x));
            }
        }
        for(int x=0;x<98;x++)
        {
            int q=(int)(Math.random()*temp.size());
            letters.add(temp.remove(q));
        }
    }
}
