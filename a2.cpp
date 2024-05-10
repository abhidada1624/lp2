#include<bits/stdc++.h>

using namespace std;

#define N 4

// Class representing the puzzle solver
class PuzzleSolver
{
private:
    class Node
    {
    public:
        Node *parent;
        int mat[N][N];
        int x, y;
        int cost;
        int level;

        Node(Node *parent, int mat[N][N], int x, int y, int newX, int newY, int level)
            : parent(parent), x(newX), y(newY), level(level)
        {
            memcpy(this->mat, mat, sizeof this->mat);
            swap(this->mat[x][y], this->mat[newX][newY]);
            this->cost = INT_MAX;
        }
    };

    // Comparison object for priority_queue
    class Compare
    {
    public:
        bool operator()(const Node *lhs, const Node *rhs) const
        {
            return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
        }
    };

public:
    PuzzleSolver() {}

    // Function to solve the N*N - 1 puzzle
    void solvePuzzle(int initial[N][N], int x, int y, int final[N][N])
    {
        priority_queue<Node *, vector<Node *>, Compare> pq;

        Node *root = new Node(nullptr, initial, x, y, x, y, 0);
        root->cost = calculateCost(initial, final);

        pq.push(root);

        while (!pq.empty())
        {
            Node *min = pq.top();
            pq.pop();

            if (min->cost == 0)
            {
                printPath(min);
                return;
            }

            for (int i = 0; i < 4; i++)
            {
                if (isSafe(min->x + row[i], min->y + col[i]))
                {
                    Node *child = new Node(min, min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1);
                    child->cost = calculateCost(child->mat, final);
                    pq.push(child);
                }
            }
        }
    }

private:
    // Helper function to calculate the number of misplaced tiles
    int calculateCost(int initial[N][N], int final[N][N])
    {
        int count = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (initial[i][j] && initial[i][j] != final[i][j])
                {
                    count++;
                }
            }
        }
        return count;
    }

    // Helper function to check if (x, y) is a valid matrix coordinate
    bool isSafe(int x, int y)
    {
        return (x >= 0 && x < N && y >= 0 && y < N);
    }

    // Helper function to print the path from root to the current node
    void printPath(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        printPath(root->parent);
        printMatrix(root->mat);
        cout << endl;
    }

    // Helper function to print the N x N matrix
    void printMatrix(int mat[N][N])
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Direction arrays for moving the empty space (blank tile)
    int row[4] = {1, 0, -1, 0};
    int col[4] = {0, -1, 0, 1};
};

// Driver code
int main()
{
    // Initial configuration
    int initial[N][N] = {
        {2, 7, 12, 13},
        {0, 8, 5, 4},
        {9, 10, 11, 6},
        {15, 3, 1, 14}};

    // Solvable Final configuration
    int final[N][N] = {
        {2, 7, 12, 13},
        {8, 5, 4, 6},
        {9, 10, 11, 14},
        {15, 3, 1, 0}};

    PuzzleSolver solver;
    solver.solvePuzzle(initial, 1, 0, final);

    return 0;
}
