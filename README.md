# Graph Visualization Tool

A C++ application for visualizing paths and maze structures using Graphviz. This tool generates .gv files that can be rendered into graphical representations of paths through mazes and other grid-based structures.

## Features

- **Path Visualization**: Generate clean, directed graphs showing paths between points
- **Maze Integration**: Visualize paths overlaid on maze structures with wall detection
- **Color Coding**: Automatic color differentiation for start points, end points, path nodes, and obstacles
- **Multiple Algorithms**: Support for both BFS and Dijkstra pathfinding algorithms
- **Graphviz Compatibility**: Outputs standard gv files compatible with Graphviz tools

## Algorithms Implemented

### BFS (Breadth-First Search)
- Finds the shortest path in terms of number of steps
- Guarantees optimal solution for unweighted graphs
- Uses queue-based traversal

### Dijkstra Algorithm  
- Finds the shortest path considering edge weights
- Optimal for weighted graphs (all weights = 1 in this implementation)
- Uses priority queue for efficient node selection
- Guarantees shortest path in weighted environments

## Prerequisites

### Required Software
- **C++ Compiler** (C++17 or higher)
- **Graphviz** 

### Installing Graphviz

**Windows:**
```bash
choco install graphviz