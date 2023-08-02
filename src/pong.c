#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

void game();
void field(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
           int mid_rocket_two, int bottom_rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score);
int control(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
            int *mid_rocket_two, int *bottom_rocket_two);
void change_direction(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
                      int mid_rocket_two, int bottom_rocket_two, int *x_ball, int *y_ball, int *move_ball);
void move_ball(int *x_ball, int *y_ball, int *ball_direction);
void player_one_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_one_score, int *x_ball,
                       int *y_ball);
void player_two_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_two_score, int *x_ball,
                       int *y_ball);

int main() {
    initscr();
    clear();
    noecho();
    game();
    return 0;
}

void game() {
    int game = 1;
    int x_ball = 2, y_ball = 13, ball_direction = 0;
    int top_rocket_one = 12, mid_rocket_one = 13, bottom_rocket_one = 14;
    int top_rocket_two = 12, mid_rocket_two = 13, bottom_rocket_two = 14;
    int player_one_score = 0, player_two_score = 0;
    while (player_one_score != 21 && player_two_score != 21 && game) {
        nodelay(stdscr, TRUE);
        refresh();
        game = control(&top_rocket_one, &mid_rocket_one, &bottom_rocket_one, &top_rocket_two, &mid_rocket_two,
                       &bottom_rocket_two);
        change_direction(top_rocket_one, mid_rocket_one, bottom_rocket_one, top_rocket_two, mid_rocket_two,
                         bottom_rocket_two, &x_ball, &y_ball, &ball_direction);
        move_ball(&x_ball, &y_ball, &ball_direction);
        if (!x_ball) {
            player_two_scored(&top_rocket_one, &mid_rocket_one, &bottom_rocket_one, &top_rocket_two,
                              &mid_rocket_two, &bottom_rocket_two, &player_two_score, &x_ball, &y_ball);
        } else if (x_ball == 79) {
            player_one_scored(&top_rocket_one, &mid_rocket_one, &bottom_rocket_one, &top_rocket_two,
                              &mid_rocket_two, &bottom_rocket_two, &player_one_score, &x_ball, &y_ball);
        }
        clear();
        field(top_rocket_one, mid_rocket_one, bottom_rocket_one, top_rocket_two, mid_rocket_two,
              bottom_rocket_two, x_ball, y_ball, player_one_score, player_two_score);
        usleep(75000);
        refresh();
    }
}

int control(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
            int *mid_rocket_two, int *bottom_rocket_two) {
    int status = 1;
    char movement = getch();
    if ((movement == 'a' || movement == 'A') && *top_rocket_one > 1) {
        (*top_rocket_one)--, (*mid_rocket_one)--, (*bottom_rocket_one)--;
    } else if ((movement == 'z' || movement == 'Z') && *bottom_rocket_one < 24) {
        (*top_rocket_one)++, (*mid_rocket_one)++, (*bottom_rocket_one)++;
    } else if ((movement == 'k' || movement == 'K') && *top_rocket_two > 1) {
        (*top_rocket_two)--, (*mid_rocket_two)--, (*bottom_rocket_two)--;
    } else if ((movement == 'm' || movement == 'M') && *bottom_rocket_two < 24) {
        (*top_rocket_two)++, (*mid_rocket_two)++, (*bottom_rocket_two)++;
    } else if (movement == 'q' || movement == 'Q') {
        status = 0;
    }
    return status;
}

void change_direction(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
                      int mid_rocket_two, int bottom_rocket_two, int *x_ball, int *y_ball,
                      int *ball_direction) {
    if (*x_ball == 2) {
        if (*y_ball == top_rocket_one || *y_ball == mid_rocket_one || *y_ball == bottom_rocket_one) {
            if (*ball_direction == 2) {
                *ball_direction = 0;
            } else if (*ball_direction == 3) {
                *ball_direction = 1;
            }
        }
    } else if (*x_ball == 78) {
        if (*y_ball == top_rocket_two || *y_ball == mid_rocket_two || *y_ball == bottom_rocket_two) {
            if (*ball_direction == 1) {
                *ball_direction = 3;
            } else if (*ball_direction == 0) {
                *ball_direction = 2;
            }
        }
    } else if (*y_ball == 1) {
        if (*ball_direction == 2) {
            *ball_direction = 3;
        } else if (*ball_direction == 0) {
            *ball_direction = 1;
        }
    } else if (*y_ball == 24) {
        if (*ball_direction == 3) {
            *ball_direction = 2;
        } else if (*ball_direction == 1) {
            *ball_direction = 0;
        }
    }
}

void move_ball(int *x_ball, int *y_ball, int *ball_direction) {
    if (!*ball_direction) {
        (*x_ball)++, (*y_ball)--;
    } else if (*ball_direction == 1) {
        (*x_ball)++, (*y_ball)++;
    } else if (*ball_direction == 2) {
        (*x_ball)--, (*y_ball)--;
    } else if (*ball_direction == 3) {
        (*x_ball)--, (*y_ball)++;
    }
}

void field(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
           int mid_rocket_two, int bottom_rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score) {
    printw("                                   %.2d       %.2d\n", player_one_score, player_two_score);
    for (int y = 0; y <= 26; y++) {
        for (int x = 0; x <= 80; x++) {
            if (y == 0 || y == 25) {
                printw("#");
            } else if ((x == 0 || x == 80) && y < 25) {
                printw(".");
            } else if (y > 0 && y < 25 && x == 40) {
                printw("|");
            } else {
                if (x == 1) {
                    if (y == top_rocket_one || y == mid_rocket_one || y == bottom_rocket_one) {
                        printw("|");
                    } else {
                        printw(" ");
                    }
                } else if (x == 79) {
                    if (y == top_rocket_two || y == mid_rocket_two || y == bottom_rocket_two) {
                        printw("|");
                    } else {
                        printw(" ");
                    }
                } else if (x == x_ball && y == y_ball) {
                    printw("o");
                } else {
                    printw(" ");
                }
            }
        }
        printw("\n");
    }
}

void player_one_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_one_score, int *x_ball,
                       int *y_ball) {
    (*player_one_score)++;
    *x_ball = 78, *y_ball = 13;
    *top_rocket_one = 12, *mid_rocket_one = 13, *bottom_rocket_one = 14;
    *top_rocket_two = 12, *mid_rocket_two = 13, *bottom_rocket_two = 14;
    if (*player_one_score == 21) {
        endwin();
        printf(
            "        _\n"
            " _ __  | |  __ _  _   _   ___  _ __    ___   _ __    ___\n"
            "| '_ \\ | | / _` || | | | / _ \\| '__|  / _ \\ | '_ \\  / _ \\\n"
            "| |_) || || (_| || |_| ||  __/| |    | (_) || | | ||  __/\n"
            "| .__/ |_| \\__,_| \\__, | \\___||_|     \\___/ |_| |_| \\___|\n"
            "|_|               |___/          _         ____   _\n"
            " ___   ___  ___   _ __  ___   __| |       |___ \\ / |\n"
            "/ __| / __|/ _ \\ | '__|/ _ \\ / _` |         __) || |\n"
            "\\__ \\| (__| (_) || |  |  __/| (_| |        / __/ | |\n"
            "|___/ \\___|\\___/ |_|   \\___| \\__,_|       |_____||_|\n");
    }
}

void player_two_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_two_score, int *x_ball,
                       int *y_ball) {
    (*player_two_score)++;
    *x_ball = 2, *y_ball = 13;
    *top_rocket_one = 12, *mid_rocket_one = 13, *bottom_rocket_one = 14;
    *top_rocket_two = 12, *mid_rocket_two = 13, *bottom_rocket_two = 14;
    if (*player_two_score == 21) {
        endwin();
        printf(
            "        _                             _ \n"
            " _ __  | |  __ _  _   _   ___  _ __  | |_ __      __ ___\n"
            "| '_ \\ | | / _` || | | | / _ \\| '__| | __|\\ \\ /\\ / // _ \\\n"
            "| |_) || || (_| || |_| ||  __/| |    | |_  \\ V  V /| (_) |\n"
            "| .__/ |_| \\__,_| \\__, | \\___||_|     \\__|  \\_/\\_/  \\___/\n"
            "|_|               |___/          _         ____   _\n"
            " ___   ___  ___   _ __  ___   __| |       |___ \\ / |\n"
            "/ __| / __|/ _ \\ | '__|/ _ \\ / _` |         __) || |\n"
            "\\__ \\| (__| (_) || |  |  __/| (_| |        / __/ | |\n"
            "|___/ \\___|\\___/ |_|   \\___| \\__,_|       |_____||_|\n");
    }
}