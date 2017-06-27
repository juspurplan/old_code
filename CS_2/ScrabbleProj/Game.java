package scrabble;
import java.io.FileNotFoundException;
public class Game
{
    public Bag bag;
    public Player player1;
    public Player player2;
    public Player player3;
    public Player player4;
    public Player currentPlayer;
    public Board board;
    public int players;
    public Game(int players) throws FileNotFoundException
    {
        bag=new Bag();
        board=new Board();
        currentPlayer=player1=new Player(this,1);
        player2=new Player(this,2);
        if(players==3 || players==4) player3=new Player(this,3);
        if(players==4) player4=new Player(this,4);
        this.players=players;
    }
    public void switchPlayers()
    {
        if(players==3)
        {
            if(currentPlayer==player1) currentPlayer=player2;
            else if(currentPlayer==player2) currentPlayer=player3;
            else currentPlayer=player1;
        }
        else if(players==4)
        {
            if(currentPlayer==player1) currentPlayer=player2;
            else if(currentPlayer==player2) currentPlayer=player3;
            else if(currentPlayer==player3) currentPlayer=player4;
            else currentPlayer=player1;
        }
        else
        {
            if(currentPlayer==player1) currentPlayer=player2;
            else currentPlayer=player1;
        }
    }
}
