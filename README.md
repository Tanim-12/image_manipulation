# Image Editing Software

Course: CSE1101L — Final Project 
Name: Syed Tasnim Ferdus Tanim 
Roll: BSSE 1819

A simple C image editor created for the final lab project. The application uses
the IUP GUI toolkit and works with BMP images.

## Features

- Open BMP images
- Save edited images as BMP files
- Convert an image to grayscale
- Increase or decrease brightness
- Invert image colors
- Flip an image horizontally
- Flip an image vertically
- Rotate an image
- Blur an image
- Crop an image using X, Y, width, and height values
- Undo the most recent edit
- Exit the application

## How to Run

### Using the executable

Double-click the `imageeditor` executable to start the application.

### Using the build script on macOS/Linux

Make sure the IUP library is installed and available at the location configured
in `build.sh`, then run:

```bash
chmod +x build.sh
./build.sh imageeditor
```

The script compiles the source files and starts the program.

### Using a Windows batch file

If a Windows build is provided with the project, run it from Command Prompt:

```bat
build.bat
```

You can also double-click the generated `.exe` file. The current repository
contains `build.sh` and `imageeditor`; a `build.bat` file is not included in
this version.

## Basic Usage

1. Click **Open** and select a BMP image.
2. Choose an editing operation from the toolbar.
3. For brightness, enter a value and click **Apply Brightness**.
4. For cropping, enter the X and Y position and the crop width and height,
   then click **Apply Crop**.
5. Click **Undo** to reverse the latest operation.
6. Click **Save** to save the edited image as a BMP file.

## Screenshots

Each screenshot below shows the editor performing one specific operation.
Files are stored in the `screenshots/` folder.

### Opening an image

![Opening an image](screenshots/Opening%20an%20image.png)

### Opening Interphase

![Opening Interphase](screenshots/Opening%20Interphase.png)

### Grayscale

![Grayscale](screenshots/Grayscale.png)

### Brightness

![Brightness](screenshots/Brightness.png)

### Invert

![Invert](screenshots/Invert.png)

### Horizontal Flip

![Horizontal Flip](screenshots/Horizontal%20Flip.png)

### Vertical Flip

![Vertical Flip](screenshots/Vertical%20Flip.png)

### Rotate

![Rotate](screenshots/Rotate.png)

### Blur

![Blur](screenshots/Blur.png)

### Crop

![Crop](screenshots/Crop.png)

### Crop error handling

![Crop error handling](screenshots/Crop%20error%20handling.png)

### Undo

![Undo](screenshots/Undo.png)

### Undo Handling

![Undo Handling](screenshots/Undo%20Handling.png)

### Saving image

![Saving image](screenshots/Saving%20image.png)

## Project Structure

```text
LAB FINAL PROJECT/
├── build.sh              # Builds and runs the application on macOS/Linux
├── main.c                # Program entry point and IUP event loop
├── gui.c                 # Creates the interface and handles button actions
├── gui.h                 # GUI function declarations
├── image.c               # Loads, copies, saves, and frees image data
├── image.h               # Pixel and Image structures and image declarations
├── processing.c          # Image editing algorithms
├── processing.h          # Image processing function declarations
├── stb_image.h           # Third-party image loading implementation
├── stb_image_write.h     # Third-party image writing implementation
├── imageeditor           # Compiled executable
├── tempCodeRunnerFile.c  # Temporary editor-generated C file
└── README.md             # Project documentation
```

## Source File Responsibilities

### `main.c`

Initializes IUP, creates the editor window, starts the main event loop, and
cleans up when the application closes.

### `gui.c` and `gui.h`

Build the toolbar, brightness controls, crop controls, and image display.
They also connect the buttons to the image editing operations.

### `image.c` and `image.h`

Define the `Pixel` and `Image` data structures and provide functions for
loading BMP data, copying images for undo, saving BMP files, and freeing memory.

### `processing.c` and `processing.h`

Implement grayscale, brightness, invert, horizontal flip, vertical flip,
rotation, blur, crop, and undo-related image operations.

### `stb_image.h` and `stb_image_write.h`

Single-header libraries used to read image data and write BMP files.

## Requirements

- C compiler such as Clang or GCC
- IUP GUI library
- macOS/Linux for `build.sh`, or a Windows build script and compiler for
  `build.bat`