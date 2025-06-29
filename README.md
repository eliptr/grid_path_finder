# grid_path_finder

This project simulates a vacuum cleaner navigating through a room represented as a 2D grid with obstacles. It calculates and prints the shortest path from the vacuum cleaner's starting position to a target position, avoiding obstacles and only turning at viable corners.


## what it does
- My program reads a 2D map of the room with obstacles.
- It detects all valid "corner" positions that can be used to change direction.
- It calculates the shortest viable path using a custom heuristic (A*-like approach).
- Outputs the path as a series of directions:
  - L for Left
  - R for Right
  - U for Up
  - D for Down
- Visualizes the final path in the grid.

## how to build and run
- The program expects input from stdin in the following format:

<dimension>
  
<start_x> <start_y>

<target_x> <target_y>

<grid> (row by row, top to bottom)

- dimension: Integer for the size of the square grid (e.g., 10).
- start_x, start_y: Starting position of the vacuum.
- target_x, target_y: Target location to reach.
- grid: A grid of 0s (empty space) and 1s (obstacles), read top to bottom and left to right.

- how to build and run
  bash
  gcc -o finder finder.c -lm
  ./finder < input.txt

## example
- input.txt:

5 <br>
0 0 <br>
4 4 <br>
00000 <br>
00100 <br>

00100

00100

00000

- Output:
  - The path as a string of directions (e.g., RRRRDDDD). 
  - The updated grid with the path marked: 
  - 2 for visited path
  - 3 for start and target positions

## How It Works
- Corner Detection: Identifies all corner points in the map that the vacuum can use to change direction.
- Pathfinding: Uses a simplified custom A* algorithm prioritizing shortest travel distance and fewer turns with a custom priority queue.
- Traversal Logic: At each node it detects all the possible nodes it can travel to if the path is clear and prioritizes them based on which is closer to the target.

## Limitations
Assumes a square grid.

No real-time interactivity — input and output are done via terminal.
