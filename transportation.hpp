#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

namespace Transportation {

void printTransportTable(const vector<vector<double>>& cost,
                         const vector<vector<double>>& allocation,
                         const vector<double>& supply,
                         const vector<double>& demand) {
    size_t m = cost.size();
    size_t n = cost[0].size();

    cout << "\nTransportation Table:\n";
    cout << setw(10) << " ";
    for (size_t j = 0; j < n; j++) {
        cout << setw(10) << "D" << j + 1;
    }
    cout << setw(10) << "Supply" << endl;

    for (size_t i = 0; i < m; i++) {
        cout << setw(10) << "S" << i + 1;
        for (size_t j = 0; j < n; j++) {
            if (allocation[i][j] > 0) {
                cout << setw(8) << cost[i][j] << "*" << allocation[i][j];
            } else {
                cout << setw(10) << cost[i][j];
            }
        }
        cout << setw(10) << supply[i] << endl;
    }

    cout << setw(10) << "Demand";
    for (size_t j = 0; j < n; j++) {
        cout << setw(10) << demand[j];
    }
    cout << endl << endl;
}

double calculateTotalCost(const vector<vector<double>>& allocation,
                          const vector<vector<double>>& cost) {
    double total = 0;
    for (size_t i = 0; i < allocation.size(); i++) {
        for (size_t j = 0; j < allocation[0].size(); j++) {
            total += allocation[i][j] * cost[i][j];
        }
    }
    return total;
}

// Vogel's Approximation Method
vector<vector<double>> vogelApproximation(vector<vector<double>> cost,
                                          vector<double> supply,
                                          vector<double> demand) {
    size_t m = supply.size();
    size_t n = demand.size();
    vector<vector<double>> allocation(m, vector<double>(n, 0));
    vector<bool> rowDone(m, false);
    vector<bool> colDone(n, false);

    while (true) {
        if (all_of(rowDone.begin(), rowDone.end(), [](bool v) { return v; }) &&
            all_of(colDone.begin(), colDone.end(), [](bool v) { return v; })) {
            break;
        }

        // Calculate penalties
        vector<pair<double, int>> rowPenalty(m, { -1, -1 });
        vector<pair<double, int>> colPenalty(n, { -1, -1 });

        for (size_t i = 0; i < m; i++) {
            if (rowDone[i]) continue;
            vector<double> temp;
            for (size_t j = 0; j < n; j++) {
                if (!colDone[j]) temp.push_back(cost[i][j]);
            }
            if (temp.size() >= 2) {
                sort(temp.begin(), temp.end());
                rowPenalty[i] = { temp[1] - temp[0], i };
            } else if (temp.size() == 1) {
                rowPenalty[i] = { temp[0], i };
            }
        }

        for (size_t j = 0; j < n; j++) {
            if (colDone[j]) continue;
            vector<double> temp;
            for (size_t i = 0; i < m; i++) {
                if (!rowDone[i]) temp.push_back(cost[i][j]);
            }
            if (temp.size() >= 2) {
                sort(temp.begin(), temp.end());
                colPenalty[j] = { temp[1] - temp[0], j };
            } else if (temp.size() == 1) {
                colPenalty[j] = { temp[0], j };
            }
        }

        // Choose max penalty
        pair<double, int> maxRow = *max_element(rowPenalty.begin(), rowPenalty.end());
        pair<double, int> maxCol = *max_element(colPenalty.begin(), colPenalty.end());

        int selectedRow = -1, selectedCol = -1;
        if (maxRow.first > maxCol.first) {
            selectedRow = maxRow.second;
            double minVal = numeric_limits<double>::max();
            for (size_t j = 0; j < n; j++) {
                if (!colDone[j] && cost[selectedRow][j] < minVal) {
                    minVal = cost[selectedRow][j];
                    selectedCol = j;
                }
            }
        } else {
            selectedCol = maxCol.second;
            double minVal = numeric_limits<double>::max();
            for (size_t i = 0; i < m; i++) {
                if (!rowDone[i] && cost[i][selectedCol] < minVal) {
                    minVal = cost[i][selectedCol];
                    selectedRow = i;
                }
            }
        }

        // Allocate
        double qty = min(supply[selectedRow], demand[selectedCol]);
        allocation[selectedRow][selectedCol] = qty;
        supply[selectedRow] -= qty;
        demand[selectedCol] -= qty;

        if (supply[selectedRow] == 0) rowDone[selectedRow] = true;
        if (demand[selectedCol] == 0) colDone[selectedCol] = true;
    }

    return allocation;
}

// MODI Method to improve solution
bool modiOptimize(vector<vector<double>>& allocation,
                  const vector<vector<double>>& cost) {
    size_t m = allocation.size();
    size_t n = allocation[0].size();
    vector<double> u(m, numeric_limits<double>::max());
    vector<double> v(n, numeric_limits<double>::max());

    u[0] = 0;
    bool updated;
    do {
        updated = false;
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (allocation[i][j] > 0) {
                    if (u[i] != numeric_limits<double>::max() && v[j] == numeric_limits<double>::max()) {
                        v[j] = cost[i][j] - u[i];
                        updated = true;
                    }
                    else if (v[j] != numeric_limits<double>::max() && u[i] == numeric_limits<double>::max()) {
                        u[i] = cost[i][j] - v[j];
                        updated = true;
                    }
                }
            }
        }
    } while (updated);

    // Find opportunity cost
    double maxNeg = 0;
    pair<int, int> pos = { -1, -1 };
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            if (allocation[i][j] == 0) {
                double diff = cost[i][j] - (u[i] + v[j]);
                if (diff < maxNeg) {
                    maxNeg = diff;
                    pos = { (int)i, (int)j };
                }
            }
        }
    }

    if (maxNeg >= 0) return false; // Optimal

     
    return false;
}

void runTransportation() {
    int sources, destinations;
    cout << "Enter number of sources: ";
    cin >> sources;
    cout << "Enter number of destinations: ";
    cin >> destinations;

    vector<double> supply(sources);
    vector<double> demand(destinations);

    cout << "Enter supply values:\n";
    double totalSupply = 0;
    for (int i = 0; i < sources; i++) {
        cout << "Source " << i + 1 << ": ";
        cin >> supply[i];
        totalSupply += supply[i];
    }

    cout << "Enter demand values:\n";
    double totalDemand = 0;
    for (int j = 0; j < destinations; j++) {
        cout << "Destination " << j + 1 << ": ";
        cin >> demand[j];
        totalDemand += demand[j];
    }

    // Balance the problem if needed
    if (totalSupply > totalDemand) {
        cout << "Adding dummy destination to balance.\n";
        for (int i = 0; i < sources; i++)
            supply[i] = supply[i];
        demand.push_back(totalSupply - totalDemand);
        destinations++;
    } else if (totalDemand > totalSupply) {
        cout << "Adding dummy source to balance.\n";
        supply.push_back(totalDemand - totalSupply);
        sources++;
    }

    vector<vector<double>> cost(sources, vector<double>(destinations, 0));
    cout << "Enter cost matrix:\n";
    for (int i = 0; i < sources; i++) {
        for (int j = 0; j < destinations; j++) {
            cout << "Cost from S" << i + 1 << " to D" << j + 1 << ": ";
            cin >> cost[i][j];
        }
    }

    vector<vector<double>> allocation = vogelApproximation(cost, supply, demand);

    printTransportTable(cost, allocation, supply, demand);

    double totalCost = calculateTotalCost(allocation, cost);
    cout << "Initial Solution Cost (VAM): " << totalCost << endl;

}

}  
