#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

namespace Simplex {

void printTable(const vector<vector<double>>& table, const vector<string>& basis) {
    size_t numRows = table.size();
    size_t numCols = table[0].size();
    size_t numVars = numCols - numRows; // x1..xn + slack
    size_t slackStart = numVars;

    // Header
    cout << setw(8) << "Basic";
    for (size_t j = 0; j < numVars; ++j)
        cout << setw(10) << "x" + to_string(j + 1);
    for (size_t j = 0; j < numRows - 1; ++j)
        cout << setw(10) << "s" + to_string(j + 1);
    cout << setw(10) << "RHS" << endl;

    // Rows
    for (size_t i = 0; i < numRows; ++i) {
        if (i < numRows - 1)
            cout << setw(8) << basis[i];
        else
            cout << setw(8) << "Z";

        for (size_t j = 0; j < numCols; ++j) {
            cout << setw(10) << fixed << setprecision(2) << table[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int findPivotColumn(const vector<vector<double>>& table) {
    size_t lastRow = table.size() - 1;
    int pivotCol = -1;
    double minVal = 0;
    for (size_t j = 0; j < table[0].size() - 1; j++) {
        if (table[lastRow][j] < minVal) {
            minVal = table[lastRow][j];
            pivotCol = static_cast<int>(j);
        }
    }
    return pivotCol;
}

int findPivotRow(const vector<vector<double>>& table, int pivotCol) {
    double minRatio = numeric_limits<double>::max();
    int pivotRow = -1;
    for (size_t i = 0; i < table.size() - 1; i++) {
        if (table[i][pivotCol] > 0) {
            double ratio = table[i].back() / table[i][pivotCol];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = static_cast<int>(i);
            }
        }
    }
    return pivotRow;
}

void performSimplex(vector<vector<double>>& table) {
    size_t numRows = table.size();
    size_t numCols = table[0].size();
    size_t numVars = numCols - numRows - 1;

    vector<string> basis(numRows - 1);
    for (size_t i = 0; i < basis.size(); i++) {
        basis[i] = "s" + to_string(i + 1); // Initial basis is slack variables
    }

    while (true) {
        printTable(table, basis);

        int pivotCol = findPivotColumn(table);
        if (pivotCol == -1) break;

        int pivotRow = findPivotRow(table, pivotCol);
        if (pivotRow == -1) {
            cout << "Unbounded solution\n";
            return;
        }

        basis[pivotRow] = "x" + to_string(pivotCol + 1); // Update basis

        double pivot = table[pivotRow][pivotCol];
        for (size_t j = 0; j < numCols; j++) {
            table[pivotRow][j] /= pivot;
        }

        for (size_t i = 0; i < numRows; i++) {
            if (static_cast<int>(i) != pivotRow) {
                double factor = table[i][pivotCol];
                for (size_t j = 0; j < numCols; j++) {
                    table[i][j] -= factor * table[pivotRow][j];
                }
            }
        }
    }

    cout << "\nFinal Optimal Table:\n";
    printTable(table, basis);
    cout << "Optimal value: " << table.back().back() << endl;
}

bool isFeasible(const vector<vector<double>>& table) {
    for (size_t i = 0; i < table.size() - 1; i++) {
        if (table[i].back() < -1e-6) {
            return false;
        }
    }
    return true;
}

void runSimplex() {
    int constraints, variables;
    cout << "Enter number of constraints: ";
    cin >> constraints;
    cout << "Enter number of variables: ";
    cin >> variables;

    vector<vector<double>> table(constraints + 1, vector<double>(variables + constraints + 1, 0));

    cout << "Enter coefficients of constraints (LHS) and RHS:\n";
    for (int i = 0; i < constraints; i++) {
        for (int j = 0; j < variables; j++) {
            cout << "Coefficient x" << j + 1 << " in constraint " << i + 1 << ": ";
            cin >> table[i][j];
        }
        table[i][variables + i] = 1; // Slack
        cout << "RHS value for constraint " << i + 1 << ": ";
        cin >> table[i].back();
    }

    cout << "Enter coefficients of objective function (to maximize):\n";
    for (int j = 0; j < variables; j++) {
        cout << "Coefficient x" << j + 1 << " in objective: ";
        cin >> table[constraints][j];
        table[constraints][j] *= -1; // Standard form
    }

    performSimplex(table);
}

} 
