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
Found a path!
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

The algorithm doesnot find the optimum path but try to find 'a' path to the target. 
Improvements can be made to midify the logic to find and efficient path.
