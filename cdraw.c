#include "cdraw.h"

Stage* create_stage(int width, int height, bool debug) {
    Stage* stage = (Stage*) malloc(sizeof(Stage));

    stage->fullscreen = false;
    stage->debug = debug;

    if (width <= 0 || height <= 0) {
        // Make it "full screen"
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        width = w.ws_col / 2;
        height = w.ws_row - 1;

        stage->fullscreen = true;

    }

    stage->width = width;
    stage->height = height;
    stage->background = WHITE;
    stage->scenes = create_list(3);

    return stage;
}

void free_stage(Stage* stage) {
    // Free scenes
    for (int i = 0; i < stage->scenes->size; i++) {
        free_scene(stage->scenes->elements[i]);
    }

    free_list(stage->scenes, false);

    free(stage);
}

Scene* create_scene(int x, int y) {

    Scene* scene = (Scene*) malloc(sizeof(Scene));
    scene->x = x;
    scene->y = y;

    scene->rects = create_list(3);

    return scene;
}

void free_scene(Scene* scene) {

    free_list(scene->rects, true);
    
    free(scene);
}

Rect* create_rect(int x, int y, int x2, int y2, Color c) {
    Rect* rect = (Rect*) malloc(sizeof(Rect));

    // TODO check for max values and validate.

    rect->x = x;
    rect->y = y;
    rect->x2 = x2;
    rect->y2 = y2;

    rect->color= c;

    return rect;
}

void free_rect(Rect* rect) {
    free(rect);
}

void draw_stage(Stage* stage, bool init) {

    if (!init) {
        // First move cursor to the begining.
        printf("\x1B[%dA\x1B[1000D", stage->height);
    }

    Color checkCol; // Temp var for storing stage color.
    Color currentColor = stage->background;

    printf("%s", get_color(stage->background));

    // Now draw the screen.
    for (int y = 0; y < stage->height; y++) {
        // Set the color.

        for (int x = 0; x < stage->width; x++) {

            // Check if different color.
            if (currentColor != (checkCol = get_stage_color(stage, x, y))) {
                currentColor = checkCol;
                printf("%s", get_color(currentColor));
            }
            if (stage->debug) {
                printf("%d%d", x%10, y%10);
            } else {
                printf("  ");
            }

        }
        // Go to the next line.
        printf("%s", init ? "\n" : "\x1B[1B\x1B[1000D");
    }
    printf("%s", get_color(RESET));
    if (stage->fullscreen) {
        printf("\n");
    }
}


Color get_stage_color(Stage* stage, int x, int y) {
    // Go through all the Scenes starting at the top then check if the
    // point is in one of the rectangles.
    
    // Stands for translated x and y.
    int transX = x;
    int transY = y;

    for (int sceneI = 0; sceneI < stage->scenes->size; sceneI++) {
        Scene* scene = (Scene*) stage->scenes->elements[sceneI];

        transX = x - scene->x;
        transY = y - scene->y;

        // Go through rectangles.
        for (int rectI = 0; rectI < scene->rects->size; rectI++) {
            Rect* rect = (Rect*) scene->rects->elements[rectI];

            // Check if point is inside of the rect.
            if (rect->x <= transX && transX <= rect->x2) {
                if (rect->y <= transY && transY <= rect->y2) {
                    return rect->color;
                }
            }

        }
    }

    return stage->background;
}

char* get_color(Color col) {
    char* PIXEL_COLORS[10] = {
        "\x1B[47m", // WHITE
        "\x1B[40m", // BLACK
        "\x1B[41m", // RED
        "\x1B[42m", // GREEN
        "\x1B[43m", // YELLOW
        "\x1B[44m", // BLUE
        "\x1B[45m", // MAGENTA
        "\x1B[46m", // CYAN
        NULL,
        "\x1B[0m" // RESET
    };

    return PIXEL_COLORS[col];
}
