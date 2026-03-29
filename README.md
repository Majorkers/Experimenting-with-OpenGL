# Experimenting with OpenGL

Developed by [Kourkouk](https://github.com/Kourkouk) & [ThanasisZormpas](https://github.com/ThanasisZormpas).

This repository is a collection of 3D computer graphics projects and exercises built with **C++** and **OpenGL** (using the GLUT library). It serves as our sandbox for exploring matrix transformations, 3D environments, and rendering.

---

## Projects Overview

### 1. Cube Transformations (Scaling & Shearing)
**Folder:** [`/Cube_Transformations`](./Cube_Transformations)

This project explores fundamental 3D transformations applied to a multi-colored cube using the fixed-function pipeline and **Display Lists** (`glGenLists`) for optimized rendering.
* **`scaling_cube.c`**: Implements continuous rotation on multiple axes alongside a pulsing scale effect.
* **`shearing_cube.c`**: Implements a custom 4x4 Shearing Matrix using `glMultMatrixf`, as OpenGL lacks a native `glShear` function. The cube dynamically leans back and forth based on trigonometric calculations.

### 2. 3D Village Scene
**Folder:** [`/Village_Scene`](./Village_Scene) | **File:** `village_scene.c`

A more complex project focusing on constructing a full 3D environment and scene graph.
* **Features:** Features an interactive 3D environment with a dynamic Day/Night cycle (animated light source), interactive camera controls via arrow keys, a toggleable spotlight, and a right-click context menu to switch between Smooth/Flat shading and lighting modes.
* **Geometry:** The scene consists of a ground plane and multiple distinct houses. The houses are constructed using hierarchical transformations (glPushMatrix/glPopMatrix) combining solid cubes for the main structure and custom-drawn polygon primitives (GL_QUADS, GL_TRIANGLES) for the roofs, complete with proper surface normals for accurate lighting.

---

## How to Run Locally

To explore these projects on your own machine:

1. Clone this repository: 
   ```bash
   git clone [https://github.com/Majorkers/Experimenting-with-OpenGL.git](https://github.com/Majorkers/Experimenting-with-OpenGL.git)
