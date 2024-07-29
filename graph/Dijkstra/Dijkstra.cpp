class Solution
{
public: 
  struct myPair {
      int node;
      long long d;
  };
  
  class cmp {
  public:
      bool operator()(const myPair& a, const myPair& b) {
          if (a.d != b.d) a.d > b.d;
          return a.node < b.node;
      }
  };
  
  //Function to find the shortest distance of all the vertices
  //from the source vertex S.
  vector <int> dijkstra(int V, vector<vector<int>> adj[], int s)
  {
      // Code here
      vector<int> d(V, INT_MAX);
      d[s] = 0;
      vector<bool> visited(V, false);
      
      priority_queue<myPair, vector<myPair>, cmp> q;
      q.push({ s, d[s] });
  
      while (!q.empty()) {
          myPair u = q.top();
          q.pop();
          //* optional: but good for performance
          if (visited[u.node])
              continue;
              
          visited[u.node] = true;
          for (const auto& ele : adj[u.node]) {
              int v = ele[0];
              int w = ele[1];
              // optional: but good for performance
              if(visited[v]) 
                continue;
                  
              if ( d[u.node] + w < d[v]) {
                  d[v] = d[u.node] + w;
                  q.push({ v, d[v] });
              }
          }
      }
      return d;
  }
    
  
};
