#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<string, list<string>> adj;
    map<string, bool> vis;
    queue<pair<string, int>> q;
    Graph()
    {
        this->adj = adj;
        this->vis = vis;
        this->q = q;
    }

    void setvis()
    {
        for (auto i : adj)
        {
            vis[i.first] = false;
        }
    }
    void print()
    {
        for (auto i : adj)
        {
            cout << i.first << " -> ";
            for (auto j : i.second)
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void bfsRec(queue<pair<string, int>> q)
    {
        if (q.empty())
            return;
        string node = q.front().first;
        int level = q.front().second;
        cout << node << " -> " << level << "  ,  ";
        q.pop();
        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                vis[it] = true;
                q.push({it, level + 1});
            }
        }
        bfsRec(q);
    }

    void bfs(string s)
    {
        q.push({s, 0});
        vis[s] = true;
        cout << "BFS" << endl;
        bfsRec(q);
        cout << endl;
    }

    void dfs(string s, int level)
    {
        vis[s] = true;
        cout << s << " -> " << level << "  ,  ";
        for (auto it : adj[s])
        {
            if (!vis[it])
            {
                dfs(it, level + 1);
            }
        }
    }
    
};

int main()
{
    Graph g;
    int n;
    cout << "Enter total number of cities : " << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string u, v;
        cout << "Enter source : " << endl;
        cin >> u;
        cout << "Enter destination : " << endl;
        cin >> v;
        g.adj[u].push_back(v);
        g.adj[v].push_back(u);
    }
    while (true)
    {
        cout << "\n * * * M E N U * * * " << endl;
        cout << "1.DFS" << endl;
        cout << "2.BFS" << endl;
        cout << "3.EXIT" << endl;
        int n;
        cout << "Enter your choice : " << endl;
        cin >> n;
        if (n == 1)
        {
            cout << "Enter starting node ? " << endl;
            string s;
            cin >> s;
            if (g.adj.count(s) == 0)
            {
                cout << "Invalid Node!" << endl;
                exit(0);
            }

            g.setvis();
            g.dfs(s, 0);
        }
        else if (n == 2)
        {
            cout << "Enter starting node ? " << endl;
            string s;
            cin >> s;
            g.setvis();
            g.bfs(s);
        }
        else
            exit(0);
    }

    return 0;
}