#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE 4

int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
int current_block[BLOCK_SIZE][BLOCK_SIZE] = {0};
int current_block_x = 0;
int current_block_y = 0;
int score = 0;

int blocks[7][4][4] = {
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,2,2,0},
        {0,2,2,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,3,3,0},
        {3,3,0,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {4,4,0,0},
        {0,4,4,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,5,5,0},
        {5,5,0,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {6,6,6,0},
        {0,0,6,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,7,0,0},
        {7,7,7,0},
        {0,0,0,0}
    }
};

void init_block() {
    int block_type = rand() % 7;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            current_block[i][j] = blocks[block_type][i][j];
        }
    }
    current_block_x = BOARD_WIDTH / 2 - 2;
    current_block_y = 0;
}

void draw_block(int x, int y, int block[BLOCK_SIZE][BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block[i][j] != 0) {
                mvprintw(y + i, x + j * 2, "[]");
            }
        }
    }
}

void draw_board() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] != 0) {
                mvprintw(i, j * 2, "[]");
            }
        }
    }
}

void clear_block(int x, int y, int block[BLOCK_SIZE][BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block[i][j] != 0) {
                mvprintw(y + i, x + j * 2, "  ");
            }
        }
    }
}

void clear_board() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            mvprintw(i, j * 2, "  ");
        }
    }
}

int check_collision(int x, int y, int block[BLOCK_SIZE][BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block[i][j] != 0 && (y + i >= BOARD_HEIGHT || x + j < 0 || x + j >= BOARD_WIDTH || board[y + i][x + j] != 0)) {
                return 1;
            }
        }
    }
    return 0;
}

void merge_block(int x, int y, int block[BLOCK_SIZE][BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block[i][j] != 0) {
                board[y + i][x + j] = block[i][j];
            }
        }
    }
}

void check_lines() {
    int lines_cleared = 0;
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        int line_full = 1;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == 0) {
                line_full = 0;
                break;
            }
        }
        if (line_full) {
            lines_cleared++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board[0][j] = 0;
            }
            i++;
        }
    }
    score += lines_cleared * lines_cleared;
}

int main() {
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);

    init_block();

    while (1) {
        clear_block(current_block_x, current_block_y, current_block);
        if (check_collision(current_block_x, current_block_y + 1, current_block)) {
            merge_block(current_block_x, current_block_y, current_block);
            check_lines();
            init_block();
            if (check_collision(current_block_x, current_block_y, current_block)) {
                break;
            }
        } else {
            current_block_y++;
        }
        draw_board();
        draw_block(current_block_x, current_block_y, current_block);
        mvprintw(BOARD_HEIGHT + 1, 0, "Score: %d", score);
        refresh();
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                if (!check_collision(current_block_x - 1, current_block_y, current_block)) {
                    current_block_x--;
                }
                break;
            case KEY_RIGHT:
                if (!check_collision(current_block_x + 1, current_block_y, current_block)) {
                    current_block_x++;
                }
                break;
            case KEY_DOWN:
                if (!check_collision(current_block_x, current_block_y + 1, current_block)) {
                    current_block_y++;
                }
                break;
            case KEY_UP:
                {
                    int rotated_block[BLOCK_SIZE][BLOCK_SIZE] = {0};
                    for (int i = 0; i < BLOCK_SIZE; i++) {
                        for (int j = 0; j < BLOCK_SIZE; j++) {
                            rotated_block[i][j] = current_block[BLOCK_SIZE - j - 1][i];
                        }
                    }
                    if (!check_collision(current_block_x, current_block_y, rotated_block)) {
                        for (int i = 0; i < BLOCK_SIZE; i++) {
                            for (int j = 0; j < BLOCK_SIZE; j++) {
                                current_block[i][j] = rotated_block[i][j];
                            }
                        }
                    }
                }
                break;
            case 'q':
                goto end;
                break;
        }
    }

    mvprintw(BOARD_HEIGHT / 2, BOARD_WIDTH - 5, "Game Over");
    refresh();
    getch();

end:
    endwin();
    return 0;
}