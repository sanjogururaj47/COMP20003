/* EFFICIENCY:
 *
 * Why we ignore the lower order growth in the Big O notation
 * 	its due to the fact that we are interested only in the larger input case
 * 	They always cross at some threshold value of n (num of inputs)
 *
 *
 * Some classes of complexity
 * 	
 * 	1 - Constant time operation, doesnt depend on n (initialising a variable)
 * 	logn - Binary search
 * 	n - Looping through n items
 * 	nlogn - Efficient sorting algorithms
 * 	n^2 - Pairwise comparisons within loops
 * 	2^n - all possible subsets
 * 	n! - all possible permutations
 *
 *
 * big O is upper bound (closest upper bound):
 * 	eg O(n^2) is in O(n^3)
 *
 * big-Omega is lower bound:
 * 	To check we flip it around and perform the Big O analysis 
 * 	eg Omega(n^2) in Omega(n^3)
 * 	1. flip it aroung
 * 		is n^3 in O(n^2) --> NO
 * 	thus Omega(n^2) is not in Omega(n^3) or n^3 is not a lower bound of n^2
 *
 * Big-Theta is tight-bound
 * 	f(n) is Theta(g(n)) when:
 * 		f(n) is O(g(n)) and Omega(g(n))
 * 	eg check if T(n) = 2n^2 + 4 in Theta(n^2)
 * 		
 * 		first check for Big O:
 * 			is T(n) < c*(g(n)) for all n > N0
 * 			yes since 2n^2 + 4 < 6n^2
 *
 * 		second, check for Omega(n):
 * 			reverse big O and check
 * 			is n^2 < c*(2n^2 + 4) for all n > N0
 * 			yes since n^2 < 1*(2n^2 + 4)
 *
 * 		Thus we can say that T(n) is in Theta()
 *
 * Why complexity:
 * 	helps us describe how problems grow with the size of the input
 * 		mostly interestes in the asymptotic behaviour
 * 		big-O notation is the main tool we use to classify performance
 */

/* 
 * DATA STRUCTURES
 * 	
 * Abstract data types:
 * 	Describes what it does, but does not specify an implementation
 * 	eg stacks, queues, dictionaries
 *
 * Concrete Data structures:
 * 	Implements an abstract data type
 * 		arrays, linked lists, trees
 *
 * // random access storages are called so since we can access any part of the memory with
 * constant time complexity, not true for storages such as CDs or tapes
 * 
 *
 * COMPLEXITY:
 * 	
 * 	log10(n) = log2(N)*log10(2);
 *
 * 	 t(n) = log10(n) has the same complexity as t(n) = log2(n)
 * 	 t(n) = 4^n and t(n) = 2^n does NOT have the same complexity
 * 	 
 *
 * 	 If a program is in stages:
 * 	 	stage 1 = O(m) and stage 2 = O(n) then,
 * 	 	the complexity is O(m+n)
 * 	 	similarly O(m)*O(n) = O(m*n)
 *
 * 	 	
 * WHEN YOU HAVE AN ARRAY OF POINTER YOU HAVE TO FIRST FREE THE INDIVIDUAL INDEXES
 * 	eg: int **c;
 * 		free c[i] before free(c) // important to do both, because you would lose access to 
 * 		c[i] when you free xc 
