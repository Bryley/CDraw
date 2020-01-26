#ifndef CDRAW_H
#define CDRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "list.h"

typedef enum {
    WHITE = 0,
    BLACK = 1,
    RED = 2,
    GREEN = 3,
    YELLOW = 4,
    BLUE = 5,
    MAGENTA = 6,
    CYAN = 7,
    RESET = 9
} Color;

/* Stores a rectangle shape.
 * Requirements:
 *   - x2 >= x
 *   - y2 >= y
 * Any of the coords may be out of the screen.
 */
typedef struct {
    int x;
    int y;
    int x2;
    int y2;
    Color color;
} Rect;

/*
 * Scene will store shapes that will be drawn.
 */
typedef struct {
    int x;
    int y;
    List* rects;
} Scene;

/*
 * Stage is a list of scenes and stores size of the screen and background.
 * The scenes will be drawn from 0th index to final index of the scenes list.
 *  - If debug is true then each pixel will display information about it's x and y
 *      position in modulo 10.
 */
typedef struct {
    int width;
    int height;
    bool fullscreen;
    bool debug;
    Color background;
    List* scenes;
} Stage;

/*
 * Creates a new stage from scratch.
 * If width or height is less than or equal to 0 then we will use
 * the full terminal window.
 */
Stage* create_stage(int width, int height, bool debug);

void free_stage(Stage* stage);

/*
 * Creates a scene object from a given width and height.
 */
Scene* create_scene(int x, int y);

/*
 * Free's a screen struct from memory.
 */
void free_scene(Scene* scene);

/*
 * Creates a rectangle from scratch.
 */
Rect* create_rect(int x, int y, int x2, int y2, Color c);

void free_rect(Rect* rect);

/*
 * Will render the scene. If init is true then it will move the cursor first.
 */
void draw_stage(Stage* stage, bool init);

/*
 * Will color a single pixel on the screen.
 */
void color_pixel(Stage* stage, int x, int y, Color color);

/*
 * Takes the x and y coordinate and returns the stage color at that point.
 */
Color get_stage_color(Stage* stage, int x, int y);

/*
 * Returns the color given as a string.
 */
char* get_color(Color col);

#endif
