#include <stdio.h>
#include <raylib.h>

#include "main.h"
#include "setup.h"

void setup(bool settings[MAX_SETTINGS]);
void draw_button(
    const char *text,
    int text_size,
    Rectangle box,
    ui_colours ui_colours,
    bool *setting
);

void setup(bool settings[MAX_SETTINGS]) {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ponging it");

    while (!settings[START] && WindowShouldClose() == false) {
        
        int width = MeasureText("Pongin' It", 40);
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Pongin' It", (WINDOW_WIDTH - width) / 2, 75, 40, WHITE);

        int centre = (WINDOW_WIDTH - UI_BOX_WIDTH) / 2;

        int y = UI_TOP_BOX;
        
        ui_colours ui_colours = {WHITE, BLACK, GRAY, WHITE};
        Rectangle box = {(centre), y, UI_BOX_WIDTH, UI_BOX_HEIGHT};

        draw_button("CHALLENGE AI", UI_TEXT_SIZE, box, ui_colours, &settings[SINGLEPLAYER]);
        box.y += UI_BOX_SPACING;
        draw_button("MULTIBALLS", UI_TEXT_SIZE, box, ui_colours, &settings[MULTIBALL]);
        box.y += UI_BOX_SPACING;
        draw_button("POWERUPS", UI_TEXT_SIZE, box, ui_colours, &settings[POWERUPS]);
        box.y += UI_BOX_SPACING;
        draw_button("START", UI_TEXT_SIZE, box, ui_colours, &settings[START]);
        box.y += UI_BOX_SPACING;

        if (settings[SINGLEPLAYER]) {
            DrawText("Bring it on!", 0, 0, 20, WHITE);
        }
        if (settings[MULTIBALL]) {
            DrawText("You like chaos?", 0, 20, 20, WHITE);
        }
        if (settings[POWERUPS]) {
            DrawText("Balance is a joke.", 0, 40, 20, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();
}

void draw_button(
    const char *text,
    int text_size,
    Rectangle box,
    ui_colours ui_colours,
    bool *setting
) {
    Vector2 mouse = GetMousePosition();
    Rectangle inner_box = {box.x + 2, box.y + 2, box.width - 4, box.height - 4};

    DrawRectangleRec(box, ui_colours.outer);

    DrawText(
        text, (WINDOW_WIDTH - MeasureText(text, text_size)) / 2 + 2,
        box.y + (box.height / 2), text_size, ui_colours.text
    );

    if (!CheckCollisionPointRec(mouse, box)) {
        DrawRectangleRec(inner_box, ui_colours.inner);
        DrawText(
            text, (WINDOW_WIDTH - MeasureText(text, text_size)) / 2 + 2,
            box.y + (box.height / 2), text_size, ui_colours.text
        );
    } else {
        DrawRectangleRec(inner_box, ui_colours.hover);
        DrawText(
            text, (WINDOW_WIDTH - MeasureText(text, text_size)) / 2 + 2,
            box.y + (box.height / 2), text_size, ui_colours.text
        );
    }

    if (CheckCollisionPointRec(mouse, box) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        DrawRectangleRec(inner_box, ui_colours.outer);
    }
    if (CheckCollisionPointRec(mouse, box) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        *setting = !*setting;
    }
}
