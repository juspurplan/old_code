class ChangeCounter
{
	public static void main (String[]args)
	{
		int pennies = 13;
		int nickels = 8;
		int dimes = 4;
		int quarters = 2;
		double total = (pennies*0.01)+(nickels*0.05)+(dimes*0.1)+(quarters*0.25);

		System.out.println("My piggy bank held " +pennies +" pennies, " +nickels +" nickels, " +dimes+" dimes and " +quarters+" quarters.");
		System.out.println("This adds up to " +total+".");
	}
}