#include "cdraw.h"


int main(void) {

    Stage* stage = create_stage(-1, 10, false);

    draw_stage(stage, true);

    Rect* redRect = create_rect(1, 1, 8, 8, CYAN);

    Scene* scene = create_scene(12, 1);
    add_to_list(scene->rects, redRect);

    add_to_list(stage->scenes, scene);

    draw_stage(stage, false);

    free_stage(stage);

    return 0;
}
