/*
 * Project6.c
 *
 * My Name
 * My TA
 * My Section Time
 *
 *
 */


#include <stdio.h>
#include "MazeParams.h"
#include <climits>

/* return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 */
int minIt(int x[], int n) {
	return 0;
}

/* return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * solve the problem recursively and 
 * use an "n-1" type of decomposition
 */
int minRec1(int x[], int n) {
	//base case: n == 1
	if (n == 1) {
		return x[0];
	}

	//recursive case
	int curr_value = x[n-1];
	int min_lower = minRec1(x, n-1);

	return (curr_value < min_lower) ? (curr_value) : (min_lower);
}

/*
 * return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and 
 * use an "n / 2" type of decomposition
 */
int minRec2(int x[], int n) {
	//base case:
	if (n == 1) {
		return x[0];
	}

	//recursive case
	int min_lower = minRec2(x, n/2 );
	int min_upper = minRec2(x + n/2, n/2 + n%2);

	return (min_lower < min_upper) ? (min_lower) : (min_upper);
}


/*
 * calculate and return the square root of x.
 * The other two parameters are estimates of the square root.
 * low_guess is smaller than the actual square root, and high_guess 
 * is larger than the actual square root.
 * Searching for the square root can be done much like searching
 * for a name in a phone book.
 *
 * Since you can't calculate a square root exactly, for this problem
 * you're required to calculate the answer to 15 decimal digits of
 * accuracy.
 */
double sqrtIt(double x, double low_guess, double high_guess) {
	return 0;
}

/*
 * calculate and return the square root of x.
 * The other two parameters are estimates of the square root.
 * low_guess is smaller than the actual square root, and high_guess 
 * is larger than the actual square root.
 * Searching for the square root can be done much like searching
 * for a name in a phone book.
 *
 * Since you can't calculate a square root exactly, for this problem
 * you're required to calculate the answer to 15 decimal digits of
 * accuracy.
 */
double sqrtRec(double x, double low_guess, double high_guess) {
	double mid_guess = (low_guess + high_guess)/2;
	double test = mid_guess * mid_guess;
	double diff = test - x;
	
	//base case
	if (diff < .000000000000009 && diff > -0.000000000000009) {
		return mid_guess;
	}
	else if (diff > 0) {
		return sqrtRec(x, low_guess, mid_guess);
	}
	else /* (diff < 0) */ {
		return sqrtRec(x, mid_guess, high_guess);
	}
}


/*
 * using only recursion, write a string comparison function
 * return -1 if str1 is less than str2
 * return 0 if the two strings are equal
 * return +1 if str1 is greater than str2
 * when comparing strings, use the ASCII value to compare each character
 * (i.e., that means 'A' is less than 'a' since it's ASCII value is smaller)
 * The string str1 is less than str2 if either
 * str1[0] < str2[0]
 * or there exists a k such that str1[k] < str2[k] and 
 *   for all j < k str1[j] == str2[j]
 *   and k is less than the length of str1 and str2
 */

int strCompare(char* str1, char* str2) {
	//base case: when one of the chars reach null character.
	char c1 = *str1;
	char c2 = *str2;
	if (c1 == 0 && c2 != 0) {
		return -1;
	}
	else if (c1 != 0 && c2 == 0) {
		return 1;
	}
	else if (c1 == 0 && c2 == 0) {
		return 0;
	}

	//recursive case: both chars are not null characters
	if (c1 < c2) {
		return -1;
	}
	else if( c1 > c2 ) {
		return 1;
	}
	else /* (c1 == c2) */ {
		return strCompare(str1+1, str2+1);
	}
}

/*
 * if c is not a letter return -1
 * if c is a letter, return the position of c in the alphabet 
 * where 'A' (and 'a') are position 1 and 'Z' (and 'z') are position 26
 *
 * This code is rather ugly as I'm exploiting some detailed knowledge of the ASCII table
 */
int whatLetter(char c) {
	if (c < 'A') { return -1; }
	if (c > 'z') { return -1; }
	if (c > 'Z' && c < 'a') { return -1; }
	return c & ~32 - 64;
}

/*
 * same as before, only this time 
 * ignore anything that is not a letter
 * ignore the case (upper case, lower case)
 * So, strCompare2("Hello", "hello") should return 0 (they're the same)
 * strCompare2("The plane!", "theater") should return 1 since "theplane" is larger than "theater"
 * once again, you can only use recursion, no loops
 */
int strCompare2(char* str1, char* str2) {
	char c1 = *str1;
	char c2 = *str2;

	//special case: if there are any "illegal" chars, skip them.
	if( whatLetter(c1) == -1 && c1 != 0) {
		//printf("skipping c1(%c) = %i, c2(%c) = %i\n", c1, whatLetter(c1), c2, whatLetter(c2));
		return strCompare2(str1+1, str2);
	}
	if (whatLetter(c2) == -1 && c2 != 0) {
		//printf("c1(%c) = %i, skipping c2(%c) = %i\n", c1, whatLetter(c1), c2, whatLetter(c2));
		return strCompare2(str1, str2+1);
	}

	//printf("c1(%c) = %i, c2(%c) = %i \n", c1, whatLetter(c1), c2, whatLetter(c2));

	//base case: when one of the chars reach null character.
	if (c1 == 0 && c2 != 0) {
		return -1;
	}
	else if (c1 != 0 && c2 == 0) {
		return 1;
	}
	else if (c1 == 0 && c2 == 0) {
		return 0;
	}

	//recursive case: 
	//c1 and c2 are not null characters.
	if (whatLetter(c1) < whatLetter(c2)) {
		return -1;
	}
	else if( whatLetter(c1) > whatLetter(c2) ) {
		return 1;
	}
	else /* (c1 == c2) */ {
		return strCompare2(str1+1, str2+1);
	}
}



/*
 * the two dimensional array maze[MATRIX_SIZE][MATRIX_SIZE] contains a maze
 * Each square is (initially) either a 1 or a zero.  Each 1 represents a wall
 * (you cannot walk through walls, so you can't go into any square where the 
 * value is 1).  Each 0 represents an open space.  
 *
 * Write an recursive solution to find your way out of the maze
 * Your starting point is at row and col. (params to this function)
 * Your exit point is somewhere in the last row (which is: MATRIX_SIZE - 1)
 *
 * There is a relatively easy recursive solution to this problem, the trick is
 * to think of the solution in the following terms:
 *   "Not counting the steps I've taken so far to get out of this maze,
 *    what is the minimum number of steps I can take from here, without 
 *    backtracking, and get to the exit?"
 * In some cases, you may find yourself in a spot in the maze that there's
 * no way out (at least, not without backtracking). In that case, the number 
 * of steps you'd have to take is infinite. You can use the value -1 to represent
 * this possibility. If you had a function that could answer that question for you
 * from each possible direction you might consider going, then you'd (obviously)
 * call that function on each possible direction and choose whichever possiblity
 * returned the shortest number of steps to the exit.
 *
 * With that hint, the base case should be pretty obvious.  In fact,
 * I'd suggest you consider the possibility that the base case is "Yup, the 
 * shortest path to the exit is zero steps from here, I know 'cause I'm already at 
 * the exit!"
 *
 * There is one tricky part to this decomposition.  You need to make certain 
 * that the problem is getting smaller.  The "bigness" or "smallness" of this 
 * problem is the number of squares that have not yet been tested.  Each time
 * you test an adjacent square (making a recursive call to decide if the
 * shortest path to the exit goes through that square), you'll be reducing 
 * the number of squares that have not yet been tested.  Eventually, you must 
 * have tested all the squares and so you'll have to have found a way to the 
 * exit.
 *
 * The easy way to deal with the tricky part is to leave "bread crumbs" behind.
 * Before you recursively check any (or all) of your neighbors to see if you 
 * can find the exit from there -- drop a bread crumb in your current square.
 * Then, don't ever check to see if you can find the exit using a square
 * with a breadcrumb in it (backtracking into that square would be silly).
 *
 * If you're trying to see if you can find an exit from some square, and all 
 * the adjacent squares are either walls, or have bread crumbs in them, then
 * you already know the answer -- "The shortest path to the exit does NOT go 
 * through this square".  Pick up your bread crumb and return infinity (or -1).
 * 
 * You can set the value of the current square to "2" to indicate that a bread
 * crumb has been dropped.  Set the square back to 0 when you want to pick 
 * the bread crumb back up.
 * be sure not to change any of the squares that are 1 (the walls).
 *
 * for partial credit, you can leave all your bread crumbs on the floor.
 * for full credit, you must pick up all the bread crumbs EXCEPT those
 * along the shortest path to the exit, and you must return the number of 
 * steps along that path.
 */

//forward declare
int smallest (int a, int b, int c, int d);

void printMaze(void) ;


int solveMazeRec(int row, int col) {
	//place bread crumb
	maze[row][col] = 2;
	//debug line
	//printMaze();
	//printf("\n");

	//base case, we reached the exit
	if(row == MATRIX_SIZE -1) {
		maze[row][col] = 2;
		//printf("WINNNN!!!\n");
		return 0;
	}
	
	//recursive case:
	bool N_allowed = (row-1) >= 0 && maze[row-1][col] == 0;
	bool E_allowed = (col+1) < MATRIX_SIZE && maze[row][col+1] == 0;
	bool S_allowed = (row+1) < MATRIX_SIZE && maze[row+1][col] ==0;
	bool W_allowed = (col-1) >=0 && maze[row][col-1] == 0;
	
	int N_min_path = -1;
	int E_min_path = -1;
	int S_min_path = -1;
	int W_min_path = -1;

	if(N_allowed) {
		N_min_path = solveMazeRec(row-1, col);
	}
	if(E_allowed) {
		E_min_path = solveMazeRec(row, col+1);
	}
	if(S_allowed) {
		S_min_path = solveMazeRec(row+1, col);
	}
	if(W_allowed) {
		W_min_path = solveMazeRec(row, col-1);
	}

	int min_path = smallest(N_min_path, E_min_path, S_min_path, W_min_path);

	switch(min_path){
	case 0:
		//N was shortest path
		//remove bread crumbs for other paths, if they were attempted
		//printf("(%i , %i) Return N: %i\n", row, col, N_min_path +1);
		if (E_allowed){
			maze[row][col+1] = 0;
		}
		if (S_allowed) {
			maze[row+1][col] = 0;
		}
		if (W_allowed) {
			maze[row][col-1] = 0;
		}
		return N_min_path + 1;
		break;

	case 1:
		//E was shortest path
		//remove bread crumbs for other paths, if they were attempted
		//printf("(%i , %i) Return E: %i\n", row, col, E_min_path +1);
		if (N_allowed) {
			maze[row-1][col] = 0;
		}
		if (S_allowed) {
			maze[row+1][col] = 0;
		}
		if (W_allowed) {
			maze[row][col-1] = 0;
		}
		return E_min_path + 1;
		break;

	case 2:
		//S was shortest path
		//remove bread crumbs
		//printf("(%i , %i) Return S: %i\n", row, col, S_min_path +1);
		if (N_allowed) {
			maze[row-1][col] = 0;
		}
		if (E_allowed){
			maze[row][col+1] = 0;
		}
		if (W_allowed) {
			maze[row][col-1] = 0;
		}
		return S_min_path + 1;
		break;

	case 3:
		//W was shortest path
		//remove bread crumbs
		//printf("(%i , %i) Return W: %i\n", row, col, W_min_path +1);
		if (N_allowed) {
			maze[row-1][col] = 0;
		}
		if (E_allowed){
			maze[row][col+1] = 0;
		}
		if (S_allowed) {
			maze[row+1][col] = 0;
		}
		return W_min_path + 1;
		break;

	case -1:
		//all paths were dead ends
		//remove all bread crumbs
		//return -1 for inf path length
		//printf("(%i , %i) Return -1\n", row, col );
		if (N_allowed) {
			maze[row-1][col] = 0;
		}
		if (E_allowed){
			maze[row][col+1] = 0;
		}
		if (S_allowed) {
			maze[row+1][col] = 0;
		}
		if (W_allowed) {
			maze[row][col-1] = 0;
		}
		return -1;
		break;

	default:
		//if executions gets here, something broke
		printf("Something broke in maze solver.\n");
		return -100;
		break;	
	}


}

//returns the:
//0 - a
//1 - b
//2 - c
//3 - d
//where the corresponding integer is the smallest non negative int.
//returns -1 if a, b, c, d are -1
int smallest (int a, int b, int c, int d) {
	if (a == -1 && b == -1 && c == -1 && d == -1){
		return -1;
	}

	a = (a==-1) ? (INT_MAX) : (a);
	b = (b==-1) ? (INT_MAX) : (b);
	c = (c==-1) ? (INT_MAX) : (c);
	d = (d==-1) ? (INT_MAX) : (d);

	if (a <= b && a <= c && a <= d) {
		return 0;
	}
	else if (b <= a && b <= c && b <= d) {
		return 1;
	}
	else if (c <= a && c <= b && c <= d ) {
		return 2;
	}
	else if (d <= a && d <= b && d <= c) {
		return 3;
	}
	
}


/**********************
 * adjacentCell and isOK are functions provided to help you write
 * solveMazeIt()
 */

/*
 * OK, we're currently at maze[row][col] and we're considering moving
 * in direction dir.  
 * Set trow and tcol (local variables inside the calling function)
 * to the row and column that we would move to IF we moved in
 * that direction
 *
 * For example, there are two good ways to use this function.
 * 1. to actually move one step in a direction use:
 *       adjacentCell(row, col, dir, &row, &col);
 *    That will set row and col to new values.  The new values will
 *    be one square away from the old values.
 *
 * 2. to set trow and tcol to a square that is adjacent to row and col use:
 *       adjacentCell(row, col, dir, &trow, &tcol);
 *    That will not change row and col, but will change trow and tcol.
 *    This is useful if you aren't sure if you can actually move in this 
 *    direction yet (e.g., maze[trow][tcol] may be a wall!).  So, you set
 *    trow and tcol, and then check to see if it's OK to move there
 */
void adjacentCell(int row, int col, int dir, int* trow, int* tcol) {
	*trow = row;
	*tcol = col;
	switch(dir) {
	case 0: // UP
		*trow = *trow - 1;
		break;
	case 1: // RIGHT
		*tcol = *tcol + 1;
		break;
	case 2: // DOWN
		*trow = *trow + 1;
		break;
	case 3: // LEFT
		*tcol = *tcol - 1;
		break;
	}
}


/* 
 * return false if there is a wall in the square for row and col
 * return true if it's not a wall.
 */
int isOK(int row, int col) {
	return (row > 0 && row < MATRIX_SIZE
		&& col > 0 && col < MATRIX_SIZE
		&& maze[row][col] != 1);
}

/*
 * return the value of the direction that is one turn to the right
 */
int turnRight(int dir) {
	return (dir + 1) % 4;
}

/*
 * return the value of the direction that is one turn to the left
 */
int turnLeft(int dir) {
	return (dir + 3) % 4;
}

/*
 * the two dimensional array maze[MATRIX_SIZE][MATRIX_SIZE] contains a maze
 * Each square is (initially) either a 1 or a zero.  Each 1 represents a wall
 * (you cannot walk through walls, so you can't go into any square where the value
 * is 1).  Each 0 represents an open space.  
 *
 * write an iterative solution to find your way out of the maze
 * Your starting point is at row and col. (params to this function)
 * Your exit point is somewhere in the last row (which is: MATRIX_SIZE - 1)
 * The maze can be solved by following the right hand wall.  In fact, there
 * is exactly one path between any two points in the maze (well, between any two
 * points that are not walls).
 *
 * The algorithm is not too bad, although it is certainly not trivial
 * Initially, you'll be headed DOWN (direction 2)
 * Each iteration do one of the following.  Note that only one of two cases
 * can possibly apply (the properties of the maze guarantee that).
 *    case 1: you can move in the current direction
 *       In this case, you should take one step in the current direction
 *       and then turn right.  
 *    case 2: you cannot move in the current direction
 *       If there's a wall directly in front of you, then to follow the right
 *       hand wall, you'd need to turn left (placing your hand on the wall that
 *       used to be directly in front of you).  So, if you discover this case
 *       then turn left.  Don't move, just turn left.
 * If you were walking down a straight corridor (with walls on both sides)
 * then you'd alternate case 1 and case 2.  On the first iteration, you'd
 * take a step, and then turn right (case 1).  This causes you to walk
 * one position down the hallway but then turn to face the wall.
 * On the next iteration, you'll be facing the wall, so you can't walk
 * forward and therefore (case 2) you'll turn left.  On the third iteration
 * you'll be able to walk down the hallway again.
 *
 * If you follow those two cases, then you'll eventually find your way out
 * of the maze.  To confirm that you're making it out, leave a "bread crumb" 
 * behind each square along the path to the exit.
 * For partial credit, place a bread crumb in every square you visit.
 * For full credit, pick up all the breadcrumbs when you backtrack.  
 * Backtracking is when you go back to a square you've already been before.  
 * If the square you're about to step into has a breadcrumb, then pick up 
 * the bread crumb in the square you're at now.
 * You indicate "bread crumbs" by setting the square equal to "2"
 */
void solveMazeIt(int row, int col) {
	int dir = 2; // 0 is up, 1 is right, 2 is down, 3 is left.
	maze[row][col] = 2; // drop a bread crumb in the starting square
	while (row < MATRIX_SIZE - 1) { // the exit is the only open square 
				// in the last row

		/* the rest of this loop is yours */

	}
}


/*
 * This struct is used in part5, martian currency
 * A Martian indicates a collection of coins. The components indicate the number of pennies
 * nicks and dodeks in that collection. The value (in cents) of a Martian is the weighted sum
 * i.e., if you had two pennies, three nicks and four dodeks, you'd have 2 + 15 + 48 = 65 cents
 */

struct Martian {
	int pennies;
	int nicks;
	int dodeks;
};

//forward declare change() with variable values.
Martian change(int cents, int nick_val, int dodek_val);

int getSum(Martian m){
	if(m.pennies < 0 || m.nicks < 0 || m.dodeks <0) {
		return INT_MAX;
	}
	else {
		return m.pennies+m.nicks+m.dodeks;
	}
}

/*
 * using recursion, with no loops or globals, write a function that calculates the optimal
 * (fewest total coins) change for a given amount of money. Return a Martian struct that indicates
 * this optimal collection of coins.
 */
Martian change(int cents) {
	return change(cents, int(5), int(12));
}

/*
 * Same as before, except the more general version where the coins have values
 * a cents and b cents, with a and b being algebraic. For the original problem, 
 * a is the constant 5 (nick_value = 5 cents) and b is the constant 12 
 * (dodek_value = 12 cents). 
 * If you've really mastered thinking recursively, then this version of the 
 * martian change problem is just as easy as the concrete version 
 */
Martian change(int cents, int nick_val, int dodek_val) {
	//base case: cents <= 0;
	if(cents == 0) {
		Martian m;
		m.pennies = 0;
		m.nicks = 0;
		m.dodeks = 0;

		return m;
	}
	if(cents < 0){
		Martian m;
		m.pennies = -1;
		m.nicks = -1;
		m.dodeks = -1;
		return m;
	}

	//recursive case
	Martian m1, m2, m3;

	m1 = change(cents-dodek_val, nick_val, dodek_val);
	m2 = change(cents-nick_val, nick_val, dodek_val);
	m3 = change(cents-1, nick_val, dodek_val);
	
	int sum1 = getSum(m1);
	int sum2 = getSum(m2);
	int sum3 = getSum(m3);

	if(sum1 <= sum2 && sum1 <= sum3) {
		m1.dodeks = m1.dodeks+1;
		return m1;
	}
	else if (sum2 <= sum1 && sum2 <= sum3) {
		m2.nicks = m2.nicks+1;
		return m2;
	}
	else /* (sum3 <= sum1 && sum3 <= sum2) */ {
		m3.pennies = m3.pennies+1;
		return m3;
	}
}

/* 
 * without using recursion, solve the Martian change problem described above.
 * it's not too bad for the specific case of nick_value = 5 and dodek_value = 12
 */
Martian changeIt(int cents) {
}

/*
 * However, I don't have a solution for the general case. In fact, I consider 
 * the general problem to "challenging" (i.e, an exercise in futility). 
 * But, if you like banging your head against the wall for zero credit
 * this is the problem for you!
 */
Martian changeIt(int cents, int nick_value, int dodek_value) {
}
