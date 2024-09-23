#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_ROWS 100
#define N_COLS 100

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

#define CELL_WIDTH (WIN_WIDTH / N_COLS)
#define CELL_HEIGHT (WIN_HEIGHT / N_ROWS)

#define N_CELLS (N_ROWS * N_COLS)

#define CELL(x, y) ((y) * N_ROWS + (x))

void place_gosper_glider_gun(int *cells, int x, int y) {
    int gun[][2] = {{0, 4},  {0, 5},  {1, 4},  {1, 5},  {10, 4}, {10, 5}, {10, 6}, {11, 3},
                    {11, 7}, {12, 2}, {12, 8}, {13, 2}, {13, 8}, {14, 5}, {15, 3}, {15, 7},
                    {16, 4}, {16, 5}, {16, 6}, {17, 5}, {20, 2}, {20, 3}, {20, 4}, {21, 2},
                    {21, 3}, {21, 4}, {22, 1}, {22, 5}, {24, 0}, {24, 1}, {24, 5}, {24, 6},
                    {34, 2}, {34, 3}, {35, 2}, {35, 3}};
    int gun_size = sizeof(gun) / sizeof(gun[0]);
    for (int i = 0; i < gun_size; i++) {
        cells[CELL(x + gun[i][0], y + gun[i][1])] = 1;
    }
}

void place_breeder(int *cells, int x, int y) {
    place_gosper_glider_gun(cells, x, y);
    for (int i = 0; i < 5; i++) {
        cells[CELL(x + 120 + i * 20, y + 80)] = 1;
        cells[CELL(x + 121 + i * 20, y + 80)] = 1;
        cells[CELL(x + 120 + i * 20, y + 81)] = 1;
        cells[CELL(x + 121 + i * 20, y + 81)] = 1;
    }
}

void initialize_grid(int *cells, int N) {
    memset(cells, 0, N * sizeof(int));

    place_breeder(cells, 10, 10);
}

void introduce_disturbance(int *cells) {
    for (int i = 0; i < N_CELLS / 100; i++) {
        int x = rand() % N_COLS;
        int y = rand() % N_ROWS;
        cells[CELL(x, y)] = !cells[CELL(x, y)];
    }
}

int main(void) {
    srand(time(NULL));
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Game Of LiFE");
    SetTargetFPS(60);

    bool close = false;
    bool paused = true;

    int frame_counter = 0;
    int act_frame = 2;

    int cells[N_CELLS];
    int new_cells[N_CELLS];

    initialize_grid(cells, N_CELLS);

    while (!WindowShouldClose() && !close) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 pos = GetMousePosition();
            int col = (int)pos.x / CELL_WIDTH;
            int row = (int)pos.y / CELL_HEIGHT;
            if (col >= 0 && col < N_COLS && row >= 0 && row < N_ROWS) {
                int index = CELL(col, row);
                cells[index] = !cells[index];
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_Q)) close = true;
        if (IsKeyPressed(KEY_SPACE)) paused = !paused;
        if (IsKeyPressed(KEY_D)) {
            introduce_disturbance(cells);
        }

        if (!paused && (frame_counter + 1) % act_frame == 0) {
            frame_counter = 0;

            for (size_t i = 0; i < N_CELLS; i++) {
                int row = i / N_ROWS;
                int col = i % N_ROWS;
                int neighbor = 0;

                // Toroidal grid
                /* for (int dy = -1; dy <= 1; dy++) { */
                /*     for (int dx = -1; dx <= 1; dx++) { */
                /*         if (dx == 0 && dy == 0) continue; */
                /*         int nx = (col + dx + N_COLS) % N_COLS; */
                /*         int ny = (row + dy + N_ROWS) % N_ROWS; */
                /*         neighbor += cells[CELL(nx, ny)]; */
                /*     } */
                /* } */

                /* Normal Grid */
                if (row > 0) neighbor += cells[CELL(col, row - 1)];
                if (row < N_ROWS - 1) neighbor += cells[CELL(col, row + 1)];
                if (col > 0) neighbor += cells[CELL(col - 1, row)];
                if (col < N_COLS - 1) neighbor += cells[CELL(col + 1, row)];
                if (row > 0 && col > 0) neighbor += cells[CELL(col - 1, row - 1)];
                if (row > 0 && col < N_COLS - 1) neighbor += cells[CELL(col + 1, row - 1)];
                if (row < N_ROWS - 1 && col > 0) neighbor += cells[CELL(col - 1, row + 1)];
                if (row < N_ROWS - 1 && col < N_COLS - 1) neighbor += cells[CELL(col + 1, row + 1)];

                new_cells[i] =
                    (cells[i] && (neighbor == 2 || neighbor == 3)) || (!cells[i] && neighbor == 3);
            }

            memcpy(cells, new_cells, sizeof(cells));

        } else {
            frame_counter += 1;
        }

        for (size_t i = 0; i < N_CELLS; i++) {
            int row = i / N_ROWS;
            int col = i % N_ROWS;

            int x = col * CELL_WIDTH;
            int y = row * CELL_HEIGHT;

            if (cells[i] == 1) {
                DrawRectangle(x, y, CELL_WIDTH, CELL_HEIGHT, RED);
            }
            DrawRectangleLines(x, y, CELL_WIDTH, CELL_HEIGHT, LIGHTGRAY);
        }

        if (paused) {
            DrawText("Paused", 10, 10, 10, RED);
            DrawText("Press SPACE to pause/resume", 10, 40, 20, DARKGRAY);
            DrawText("Click to toggle cells", 10, 70, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
