#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "main.h"
#include "setup.h"
#include "gameplay.h"
#include "utility.h"

int main() {

    SetTargetFPS(FPS);

    bool settings[MAX_SETTINGS] = {false};
    //Pregame prep

    setup(settings);
    
    //gameplay
    if (settings[START]) {
        int stats[MAX_STATS] = {0};
        gameplay(stats, settings);
    }

    //

    //print results
    while (!WindowShouldClose()) {
        BeginDrawing();
    
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
