# Battleship Pathfinding

## Description

This project implements a **modified A\*** pathfinding algorithm to navigate a battleship from a start to a target location on a 2D terrain map. The algorithm only considers **horizontal and vertical** movements (no diagonals) and avoids **elevated terrain**, which is marked as impassable.

The terrain map is read from a **JSON file**, and pathfinding is performed based on cost calculations (Manhattan distances). The grid is printed with start (`@`), target (`*`), elevation (`8`), and path markings (`@` on ground).

This work was developed as part of a coding challenge for **Globus Medical**.

---

## Files

| Filename              | Description                                                            |
| --------------------- | ---------------------------------------------------------------------- |
| `main.cpp`            | Entry point: parses input, initializes battleship and runs pathfinding |
| `pathfinding.hpp/cpp` | Contains A\*-based pathfinding logic and update state machine          |
| `read_map.hpp/cpp`    | Handles JSON parsing and terrain data formatting                       |
| `definitions.hpp`     | Core data structures and the `battleship` class definition             |
| `Makefile`            | Build system for compiling all source files                            |

---

## Important Classes and Functions

### `class battleship`

Encapsulates the state and logic for one ship navigating the map.

Key methods:

* `insert_nodes()` – Parses terrain from JSON and calculates cost for each node.
* `get_valid_neighbours()` – Returns adjacent traversable nodes.
* `print_nodes()` – Prints the full map.
* `print_path()` – Prints only the computed path.

### `int find_path(battleship *bu)`

Core A\* logic using cost estimates and a state machine to trace from start to target.

### `int read_file(Document *doc, string f_name)`

Reads and parses the input `.json` map file into a RapidJSON `Document`.

### `void print_map_and_mark(...)`

Prints the raw map and marks the `start` and `target` fields based on values.

---

## Instructions to Build

### Requirements:

* C++20 or higher
* [RapidJSON](https://github.com/Tencent/rapidjson) (header-only, included in the repo)
* A terminal with `make` installed

### Build:

From the root directory, run:

```bash
make
```

This will produce an executable named `pathfinding`.

### Run:

```bash
./pathfinding <path_to_map.json> <x_max> <y_max>
```

Example:

```bash
./pathfinding input/map.json 32 32
```

---

## Testing Options

* You can change the map file to test different terrains and obstacles.
* The `print_map_and_mark()` output lets you visually inspect the map and path.
* Modify start and target positions in the input file or use different scenarios.

---

## Results

Once executed, the program:

* Prints the parsed terrain map.
* Shows the valid path (if found), replacing traversed ground nodes with `@`.
* Displays the path-finding status (`Found a path!` or `No valid path found!`).

Sample Output:

```
Map file: .\input\map.json
x_max: 32
y_max: 32
File object created
Reading map..
- - - 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 - - - - 8 8 8 8 8 8 
- - - 8 - - - - - - - - - - - - - 8 - - - 8 - - - - 8 - - - - - 
- - @ 8 - - - - - - - - - - - - - 8 - - - 8 - - - - 8 - - - - - 
- - - 8 - - - 8 8 8 8 - - - - - - 8 - - - 8 - - - - 8 - - - - - 
- - - 8 - - 8 8 8 8 8 8 - - - - 8 8 - - - 8 - - - - 8 8 8 8 8 - 
- - - 8 - - 8 - - - - 8 - - - - 8 - - - - 8 - 8 - - 8 8 - - 8 - 
- - - 8 - 8 - - - - - 8 8 - - - 8 - - - - 8 - 8 - - 8 - - - 8 - 
- - - 8 - 8 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - 8 - - - 8 - 
- - - 8 - - 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - 8 8 - - 8 8 
- 8 8 8 - - 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - - 8 - - - 8 
- 8 - - - - 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - - 8 8 - - 8 
- 8 - - - - 8 - - - - - - - - - - 8 - - - 8 - 8 - - - - - - - 8 
- 8 8 8 - 8 - - - - - - - - - - - 8 - - - 8 - 8 - - - - - - - 8 
- - - 8 8 8 - - - - - - - - - - - 8 - - - 8 - 8 - - - 8 8 - - 8 
- - - - - - - - - - - - - - - - - 8 - - - 8 - 8 - - - 8 - - - 8 
- - - - - - - - - - - - - - - - - 8 - - - 8 - 8 - - 8 8 - - - 8 
- - 8 8 8 8 8 8 8 - - - - - - - - 8 - - - 8 - 8 - - 8 - - - - 8 
- - - - 8 8 - - 8 8 - - - - - - - 8 - - - 8 - 8 - - 8 - - - - 8 
- - - - 8 - - - - 8 - - - 8 - - - 8 8 - - 8 8 8 - 8 8 - - - - 8 
- - - - 8 - - - - 8 - - 8 8 - - - - - - - - - - - 8 - - - - - 8 
- - - - 8 - - - - 8 - - 8 - - - - - - - - - - - - 8 - - - - - 8 
- - - - 8 - - - - 8 - - 8 - 8 8 8 8 8 8 8 - - - - 8 - - - - - 8 
- - - - 8 - - - - - - - 8 - - - - - - - 8 - - - - 8 - - - - - 8 
- - - 8 8 - - - - - - - 8 - - - - - - - 8 - - - - 8 - - - - - 8
- - 8 8 - - - - - - - - 8 - - - - - - 8 8 - - - - 8 - - - - - 8
- - 8 - - - - - - - - - 8 - - - - - - 8 - - - - - 8 - - - - - 8
8 8 8 - - - - - - - - 8 8 - - - - - - 8 - - - - 8 8 - - - - - 8
8 8 8 8 - - - - 8 8 8 - - - - - - - - 8 - - - - 8 - - - - - - 8
8 - - 8 8 8 8 8 8 - - - - - - - - - - 8 - - - 8 - - - - * - - 8 
8 - - - - - - - - - - - - - - - - - - - 8 8 8 - - - - - - - 8 8
8 - 8 8 8 8 8 8 8 8 8 8 8 8 - - - - - - - - - - - - - - - - 8 8
8 8 8 - - - - - - - - - - - 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8
Start at (2,2)
Target at (28,28)
Running path finding..
Found a path! Points are:
(2,2), (3,2), (4,2), (5,2), (6,2), (7,2), (8,2), (8,1), (7,1), (7,2), (8,2), (8,1), (8,0), (9,0), (10,0), (11,0), (12,0), (13,0), (13,1), (13,2), (14,2), (15,2), (15,3), (15,4), (15,5), (15,6), (15,7), (15,8), (15,9), (16,9), (16,10), (17,10), (18,10), (19,10), (20,10), (21,10), (22,10), (23,10), (24,10), (25,10), (26,10), (26,9), (25,9), (25,10), (25,11), (24,11), (23,11), (22,11), (21,11), (20,11), (19,11), (18,11), (18,12), (17,12), (17,13), (17,14), (18,14), (19,14), (20,14), (20,15), (20,16), (20,17), (20,18), (20,19), (20,20), (20,21), (21,21), (22,21), (23,21), (24,21), (25,21), (26,21), (27,21), (28,21), (28,22), (27,22), (27,23), (26,23), (25,23), (25,24), (24,24), (23,24), (22,24), (21,24), (20,24), (19,24), (18,24), (17,24), (17,25), (16,25), (15,25), (14,25), (14,26), (13,26), (12,26), (12,27), (12,28), (11,28), (11,27), (11,26), (11,25), (12,25), (13,25), (13,26), (14,26), (14,25), (14,24), (15,24), (16,24), (17,24), (18,24), (19,24), (19,23), (20,23), (21,23), (22,23), (23,23), (24,23), (24,24), (25,24), (25,23), (25,22), (26,22), (27,22), (28,22), (28,21), (28,20), (27,20), (27,21), (28,21), (28,22), (27,22), (27,23), (26,23), (25,23), (25,24), (24,24), (23,24), (22,24), (21,24), (20,24), (19,24), (18,24), (17,24), (17,25), (16,25), (15,25), (14,25), (14,26), (13,26), (12,26), (12,27), (12,28), (12,29), (13,29), (14,29), (14,28), (15,28), (16,28), (17,28), (18,28), (19,28), (20,28), (21,28), (22,28), (23,28), (24,28), (25,28), (26,28), (27,28), (28,28)
Printing path..
- - - 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 - - - - 8 8 8 8 8 8 
- - - 8 - - - - - - - - - - - - - 8 - - - 8 - - - - 8 - - - - - 
- - @ 8 - - - - - - - - - - - - - 8 - - - 8 - - - - 8 - - - - - 
- - @ 8 - - - 8 8 8 8 - - - - - - 8 - - - 8 - - - - 8 - - - - - 
- - @ 8 - - 8 8 8 8 8 8 - - - - 8 8 - - - 8 - - - - 8 8 8 8 8 - 
- - @ 8 - - 8 - - - - 8 - - - - 8 - - - - 8 - 8 - - 8 8 - - 8 - 
- - @ 8 - 8 - - - - - 8 8 - - - 8 - - - - 8 - 8 - - 8 - - - 8 - 
- @ @ 8 - 8 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - 8 - - - 8 - 
@ @ @ 8 - - 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - 8 8 - - 8 8
@ 8 8 8 - - 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - - 8 - - - 8
@ 8 - - - - 8 - - - - - 8 - - - 8 - - - - 8 - 8 - - - 8 8 - - 8
@ 8 - - - - 8 - - - - - - - - - - 8 - - - 8 - 8 - @ @ @ @ - - 8
@ 8 8 8 - 8 - - - - - - - - - - - 8 - - - 8 - 8 - @ @ @ @ @ - 8
@ @ @ 8 8 8 - - - - - - - - - - - 8 - - - 8 - 8 - @ @ 8 8 @ - 8
- - @ - - - - - - - - - - - - - - 8 - - - 8 - 8 @ @ @ 8 @ @ - 8
- - @ @ @ @ @ @ @ @ - - - - - - - 8 - - - 8 - 8 @ @ 8 8 @ - - 8
- - 8 8 8 8 8 8 8 @ @ - - - - - - 8 - - - 8 - 8 @ @ 8 - @ - - 8 
- - - - 8 8 - - 8 8 @ - @ @ @ - - 8 - - - 8 - 8 @ @ 8 - @ - - 8
- - - - 8 - - - - 8 @ @ @ 8 @ - - 8 8 - - 8 8 8 @ 8 8 - @ - - 8
- - - - 8 - - - - 8 @ @ 8 8 @ - - - - - - - - @ @ 8 - - @ - - 8
- - - - 8 - - - - 8 @ @ 8 - @ @ @ @ @ @ @ @ - @ @ 8 - - @ - - 8
- - - - 8 - - - - 8 @ @ 8 - 8 8 8 8 8 8 8 @ - @ @ 8 - - @ - - 8
- - - - 8 - - - - - @ @ 8 - - - - - - - 8 @ - @ @ 8 - - @ - - 8
- - - 8 8 - - - - - @ @ 8 - - - - - - - 8 @ - @ @ 8 - - @ - - 8 
- - 8 8 - - - - - - @ @ 8 - - - - - - 8 8 @ - @ @ 8 - - @ - - 8
- - 8 - - - - - - @ @ @ 8 - - - - - - 8 - @ @ @ @ 8 - - @ - - 8
8 8 8 - - - - - - @ @ 8 8 - - - - - - 8 - @ @ @ 8 8 - - @ - - 8
8 8 8 8 - - - - 8 8 8 - - - - - - - - 8 @ @ @ @ 8 - - - @ - - 8
8 - - 8 8 8 8 8 8 - - - - - - - - - - 8 @ @ @ 8 - - - - * - - 8
8 - - - - - - - - - - - - - - - - - - - 8 8 8 - - - - - - - 8 8
8 - 8 8 8 8 8 8 8 8 8 8 8 8 - - - - - - - - - - - - - - - - 8 8
8 8 8 - - - - - - - - - - - 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 
...
```

If no valid path exists, the program gracefully reports failure.

## Future Development notes:

The algorithm does not find the optimal path but tries to find 'a' path to the target. 
Improvements can be made to midify the logic to find and efficient path.
