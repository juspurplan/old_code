class Seconds
{
	public static void main (String[]args)
	{
		final int year = 365;
		final int day = 24;
		final int hour = 60;
		final int minute = 60;
		int total = year*day*hour*minute;

		System.out.println("There are " +total + " seconds in one year.");
	}
}