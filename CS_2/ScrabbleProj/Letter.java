package scrabble;
public class Letter
{
    public char letter;
    public int points;

    public Letter(char letter)
    {
        this.letter=letter;
        if(letter=='A' || letter=='E' || letter=='I' || letter=='L' ||
                letter=='N' || letter=='O' || letter=='R' || letter=='S'
                || letter=='T' || letter=='U') points=1;
        if(letter=='D' || letter=='G') points=2;
        if(letter=='B' || letter=='C' || letter=='M' || letter=='P') points=3;
        if(letter=='F' || letter=='H' || letter=='V' || letter=='W' ||
                letter=='Y') points=3;
        if(letter=='K') points=5;
        if(letter=='J' || letter=='X') points=8;
        if(letter=='Q' || letter=='Z') points=10;
    }

    public String toString()
    {
    	return Character.toString(Character.toUpperCase(letter));
    }
}
