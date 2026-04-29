# A-maze-d - Multi-Robot Maze Solver

A pathfinding system that navigates multiple robots through a maze simultaneously, finding all shortest paths and optimally distributing robots to minimize total traversal time.

## Core Algorithm: BFS-Based Shortest Path with Flow Optimization

### Step 1: Distance Computation via BFS (Reverse Direction)

The algorithm begins with a **reverse BFS** starting from the END room:

1. Initialize all rooms with `distance = -1`
2. Set `distance(END) = 0`
3. Process each room in queue order, updating neighbors: `neighbor->distance = current->distance + 1`
4. Result: Every room has its distance to the END room

```
Example maze: [0] - [2] - [3] - [1(END)]

After BFS from END:
[0]: distance = 3
[2]: distance = 2
[3]: distance = 1
[1]: distance = 0
```

This reverse approach is crucial: robots can always move toward decreasing distance values, guaranteeing convergence to the exit.

### Step 2: Path Extraction (Finding All Shortest Paths)

Once distances are computed, extract all shortest non-intersecting paths:

1. From START, find all neighbors with valid distances (`distance == -2` means already used)
2. Follow a greedy algorithm: always move to a neighbor room with `distance = current->distance - 1`
3. Mark visited rooms with `distance = -2` to avoid reusing them in other paths
4. Path ends when reaching the END room

Key insight: By marking visited rooms, we extract **all shortest paths without overlap**. Each path is a valid solution with optimal length.

### Step 3: Robot Assignment (Cost Function Optimization)

Assign each robot to a path minimizing total traversal time:

```c
cost(path) = path->length + path->robots_count
```

For each robot, choose the path with minimum cost (length + current occupancy). This balances:
- **Long paths get robots first** (fewer robots competing)
- **Occupied paths are deprioritized** (unless still cheaper than alternatives)

Result: Robots are distributed to minimize bottlenecks.

### Step 4: Movement Simulation

Execute movement in discrete cycles:

1. Each cycle, attempt to move every robot one room forward
2. Check: target room is empty (or is END/START)
3. Mark current room as free, mark next room as occupied
4. Print moves atomically: `P1-room2 P2-room3`
5. Continue until all robots reach END

Key constraint: **One robot per non-start/end room** prevents conflicts.

## Implementation Details

### Data Structures

**Room (graph node):**
```c
typedef struct {
    char *name;           // Room identifier
    int distance;         // Distance to END (-1 = unvisited, -2 = used in path)
    bool occupied;        // Is a robot currently here?
    tunnel_t *tunnels;    // Adjacency list
} room_t;
```

**Path (solution trajectory):**
```c
typedef struct {
    room_t **rooms;       // Ordered room sequence
    int length;           // Path length
    int robots_count;     // Robots assigned to this path
} path_t;
```

**Robot (mobile entity):**
```c
typedef struct {
    int id;               // Robot identifier (1-indexed)
    path_t *path;         // Assigned path
    int pos_in_path;      // Current position in path (-1 = not started)
    bool finished;        // Has reached END?
} robot_t;
```

### File Format Parsing

Input format:
```
<number_of_robots>
##start
<room_name> <x> <y>
<room_name> <x> <y>
##end
<room_name> <x> <y>
<room1_name>-<room2_name>  (tunnel)
```

The parser builds an adjacency list graph, handles comments (`#`), and validates start/end existence.

## Complexity Analysis

- **Distance computation:** O(R + T) where R = rooms, T = tunnels (BFS is linear)
- **Path extraction:** O(R) per path, multiple paths possible (worst: factorial in graph structure)
- **Robot assignment:** O(Robots × Paths)
- **Movement simulation:** O(Turns × Robots) where Turns ≤ longest path

## How to Use

### Compilation
```bash
make
```

### Execution
```bash
./amazed < input_file
```

### Example Input
```
3
##start
0 1 0
##end
1 13 0
2 5 0
3 9 0
0-2
2-3
3-1
```

### Example Output
```
#number_of_robots
3
#rooms
##start
0 1 0
##end
1 13 0
2 5 0
3 9 0
#tunnels
0-2
2-3
3-1
#moves
P1-2 P2-0
P1-3 P2-2 P3-0
P1-1 P2-3 P3-2
P2-1 P3-3
P3-1
```

All robots reach the exit in 5 turns with optimal path distribution.
