import sys
import collections

speedup_map = {}

def answer(n) :
	if (n == 0):
		# special case. Since recurse(0) == 1 and we want answer(0) == 0
		return 0
	else:
		# initialize map to speed up recursion
		global speedup_map
		speedup_map = {}

		# we must have stairs of 2 steps 
		# so we manually modify the 1st recursion lvl 
		# do not grab n, since the next lvl will only have 1 path [a grab 0] thsi will return 1
		# whcih means we counted the stair case that looks like [n,0,0,0...]
		count = 0
		for i in range(0, n):
			count += recurse(n, i)
			#speedup_map[n] = count
		return count



def recurse(n, grab) :
	new_n = n - grab
	if (new_n == 0): # base case. we found a solution. We used all our bricks.
		return 1
	elif (new_n > 0 and grab == 0): # base case. not a solution. There are no more legal grabs and we still have bricks left
		return 0
	elif (str(n)+","+str(grab) in speedup_map): # check if recurse(n) was calculated before
		return speedup_map[str(n)+","+str(grab)]

	else:
		count = 0
		max_next_grab = min(new_n, grab -1); # the next grabs must be LESS THAN the previous grab

		for i in range(1, max_next_grab +1): # Try grabbing some bricks. If max_next_grab ==1, then we do not recurse. it will return 0
			count += recurse(new_n, i)

		speedup_map[str(n)+","+str(grab)] = count
		return count