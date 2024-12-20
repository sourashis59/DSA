# Condition for Euler path:
### Definitions:
- Euler Path: Path in graph which covers all edges
- Euler Circuit: Cycle in graph which covers all edges
- Euler Circuit is also and Euler Path

### Conditions:
- For Circuit, all nodes should be connected

|  | ***Euler Circuit*** | ***Euler path*** |
|----------|----------|----------|
| ***Undirected graph*** | Every vertex has even degree | Either Euler Circuit exists, or exactly two vertices have odd degree |
| ***Directed graph*** | Every vertex has equal indegree and outdegree | Either Euler Circuit exists, or one vertex has (outdeg = indeg + 1) and one vertex has (indeg = outdeg + 1) and all other vertices have equal in and out degree |

- In Euler path for directed graph, the node with (outdeg = indeg + 1) is the starting node of the Euler Path, and the node with (indeg = outdeg + 1) is the ending node.


# Find one Euler Path:
## Hierholzer Algorithm: 
### Edges in Euler Path = edges in Postorder DFS  
```
dfs(e) {
  remove edge e from graph

  // let, e = u->v
  // neighbor edge ne = v->w [for each w: adj[v]]
  for (each neighbor edge ne)
    dfs(ne);

  res.push_back(e); 
}

findEulerPath() {
  u = find starting node for Euler path
  dfs(dummyNode->u)
  reverse(res)
  return res
}
```

### Implementation:
```
vector<vector<int>> adj;    
vector<int> res;

void dfs(int v) {
    while (adj[v].size()) {
        int w = adj[v].back();
        adj[v].pop_back();
        dfs(w);
    }
    res.push_back(v);
}

vector<int> findEulerPath(vector<vector<int>> &adj) {
  this->adj = adj;
  res = vector<int>();

  // find the indegree and outdegree for each node
  // source node, s = node with one more out degree than indegree [if Euler path exists but circuit does not exist]
  //                  or, any node, if all nodes have  equal indegree and outdegree [if Euler circuit exists]
  // If neither Euler path nor circuit exists, then not possible, return error
  int s = ..... find source of Euler path .......
  dfs(s);
  reverse(res.begin(), res.end());
  return res;
}

```
