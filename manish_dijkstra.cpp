
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <cctype>

using namespace std;

int getNodeIndex(char input) {
    input = toupper(input);
    return isdigit(input) ? input - '0' : (input >= 'A' && input <= 'E' ? input - 'A' : -1);
}

int getMinDistanceVertex(const vector<int>& distances, const set<int>& visited) {
    int minIndex = -1, minDistance = INT_MAX;
    for (int i = 0; i < distances.size(); i++) {
        if (visited.find(i) == visited.end() && distances[i] < minDistance) {
            minDistance = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void displayPath(const vector<int>& distances, const vector<int>& previous, int start, int end) {
    cout << "Shortest path from " << start << " to " << end << ": ";
    vector<int> path;
    for (int at = end; at != -1; at = previous[at]) {
        path.insert(path.begin(), at);
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << (i > 0 ? " -> " : "") << path[i];
    }
    cout << "\nTotal distance: " << distances[end] << endl;
}

void dijkstraAlgorithm(const vector<vector<pair<int, int>>>& graph, int start, int end) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX), previous(n, -1);
    set<int> visited;
    distances[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = getMinDistanceVertex(distances, visited);
        if (u == -1) break;
        visited.insert(u);

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first, weight = neighbor.second;
            if (visited.find(v) == visited.end() && distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
            }
        }
    }

    displayPath(distances, previous, start, end);
}

int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 10}, {4, 3}},
        {{2, 2}, {0, 10}, {3, 4}, {4, 1}},
        {{1, 2}, {3, 9}, {4, 8}},
        {{1, 4}, {2, 9}, {4, 2}},
        {{0, 3}, {1, 1}, {2, 8}, {3, 2}}
    };

    string input;
    int start, end;

    cout << "Please input the starting node: (A=0, B=1, C=2, D=3, E=4): ";
    cin >> input;
    start = getNodeIndex(input[0]);

    cout << "Please input the destination node: (A=0, B=1, C=2, D=3, E=4): ";
    cin >> input;
    end = getNodeIndex(input[0]);

    if (start == -1 || end == -1 || start >= graph.size() || end >= graph.size()) {
        cout << "Invalid input. Please use values between A and E." << endl;
        return 1;
    }

    dijkstraAlgorithm(graph, start, end);

    return 0;
}
