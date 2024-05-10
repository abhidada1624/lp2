#include <bits/stdc++.h>
using namespace std;
#define n 4

class puzzle
{
public:
    puzzle() {}
    class node
    {
    public:
        node *parent;
        int mat[n][n];
        int x, y;
        int cost;
        int level;
        node(node *parent, int mat[n][n], int x, int y, int newx, int newy, int level)
       // :parent(parent),x(newx),y(newy),level(level)
        {
            this->x = newx;
            this->y = newy;
            this->parent = parent;
            this->level = level;
            memcpy(this->mat, mat, sizeof(this->mat));
            swap(this->mat[x][y], this->mat[newx][newy]);
            this->cost = INT_MAX;
        }
    };
    class compare
    {
    public:
        bool operator()( node *lhs,  node *rhs)
        {
            return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
        }
    };
    
    int calcucost(int ini[n][n], int fini[n][n])
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (ini[i][j] && ini[i][j] != fini[i][j])
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    void printmat(int mat[n][n])
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    int issafe(int x, int y)
    {
        return (x >= 0 && x < n) && (y < n && y >= 0);
    }
    void path(node *root)
    {
        if (root == NULL)
            return;
        path(root->parent);
        printmat(root->mat);
        cout << endl;
    }
    int row[4] = {1, 0, -1, 0};
    int col[4] = {0, -1, 0, 1};

    void solve(int ini[n][n], int x, int y, int fina[n][n])
    {
        priority_queue<node *, vector<node *>, compare> pq;
        node *root = new node(nullptr, ini, x, y, x, y, 0);
        root->cost = calcucost(ini, fina);
        pq.push(root);
        while (!pq.empty())
        {
            node *top = pq.top();
            pq.pop();
            if (top->cost == 0)
            {
                path(top);
                return;
            }
            for (int i = 0; i < 4; i++)
            {
                if (issafe(top->x + row[i], top->y + col[i]))
                {
                    node *child = new node(top, top->mat, top->x, top->y, top->x + row[i], top->y + col[i], top->level + 1);
                    child->cost = calcucost(top->mat, fina);
                    pq.push(child);
                }
            }
        }
    }
};

int main()
{
    int initial[n][n] = {
        {2, 7, 12, 13},
        {0, 8, 5, 4},
        {9, 10, 11, 6},
        {15, 3, 1, 14}};

    // Solvable Final configuration
    int final[n][n] = {
        {2, 7, 12, 13},
        {8, 5, 4, 6},
        {9, 10, 11, 14},
        {15, 3, 1, 0}};
    puzzle obj;
    obj.solve(initial, 1, 0, final);
    return 0;
}