# Applications:
- ### State space search
- ### 0/1 - 1/K BFS
- ### Find shortest cycle from a given source node (in unweighted graph):
  - From that source, start BFS until encountering a node u which has neighbor = source node
  - Finding shortest cycle in a graph:
    - from each vertex do BFS
    - Time complexity = O((E + V)^2)
- ### Find all the vertices on any (all) shortest path between a given pair of vertices (a, b): [Very Hot]
  - Do BFS twice:
    - Do BFS from a. let, `da[u]` = shortest distance from a to u for each node.
    - Do BFS from b in the ***transpose graph***. let, `db[u]` = shortest distance from b to u for each node.
    - Now in the original graph, for each node u, check if u falls on a shortest path from a and b. The condition is:
      ```
      da[u] + db[u] = da[b]
      ```
  - ***For Weighted Graph***:
    - just do Dijkstra isntead of BFS man!
- ### **State Space Search Application:** Find the shortest path of even length in unweighted graph (Dijkstra for weighted graph):
  - Create a state space search graph:
  - Where, one node of original graph can map to max of 2 nodes of state space search graph.
  - Node u will be mapped to (u, true) if u is reached via even number of nodes from source, else (u, false.
  - Source node: (source, true) and dest: (dest, true).
    
