#include <stdio.h>
#include <raylib.h>
#include <float.h>

#include "bot.h"
#include "main.h"

float get_bot_movement(Rectangle paddle, struct ball ball[MAX_SIZE]) {
    int target_index = get_closest_ball_index(ball, paddle);

    float target_y = calculate_target_y(paddle, ball[target_index]);
    paddle.y = get_target_movement(paddle, target_y);

    if (paddle.y < 0) {
        paddle.y = 0;
    } else if (paddle.y > WINDOW_HEIGHT - PADDLE_HEIGHT) {
        paddle.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }

    return paddle.y;
} 

// move to target
float get_target_movement(
    Rectangle paddle,
    int target_y
) {
    if (paddle.y < target_y - (3 * PADDLE_HEIGHT / 4)) {
        paddle.y += PADDLE_SPEED;
    } else if (paddle.y > target_y - (PADDLE_HEIGHT / 4)) {
        paddle.y -= PADDLE_SPEED;
    } 
    return paddle.y;
}

// at what Y value should I intercept?
float calculate_target_y(
    Rectangle paddle,
    struct ball ball
) {
    float time_to_hit;

    if (ball.x_speed == 0) {
        return 0;
    } else {
        time_to_hit = ((paddle.x - (PADDLE_WIDTH / 2)) - (ball.centre.x + BALL_RADIUS)) / ball.x_speed;
    }

    float y_displacement = ball.centre.y + time_to_hit * ball.y_speed;
    while (y_displacement > WINDOW_HEIGHT || y_displacement < 0) {
        if (y_displacement > WINDOW_HEIGHT) {
            y_displacement -= 2 * (y_displacement - WINDOW_HEIGHT);
        } else if (y_displacement < 0) {
            y_displacement -= 2 * (y_displacement);
        }
    }
    return y_displacement;
}

// Which ball is closest?
int get_closest_ball_index(
    struct ball ball[MAX_SIZE],
    Rectangle paddle
) {
    float distance;
    float shortest = FLT_MAX;
    int index = -1;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (!ball[i].is_exist) {
            continue;
        }
        distance = paddle.x - ball[i].centre.x;
        if (ball[i].is_first_hit) {
            distance = distance / SPAWN_SPEED_COE;
        }
        if (distance < shortest && distance >= 0) {
            shortest = distance;
            index = i;
        }
    }
    return index;
}