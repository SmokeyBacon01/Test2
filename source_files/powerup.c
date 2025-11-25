
#include <stdio.h>
#include <raylib.h>

#include "main.h"
#include "powerup.h"
#include "utility.h"

pickup generate_powerup(pickup powerup) {
    powerup.is_exist = true;
    powerup.centre.x = LEFT_PADDLE_X_POS + random_unsigned(RIGHT_PADDLE_X_POS - LEFT_PADDLE_X_POS);
    powerup.centre.y = random_unsigned(WINDOW_HEIGHT);
    powerup.type = random_unsigned(MAX_POWERUPS);

    printf("%lf %lf\n", powerup.centre.x, powerup.centre.y);

    if (powerup.type == WIDE_PADDLE) {
        powerup.colour = DARKGRAY;
    } else if (powerup.type == GUARDIAN) {
        powerup.colour = WHITE;
    } else if (powerup.type == SPEED_BALL) {
        powerup.colour = YELLOW;
    } else if (powerup.type == BIG_BALL) {
        powerup.colour = DARKPURPLE;
    } else if (powerup.type == GHOST_BALL) {
        powerup.colour = GRAY;
    } else if (powerup.type == EVIL_BALL) {
        powerup.colour = RED;
    }

    return powerup;
}

    
pickup initialise_powerup(pickup powerup) {
    powerup.centre.x = 0;
    powerup.centre.y = 0;
    powerup.radius = POWERUP_RADIUS;
    powerup.type = WIDE_PADDLE;
    powerup.duration = POWERUP_DURATION;
    powerup.is_exist = false;
    return powerup;
}

void activate_powerup(pickup powerup) {
    // add powerups as they come.
}