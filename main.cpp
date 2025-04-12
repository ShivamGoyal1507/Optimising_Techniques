#include <iostream>
#include "simplex.hpp"
#include "dual_simplex.hpp"
#include "assignment.hpp"
#include "transportation.hpp"
#include "integer.hpp"

using namespace std;

void displayMenu() {
    cout << "\nOperations Research Methods:\n";
    cout << "1. Simplex Method\n";
    cout << "2. Dual Simplex Method\n";
    cout << "3. Assignment Problem (Hungarian Algorithm)\n";
    cout << "4. Transportation Problem (Vogel's Approximation)\n";
    cout << "5. Integer Linear Programming (Branch and Bound)\n";
    cout << "6. Mixed Integer Programming (Branch and Bound)\n";
    cout << "7. Exit\n";
    cout << "Enter your choice (1-7): ";
}

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "\n--- Simplex Method ---\n";
                Simplex::runSimplex();
                break;
            case 2:
                cout << "\n--- Dual Simplex Method ---\n";
                DualSimplex::runDualSimplex();
                break;
            case 3:
                cout << "\n--- Assignment Problem ---\n";
                Assignment::runAssignment();
                break;
            case 4:
                cout << "\n--- Transportation Problem ---\n";
                Transportation::runTransportation();
                break;
            case 5:
                cout << "\n--- Integer Linear Programming ---\n";
                IntegerProgramming::runIntegerProgramming(false);
                break;
            case 6:
                cout << "\n--- Mixed Integer Programming ---\n";
                IntegerProgramming::runIntegerProgramming(true);
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}