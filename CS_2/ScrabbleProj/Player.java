package scrabble;

import java.util.Collections;
import java.util.Arrays;
import java.util.List;
import java.util.Queue;
public class Player
{
	public int points;
    public Game game;
    public Letter[] hand;
    public int player;

    public Player(Game g,int player)
    {
        hand=new Letter[7];
        points = 0;
        game = g;
        this.player=player;
        fillHand();
    }
    public void play(int letter, int r, int c)
    {
    	Board bo = game.board;
    	bo.addLetter(hand[letter],r,c);
    	hand[letter] = null;
    }
    public void play(int letter,String coord)
    {
        int row=Integer.parseInt(coord.substring(1))-1;
        int col=coord.charAt(0)-'a';
        play(letter,row,col);
    }
    public Letter remove(int r,int c)
    {
        Board b= game.board;
        Letter temp =b.board[r][c];
        b.board[r][c]=null;
        return temp;
    }
    public void exchange(boolean[] letters)
    {
    	Bag b = game.bag;
    	Queue<Letter> q = b.letters;
		for(int x = 0; x<7; x++)
		{
			if(letters[x])
			{
				q.add(hand[x]);
				hand[x]=null;
			}
		}
		fillHand();
    }
    public void exchange(String s)
    {
        boolean[] q=new boolean[7];
        for(char a:s.toCharArray())
        {
            q[a-'1']=true;
        }
        exchange(q);
    }
    public void fillHand()
    {
    	Bag b = game.bag;
    	Queue<Letter> q =b.letters;
    	for(int x = 0; x<7;x++)
    	{
    		if(hand[x]==null)
    		{
    			hand[x]=q.remove();
    		}
    	}
    	Collections.shuffle((List)q);
    }
    public void addLetter()
    {

    }
    public Letter removeLetter(int index)
    {
        return null;
    }
    public void shuffleHand()
    {
    	List list = Arrays.asList(hand);
    	Collections.shuffle(list);
		hand = (Letter[])list.toArray();
    }
    @Override public String toString()
    {
    	String output = "          1 2 3 4 5 6 7\nPlayer "+player+": ";
    	for(int x = 0;x<7;x++)
    	{
    		output+=hand[x].letter+" ";
    	}
    	output+="| "+points;
    	return output;

    }
}
