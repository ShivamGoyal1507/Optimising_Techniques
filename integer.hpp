#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <cmath>
#include <queue>
#include "simplex.hpp"

using namespace std;

namespace IntegerProgramming {

struct Node {
    vector<vector<double>> table;
    double z; // Objective value
    vector<double> solution;
    bool feasible;
    int varToBranch; // Variable to branch on (-1 if none)
    
    Node(const vector<vector<double>>& t, double z_val, const vector<double>& sol, bool feas)
        : table(t), z(z_val), solution(sol), feasible(feas), varToBranch(-1) {}
};

void printSolution(const vector<double>& solution, double z) {
    cout << "\nSolution: ";
    for (size_t i = 0; i < solution.size(); i++) {
        cout << "x" << i+1 << " = " << solution[i] << " ";
    }
    cout << "\nObjective value: " << z << endl;
}

bool isInteger(double val, double tolerance = 1e-6) {
    return abs(val - round(val)) < tolerance;
}

int findFractionalVar(const vector<double>& solution) {
    for (size_t i = 0; i < solution.size(); i++) {
        if (!isInteger(solution[i])) {
            return i;
        }
    }
    return -1;
}

Node solveRelaxation(vector<vector<double>> table) {
    Simplex::performSimplex(table);
    
    vector<double> solution(table[0].size() - 1, 0);
    for (size_t i = 0; i < solution.size(); i++) {
        solution[i] = 0;
        bool isBasic = false;
        int basicRow = -1;
        
        for (size_t j = 0; j < table.size() - 1; j++) {
            if (abs(table[j][i] - 1) < 1e-6) {
                bool isBasicVar = true;
                for (size_t k = 0; k < table[0].size(); k++) {
                    if (k != i && abs(table[j][k]) > 1e-6) {
                        isBasicVar = false;
                        break;
                    }
                }
                if (isBasicVar) {
                    isBasic = true;
                    basicRow = j;
                    break;
                }
            }
        }
        
        if (isBasic) {
            solution[i] = table[basicRow].back();
        }
    }
    
    bool feasible = true;
    for (size_t i = 0; i < table.size() - 1; i++) {
        if (table[i].back() < -1e-6) {
            feasible = false;
            break;
        }
    }
    
    return Node(table, table.back().back(), solution, feasible);
}

void branchAndBound(vector<vector<double>> initialTable, bool isMIP = false) {
    queue<Node> activeNodes;
    Node bestNode(initialTable, -numeric_limits<double>::max(), vector<double>(), false);
    
    // Solve initial relaxation
    Node root = solveRelaxation(initialTable);
    if (!root.feasible) {
        cout << "Problem is infeasible.\n";
        return;
    }
    
    root.varToBranch = findFractionalVar(root.solution);
    activeNodes.push(root);
    
    while (!activeNodes.empty()) {
        Node current = activeNodes.front();
        activeNodes.pop();
        
        // Prune if worse than best integer solution
        if (current.z <= bestNode.z) {
            continue;
        }
        
        // If integer solution (for pure IP) or meets MIP requirements
        bool isIntegerSol = true;
        for (size_t i = 0; i < current.solution.size(); i++) {
            if ((!isMIP || i < initialTable[0].size() - initialTable.size() - 1) && 
                !isInteger(current.solution[i])) {
                isIntegerSol = false;
                break;
            }
        }
        
        if (isIntegerSol) {
            if (current.z > bestNode.z) {
                bestNode = current;
                cout << "New best integer solution found:\n";
                printSolution(bestNode.solution, bestNode.z);
            }
            continue;
        }
        
        // Branch on fractional variable
        int branchVar = findFractionalVar(current.solution);
        if (branchVar == -1) continue;
        
        // Create <= floor constraint
        vector<vector<double>> leftTable = current.table;
        vector<double> newConstraint(leftTable[0].size(), 0);
        newConstraint[branchVar] = 1;
        newConstraint.back() = floor(current.solution[branchVar]);
        leftTable.insert(leftTable.end() - 1, newConstraint);
        
        // Create >= ceil constraint
        vector<vector<double>> rightTable = current.table;
        newConstraint[branchVar] = 1;
        newConstraint.back() = ceil(current.solution[branchVar]);
        rightTable.insert(rightTable.end() - 1, newConstraint);
        
        // Solve left branch
        Node left = solveRelaxation(leftTable);
        left.varToBranch = findFractionalVar(left.solution);
        if (left.feasible && left.z > bestNode.z) {
            activeNodes.push(left);
        }
        
        // Solve right branch
        Node right = solveRelaxation(rightTable);
        right.varToBranch = findFractionalVar(right.solution);
        if (right.feasible && right.z > bestNode.z) {
            activeNodes.push(right);
        }
    }
    
    if (bestNode.feasible) {
        cout << "\nOptimal ";
        if (isMIP) cout << "mixed ";
        cout << "integer solution:\n";
        printSolution(bestNode.solution, bestNode.z);
    } else {
        cout << "No feasible integer solution found.\n";
    }
}

void runIntegerProgramming(bool mixed = false) {
    int constraints, variables;
    cout << "Enter number of constraints: ";
    cin >> constraints;
    cout << "Enter number of variables: ";
    cin >> variables;

    vector<vector<double>> table(constraints + 1, vector<double>(variables + constraints + 1, 0));

    // Input constraints
    cout << "Enter coefficients of constraints (LHS) and RHS:\n";
    for (int i = 0; i < constraints; i++) {
        for (int j = 0; j < variables; j++) {
            cout << "Coefficient x" << j + 1 << " in constraint " << i + 1 << ": ";
            cin >> table[i][j];
        }
        // Add slack variables
        table[i][variables + i] = 1;
        cout << "RHS value for constraint " << i + 1 << ": ";
        cin >> table[i].back();
    }

    // Input objective function
    cout << "Enter coefficients of objective function (to maximize):\n";
    for (int j = 0; j < variables; j++) {
        cout << "Coefficient x" << j + 1 << " in objective: ";
        cin >> table[constraints][j];
        table[constraints][j] *= -1; // Convert to standard form
    }

    cout << "\nSolving using Branch and Bound...\n";
    branchAndBound(table, mixed);
}

} // namespace IntegerProgramming