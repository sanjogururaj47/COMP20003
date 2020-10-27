# MERGE SORT AND THE MASTER THEOREM
## MERGE SORT
### Bottom up appraoch
- Break list into n singleton lists
- Instert single lists into a queue
- deQueue the first two items, merge them and enQueue them.
 ![Image of bottom-up illustration]
 (Scrots/merge_sort.jpg) 
- The way we insert the items into the Queue alters the stability of the sort


## MASTER THEOREM
- $T(n) =  aT(n/b) + f(n)$
- size of the subproblems decreases by b
	- base case reached after $log_b(n)$
- At the kth level we would have $a^k$ problems
- At the kth level, total work done is: $a^k*O(n/b^k)^d = O(n^d)*(a/b^d)^K$
- As k increases from $0 - log_b(n)$, we get a geometric series representing how the amount of work done increases $\sum O(n^d)*(a/b^d)^K$
![Image of complexity in the master theorem analysis]
(Scrots/complexity.jpg)
![Image of complexity in the master theorem analysis]
(Scrots/complexity2.jpg)
![Image of complexity in the master theorem analysis]
(Scrots/complexity3.jpg)
