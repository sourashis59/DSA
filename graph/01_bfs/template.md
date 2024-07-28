# 0-1 BFS
- If edge weights are 0 or 1, then 0-1 BFS can be used instead of Dijkstra algorithm.
- Time complexity of 0-1 BFS = `O(V + E)`

## Dijsktra algorithm [Time = `O(E * logV)`]
```
dijkstra(source, target) {
  for (each u):
    dist[u] = INT_MAX,
    visited[u] = false // visited is optional for dijktra, but improves performance

  // contains {node, min distance from source to node}
  priority_queue q;
  q.push(source, 0);

  while (q.size()) {
    u = q.pop();
    visited[u] = true;
    for (v: adj[u]) {
      if (visited[v]) continue;
      if (dist[u] + weight(u, v) < dist[v]) {
        dist[v] = dist[u] + weight(u, v);
        q.push({v, dist[v]});
      }
    }
  }
  return dist;
}
```


## 0-1 BFS: [Time = `O(E+V)`]
### Changes:
- priority_queue --> deque
- while inserting into queue, if weight is 0, insert in front, else if weight is 1, insert in back

 ```
shortest_dist(source, target) {
  for (each u):
    dist[u] = INT_MAX,
    visited[u] = false // visited is optional for dijktra, but improves performance

  // contains {node, min distance from source to node}
  //------------------------------CHANGE------------------------------
  deque q;
  //------------------------------CHANGE------------------------------
  q.push(source, 0);

  while (q.size()) {
    //------------------------------CHANGE------------------------------
    u = q.pop_front();
    //------------------------------CHANGE------------------------------
    visited[u] = true;
    for (v: adj[u]) {
      if (visited[v]) continue;
      if (dist[u] + weight(u, v) < dist[v]) {
        dist[v] = dist[u] + weight(u, v);
        //------------------------------CHANGE------------------------------
        if (w == 0) q.push_front(v);
        else /*if (w == 1)*/q.push_back(v);
        //------------------------------CHANGE------------------------------  
      }
    }
  }
  return dist;
}
```

### Time complexity proof:
- Each node can be enqueued atmost twice.
- Because for all node we start with dist[v] = INT_MAX
- And we insert a node v into q, if we find a better path than the previous one [i.e., we find shorter dist from source to v, than current dist[v]]
- dist[v] can become INT_MAX --> 1 --> 0 [so at most 2 times dist[v] can change]

