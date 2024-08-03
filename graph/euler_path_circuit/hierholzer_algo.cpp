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
