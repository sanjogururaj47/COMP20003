
/* SORTIN MATE */

/* Introduction:
 * 	
 * 	Non comparison sorting: distributed counting
 * 	
 * 	Comparision Sorting:
 * 		Selecttion: select the smallest element in the sub array and swap it with the
 * 		current element.
 */

/* selection sort */

void selection_sort(item *A, int n) {
	int i, j, min;
	for(i = 0; i < n-1; i++) {
		min = j;
		for(j = i+1; j< n; j++) {
			if(A[j] < A[min]) min = j;
		}
		swap(A[i], A[min]);
	}
}

/* analysis:
 * 	complexity = O(n^2)
 * 	But it uses relatively few swaps
 * 	usefuyl when moving items in memory is expensive
 */




/* insertion sort:
 * 	 Start from the second element, keep moving it left if the previous element is smaller
 */

void insertion_sort(item *A, int n) {
	int i, j, val;
	for(i = 1; i<n; i++) {
		val = A[i];
		j = i;
		while(A[j-1] > val && j != 0) {
			A[j] = A[j-1];
			j--;
		}
		A[j] = val;
	}
}

/* analysis:
 * 	Time complexity: O(n^2)
 * 	but we would use this is since it outperforms more efficient algorithms in the case of 
 * 	very small n
 */




/* Divide and Conquer */

/* divide the problem into smaller problems, solve them and combine them.
 * 	
 * 	QUICK SORT:
 * 		1. Choose a pivot randomly
 * 		2. Move the items less than the pivot to the left of the array and the items greater
 * 			than the pivot to the left of the array.
 * 		3. And the pivot goes between the set.
 * 		4. Now recurse of the halfs, until you get to the base case, which is if you have a 
 * 			single item in the subarray.
 */

void quick_sort(item A[], int l, int r) {
	int i;
	if(r <= 1) return;
	// find the position of the pivot
	i = partition(A, l, r);

	quick_sort(A, l, i - 1);
	quick_sort(A,i+1, r);
}


int partition(item A[], int l, int r) {
	int i = l-1, j = r;
	item v = A[r];
	while(l) {
		while(less(A[++i], v) /* do nothing */;
		while(less(v, A[--j]) /* do nothing */;
		if(i>=j) break;
		swap(A[i], A[j]);
	}
	swap(A[i], A[r]);
	return i;
}

/* analysis:
 * 	Divide and conquer approach to solve
 * 	Split-Solve-Join
 *
 * 	Advantages:
 * 		Good average case complexity: O(logn)
 * 		In-place sort, no extra space required
 * 	Disadvantages:
 * 		Worst case complexity: O(n^2) (might pick the smallest item as the pivot)
 * 		Requires random access
 */


/* usually divide and conquer algorithms have a complexity of O(logn) */


/* QUICK POINTS FOR SORTING */
/* selection is unstable, insertion is stable, selection sort is an in-place sort.
 * Selection: Best-O(n^2), Average-O(n^2), Worst-O(n^2)
 * Insertion: Best-O(n), Average-O(n^2), Worst-O(n^2)
 * Quicksort: Best-O(nlogn), Average-O(nlogn), Worst-O(n^2)
 *
 */








/* Mergesort */


/* two lists that are sorted, we have two pointers pointing to the first element of each of the 
 * arrays.
 * We compare the two pointers and put the smaller element in the first index of the new bigger 
 * array with size size(arr1) + size(arr2).
 * Then we move the pointer to the next element in the array whose first element was smaller.
 *
 *
 * Producing the sub arrays
 * 	- Split the array into two subarrays
 * 	- Split the subarrays until there is only one element in the array (which is by definition
 * 		sorted)
 * 	- Then compare the two arrays which have only one element and put the smaller element in 
 * 		a new array.
 * 	- Do the same for the other subarray.
 * 	- Now we have two sorted subarrays, we repeat this process for the bigger subarrays and 
 * 		generate new sorted array.
 * Analysis:
 * 	- the merge sort algorithm is analogous to a binary tree
 * 	- thus the number of comparisons we need is logn*num_elements thus the algorithms is an
 * 		O(nlogn) algorithm.
 */

/* merge with indexing and arrays */
void merge(item sorted[], item A[], item B[], int size_a, int size_b) {

	int i,j,k;

	for(i = 0, j = 0, k = 0; k < n+m; k++) {

		if(i == size_a) sorted[k] = B[j++]; continue;
		if(j == size_b) sorted[k] = A[i++]; continue;

		if(A[i] <= B[j]) sorted[k] = A[i++];
		else sorted[k] = B[j++];
	}
}

/* mergesort: topdown (recursive) */

int[] mergesort(item unsorted[], int first, int last) {

	/* base case */
	if(first < last) {
		int i;

		/* auxilary arrays */
		item B[], C[];

		/* find the middle index */
		int mid = (int)(last - first + 1)/2;
		for(i = 0; i < mid; i++) B[i] = unsorted[i];
		for(i = mid; i <= last; i++) C[i-mid] = unsorted[i];

		/* recurse */
		B = mergesort(B, 0, mid - 1);
		C = mergesort(C, 0, mid - 1);

		/* combine */
		unsorted = merge(B,C);
	}
	return unsorted;
}

/* Analysis:
 * 	- better than quicksort since it doesnt need random access, thus it works well with linked
 * 		lists
 * 	- Stable algorithm
 * 	- Worst case complexity O(nlogn)
 * 	- Average case O(nlogn)
 * 	- Can be used to sort huge files on disk (not RAM).
 * 	- Arrays require O(n) extra space
 * 	- If RAM is available then use quick sort since it is quicker.
 */


