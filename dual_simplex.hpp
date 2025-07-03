#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

namespace DualSimplex {

const double EPS = 1e-9;

void printTable(const vector<vector<double>>& table) {
    for (const auto& row : table) {
        for (double val : row) {
            cout << setw(10) << fixed << setprecision(2) << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

size_t findNegativeRow(const vector<vector<double>>& table) {
    for (size_t i = 0; i < table.size() - 1; ++i) {
        if (table[i].back() < -EPS)
            return i;
    }
    return table.size(); // Indicates not found
}

size_t findDualPivotCol(const vector<vector<double>>& table, size_t pivotRow) {
    size_t col = table[0].size(); // Indicates not found
    double minRatio = numeric_limits<double>::max();

    for (size_t j = 0; j < table[0].size() - 1; ++j) {
        if (table[pivotRow][j] < -EPS) {
            double numerator = table.back()[j];
            double denominator = table[pivotRow][j];
            double ratio = fabs(numerator / denominator);
            if (ratio < minRatio) {
                minRatio = ratio;
                col = j;
            }
        }
    }

    return col;
}

void pivot(vector<vector<double>>& table, size_t pivotRow, size_t pivotCol) {
    double pivotElement = table[pivotRow][pivotCol];
    if (fabs(pivotElement) < EPS) {
        cout << "Pivot element is zero — cannot proceed.\n";
        exit(1);
    }

    // Normalize pivot row
    for (size_t j = 0; j < table[0].size(); ++j) {
        table[pivotRow][j] /= pivotElement;
    }

    // Eliminate pivot column in other rows
    for (size_t i = 0; i < table.size(); ++i) {
        if (i != pivotRow) {
            double factor = table[i][pivotCol];
            for (size_t j = 0; j < table[0].size(); ++j) {
                table[i][j] -= factor * table[pivotRow][j];
            }
        }
    }
}

void performDualSimplex(vector<vector<double>>& table) {
    while (true) {
        size_t pivotRow = findNegativeRow(table);
        if (pivotRow >= table.size() - 1) break;

        size_t pivotCol = findDualPivotCol(table, pivotRow);
        if (pivotCol >= table[0].size()) {
            cout << "Infeasible solution: no valid pivot column.\n";
            return;
        }

        pivot(table, pivotRow, pivotCol);
    }

    cout << "\nOptimal Table:\n";
    printTable(table);
    cout << "Optimal value: " << -table.back().back() << endl; // Convert back to maximization
}

void runDualSimplex() {
    int constraints, variables;
    cout << "Enter number of constraints: ";
    cin >> constraints;
    if (constraints <= 0) {
        cout << "Number of constraints must be positive.\n";
        return;
    }

    cout << "Enter number of variables: ";
    cin >> variables;
    if (variables <= 0) {
        cout << "Number of variables must be positive.\n";
        return;
    }

    size_t totalCols = static_cast<size_t>(variables + constraints + 1);
    vector<vector<double>> table(constraints + 1, vector<double>(totalCols, 0));

    // Input constraints
    cout << "\nEnter coefficients of each constraint followed by RHS:\n";
    for (int i = 0; i < constraints; ++i) {
        for (int j = 0; j < variables; ++j) {
            cout << "Constraint " << i + 1 << ", Coefficient of x" << j + 1 << ": ";
            cin >> table[i][j];
        }
        table[i][variables + i] = 1; // Slack variable
        cout << "Constraint " << i + 1 << ", RHS: ";
        cin >> table[i].back();
    }

    // Input objective function
    cout << "\nEnter coefficients of the objective function (to maximize):\n";
    for (int j = 0; j < variables; ++j) {
        cout << "Coefficient of x" << j + 1 << ": ";
        cin >> table[constraints][j];
        table[constraints][j] *= -1; // Convert to standard LP form (minimization)
    }

    cout << "\nInitial Table:\n";
    printTable(table);

    performDualSimplex(table);
}

}
