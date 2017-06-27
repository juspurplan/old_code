public class ChangeCounter
{
	public static void main (String[]args)
	{
		int pennies = 13;
		int nickels = 8	;
		int dimes = 4;
		int quarters = 2;

		double dollars = pennies+nickels+dimes+quarters;

		pennies *=1;
		nickels *=5;
		dimes *=10;
		quarters *=25;

		System.out.println("My piggy bank held " +quarters);
	}
}