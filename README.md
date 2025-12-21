# CST207 Group Project

## Project Overview

This repository contains the complete implementation of the CST207 Group Project: **AI-Driven Sorting Algorithm Optimizer**.

The project uses AI (k-Nearest Neighbors algorithm) to predict the best sorting algorithm for different datasets based on their features.

---

## Dataset Generation & Feature Extraction Module

This repository contains the dataset generation and feature extraction module for CST207.

### Project Structure

```
CST207-group-proj/
├── dataset-generation-feature-extraction/
│   ├── dataset.h              # Header file with function declarations
│   ├── dataset.cpp            # Implementation of all functions
│   ├── test_generation.cpp    # Test file for data generation
│   ├── test_extraction.cpp    # Test file for feature extraction
│   └── 功能说明.md             # Detailed documentation in Chinese
│
├── knn_predictor.h            # k-NN predictor header (Member 4)
├── knn_predictor.cpp          # k-NN predictor implementation
├── sorting_algorithms.h       # Sorting algorithms header
├── sorting_algorithms.cpp     # Sorting algorithms implementation
├── utils.h                    # Utility functions header
├── utils.cpp                  # Utility functions implementation
├── main.cpp                   # Main program with interactive menu
│
├── compile.bat                # Windows compilation script
├── README_KNN.md              # Detailed k-NN module documentation
└── TESTING.md                 # Testing guide and procedures
```

---

## Features

### Data Generation Functions (5)
- `generateRandom(n)` - Random arrays
- `generateNearlySorted(n, swaps)` - Nearly sorted arrays
- `generateReversed(n)` - Reversed arrays
- `generateFewUnique(n, uniqueCount)` - Arrays with few unique values
- `generateLargeRandom(n)` - Large random arrays

### Feature Extraction Functions (3)
- `getDatasetSize(arr)` - Get array size
- `calculateSortedness(arr)` - Calculate sortedness (0-100%)
- `calculateUniqueRatio(arr)` - Calculate unique element ratio (0.0-1.0)

### k-NN AI Module (Member 4)
- Predicts optimal sorting algorithm based on dataset features
- Uses k=5 nearest neighbors voting mechanism
- 30 training samples covering various data patterns
- Supports 4 sorting algorithms: Bubble, Insertion, Merge, Quick Sort

### Sorting Algorithms (4)
- **Bubble Sort** - O(n²) with early termination
- **Insertion Sort** - O(n²) average, O(n) best case
- **Merge Sort** - O(n log n) guaranteed, stable
- **Quick Sort** - O(n log n) average case

---

## How to Compile and Run

### Prerequisites
- g++ compiler with C++11 support
- See [TESTING.md](TESTING.md) for detailed installation instructions

### Compilation

**Using compile script (Windows):**
```bash
compile.bat
```

**Manual compilation:**
```bash
g++ -std=c++11 -o ai_sorter dataset-generation-feature-extraction/dataset.cpp knn_predictor.cpp sorting_algorithms.cpp utils.cpp main.cpp
```

### Running the Program

```bash
ai_sorter.exe     # Windows
./ai_sorter       # Linux/Mac
```

---

## Documentation

- **[README_KNN.md](README_KNN.md)** - Comprehensive k-NN module documentation (Chinese/English)
- **[TESTING.md](TESTING.md)** - Testing guide and verification procedures
- **[功能说明.md](dataset-generation-feature-extraction/功能说明.md)** - Dataset module documentation (Chinese)

---

## Testing

See [TESTING.md](TESTING.md) for:
- Detailed testing procedures
- Recommended test cases
- Verification checklist
- Troubleshooting guide

---

**Course:** CST207  
**Project:** AI-Driven Sorting Algorithm Optimizer  
**Member 4 Module:** k-Nearest Neighbors Predictor
