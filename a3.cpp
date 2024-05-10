#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<string, int> cityToIndex; // Map city names to unique indices
    vector<vector<pair<int, int>>> adj;     // Adjacency list of pairs (neighbor index, edge weight)
    int vertices;

    Graph(int v)
    {
        this->vertices = v;
        adj.resize(v);
    }

    // Add an edge between two cities with a given weight
    void addedge(string u, string v, int w)
    {
        int index_u = getIndex(u);
        int index_v = getIndex(v);
        adj[index_u].push_back({index_v, w});
        adj[index_v].push_back({index_u, w});
    }

    // Helper function to get index of a city, assigning a new index if not already present
    int getIndex(string city)
    {
        if (cityToIndex.find(city) == cityToIndex.end())
        {
            int newIndex = cityToIndex.size(); // Assign a new index
            cityToIndex[city] = newIndex;
        }
        return cityToIndex[city];
    }

    // Dijkstra's algorithm to find shortest paths from a source city
    vector<int> dijkstra(string source)
    {
        int sourceIndex = getIndex(source);
        vector<int> dist(vertices, INT_MAX);
        set<pair<int, int>> st;//pair<weight,vertices>
        st.insert({0, sourceIndex});
        dist[sourceIndex] = 0;

        while (!st.empty())
        {
            auto top = *(st.begin());
            int nodedist = top.first;
            int node = top.second;
            st.erase(st.begin());

            for (auto it : adj[node])
            {
                int neighbor = it.first;
                int weight = it.second;
                if (nodedist + weight < dist[neighbor])
                {
                    auto ispresent = st.find({dist[neighbor], neighbor});
                    if (ispresent != st.end())
                    {
                        st.erase(ispresent);
                    }
                    dist[neighbor] = nodedist + weight;
                    st.insert({dist[neighbor], neighbor});
                }
            }
        }
        return dist;
    }
};

int main()
{
    cout << "Enter total number of cities: " << endl;
    int n;
    cin >> n;

    Graph g(n);

    cout << "Enter connections between cities (source destination weight):" << endl;
    for (int i = 0; i < n; i++)
    {
        string u, v;
        int w;
        cout << "Enter source city: ";
        cin >> u;
        cout << "Enter destination city: ";
        cin >> v;
        cout << "Enter the distance between " << u << " and " << v << ": ";
        cin >> w;
        g.addedge(u, v, w);
    }

    cout << "\nEnter the source city: " << endl;
    string source;
    cin >> source;

    vector<int> ans = g.dijkstra(source);

    cout << "\nShortest distances from " << source << " to all other cities:" << endl;
    for (auto cityDist : g.cityToIndex)
    {
        if (cityDist.first != source)
        {
            cout << cityDist.first << ": " << ans[cityDist.second] << " units" << endl;
        }
    }

    return 0;
}
