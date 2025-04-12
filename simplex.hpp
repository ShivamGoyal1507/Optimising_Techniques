#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

namespace Simplex {

void printTable(const std::vector<std::vector<double>>& table) {
    for (const auto& row : table) {
        for (double val : row) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int findPivotColumn(const std::vector<std::vector<double>>& table) {
    int lastRow = table.size() - 1;
    int pivotCol = -1;
    double minVal = 0;
    for (int j = 0; j < table[0].size() - 1; j++) {
        if (table[lastRow][j] < minVal) {
            minVal = table[lastRow][j];
            pivotCol = j;
        }
    }
    return pivotCol;
}

int findPivotRow(const std::vector<std::vector<double>>& table, int pivotCol) {
    double minRatio = std::numeric_limits<double>::max();
    int pivotRow = -1;
    for (int i = 0; i < table.size() - 1; i++) {
        if (table[i][pivotCol] > 0) {
            double ratio = table[i].back() / table[i][pivotCol];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }
    return pivotRow;
}

void performSimplex(std::vector<std::vector<double>>& table) {
    while (true) {
        int pivotCol = findPivotColumn(table);
        if (pivotCol == -1) break;  // Optimal reached

        int pivotRow = findPivotRow(table, pivotCol);
        if (pivotRow == -1) {
            std::cout << "Unbounded solution\n";
            return;
        }

        double pivot = table[pivotRow][pivotCol];
        for (int j = 0; j < table[0].size(); j++) {
            table[pivotRow][j] /= pivot;
        }

        for (int i = 0; i < table.size(); i++) {
            if (i != pivotRow) {
                double factor = table[i][pivotCol];
                for (int j = 0; j < table[0].size(); j++) {
                    table[i][j] -= factor * table[pivotRow][j];
                }
            }
        }
    }

    std::cout << "\nOptimal Table:\n";
    printTable(table);
    std::cout << "Optimal value: " << table.back().back() << std::endl;
}

void runSimplex() {
    int constraints, variables;
    std::cout << "Enter number of constraints: ";
    std::cin >> constraints;
    std::cout << "Enter number of variables: ";
    std::cin >> variables;

    std::vector<std::vector<double>> table(constraints + 1, std::vector<double>(variables + constraints + 1, 0));

    // Input constraints
    std::cout << "Enter coefficients of constraints (LHS) and RHS:\n";
    for (int i = 0; i < constraints; i++) {
        for (int j = 0; j < variables; j++) {
            std::cout << "Coefficient x" << j + 1 << " in constraint " << i + 1 << ": ";
            std::cin >> table[i][j];
        }
        // Add slack variables
        table[i][variables + i] = 1;
        std::cout << "RHS value for constraint " << i + 1 << ": ";
        std::cin >> table[i].back();
    }

    // Input objective function
    std::cout << "Enter coefficients of objective function (to maximize):\n";
    for (int j = 0; j < variables; j++) {
        std::cout << "Coefficient x" << j + 1 << " in objective: ";
        std::cin >> table[constraints][j];
        table[constraints][j] *= -1; // Convert to standard form
    }

    performSimplex(table);
}

} // namespace Simplex