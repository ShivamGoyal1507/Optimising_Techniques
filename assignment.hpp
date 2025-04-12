#pragma once
#include <iostream>
#include <vector>
#include <limits>

namespace Assignment {

const int INF = 1e9;

int hungarian(std::vector<std::vector<int>>& cost) {
    int n = cost.size();
    std::vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);

    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv(n + 1, INF);
        std::vector<bool> used(n + 1, false);
        
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
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
            
            for (int j = 0; j <= n; j++) {
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

    return -v[0];
}

void runAssignment() {
    int n;
    std::cout << "Enter number of workers/tasks: ";
    std::cin >> n;

    std::vector<std::vector<int>> cost(n, std::vector<int>(n));

    std::cout << "Enter cost matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> cost[i][j];
        }
    }

    int result = hungarian(cost);
    std::cout << "\nOptimal assignment cost: " << result << std::endl;
}

} // namespace Assignment