# 📊 Operations Research Methods in C++

## 🧠 Overview
This C++ program implements six essential Operations Research (OR) algorithms, widely used in optimization and decision science:

- **Simplex Method** for Linear Programming (LP)
- **Dual Simplex Method**
- **Assignment Problem** (Hungarian Algorithm)
- **Transportation Problem** (Vogel’s Approximation Method)

Each algorithm is modularized in its own header file for clarity and reusability.

---

## ✨ Features

- ✔️ **Simplex Method** – Solves LP problems in standard form  
- ✔️ **Dual Simplex Method** – Solves LP problems with infeasible starting points  
- ✔️ **Hungarian Algorithm** – Solves optimal assignment of workers to tasks  
- ✔️ **Vogel’s Approximation Method (VAM)** – Provides initial feasible solution for transportation problems  
- ✔️ **Interactive Menu Interface** – Simple command-line navigation  
- ✔️ **Formatted Output** – Easy-to-read results for each method  

---

## 📁 File Structure

```
project/
├── simplex.hpp          # Simplex Method
├── dual_simplex.hpp     # Dual Simplex Method
├── assignment.hpp       # Hungarian Algorithm
├── transportation.hpp   # Vogel's Approximation Method
└── main.cpp             # Main program and user interface
```

---

## ⚙️ Compilation & Execution

### Compile:
```bash
make
```

### Run:
```bash
make run
```

---

## 🧑‍💻 Menu and Usage

After running the executable, you'll see the following menu:

```
Operations Research Methods:
1. Simplex Method
2. Dual Simplex Method
3. Assignment Problem (Hungarian Algorithm)
4. Transportation Problem (Vogel's Approximation)
5. Exit
Enter your choice (1-5):
```

Select an option and follow the interactive prompts to input your problem data.

---

## 📌 Method Details

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
- Input: Number of workers/tasks (`n`)  
- Enter a square `n × n` cost matrix  
- Output: Optimal assignment and minimum cost

---

### 4. Transportation Problem (Vogel’s Approximation Method)
- Input:
  - Number of sources and destinations  
  - Supply for each source  
  - Demand for each destination  
  - Cost matrix  


---

## 🚚 Example Inputs

### Simplex Example:
```
Enter number of constraints: 2
Enter number of variables: 2

Enter coefficients of each constraint followed by RHS:
Constraint 1, Coefficient of x1: -1
Constraint 1, Coefficient of x2: 1
Constraint 1, RHS: -1
Constraint 2, Coefficient of x1: 1
Constraint 2, Coefficient of x2: 2
Constraint 2, RHS: 6

Enter coefficients of the objective function (to maximize):
Coefficient of x1: 3
Coefficient of x2: 2
```

### Assignment Example:
```
Enter number of workers: 3
Enter number of tasks: 3

Enter the cost matrix (3 x 3):
Worker 1: 90 75 75
Worker 2: 35 85 55
Worker 3: 125 95 90
```

### Transportation Example:
```
  Enter number of sources: 2
  Enter number of destinations: 2
  Enter supply values:
  Source 1: 20
  Source 2: 30
  Enter demand values:
  Destination 1: 25
  Destination 2: 25
  Enter cost matrix:
  Cost from S1 to D1: 8
  Cost from S1 to D2: 6
  Cost from S2 to D1: 10
  Cost from S2 to D2: 7
```

---

## 📊 Dependencies
- Standard C++ Library (no external dependencies)

---

## 📅 Notes
- All inputs should be numerical (integers or floats)
- Basic input validation included
- For large inputs, output may exceed standard terminal width


