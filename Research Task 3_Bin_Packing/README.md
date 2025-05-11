# Bin Packing - First Fit Algorithm

A C++ implementation of the First Fit bin packing algorithm for optimal resource allocation.

## Features
- Implements First Fit strategy
- Handles oversized items with error reporting
- Displays detailed bin contents and total sums
- Supports custom item lists and bin capacities
- Clear terminal output formatting

A C++ implementation of the First Fit bin packing algorithm for resource allocation optimization.


## Bin Packing Algorithms

### First Fit Algorithm
**Definition**:  
A greedy algorithm that:
1. Processes items in given order
2. Places each item in the first bin with available space
3. Creates new bin if no existing bin can accommodate the item

**Algorithm Steps**:
1. Initialize empty bins list
2. For each item:
   - If item > bin capacity → mark as illegal
   - Else try to place in first bin with sufficient remaining space
   - If no fit found → create new bin
3. Return valid bins and illegal items list

**Complexity**:
| Metric        | Value       |
|---------------|-------------|
| Time          | O(n²)       |
| Space         | O(n)        |

### Best Fit Algorithm
**Definition**:  
Alternative strategy that:
1. Processes items in given order
2. Places each item in the bin with *smallest remaining space* that can accommodate it
3. Creates new bin if no existing bin can accommodate the item

**Comparison**:
| Feature             | First Fit       | Best Fit        |
|-----------------    |-----------------|-----------------|
| Placement Rule      | First available | Tightest fit    |
| Average Performance | Faster          | Better space use|
| Complexity          | O(n²)           | O(n log n)      |

## Requirements
- C++17 compatible compiler (g++/clang++)
- CMake 3.10+ (optional)

## Installation

### Basic Compilation
```bash
g++ -o bin_packer main.cpp -std=c++17
- CMake 3.10+ (optional)

## Installation
### Basic Compilation
```bash
g++ -o bin_packer main.cpp -std=c++17
