#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

namespace Transportation {

void printTransportTable(const vector<vector<double>>& cost, 
                        const vector<vector<double>>& allocation,
                        const vector<double>& supply,
                        const vector<double>& demand) {
    int m = cost.size();
    int n = cost[0].size();
    
    cout << "\nTransportation Table:\n";
    cout << setw(10) << " ";
    for (int j = 0; j < n; j++) {
        cout << setw(10) << "D" << j+1;
    }
    cout << setw(10) << "Supply" << endl;
    
    for (int i = 0; i < m; i++) {
        cout << setw(10) << "S" << i+1;
        for (int j = 0; j < n; j++) {
            if (allocation[i][j] > 0) {
                cout << setw(8) << cost[i][j] << "*" << allocation[i][j];
            } else {
                cout << setw(10) << cost[i][j];
            }
        }
        cout << setw(10) << supply[i] << endl;
    }
    
    cout << setw(10) << "Demand";
    for (int j = 0; j < n; j++) {
        cout << setw(10) << demand[j];
    }
    cout << endl << endl;
}

pair<int, int> findMinCostCell(const vector<vector<double>>& cost, 
                             const vector<bool>& rowDone, 
                             const vector<bool>& colDone) {
    double minVal = numeric_limits<double>::max();
    pair<int, int> minPos = {-1, -1};
    
    for (int i = 0; i < cost.size(); i++) {
        if (rowDone[i]) continue;
        for (int j = 0; j < cost[0].size(); j++) {
            if (colDone[j]) continue;
            if (cost[i][j] < minVal) {
                minVal = cost[i][j];
                minPos = {i, j};
            }
        }
    }
    return minPos;
}

void vogelApproximation(vector<vector<double>>& cost, 
                       vector<double>& supply, 
                       vector<double>& demand) {
    int m = supply.size();
    int n = demand.size();
    
    vector<vector<double>> allocation(m, vector<double>(n, 0));
    vector<bool> rowDone(m, false);
    vector<bool> colDone(n, false);
    
    while (true) {
        // Check if all supplies and demands are exhausted
        bool allDone = true;
        for (bool done : rowDone) if (!done) allDone = false;
        for (bool done : colDone) if (!done) allDone = false;
        if (allDone) break;
        
        // Find the cell with minimum cost
        auto [i, j] = findMinCostCell(cost, rowDone, colDone);
        if (i == -1 || j == -1) break;
        
        // Allocate as much as possible
        double quantity = min(supply[i], demand[j]);
        allocation[i][j] = quantity;
        supply[i] -= quantity;
        demand[j] -= quantity;
        
        // Mark row or column as done if exhausted
        if (supply[i] == 0) rowDone[i] = true;
        if (demand[j] == 0) colDone[j] = true;
    }
    
    // Calculate total cost
    double totalCost = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            totalCost += allocation[i][j] * cost[i][j];
        }
    }
    
    printTransportTable(cost, allocation, supply, demand);
    cout << "Initial Basic Feasible Solution (VAM): " << totalCost << endl;
}

void runTransportation() {
    int sources, destinations;
    cout << "Enter number of sources: ";
    cin >> sources;
    cout << "Enter number of destinations: ";
    cin >> destinations;
    
    vector<double> supply(sources);
    vector<double> demand(destinations);
    vector<vector<double>> cost(sources, vector<double>(destinations));
    
    cout << "Enter supply values for each source:\n";
    for (int i = 0; i < sources; i++) {
        cout << "Source " << i+1 << ": ";
        cin >> supply[i];
    }
    
    cout << "Enter demand values for each destination:\n";
    for (int j = 0; j < destinations; j++) {
        cout << "Destination " << j+1 << ": ";
        cin >> demand[j];
    }
    
    cout << "Enter cost matrix (" << sources << "x" << destinations << "):\n";
    for (int i = 0; i < sources; i++) {
        for (int j = 0; j < destinations; j++) {
            cout << "Cost from Source " << i+1 << " to Destination " << j+1 << ": ";
            cin >> cost[i][j];
        }
    }
    
    vogelApproximation(cost, supply, demand);
}

} // namespace Transportation