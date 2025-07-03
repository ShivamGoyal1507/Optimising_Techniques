#include <iostream>
#include "simplex.hpp"
#include "dual_simplex.hpp"
#include "assignment.hpp"
#include "transportation.hpp"

using namespace std;

void displayMenu() {
    cout << "\nOptimisation Methods:\n";
    cout << "1. Simplex Method\n";
    cout << "2. Dual Simplex Method\n";
    cout << "3. Assignment Problem (Hungarian Algorithm)\n";
    cout << "4. Transportation Problem (Vogel's Approximation)\n";
    cout << "5. Exit\n";
    cout << "Enter your choice (1-5): ";
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
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
