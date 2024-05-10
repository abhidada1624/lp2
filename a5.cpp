#include<bits/stdc++.h>
using namespace std;

class NQueens
{
private:
    int n;
    vector<int> columns;
    set<int> diag1; // (row - col) values
    set<int> diag2; // (row + col) values
    vector<vector<int>> solutions;

public:
    NQueens(int size) : n(size)
    {
        columns.assign(n, -1); // Initialize columns to -1 (no queen placed)
    }

    bool isSafe(int row, int col)
    {
        return columns[col] == -1 && !diag1.count(row - col) && !diag2.count(row + col);
    }

    void placeQueen(int row, int col)
    {
        columns[col] = row;
        diag1.insert(row - col);
        diag2.insert(row + col);
    }

    void removeQueen(int row, int col)
    {
        columns[col] = -1;
        diag1.erase(row - col);
        diag2.erase(row + col);
    }

    // Backtracking method to find all solutions
    void backtrack(int row)
    {
        if (row == n)
        {
            vector<int> solution(columns.begin(), columns.end());
            solutions.push_back(solution);
            return;
        }

        for (int col = 0; col < n; ++col)
        {
            if (isSafe(row, col))
            {
                placeQueen(row, col);
                backtrack(row + 1);
                removeQueen(row, col);
            }
        }
    }

    // Branch and bound method using a heuristic to estimate lower bounds
    void branchAndBound(int row)
    {
        if (row == n)
        {
            vector<int> solution(columns.begin(), columns.end());
            solutions.push_back(solution);
            return;
        }

        vector<pair<int, int>> candidateColumns;
        for (int col = 0; col < n; ++col)
        {
            if (isSafe(row, col))
            {
                int estimatedLowerBound = n - row - 1; // Initial lower bound estimate
                placeQueen(row, col);
                // Update lower bound estimate based on constraints
                for (int r = row + 1; r < n; ++r)
                {
                    if (isSafe(r, col))
                    {
                        estimatedLowerBound--;
                    }
                }
                candidateColumns.emplace_back(col, estimatedLowerBound);
                removeQueen(row, col);
            }
        }

        // Sort candidate columns by estimated lower bound (ascending)
        sort(candidateColumns.begin(), candidateColumns.end(), [](const auto &a, const auto &b)
             { return a.second < b.second; });

        for (const auto it: candidateColumns)
        {
            // it.first = col
            placeQueen(row, it.first);
            branchAndBound(row + 1);
            removeQueen(row, it.first);
        }
    }

    // Solve using backtracking methodw
    vector<vector<int>> solveBacktracking()
    {
        solutions.clear();
        backtrack(0);
        return solutions;
    }

    // Solve using branch and bound method
    vector<vector<int>> solveBranchAndBound()
    {
        solutions.clear();
        branchAndBound(0);
        return solutions;
    }
};

void printBoard(const vector<int> &columns)
{
    int n = columns.size();
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (columns[col] == row)
            {
                cout << "Q ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n = 6; // Change n to desired board size
    NQueens queens(n);

    // Solve using backtracking method
    vector<vector<int>> solutionsBacktracking = queens.solveBacktracking();
    cout << "Found " << solutionsBacktracking.size() << " solutions using backtracking for " << n << "-Queens:" << endl;
    for (const auto &solution : solutionsBacktracking)
    {
        printBoard(solution);
    }   

    cout << endl;

    // Solve using branch and bound method
    vector<vector<int>> solutionsBranchAndBound = queens.solveBranchAndBound();
    cout << "Found " << solutionsBranchAndBound.size() << " solutions using branch and bound for " << n << "-Queens:" << endl;
    for (const auto &solution : solutionsBranchAndBound)
    {
        printBoard(solution);
    }

    return 0;
}
