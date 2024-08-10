# Application:
- ### Lexicographically smallest path:
  - DFS can used to find the lexicographically smallest path from source to dest node. While visiting neighbors of each node u, just process in lexicographical order.
- ### Check if a is ancestor of b in Tree: (Balanced Parenthesization property of DFS) 
  - #### Given a ***Tree*** and ***Root***
  - #### Query: given 2 nodes a and b, check if a is ancestor of b in O(1) time
  - Solution is: preprocess the graph: Run DFS from the root node
  - Calculate `startTime[u]` and `finishTime[u]` for each node
  - In a tree, if we do DFS from root, vertex a is ancestor of vertex b, ***if and only if***:
    - `startTime[a] < starTime[b]` and `finishTime[a] > finishTime[b]`
      
- ### Find bridges in an undirected graph: [TODO]
  - First convert the given graph into a directed graph by running a series of depth first searches and making each edge directed as we go through it, in the direction we went.
  - Second, find the strongly connected components in this directed graph.
  - Bridges are the edges whose ends belong to different strongly connected components
