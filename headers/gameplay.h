// The core gameplay loop of a single ball flying around

#include <raylib.h>

#include "main.h"

#define SCORE_SIZE 50

// Struct Defs

// Function Defs

void gameplay(
    int stats[MAX_STATS], 
    bool settings[MAX_SETTINGS]
);
void initialise_balls (struct ball ball[MAX_SIZE]);
void draw_balls (struct ball ball[MAX_SIZE]);
void start_game(bool *is_game_start);

void draw_score(int stats[MAX_STATS]);

void update_ball(
    struct ball ball[MAX_SIZE],
    int stats[MAX_STATS],
    int i
);
bool is_ball_active (struct ball ball);
int y_speed(Rectangle paddle, struct ball ball);
void ball_collision(struct ball ball[MAX_SIZE],
    Rectangle paddles[MAX_STATS],
    int i,
    pickup powerup
);
void move_paddle(float *paddle_y, int up, int down);

void draw_score(int stats[MAX_STATS]);
