package scrabble;
import java.io.FileNotFoundException;
import java.util.*;
import java.text.ParseException;
public class Main
{
    public static void main(String[] args) throws FileNotFoundException
    {
    	Scanner scan = new Scanner(System.in);
        System.out.print("Please enter the number of players: ");
        int numplayer = scan.nextInt();
        Game g = new Game(numplayer);
        while(true)
        {
            System.out.println(g.board);
            System.out.println(g.currentPlayer);
            String play ="";

            do
            {
                System.out.print("Play, Exchange, Shuffle, or Pass? ");
                play = scan.next();
            } while(!play.equals("play") && !play.equals("exchange") && !play.equals("pass") && !play.equals("shuffle"));

            boolean nextPlayer=false;
            if(play.toLowerCase().equals("play"))
            {
                System.out.print("What is the first letter you want to place? ");
                int index=scan.nextInt();
                System.out.println("Please enter the coordinate of the first letter: ");
                String coor = scan.next();
                int xcoor = coor.charAt(0)-'a';
                int ycoor = Integer.parseInt(coor.substring(1));
                System.out.print("Please enter the direction of the word: ");
                boolean vertical=scan.next().equalsIgnoreCase("vertical");
                Map<Integer,Integer> map = new TreeMap<Integer,Integer>();
                if(vertical)
                {
                	///////////vertical
                    ArrayList<Integer> xcoords=new ArrayList<Integer>();
                    xcoords.add(index);
                    System.out.println("Enter the letters you wantin the order you want");
                    try
                    {
                        while(true)
                        {
                            int beanz = scan.nextInt();
                            if(beanz >7 || beanz<1)
                            {
                                System.out.println("bad input");
                            }
                            else
                            {
                                xcoords.add(beanz);
                            }
                        }
                    }
                    catch(Exception e)
                    {
                        //add letters to board xD
                        for(int z = 0 ; z<xcoords.size() ;z++)
                        {
                            Player curr = g.currentPlayer;
                            Board b = g.board;
                            Letter[][] c = b.board;
                            if(c[ycoor+z-1][xcoor] == null)
                            {
                                curr.play(xcoords.get(z)-1,ycoor+z-1 , xcoor);
                                map.put(ycoor+z-1,xcoor);
                            }
                            else
                            {
                                 ycoor++;
                                curr.play(xcoords.get(z)-1,ycoor+z-1 , xcoor);
                                map.put(ycoor+z-1,xcoor);
                            }

                        }
                        //if(bad word) remove the letters from the board
                        /*Board b = g.board;
                        if(!b.checkWords())
                        {
                            
                        }*/

                    }

                }
                else
                {
                	//////////horizontal
                    System.out.println("Enter the letters you wantin the order you want");
                    ArrayList<Integer> ycoords=new ArrayList<Integer>();
                    ycoords.add(index);
                    try
                    {
                        while(true)
                        {
                            int beanz = scan.nextInt();
                            if(beanz >7 || beanz<1)
                            {
                                System.out.println("bad input");
                            }
                            else
                            {
                                ycoords.add(beanz);
                            }
                        }
                    }
                    catch(Exception e)
                    {
                        //add letters to board xD
                        for(int z = 0 ; z<ycoords.size() ;z++)
                        {
                            Player curr = g.currentPlayer;
                            Board b = g.board;
                            Letter[][] c = b.board;
                            if(c[ycoor-1][xcoor+z] == null)
                            {
                                curr.play(ycoords.get(z)-1,ycoor-1 , xcoor+z);
                                map.put(ycoor-1,xcoor+z);
                            }
                            else
                            {
                                 xcoor++;
                                curr.play(ycoords.get(z)-1,ycoor-1 , xcoor+z );
                                map.put(ycoor-1,xcoor+z);
                            }

                        }
                        //if(bad word) remove the letters from the board
                        /*Board b = g.board;
                        if(b.checkWords())
                        {
                           for(Integer i : map.keySet())
                           {
                               g.currentPlayer.addLetter();
                           }
                        }*/
                    }
                }




                Player curr = g.currentPlayer;
                curr.fillHand();

                
                nextPlayer=true;
            }
            else if(play.toLowerCase().equals("exchange"))
            {
                System.out.print("Which letters do you want to exchange? ");
                g.currentPlayer.exchange(scan.next());
                nextPlayer=true;
            }
            else if(play.toLowerCase().equals("shuffle"))
            {
                g.currentPlayer.shuffleHand();
            }
            else
            {
                nextPlayer=true;
            }
            if(nextPlayer) g.switchPlayers();
        }
    }

    public Main() {
    }
}
