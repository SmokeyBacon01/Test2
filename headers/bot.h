#include <raylib.h>

#include "main.h"

float get_bot_movement(Rectangle paddle, struct ball ball[MAX_SIZE]);
float get_target_movement(
    Rectangle paddle,
    int target_y
);
float calculate_target_y(
    Rectangle paddle,
    struct ball ball
);
int get_closest_ball_index(
    struct ball ball[MAX_SIZE],
    Rectangle paddle
);