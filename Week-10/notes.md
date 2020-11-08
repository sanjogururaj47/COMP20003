# MORE GRAPH TRAVERSALS, ALL PAIRS SHORTEST PATH
---
## DFS

```

/* pseudo code for DFS over an Adjacency list */

visited[k] = ++ order;
for(t = adj[k]; t!= NULL; t = t->next) {
	if(!visited[t->v])
		visitDFS(t->v);
}
```

### DFS analysis
- finds connected components
- Complexity: $|V| + |E|$

---

## BFS  


```

int visited[V]; int order = 0;

void visitBFS(int k) {
	struct node *t;
	enQ(Q, k);
	while(!Qempty(Q)) {
		k = deQ(Q);
		if(!visited[k]) {
			visited[k] = ++order;
			for(t = adj[k]; t != NULL; t->next) {
				if(!visited[t->num])
					enQ(Qt->num); 
			}
		}
	}
}
```

- BFS doesnt account for the weights of the egdes. Thus, it doesnt always give the shortest path from one node to the other.

---

## SHORTEST PATH

- Computing shorted path using brute-force
	- complexity: $O(V!)$
	- Not feasible!

---
	
### Single Source Shortest Path. 

#### DIJKSTRA'S

- Similar to BFS but with a priority queue.
- Length of the path is the sum of the edges along the way.

##### Theory

- Any subpath along a shortest path is also a shortest path.
	- e.g. if there is a shortest path between Melbourne and Brisbane is through Sydney, then the same path to travel to Sydney from Melbourne is also the shortest one.

- Does not work for negativve edges, because the above assumption fails.

![Image of dijsktra's](Scrots/Dijkstra's.jpg)



- Code for relaxation:

```

void update_relax(u,v) {
	
	if(dist[u] + edgeweight(u,v) < dist[v]) {
		dist[v] = dist[u] + edgeweight(u,v);
		pred[v] = u;
	}
}
```

- Picking the next node
	- Process the vertices in order of estimated closeness to source, value of dist[v].
	- Create a priority queue to store vertex v and dist[v].

```

/* pseudo code for the whole dikstra's algorithm */

void dijkstra's(int **G, int s) {
	int dist[Vsize], pred[Vsize];
	
	inititalize(G< s, pred, dist);
	
	run(G, s, pred, dist);
	
	reconstruct(s, pred, dist);
}


void initialise(int **G, int Vsize, int s, int *pred, int *dist) {

	int i;
	
	/* initialise all the distances to infinity */
	for(i = 0; i < Vsize; i++)
		dist[i] = MAX_INT;
	
	dist[s] = 0;
	
	for(i = 0l i < Vl i++)
		pred[i] = NULL;

}


void run(int **G, int Vsize, int s, int *pred, int *dist) {
	
	pq_node_t *pq;
	int u, v;
	
	/* vertices into min priority, dist as priority */
	pq = makePQ(G);
	
	while(!emptyQ(pq)) {
	
		/* delete the min vertex according to the distance */
		u = deletemin(pq);
		
		/* Vertex u has been processed, shorted path to u found
		
		for (/* each v connected to u. */) {
			if(dust[u] + edgeweight(u,v) < dist[v]) 
				update(v, pred, dist, pq);
		}
	}
}


void update(int vm int *pred int *dist, pq_node_t * pq) {
	
	dist[v] = dist[u] + edgeweight(u,v);
	pred[v] = u;
	decreaseweight(pq, v, dist[v]);
}



void reconstruct(int s, int *pred, int *dist) {
	
}


```

> BFS (un-weighted graph) == Dijkstra's

##### Complexity analysis

- Complexity = C_building_pq + updating + deleting_fixing_heap + for_loop
	- C_building_pq = $O(|V|)$
	- deleting_fixing_heap = $O(logv)$
	- for_loop = out_degree(v) * v = E
	- updating = $O(logv)$

- It is important to note the type of data structures we used to implement the algorithm, the complexity for the heap data structure = $$O((V+E)*logv)$$


##### Limitations

- Assumes no negative edges
	- Distances are static
	- Good for physical distances

- Use bellman-ford for negative edges
	- Cannot deal with negative cycles
	- $O(V*E)$

---

### All pairs shortest path. 

#### Warshall's

- Transitive closure

```

for(i = 0; i < V; i++) {
	for(s = 0; s < V; s++) {
		for(t = 0; t < V; t++) {
			if(A[s][i] && A[i][t])
				A[s][t] = TRUE;
		}
	}
}
```

- This works regardless of the order we consider the intermediate vertices, since we have three loops which checks all the points in the matrix.
- This algorithm is not greedy, it is exhaustive.

![Image of warshall's](Scrots/warshall.jpg)


#### Floyd-Warshall's algorithm

- Used for dense graphs
- Helps to find bottlenecks in networks (interview questions)
	- No Edge = $-\infty$
	- Edge = Flow Capacity
	- Run floyd-warshall and keep track of the largest flow-capacity

```

/* note: A[i][i] = 0, A[u][v] = w(u,v), no-path = 0 */

for(i = 0; i < V; i++) {
	for(s = 0; s < V; s++) {
		for(t = 0; t < V; t++) {
			if(A[s][i] + A[i][t] < A[s][t])
				A[s][t] = A[s][i] + A[i][t];
		}
	}
}
```

- Complexity = $$O(n^3)$$
- The algorithm only yields the shortest-distance (numerical value), and not the whole path.
- To find the path, maintain a succcessor matrix