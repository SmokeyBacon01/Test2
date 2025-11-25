#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "utility.h"
#include "main.h"
#include "gameplay.h"
#include "multiball.h"
#include "bot.h"
#include "powerup.h"

void gameplay(
    int stats[MAX_STATS], 
    bool settings[MAX_SETTINGS]
) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ponging it");
    
    Rectangle paddle_one = {LEFT_PADDLE_X_POS, INITIAL_PADDLE_Y_POS, PADDLE_WIDTH, PADDLE_HEIGHT};
    Rectangle paddle_two = {RIGHT_PADDLE_X_POS, INITIAL_PADDLE_Y_POS, PADDLE_WIDTH, PADDLE_HEIGHT};
    Rectangle paddles[MAX_STATS] = {paddle_one, paddle_two}; 

    struct ball ball[MAX_SIZE];
    initialise_balls(ball);
    
    pickup powerup = initialise_powerup(powerup);

    if (settings[MULTIBALL]) {
        initialise_multiball(ball);
    }

    bool is_game_start = false;
    int tick = 1;
    srand(time(NULL));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (!is_game_start) {
            start_game(&is_game_start);
        } else {
            draw_score(stats);
            tick++;
        }

        if (tick % POWERUP_SPAWN_TIMER == 0 && powerup.is_exist == false) {
            powerup.is_exist = true;
            powerup = generate_powerup(powerup);
            printf("powerup generated at %lf %lf\n", powerup.centre.x, powerup.centre.y);
        }

        for (int i = 0; i < MAX_SIZE; i++) {
            if (ball[i].is_exist) {
                ball_collision(ball, paddles, i, powerup);
                update_ball(ball, stats, i);
                ball[i].spawn_timer--;
            }
        }

        move_paddle(&paddles[P1].y, KEY_W, KEY_S);
        if (!settings[SINGLEPLAYER]) {
            move_paddle(&paddles[P2].y, KEY_UP, KEY_DOWN);
        } else {
            paddles[P2].y = get_bot_movement(paddles[P2], ball);
        }
    
        DrawRectangleRec(paddles[P1], WHITE);
        DrawRectangleRec(paddles[P2], WHITE);
        draw_balls(ball);

        if (powerup.is_exist) {
            DrawCircleV(powerup.centre, powerup.radius, powerup.colour);
        }

        if (settings[MULTIBALL]) {
            int count = 1;
            multiball(ball, tick, count);
        }

        EndDrawing();
    }

    CloseWindow();
}


void move_paddle(float *paddle_y, int up, int down) {
    if (IsKeyDown(up)) {
        *paddle_y -= PADDLE_SPEED;
    } else if (IsKeyDown(down)) {
        *paddle_y += PADDLE_SPEED;
    }
    if (*paddle_y < 0) {
        *paddle_y = 0;
    } else if (*paddle_y > WINDOW_HEIGHT - PADDLE_HEIGHT) {
        *paddle_y = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }
}

int find_existent_index(struct ball ball[MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (!ball[i].is_exist) {
            return i;
        }
    }
    return 0;
}

void draw_score(int stats[MAX_STATS]) {
    char score[MAX_SIZE];
    sprintf(score, "%d - %d", stats[P1], stats[P2]);
    int centre = (WINDOW_WIDTH - MeasureText(score, SCORE_SIZE)) / 2;

    DrawText(score, centre, 0, SCORE_SIZE, WHITE);
}

void ball_collision(struct ball ball[MAX_SIZE],
    Rectangle paddles[MAX_STATS],
    int i,
    pickup powerup
) {
    if (CheckCollisionCircleRec(ball[i].centre, ball[i].radius, paddles[P1])) {
        if (ball[i].is_first_hit) {
            ball[i].x_speed /= SPAWN_SPEED_COE;
            ball[i].is_first_hit = false;
        }
        ball[i].x_speed *= -1;
        ball[i].y_speed = y_speed(paddles[P1], ball[i]) * ball[i].bounce_coefficient;

    } else if (CheckCollisionCircleRec(ball[i].centre, ball[i].radius, paddles[P2])) {
        if (ball[i].is_first_hit) {
            ball[i].x_speed /= SPAWN_SPEED_COE;
            ball[i].is_first_hit = false;
        }
        ball[i].x_speed *= -1;
        ball[i].y_speed = y_speed(paddles[P2], ball[i]) * ball[i].bounce_coefficient;
    } else if (CheckCollisionCircles(ball[i].centre, ball[i].radius, powerup.centre, powerup.radius)) {
        powerup.is_exist = false;
    }

}

int y_speed(Rectangle paddle, struct ball ball) {

    float dy = ball.centre.y - paddle.y - (PADDLE_HEIGHT / 2);

    return dy * Y_SPEED_COEFFICIENT * (1 + random_unsigned(100) / 100);
}

void update_ball(
    struct ball ball[MAX_SIZE],
    int stats[MAX_STATS],
    int i
) {

    if (is_ball_active(ball[i])) {
        ball[i].x_speed = BALL_X_SPEED * ball[i].x_speed_coefficient;
        if (ball[i].is_first_hit) {
            ball[i].x_speed *= SPAWN_SPEED_COE;
        }
    } 

    ball[i].centre.x += ball[i].x_speed;
    ball[i].centre.y += ball[i].y_speed;

    if (!ball[i].is_scored) {
        if (ball[i].centre.x - ball[i].radius < 0) {
            stats[P2]++;
            ball[i].is_scored = true;
            ball[find_existent_index(ball)].is_exist = true;
        } else if (ball[i].centre.x + ball[i].radius > WINDOW_WIDTH) {
            stats[P1]++;
            ball[i].is_scored = true;
            ball[find_existent_index(ball)].is_exist = true;
        } else if (ball[i].centre.y - ball[i].radius < 0) {
            ball[i].y_speed *= -1;
        } else if (ball[i].centre.y + ball[i].radius > WINDOW_HEIGHT) {
            ball[i].y_speed *= -1;
        }
    }
}

bool is_ball_active (struct ball ball) {
    if (ball.spawn_timer <= 0) {
        if (ball.x_speed != -BALL_X_SPEED * ball.x_speed_coefficient) {
            return true;
        }
    }
    return false;
}

void start_game(bool *is_game_start) {
    if (!(*is_game_start)) {
        DrawText("PRESS ANY KEY TO START", 0, 0, 40, WHITE);
        int key = GetKeyPressed();
        if (key != 0) {
            *is_game_start = true;
        }
    }
}

void draw_balls(struct ball ball[MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (ball[i].is_exist) {
            DrawCircle(
                ball[i].centre.x,
                ball[i].centre.y,
                ball[i].radius,
                ball[i].colour
            );
        }
    }
}

void initialise_balls (struct ball ball[MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        ball[i].centre.x = BALL_INITIAL_X;
        ball[i].centre.y = BALL_INITIAL_Y;
        ball[i].x_speed = 0;
        ball[i].y_speed = 0;
        ball[i].radius = BALL_RADIUS;
        ball[i].is_exist = false;
        ball[i].is_scored = false;
        ball[i].ghost = false;
        ball[i].colour = WHITE;
        ball[i].spawn_timer = BALL_SPAWN_DELAY;
        ball[i].bounce_coefficient = 1;

        ball[i].is_first_hit = true; 
        if (i % 2 == 0) {
            ball[i].x_speed_coefficient = 1;
        } else {
            ball[i].x_speed_coefficient = -1;
        }
    }

    ball[0].is_exist = true;
    ball[0].spawn_timer = 0;
    ball[0].is_first_hit = false;
}




