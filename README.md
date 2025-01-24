# An application for viewing a 3D model created using C++, Qt, and the MVC pattern

## Contents

1. [Description](#description)
    - [Overview](#overview)
    - [Architecture and Design Choices](#architecture-and-design-choices)
    - [Key Features and Performance](#key-features-and-performance)
2. [Technologies](#technologies)
3. [Installation and launch](#installation-and-launch)
4. [Screenshots and GIF](#screenshots-and-gif)
5. [Contact us](#contact-us-in-telegram)

## Description

This project presents `3DViewer v2.0`, a high-performance 3D model renderer designed for efficiency and maintainability.  Built using C++17, Qt, and a robust Model-View-Controller (MVC) architecture, this application demonstrates a commitment to clean, well-structured code.

### Overview

`3DViewer v2.0` efficiently loads and renders 3D models in wireframe mode from `.obj` files.  The application provides a user-friendly Qt interface for manipulating models via affine transformations (translation, rotation, and scaling) and customizing visual aspects such as line styles, vertex representations, colors, and projection type.  A key focus was on performance optimization to handle complex models with minimal lag, demonstrating a capacity to handle large datasets effectively.

### Architecture and Design Choices

The application employs a Model-View-Controller (MVC) architecture to enhance maintainability and scalability. This fundamental pattern divides the application into three distinct components:

- **Model:**  Manages the 3D model data, including loading, transformations, and internal representation.
- **View:**  Handles the visual representation of the model in the Qt user interface.
- **Controller:**  Orchestrates user interactions, managing events and updating the model and view accordingly.  This component utilizes the **Singleton pattern** to ensure a single instance manages application-wide data and interactions.

To further optimize code structure and reusability, several design patterns have been strategically integrated:

- **Facade (Manipulation):** The `Manipulation` class acts as a facade, providing a simplified interface for performing affine transformations (translation, rotation, scaling) on the 3D model. This abstraction hides the underlying complexity of the transformation logic, making the code more modular and easier to maintain.

- **Strategy (Parser and Affine Transformations):** The application leverages the Strategy pattern in two key areas:
  - **Parser:** Different parsing strategies can be easily swapped in for handling various 3D model formats (currently supporting .obj).  This allows for extensibility to other formats without altering core application logic.
  - **Affine Transformations:**  Various transformation algorithms (e.g., different matrix multiplication approaches) can be implemented as interchangeable strategies. This permits the use of different, potentially more performant, transformation methods without affecting the overall system architecture.

These design patterns significantly contribute to the application's modularity, flexibility, and maintainability.  They make the code easier to understand, test, and extend, while promoting efficient and scalable design principles.

### Key Features and Performance

- **High Performance Rendering:**  Handles models with up to 1,000,000 vertices without significant UI performance degradation (maintains responsiveness below 0.5 seconds). This showcases an understanding of optimization techniques for efficient data handling and rendering.
- **Support for .obj Files:**  Loads standard `.obj` files containing vertex and face data.
- **Affine Transformations:**  Enables intuitive manipulation of models via translation, rotation, and scaling along all three axes (X, Y, Z).
- **Customizable Rendering Options:** Offers a rich set of options to control the visual appearance, including line style (solid/dashed), vertex representation (none/circle/square), color and size parameters for vertices and edges, background color, and projection type.
- **Persistent Settings:**  Saves user preferences between application sessions, improving user experience.
- **Image Export:**  Exports rendered images to both BMP and JPEG formats.
- **GIF Animation Generation:** Creates short GIF animations (640x480, 10fps, 5 seconds) of affine transformations, demonstrating model manipulation capabilities.
- **Extensive Unit Testing:**  Includes comprehensive unit tests covering model loading and affine transformations, ensuring code quality and reducing the likelihood of bugs.
- **Adherence to Coding Standards:** Follows the Google C++ Style Guide for enhanced readability, maintainability, and code consistency.

## Technologies

- C++17
- Qt 6
- Makefile
- Google C++ Style Guide

## Installation and launch

*For launch on macOS:*

1. Clone the repository: `git clone <repository_url>`
2. Navigate to the project directory: `cd 3DViewer_v2.0/src`
3. Compile: `make`
4. Run: `open ./3DViewer/3dViewer.app`

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

## Contact us in telegram

Authors: Anastasia([@nanali96](https://t.me/nanali96)), Kasim([@Sckroll](https://t.me/Sckroll)), Emilia([@liaaemi](https://t.me/liaaemi))
