# CST207 Group Project

## Dataset Generation & Feature Extraction Module

This repository contains the dataset generation and feature extraction module for CST207.

### Project Structure

```
dataset-generation-feature-extraction/
├── dataset.h              # Header file with function declarations
├── dataset.cpp            # Implementation of all functions
├── test_generation.cpp    # Test file for data generation
├── test_extraction.cpp    # Test file for feature extraction
├── test_gen              # Compiled test executable (generation)
├── test_ext              # Compiled test executable (extraction)
└── 功能说明.md            # Detailed documentation in Chinese
```

### Features

**Data Generation Functions (5):**
- `generateRandom(n)` - Random arrays
- `generateNearlySorted(n, swaps)` - Nearly sorted arrays
- `generateReversed(n)` - Reversed arrays
- `generateFewUnique(n, uniqueCount)` - Arrays with few unique values
- `generateLargeRandom(n)` - Large random arrays

**Feature Extraction Functions (3):**
- `getDatasetSize(arr)` - Get array size
- `calculateSortedness(arr)` - Calculate sortedness (0-100%)
- `calculateUniqueRatio(arr)` - Calculate unique element ratio (0.0-1.0)

### How to Compile and Run

```bash
cd dataset-generation-feature-extraction

# Compile and run data generation tests
g++ -std=c++11 -o test_gen dataset.cpp test_generation.cpp
./test_gen

# Compile and run feature extraction tests
g++ -std=c++11 -o test_ext dataset.cpp test_extraction.cpp
./test_ext
```

### Documentation

See [功能说明.md](dataset-generation-feature-extraction/功能说明.md) for detailed documentation in Chinese.

---

**Course:** CST207  
**Module:** Dataset Generation & Feature Extraction
