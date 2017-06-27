package scrabble;
import java.util.TreeSet;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
public class Board
{
    public Letter[][] board;
    public TreeSet<String> dictionary;
    public Board() throws FileNotFoundException
    {
        board=new Letter[15][15];
        dictionary=new TreeSet<String>();
        Scanner scan=new Scanner(new File("words.txt"));
        while(scan.hasNext())
        {
            dictionary.add(scan.next());
        }
    }
    public void addLetter(Letter l, int x, int y)
    {
        board[y][x]=l;
    }
    public boolean checkWords()
    {
        ArrayList<String> words=new ArrayList<String>();
        for(int x=0;x<15;x++)
        {
            if(!checkLineForWord(board[x])) return false;
            Letter[] vertical=new Letter[15];
            for(int y=0;y<15;y++)
            {
                vertical[y]=board[y][x];
            }
            if(!checkLineForWord(vertical)) return false;
        }
        return true;
    }
    public boolean checkLineForWord(Letter[] l)
    {
        ArrayList<String> words=new ArrayList<String>();
        String s="";
        for(int i=0;i<15;i++)
        {
            if(l[i]==null)
            {
                if(s.length()<=1)
                {
                    s="";
                }
                else
                {
                    words.add(s);
                }
            }
            else
            {
                s+=l[i];
            }
        }
        if(s.length()>1)
        {
            words.add(s);
        }
        for(String a:words)
        {
            if(!dictionary.contains(a)) return false;
        }
        return true;
    }
    @Override public String toString()
    {
        String output="  ";
        for(char a='a';a<='o';a++) output+=a+" ";
        for(int y=0;y<15;y++)
        {
            output+="\n"+(y+1)+" ";
            for(int x=0;x<15;x++)
            {
                if(board[x][y]==null) output+="  ";
                else output+=board[x][y]+" ";
            }
        }
        return output;
    }
}
