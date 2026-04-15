#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge {
    int to;
    int weight;
};

struct Node {
    int id;
    long long dist;

    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

void dijkstra(int n, int startNode, int endNode, const vector<vector<Edge>>& adj) {
    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[startNode] = 0;
    pq.push({startNode, 0});

    while (!pq.empty()) {
        int u = pq.top().id;
        long long d = pq.top().dist;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == endNode) break;

        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                parent[edge.to] = u;
                pq.push({edge.to, dist[edge.to]});
            }
        }
    }

    if (dist[endNode] == INF) {
        cout << "NO_PATH" << endl;
    } else {
        vector<int> path;
        for (int v = endNode; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "DISTANCE " << dist[endNode] << endl;
        cout << "PATH";
        for (int i = 0; i < path.size(); ++i) {
            cout << " " << path[i];
        }
        cout << endl;
    }
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= 0 && u < n && v >= 0 && v < n) {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // Undirected graph for traffic navigation
        }
    }

    int startNode, endNode;
    while (cin >> startNode >> endNode) {
        if (startNode == -1) break;
        dijkstra(n, startNode, endNode, adj);
    }

    return 0;
}
