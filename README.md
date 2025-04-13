# Operations Research Methods in C++

## Overview

This C++ program implements six essential Operations Research (OR) algorithms, widely used in optimization and decision science:

- Simplex Method for Linear Programming (LP)
- Dual Simplex Method
- Assignment Problem (Hungarian Algorithm)
- Transportation Problem (Vogel’s Approximation Method)
- Integer Programming (IP)
- Mixed Integer Programming (MIP)

Each algorithm is modularized in its own header file for clarity and reusability.

---

## Features

- Simplex Method – Solves LP problems in standard form
- Dual Simplex Method – Solves LP problems with infeasible starting points
- Hungarian Algorithm – Solves optimal assignment of workers to tasks
- Vogel’s Approximation Method (VAM) – Provides initial feasible solution for transportation problems
- Integer Programming (IP) – Solves optimization problems with integer constraints using Branch and Bound
- Mixed Integer Programming (MIP) – Handles problems with both integer and real variables
- Binary Variable Support – Implicitly handled through constraints
- Interactive Menu Interface – Simple command-line navigation
- Formatted Output – Easy-to-read results for each method

---

## File Structure

```
project/
├── simplex.hpp          # Simplex Method
├── dual_simplex.hpp     # Dual Simplex Method
├── assignment.hpp       # Hungarian Algorithm
├── transportation.hpp   # Vogel's Approximation Method
├── branch_bound.hpp     # Integer & Mixed Integer Programming (Branch and Bound)
└── main.cpp             # Main program and user interface
```

---

## Compilation & Execution

### Compile:
```
g++ main.cpp -o or_program
```

### Run:
```
./or_program
```

---

## Menu and Usage

After running the executable, you’ll see the following menu:

```
Operations Research Methods:
1. Simplex Method
2. Dual Simplex Method
3. Assignment Problem (Hungarian Algorithm)
4. Transportation Problem (Vogel's Approximation)
5. Integer/Mixed Integer Programming (Branch and Bound)
6. Exit
Enter your choice (1-6):
```

Select an option and follow the interactive prompts to input your problem data.

---

## Method Details

### 1. Simplex Method
- Input: Number of variables and constraints
- Enter each constraint (coefficients + RHS)
- Define the objective function
- Output: Optimal solution vector and objective value

---

### 2. Dual Simplex Method
- Similar to Simplex input
- Used when initial basic solution is infeasible
- Maintains dual feasibility while optimizing

---

### 3. Assignment Problem (Hungarian Algorithm)
- Input: Number of workers/tasks (n)
- Enter a square n × n cost matrix
- Output: Optimal assignment and minimum cost

---

### 4. Transportation Problem (Vogel’s Approximation Method)
- Input:
  - Number of sources and destinations
  - Supply for each source
  - Demand for each destination
  - Cost matrix
- Output: Initial feasible solution using VAM

---

### 5. Integer / Mixed Integer Programming (Branch and Bound)
- Input: Objective function and constraints
- Specify which variables are integers or mixed
- Binary variables handled via constraints
- Solves using Branch and Bound method
- Output: Optimal integer/mixed-integer solution

---

## Example Inputs

### Simplex Example:
```
Number of constraints: 2
Number of variables: 2
Constraint 1: 1 1 <= 4
Constraint 2: 2 1 <= 5
Objective: Maximize 3x1 + 2x2
```

### Assignment Example:
```
Number of workers/tasks: 3
Cost matrix:
90 75 75
35 85 55
125 95 90
```

### Transportation Example:
```
Sources: 3
Destinations: 4
Supply: 300 400 500
Demand: 250 350 400 200
Cost matrix:
3 1 7 4
2 6 5 9
8 3 3 2
```

---

## Dependencies

- Standard C++ Library (no external dependencies)

---

## Notes

- All inputs should be numerical (integers or floats)
- Basic input validation included
- For large inputs, output may exceed standard terminal width

---

## License

This program is provided as-is for educational purposes. Feel free to modify and use it as needed.

---

## Author

[Your Name]  
[Your Contact Information]

