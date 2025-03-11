#include "dijkstras.h"
#include <algorithm>

struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}
    bool operator>(const Node& other) const {
        return weight > other.weight; // Min-heap comparison
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distance[source] = 0;
    
    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst, weight = neighbor.weight;
            
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    
    if (path.size() == 1 && path[0] != destination) {
        return {}; // No valid path exists
    }
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << path[i];
    }
    cout << " \nTotal cost is " << total << endl;
}


