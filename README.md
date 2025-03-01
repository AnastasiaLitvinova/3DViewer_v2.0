# 3DViewer

## Description

- High-performance 3D renderer in C++17, Qt6 and MVC, supporting .obj files.

## Goal

- Effective visualization of 3D models with the possibility of transformation and customization.

## Architecture

- MVC (Model, View, Controller)
- Patterns
  - Facade (Manipulation)
  - Strategy (Parser, Affine Transformations)
  - Singleton (Controller)

## Requirements

- C++17
- Qt6.

****Installation (macOS):**
1. `git clone <repository_url>`
2. `cd 3D Viewer_v2.0/src`
3. `make`
4. `open ./3D Viewer/3d Viewer.app`

## Functionality

- Download .obj
- Affine transformations
  - Transfer
  - Rotation
  - Scaling
- Customize Appearance
  - Lines
  - Vertices
  - Color
  - Projection
- Export to BMP/JPEG
- Create GIF animations
- Saving settings
- Unit tests
- Google C++ Style Guide.

## Screenshots and GIF

- The interface is available after selecting the correct model via the `Choose File` button:
  ![img_1][img_1]
- It is also possible to save a screenshot to any selected folder:
  ![img_2][img_2] \
  *Window after saving* \
  ![img_3][img_3] \
  *Screenshot taken*
- After clicking the `GIF` button, any manipulations with the model will be recorded:
  ![img_4][img_4] \
  *After the recording, a window will appear* \
  ![img_5][img_5] \
  *The result of the manipulations is a `GIF`*

[img_1]: images/img_1.png
[img_2]: images/img_2.png
[img_3]: images/cubecarcas.jpg
[img_4]: images/img_3.png
[img_5]: images/cubecarcas.gif

## Authors

Anastasia([@nanali96](https://t.me/nanali96)), Kasim([@Sckroll](https://t.me/Sckroll)), Emilia([@liaaemi](https://t.me/liaaemi)).
