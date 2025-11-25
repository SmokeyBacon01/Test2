#include "main.h"
#include "utility.h"
#include "stdlib.h"
#include "time.h"

int random_unsigned(int max) {
    return rand() % max;
}

int random_signed(int max) {
    if (random_unsigned(2) == 1) {
        return random_unsigned(max); 
    } else {
        return random_unsigned(max) * -1;
    }
}