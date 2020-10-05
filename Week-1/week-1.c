/* 
 *
 * computer adds numbers using ripple carry adder using logic gates
 * and adds recursively columnwise
 *
 * Efficiency of algorithms:
 * 	depends on the size of the input
 * 	bigger input also need more space
 * 	How the time/space requirements of the algorithm scale with the input
 * 	
 * Correctness of algorithms:
 * 	algorithm rturns the desired output every time, for every possible 
 * 	(legal) input
 * 	proving and algorithm is incorrect is easier than proving it is correct
 *
 *
 *
 * Classification of algorithms:
 * 	By Task:
 * 		Numeric
 * 		Sorting
 * 		Searching
 * 		Routing (path finding, graphs)
 *
 * 	By Approach:
 * 		Brute Force (slow)
 * 		Divide and Conquer (faster)
 * 		Decrease and Conquer (fastest)
 * 		Greedy
 *
 * 	By Solution Type:
 * 		Exact
 * 		Approximate (solutions within the error tolerance)
 * 		Heuristic (arent approaching in the ideal fashion 
 * 				but gets a pretty good result, they are very fast)
 *
 *
 *	 
 * Efficiency:
 * 	Particularly interested in how the algorithms efficiency changes as the s
 * 	ize of the input grows, e.g. massive databases, internet scale applicatio
 * 	ns, high resolution images, high frame rates etc.
 *
 *
 */


/* improving the efficiency of the fibonacci algorithm using memoisation */

#include<stdio.h>


/* using recursion */

int fib(int n) {
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;

	else {
		return fib(n-1) + fib(n-2);
	}
}

/* using memoisation */

int fib(int n) {
	int i;
	int fib[n+1];
	fib[0] = 0;
	fib[1] = 1;
	for(i = 2; i<= n; i++) {
		fib[i] = fib[i-1] + fib[i-2];
	}
	return fib[n];
}
 
/* this code takes less time but more space in memory space complexity = O(n+1) */


/* Let's make it MORE efficient, by storing only the last two numbers. Works for 
 * when you only want the final result */

int fib(int n) {
	int result = 0;
	int preOldResult = 1;
	int oldResult = 1;
	if(n <= 0) return 0;
	if(n > 0 && n < 3) return 1;
	for(int i = 3; i <= n; i++) {
		result = preOldResult + oldResult;
		preOldResult = oldResult;
		oldResult = result;
	}
	return result;
}

/* Here we are assuming that adding two number takes the same amount of time 
 * everytime (true when the number < 2^32)
 * to store a fibonacci number it take Fn = 0.694*n bits */


/*
 * best ways to calculate efficiency:
 * 	calculate operations not time
 * 	look for the most expensive operations
 * 	always be aware of the assumptions
 */

 
