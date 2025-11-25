// Headers used by every function
#pragma once

#include <raylib.h>

// CONSTANT DEFINITIONS
#define MAX_SIZE 1024

#define FPS 60

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480

#define UI_BOX_WIDTH 200
#define UI_BOX_HEIGHT 50
#define UI_TEXT_SIZE 20
#define UI_TOP_BOX 150
#define UI_BOX_SPACING 75

#define BALL_RADIUS 5
#define BALL_INITIAL_X 400
#define BALL_INITIAL_Y 240
#define BALL_X_SPEED 10
#define BALL_SPAWN_DELAY 60
#define SPAWN_SPEED_COE 0.5

#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 60
#define LEFT_PADDLE_X_POS 50
#define RIGHT_PADDLE_X_POS 745
#define INITIAL_PADDLE_Y_POS 210
#define PADDLE_SPEED 5
#define Y_SPEED_COEFFICIENT 0.4

#define POWERUP_SPAWN_TIMER 180

// STRUCTS

typedef struct ui_colours {
    struct Color outer;
    struct Color inner;
    struct Color hover;
    struct Color text;
} ui_colours;

struct ball {
    Vector2 centre;
    float x_speed;
    float y_speed;
    int radius;
    bool is_exist;
    bool is_scored;
    bool ghost;
    Color colour;
    int spawn_timer;
    float bounce_coefficient;
    int x_speed_coefficient;
    bool is_first_hit;
};

typedef struct pickup {
    Vector2 centre;
    int radius;
    int type;
    int duration;
    Color colour;
    bool is_exist;
} pickup;

// ENUM DEFINITION

enum powerup {
    WIDE_PADDLE,
    GUARDIAN,
    SPEED_BALL,
    BIG_BALL,
    GHOST_BALL,
    EVIL_BALL,
    MAX_POWERUPS
};

enum stats {
    P1,
    P2,
    MAX_STATS
};

enum settings {
    SINGLEPLAYER,
    MULTIBALL,
    POWERUPS,
    START,
    MAX_SETTINGS
};

// FUNCTIONS

// Creates a button that updates some boolean if clicked.
void draw_button(
    const char *text,
    int text_size,
    Rectangle box,
    ui_colours ui_colours,
    bool *setting
);