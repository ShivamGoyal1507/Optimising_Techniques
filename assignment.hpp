#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

namespace Assignment {

const int INF = numeric_limits<int>::max();
int hungarian(vector<vector<int>>& cost, vector<pair<int, int>>& assignments) {
    int n = cost.size();
    int m = cost[0].size();
    int size = max(n, m);

    // Make the cost matrix square by padding with zeros
    vector<vector<int>> square_cost(size, vector<int>(size, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            square_cost[i][j] = cost[i][j];

    vector<int> u(size + 1), v(size + 1), p(size + 1), way(size + 1);
    for (int i = 1; i <= size; i++) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(size + 1, INF);
        vector<bool> used(size + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1 = -1;
            for (int j = 1; j <= size; j++) {
                if (!used[j]) {
                    int cur = square_cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            if (delta == INF) break;

            for (int j = 0; j <= size; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    // Extract assignment: p[j] = i means i is assigned to j
    assignments.clear();
    for (int j = 1; j <= m; j++) {
        int i = p[j];
        if (i <= n) {
            assignments.emplace_back(i - 1, j - 1); // i-th worker → j-th task
        }
    }

    return -v[0]; // optimal cost
}void runAssignment() {
    int n, m;
    cout << "Enter number of workers: ";
    cin >> n;
    if (n <= 0) {
        cout << "Number of workers must be positive.\n";
        return;
    }

    cout << "Enter number of tasks: ";
    cin >> m;
    if (m <= 0) {
        cout << "Number of tasks must be positive.\n";
        return;
    }

    vector<vector<int>> cost(n, vector<int>(m));
    cout << "\nEnter the cost matrix (" << n << " x " << m << "):\n";
    for (int i = 0; i < n; i++) {
        cout << "Worker " << i + 1 << ": ";
        for (int j = 0; j < m; j++) {
            cin >> cost[i][j];
            if (cin.fail()) {
                cout << "Invalid input! Please enter integers only.\n";
                return;
            }
        }
    }

    cout << "\nCost Matrix:\n";
    cout << setw(10) << " ";
    for (int j = 0; j < m; j++) {
        cout << setw(10) << "Task " + to_string(j + 1);
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(10) << "Worker " + to_string(i + 1);
        for (int j = 0; j < m; j++) {
            cout << setw(10) << cost[i][j];
        }
        cout << "\n";
    }

    vector<pair<int, int>> assignments;
    int result = hungarian(cost, assignments);

    cout << "\n====================================\n";
    cout << " Optimal Assignment Cost: " << result << "\n";
    cout << " Assignment:\n";
    for (auto& [worker, task] : assignments) {
        cout << "  Worker " << worker + 1 << " → Task " << task + 1 << "\n";
    }
    cout << "====================================\n";
}
}  
