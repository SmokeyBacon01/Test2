#include <raylib.h>

#include "main.h"

#define POWERUP_RADIUS 30
#define POWERUP_DURATION 5 * FPS

pickup generate_powerup(pickup powerup);
pickup initialise_powerup(pickup powerup);