# CDraw
A lightweight library for drawing in the unix terminal with colors written for C

## Installation
To use this library in your C project simply clone the repo and type `make` in the terminal to generate the `libcdraw.so` file. This file can go into the same folder as your project. When compiling your program add the option `-lcdraw` to compile your program with the library.

Finally when executing your program type (while in the folder of your project:
```
LD_LIBRARY_PATH="$LD_LIBRARY_PATH;$(pwd)" ./<executable-name>
```
Another option is to just put the libcdraw.so file into `/usr/lib`.

## Usage

For example usage look at `test.c` source code.

### Structs (typedef'd)

#### `Stage`

The stage is like a new window to put your graphics on. A stage will contain a list of `Scenes` (layers) that are stacked on top of each other and drawn one after another.

#### `Scene`

A `Scene` is very simular to a layer in a photo editing program. It will contain a list of `Rect`s that will be drawn one after another to create a picture. They can also be used to group rectangles and be made as sprites to make a game.

#### `Rect`

`Rect` stands for Rectangle and stores the 2 corner points and color of a single rectangle to be drawn.

#### `List`

A basic dynamic array list implementation in C. This library uses these to store information about shapes and scenes. Feel free to use it in other aspects of your software.

### Functions

#### `Stage* create_stage(int width, int height, bool debug);`

Creates a stage from scratch. This stage will need to be free'd with `free_stage`.
 - `width` is the width of the stage in pixel units.
 - `height` is the height of the stage in pixel units (A pixel unit is 2x1 characters).

#### `void free_stage(Stage* stage);`

Free's a stage from memory including everything inside of it.

#### `Scene* create_scene(int x, int y);`

Creates a scene object from a given x and y.
 - `x` the scenes x position from the top left of the stage.
 - `y` the scenes y position from the top left of the stage.

#### `void free_scene(Scene* scene);`

Free's a screen struct from memory.

#### `Rect* create_rect(int x, int y, int x2, int y2, Color c);`

Creates a rectangle from scratch.
 - `x` The first points x position.
 - `y` The first points y position.
 - `x2` The second points x position.
 - `y2` The second points y position.
 ` `c` The color of the rectangle.

#### `void free_rect(Rect* rect);`

Frees rectangle from memory `free_scene` will do this to all of it's rectangles.

#### `void draw_stage(Stage* stage, bool init);`

Will render the stage. If init is true then it will move the cursor first. The scenes will be drawn in order it appears in the list.

#### `Color get_stage_color(Stage* stage, int x, int y);`

Takes the x and y coordinate and returns the stage color at that point.

#### `char* get_color(Color col);`

Returns the color given as a string.

## Colors

The list of colors that can be used are:
 - WHITE
 - BLACK
 - RED
 - GREEN
 - YELLOW
 - BLUE
 - MAGENTA
 - CYAN
 - RESET
