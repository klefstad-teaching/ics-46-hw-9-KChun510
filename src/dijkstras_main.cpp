#include  "dijkstras.h"

int main() {
    Graph G;
    string filename = "small.txt";
    file_to_graph(filename, G);
    
    int source, destination;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter destination vertex: ";
    cin >> destination;
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);
    
    return 0;
}

