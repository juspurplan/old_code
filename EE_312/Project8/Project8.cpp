#include "Bugs.h"
#include <random> 
#include <cstring> 
#include <cassert>
using std::rand;

int time_step = 0;
int average_age = 0;
int average_generation = 0;
int percent_straight;
int percent_right;
int percent_left;
int percent_back;
int total_left = 0;
int total_right = 0;
int total_straight = 0;
int total_back = 0;

/* DONE: you don't need to use this function in your solution
 * however this function is used by createWorld to generate random bugs */
Bug createBug(int x, int y) {
	Bug b;
	b.age = 0;
	b.generation = 0;
	b.x = x;
	b.y = y;
	b.dir = rand() % 8;
	b.health = START_HEALTH;
	for (int k = 0; k < 8; k += 1) {
		if (DISTRIBUTED_GENES) {
			b.genes[k] = GENE_TOTAL / 8;
		} else {
			if (k == 0) {
				b.genes[k] = GENE_TOTAL;
			} else {
				b.genes[k] = 0;
			}
		}
	}
	total_straight += b.genes[0];
	total_right += b.genes[1] + b.genes[2] + b.genes[3];
	total_left += b.genes[5] + b.genes[6] + b.genes[7];
	total_back += b.genes[4];
	return b;
}

/* DONE: */
void createWorld(void) {
	/* empty the world */
	for (int i = 0; i < WORLD_SIZE; i += 1) {
		for (int j = 0; j < WORLD_SIZE; j += 1) {
			world[i][j] = EMPTY;
		}
	}

	/* create food */
	for (int k = 0; k < INITIAL_FOOD; k += 1) {
		int x = rand() % WORLD_SIZE;
		int y = rand() % WORLD_SIZE;
		world[x][y] = FOOD;
	}
	
	/* create bugs */
	while (bug_list.size() < INITIAL_BUGS) {
		int x = rand() % WORLD_SIZE;
		int y = rand() % WORLD_SIZE;
		if (world[x][y] == EMPTY) {
			world[x][y] = bug_list.size();
			bug_list.push_back(createBug(x, y));
		}
	}	
}

/*
 * DONE: keep in mind that bugs that "fall off" the edge of the world
 * automatically reappear on the opposite edge (i.e, the world is round,
 * well, if you really want to get topographical, our bugs live on a donut.
 */ 
int wrap(int y) {
	if (y < 0) { return WORLD_SIZE - 1; }
	else if (y == WORLD_SIZE) { return 0; }
	else { return y; }
}

/* DONE: you can use this function if you want, it's not required that you use it */
int newX(int x, int dir) {
	switch (dir) {
		case 0: // move up
		case 1:
		case 7:
			return wrap(x - 1);
			break; // not reached
		case 3: // move down
		case 4:
		case 5:
			return wrap(x + 1);
			break; // not reached
		case 2: // move left or right
		case 6:
			return x;
	}
	/* NOT REACHED */
	return 0;
}


/* DONE: you can use this function if you want, it's not required that you use it */
int newY(int y, int dir) {
	switch (dir) {
	case 1:
	case 2:
	case 3:
		return wrap(y + 1);
	case 5:
	case 6:
	case 7:
		return wrap(y - 1);
	case 0:
	case 4:
		return y;
	}
	/* NOT REACHED */
	return 0;
}


/* DONE: 
 * Add NUM_FOOD food objects in random locations
 * if you drop food on a bug, be sure to feed the bug
 */
void addFood(void) {
	for (int food = 0; food < NUM_FOOD; food += 1) {
		int x = rand() % WORLD_SIZE;
		int y = rand() % WORLD_SIZE;
		switch (world[x][y]) {
		case EMPTY: // empty, add the food
			world[x][y] = FOOD;
			break;
		case FOOD: // already has food, do nothing
			break;
		default: // bug, feed the bug
			bug_list[world[x][y]].health += EAT_HEALTH;
		}
	}	
	
}

/* TODO... finish this function as described below
 * move bugs 
 * if they move onto food, feed them
 * if they move onto another bug, no big deal.  Two bugs
 * can be in the same square.  Let's say bug#2 and bug #6 are in the same
 * square.  Well, both bugs are still in the bug_list, so they
 * will still be able to move next time step.
 * Since the world[][] array can only hold either a 2 or a 6, we'll just
 * put one of them there.  The easiest thing to do is just put which
 * ever bug moves into the square first into the square.  When the next
 * bug moves into the square, update his x and y (in bug_list) so that
 * he is in the square, leave the other bug alone (i.e., it's also in
 * the same square) and then set world[x][y] = 6 (the bug # of the second
 * bug).  No harm done.  The graphics will draw only the second bug
 * but who cares.  The next time step they'll move into different squares
 * (probably) and no one will notice.
 * NOTE: only the first bug to move into the square gets to eat the food
 * there.
 */
void moveBugs(void) {
	int total_age = 0;
	int total_gen = 0;
	
	/* update each bug in turn (but don't kill them) */
	for (int k = 0; k < bug_list.size(); k += 1) {
		Bug& bug = bug_list[k];

		/* TODO: Move bug k one step foward in its current direction */
		bug.x = newX(bug.x, bug.dir);
		bug.y = newY(bug.y, bug.dir);

		/* TODO: see if we stepped on food! */
		if(world[bug.x][bug.y] == FOOD) {
			bug.health += EAT_HEALTH;
		}

		/* TODO: update the world: NOTE: we may put this bug on top of another one
		 * but that is OK, as long as the other one is in the bug list */
		world[bug.x][bug.y] = k;

		/* TODO: update this bug's health due to movement cost */	
		bug.health -= MOVE_HEALTH;	
		
		/* TODO: pick a new direction for the bug, based on its genes */
		int chance = rand() % GENE_TOTAL;
		int choice = 0;
		int sum = 0;
		for(int i = 0; i< 8; i++) {
			sum += bug.genes[i];
			if(chance < sum) {
				choice = i;
				break;
			}
		}

		bug.dir = (bug.dir + choice)%8;

		/* DONE: update this bug's age for statistics */
		bug_list[k].age += 1;
		total_age += bug_list[k].age;
		total_gen += bug_list[k].generation;
	}

	/* DONE: some statistics... */
	average_age = total_age / bug_list.size();
	average_generation = total_gen / bug_list.size();
}

/* TODO: write this function 
 * look through the bug_list for dead bugs (bugs with zero 
 * health) and kill them
 *
 * To kill a bug, mark it's position in the world as EMPTY
 * then remove it from the bug_list.
 *
 * To remove a bug from the bug_list, use the following simple
 * trick.  Swap the bug with the last bug in the list, then
 * do "pop_back" on the bug_list vector.
 * Hey, since we're going to do pop_back anyway, we don't really
 * need to swap with the last bug.  We just need to copy the 
 * last bug into our position.
 *
 * WATCH OUT: there's a trap.  Be careful to account for the possibility
 * that the "last bug" is also dead.  Don't miss out on killing it
 * because you moved that bug forward in the bug_list
 *
 * Be sure to update the global statistics (total_straight, total_right, total_left and total_back)
 * for each bug that you kill.
 */
void killDeadBugs(void) {
	int index = 0;
	int max = bug_list.size();
	while (index < max) {
		Bug& curr_bug = bug_list[index];
		if(curr_bug.health <= 0) {
			world[curr_bug.x][curr_bug.y] = EMPTY;

			Bug& last_bug = bug_list[max-1];
			
			//swap
			Bug temp = curr_bug;
			curr_bug = last_bug;
			last_bug = temp;

			//update global stats
			total_straight = total_straight - last_bug.genes[0];
			total_right = total_right - last_bug.genes[1] - last_bug.genes[2] - last_bug.genes[3];
			total_left = total_left - last_bug.genes[5] - last_bug.genes[6] - last_bug.genes[7];
			total_back = total_back - last_bug.genes[4];

			bug_list.pop_back();
			max--;
		}
		else {
			index ++;
		}
	}
}

/* TODO: Finish this function 
 * Look at all the bugs in the bug_list.  For each bug
 * that has enough health to reproduce, reproduce a new bug.
 * Put the new bug in the same square and have it head in the
 * same direction.
 *
 * Give both the new bug and the old bug 1/2 the energy of the
 * old bug.
 *
 * Mutate the genes of the new bug as follows.  Choose two genes
 * at random.  Increment one of those genes (by one) and decrement
 * the other gene (by one).
 * YOU MUST ensure 
 * 1. that no genes ever get smaller than zero
 * 2. the total of the eight genes is always GENE_TOTAL
 *
 * Be sure to put the new bug in the bug_list (no need to update
 * the world, since you have two bugs in the same square anyway).
 */
void reproduceBugs(void) {
	int num_bugs = bug_list.size();
	for (int k = 0; k < num_bugs; k += 1) {
		Bug& parent = bug_list[k];

		if (parent.health > REPRODUCE_HEALTH) {

			/* TODO: make "b" a copy of ourself, but with a generation count 1 greater than our own */
			Bug child;
			child.x = parent.x;
			child.y = parent.y;
			child.dir = parent.dir;
			child.generation = parent.generation +1;

			//std::memcpy(child.genes, parent.genes, 8*sizeof(int));
			child.genes[0] = parent.genes[0];
			child.genes[1] = parent.genes[1];
			child.genes[2] = parent.genes[2];
			child.genes[3] = parent.genes[3];
			child.genes[4] = parent.genes[4];
			child.genes[5] = parent.genes[5];
			child.genes[6] = parent.genes[6];
			child.genes[7] = parent.genes[7];

			/* TODO: reduce our health by half and assign b half our health */
			parent.health = parent.health/2;
			child.health = parent.health; 

			/* TODO: mutate Bug b's genes based on the instructions in the handout */
			//inc one random gene
			child.genes[rand() % 8] += 1;
			//dec one random gene that is non-zero
			while(true) {
				int gene_num = rand() % 8;
				if(child.genes[gene_num] != 0) {
					child.genes[gene_num] -= 1;
					break;
				}
			}
			
			/* DONE: update global statistics based on the new genes in b */
			total_straight += child.genes[0];
			total_right += child.genes[1] + child.genes[2] + child.genes[3];
			total_left += child.genes[5] + child.genes[6] + child.genes[7];
			total_back += child.genes[4];

			/* DONE: add b to the global bug list */
			bug_list.push_back(child);
		}
	}	
}

void checkBack(void) {
   uint32_t back = 0;
   for (uint32_t k = 0; k < bug_list.size(); k += 1) {
      back += bug_list[k].genes[4];
   }
   //printf("actualback = %i\n", back);
   //printf("totalback = %i\n", total_back);
   assert(back == total_back);
}

void timeStep() {
	time_step += 1;
	addFood();
	moveBugs();
	killDeadBugs();
	reproduceBugs();
	percent_straight = 100 * total_straight / bug_list.size() / GENE_TOTAL;
	percent_left = 100 * total_left / bug_list.size() / GENE_TOTAL;
	percent_right = 100 * total_right / bug_list.size() / GENE_TOTAL;
	percent_back = 100 * total_back / bug_list.size() / GENE_TOTAL;

	checkBack();
}	
