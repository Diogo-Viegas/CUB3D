*This project has been created as part of the 42 curriculum by dviegas and gocaetan*

---

# CUB3D — A Wolfenstein-Style Raycasting Engine


A first-person 3D maze renderer built entirely in C, inspired by the legendary **Wolfenstein 3D** (1992). Using the raycasting technique and the **MiniLibX** graphical library, the engine projects a 2D map into a real-time 3D perspective.

---


## Description

CUB3D is a graphics programming project from the 42 curriculum. The goal is to implement a functional 3D game engine from scratch using the **raycasting** algorithm — the same technique used in early FPS games before true 3D rendering was computationally feasible.

The engine reads a `.cub` scene file that defines the map layout, wall textures, and floor/ceiling colours. It then renders the scene in real time from a first-person perspective, handling player movement, wall collision, and texture mapping across all four cardinal directions.

This project covers:
- Low-level graphics programming with direct pixel manipulation
- Linear algebra for ray-direction and distance calculations
- File parsing and strict input validation
- Memory management with no leaks
- Event-driven architecture via MiniLibX hooks

---

## Features

### Mandatory
- Real-time raycasting renderer using the **DDA algorithm**
- Textured walls mapped to four directions: North, South, East, West (`.xpm` format)
- Configurable floor and ceiling colours (RGB)
- Player movement: walk forward/backward, strafe left/right
- Player rotation: left/right arrow keys
- Clean exit on `ESC` key or window close button

### Bonus
- **Wall collision detection** — the player cannot walk through walls
- **Minimap** — top-down view of the map with player position and orientation
- **Mouse rotation** — look around by moving the mouse

---



## Instructions

### Requirements

- **OS**: Linux or macOS
- **Compiler**: `gcc` or `clang`
- **MiniLibX**: included or installed on your system
  - On Linux, also requires: `libX11`, `libXext` (`sudo apt install libx11-dev libxext-dev`)
  - On macOS, uses the native Cocoa framework

### Cloning the repository

```bash
git clone git@vogsphere.42lisboa.com:vogspher intra-uuid-d98cc1a0-bda0-4c6a-a22d-8a946637c901-7346855-gocaetan
cd CUB3D
```

### Compilation

**Mandatory part:**
```bash
make
```



**Clean build artifacts:**
```bash
make clean    # removes .o files
make fclean   # removes .o files and the executable
make re       # full recompile
```

### Running the program

```bash
./cub3D maps/example.cub
```

The program takes exactly **one argument**: the path to a valid `.cub` map file.

**Examples:**
```bash
./cub3D maps/basic.cub
./cub3D maps/large_maze.cub
```

### Error handling

If the map file is invalid, missing, or malformed, the program prints a descriptive error message to `stderr` and exits with code `1`. No graphical window will open.

---

## Map Format

The `.cub` file defines the scene. It must contain the following elements (texture and colour declarations may appear in any order, but the **map must be last**):

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,50
C 100,150,255

111111111
100000001
10N000001
100000001
111111111
```

### Texture identifiers
| Key | Meaning            |
|-----|--------------------|
| `NO` | North wall texture |
| `SO` | South wall texture |
| `WE` | West wall texture  |
| `EA` | East wall texture  |

### Colour format
- `F R,G,B` — Floor colour (each value 0–255)
- `C R,G,B` — Ceiling colour (each value 0–255)

### Map rules
| Character | Meaning                    |
|-----------|----------------------------|
| `1`       | Wall                       |
| `0`       | Empty floor                |
| `N` `S` `E` `W` | Player start position and facing direction |
| ` ` (space) | Void (treated as out-of-bounds) |

- The map must be **fully enclosed** by walls (`1`) — no open edges
- There must be **exactly one** player starting position
- Any other character is invalid and will cause the program to exit with an error

---

## Controls

| Key / Input        | Action              |
|--------------------|---------------------|
| `W` / `↑`          | Move forward        |
| `S` / `↓`          | Move backward       |
| `A`                | Strafe left         |
| `D`                | Strafe right        |
| `←`                | Rotate view left    |
| `→`                | Rotate view right   |
| Mouse (bonus)      | Rotate view         |
| `ESC`              | Exit the program    |
| Window close (✕)   | Exit the program    |
| `ALT`              | Lock/Unlock Mouse Movement

---

## Resources

### Raycasting & Graphics Theory

- **Lode's Raycasting Tutorial** — The canonical reference for DDA-based raycasting, texture mapping, and projection maths:
  https://lodev.org/cgtutor/raycasting.html

- **Permadi's Ray-Casting Tutorial** — A more visual, step-by-step explanation of the geometry behind raycasting:
  https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

- **3DSage YouTube Series** — "Make Your Own Raycaster" — practical video walkthrough:
  https://www.youtube.com/watch?v=gYRrGTC7GtA

- https://hackmd.io/@nszl/H1LXByIE2

### MiniLibX

- **MiniLibX Linux Documentation** (42 official):
  https://harm-smits.github.io/42docs/libs/minilibx

- **MiniLibX Getting Started Guide**:
  https://github.com/42Paris/minilibx-linux

### Mathematics

- **Bresenham's Line Algorithm** (DDA context):
  https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

- **Digital Differential Analyzer (DDA)**:
  https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)

### Project Reference

- **42 CUB3D Subject PDF** — Official project specification (available on your 42 intranet)
- **mcombeau/cub3D** — A well-documented reference implementation:
  https://github.com/mcombeau/cub3D

---

### AI Usage in This Project

AI assistance (specifically Claude by Anthropic) was used selectively during development of this project. Below is a transparent breakdown of where and how it was applied:

| Area | AI Assistance Used |
|------|--------------------|
| **Debugging** | Helped trace subtle pointer and memory issues during parsing, particularly with `get_next_line` buffer management |
| **Documentation** | This README was drafted with AI assistance, including structure, formatting, and wording |
| **Conceptual clarification** | Used to cross-check understanding of DDA step calculations and perpendicular distance correction (fish-eye fix) |
| **Code review** | AI was used to review memory cleanup routines and identify potential leaks before Valgrind testing |

AI was **not** used to write core algorithmic code (raycasting, texture mapping, collision detection) or to replace understanding of the subject matter. All code was written, understood, and is fully explainable by the authors.

---

*Made by dviegas & gocaetan, 42 Lisboa*
