# PRIORITY QUEUES AND HEAPS
---
## INTRODUCTION TO PRIORITY QUEUES

- They are queues sorted based on a given priority
	- e.g. healthcare, airports

### Simple implementation
- Construct the queue
- Get the highest priority

### Complexity
1. For Unsorted arrays
 - Construction: $O(n)$
 - Getting the highest priority: $O(n)$
2. For Sorted arrays
 - Construction: $O(n^2)$
 - Getting the highest priority: $O(1)$
3. Unsorted list
 - Construction: $O(n)$
 - Getting the highest priority: $O(n)$ 
4. Sorted list
 - Construction: $O(n^2)$
 - Getting the highest priority: $O(1)$


## INTRODUCTION TO HEAP
---
- A complete tree
	- All nodes are full and only empty on the last level of the tree on the right hand side.
- Every node should satisfy the "heap condition":
	- parent->key >= child->key
	- Thus the root is the maximum value in the array

![Image of heap as an array](Scrots/heaparray.jpg)

- It can be seen that the index starts at one, since the formula would not make sense otherwise
- Thus the only condition we have to check when implementing the code is
	- A[i] >= A[2*i] && A[i] >= A[2*i + 1]

### CHARACTERISTICS OF HEAPS
- The leaf starts somewhere in the middle of the array
- The last layer takes half the space of all the other layers


### OPERATIONS ON HEAPS
1. deletemax(): 
	- Delete the highest element in the heap (root)
	- Complexity: $O(logn)$
2. fixheap(): 
	- Put the last item into the root position
	- Reduce the size of heap (priority queue) by one
	- fixheap condition for root using downheap()
3. downheap():
	- Replace the new root (last element) with the greater child (maximum child)
	- Complexity: $O(logn)$
![Image of down heap](Scrots/fixheap_downheap.jpg)

```

downheap(int[] PQ, int k) {

	int j,v;
	v = PQ[k]; /* value that we move to the root */
	while(k< n/2) {
		/* point to children */
		j = k*2; /* left child */
		
		/* change to right child if it is greater than the left child */
		if(j<n && PQ[j] < PQ[j+1]) j++;
		
		/* check if the element is greater than child, break if true */
		if(v >= PQ[j]) break;
		
		PQ[k] = PQ[j];
		k = j;
	}
	/* final position of original A[k] val */
	PQ[k] = v;
}

```
![Image of the code for downheap](Scrots/downheapcode.jpg)


```

int deletemax(int[] PQ) {

	int v = PQ[1];
	PQ[1] = PQ[n--];
	downheap(1);
	return(v);
}
```


4. Inserting into the heap with upheap()
	- We insert from the right-most leaf and go up
	- We go up by checking if each of the parents are smaller than the inserted element.
	- Complexity: $O(logn)$
	
```

/* k points to the last slot (right-most leaf) */
void upheap(int *PQ, int k) {
	
	/* value to be inserted */
	int v;
	v = PQ[k];
	PQ[0] = INT_MAX;
	
	/* after insertion check if the parent is bigger than the element */
	/* access the parent by PQ[k/2](rounded down), and swap if parent is smaller */
	while(PQ[k/2] <= v) {
		PQ[k] = PQ[k/2];
		k = k/2;
	}
	PQ[k] = v;
}
```

#### HEAPSORT
- construct the heap
- swap root (max) with last element
- Remove last element from further consideration, decrease the size of the heap by 1.
- fix heap
- repeat
- so the idea is that as we keep fixing the heap, we keep obtaining the maximum element and hence sorting the data
- complexity: fix heap (Ologn) n times thus = $O(nlogn)$
	- we also need to ensure that the complexity for construction is at mazimum $O(nlogn)$

##### Building the heap
###### Stratergy 1:
1. Insert one-by-one into the array
2. upheap() sa each new item is inserted
	- complexity: 
		- Each insertion = $O(logn)$
		- but for m insertions complexity: $O(mlogn)$

	
###### Stratergy 2:
1. Insert items into unsorted array
2. Once all are insertion, downheap() for each subheap with roots from A[n/2] to A[1], since the rest of the them are leaves. (We dont need to downheap for the last row which has n/2 elements)
3. Complexity:
	- Insertion into unsorted array: $O(n)$
	- then downheap from A[n/2] to A[1]: $O(logn)$ but $\theta(m)$

![image of complexity analysis for heap generation](Scrots/Heapcreatingcomplexity.jpg)
![image of complexity analysis for heap generation](Scrots/heapcomplexity.jpg)
![image of complexity analysis for heap generation](Scrots/heapcomplexity2.jpg)


### Applications

![Applications of heaps](Scrots/Application.jpg)

	