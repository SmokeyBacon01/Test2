#include <stdio.h>
#include <multiball.h>

#include "utility.h"
#include "main.h"

void multiball(struct ball ball[MAX_SIZE], int tick, int count) {
    if (tick % MULTIBALL_DELAY == 0) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (!ball[j].is_exist) {
                ball[j].is_exist = true;
                break;
            }
        }
    } 
}

void initialise_multiball(struct ball ball[MAX_SIZE]) {
    for (int i = 1; i < MAX_SIZE; i++) {
        ball[i].spawn_timer = 0;
        ball[i].y_speed = random_signed(400) / 100.0;
    }
}
    