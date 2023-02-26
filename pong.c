#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

void field(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
           int mid_rocket_two, int bottom_rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score);
int control(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
            int *mid_rocket_two, int *bottom_rocket_two);
void player_one_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_one_score, int *x_ball,
                       int *y_ball);
void player_two_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_two_score, int *x_ball,
                       int *y_ball);
void change_dir(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
                int mid_rocket_two, int bottom_rocket_two, int *x_ball, int *y_ball, char *move_ball);
void game(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
          int mid_rocket_two, int bottom_rocket_two, int x_ball, int y_ball, int player_one_score,
          int player_two_score, char move_ball);

int main() {
    int x_ball = 2;
    int y_ball = 13;
    char move_ball = 'a';
    int top_rocket_one = 12;
    int mid_rocket_one = 13;
    int bottom_rocket_one = 14;
    int top_rocket_two = 12;
    int mid_rocket_two = 13;
    int bottom_rocket_two = 14;
    int player_one_score = 0;
    int player_two_score = 0;
    initscr();
    clear();
    game(top_rocket_one, mid_rocket_one, bottom_rocket_one, top_rocket_two, mid_rocket_two, bottom_rocket_two,
         x_ball, y_ball, player_one_score, player_two_score, move_ball);
    return 0;
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
            } else if (y >= 1 && y < 25 && x == 40) {
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

int control(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
            int *mid_rocket_two, int *bottom_rocket_two) {
    char movement = getch();
    if ((movement == 'a' || movement == 'A') && *top_rocket_one > 1) {
        *top_rocket_one -= 1;
        *mid_rocket_one -= 1;
        *bottom_rocket_one -= 1;
    } else if ((movement == 'z' || movement == 'Z') && *bottom_rocket_one < 24) {
        *top_rocket_one += 1;
        *mid_rocket_one += 1;
        *bottom_rocket_one += 1;
    } else if ((movement == 'k' || movement == 'K') && *top_rocket_two > 1) {
        *top_rocket_two -= 1;
        *mid_rocket_two -= 1;
        *bottom_rocket_two -= 1;
    } else if ((movement == 'm' || movement == 'M') && *bottom_rocket_two < 24) {
        *top_rocket_two += 1;
        *mid_rocket_two += 1;
        *bottom_rocket_two += 1;
    } else if (movement == 'q' || movement == 'Q') {
        return 0;
    }
    return 1;
}

void player_one_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_one_score, int *x_ball,
                       int *y_ball) {
    *player_one_score += 1;
    *x_ball = 78;
    *y_ball = 13;
    *top_rocket_one = 12;
    *mid_rocket_one = 13;
    *bottom_rocket_one = 14;
    *top_rocket_two = 12;
    *mid_rocket_two = 13;
    *bottom_rocket_two = 14;
    if (*player_one_score == 21) {
        endwin();
        printf("\t\t\t\t Player ONE Scored!\n\t\t\t\t __________________\n");
        printf(
            "\t\t\t\t| 2222       1111  |\n\t\t\t\t|222222     111111 "
            "|\n\t\t\t\t|22  22    11  111 |\n\t\t\t\t|2   22    1   111 "
            "|\n\t\t\t\t|   22         111 |\n\t\t\t\t|  22          111 "
            "|\n\t\t\t\t|2222222       111 |\n\t\t\t\t|22222222     "
            "11111|\n\t\t\t\t __________________\n\n");
    }
}

void player_two_scored(int *top_rocket_one, int *mid_rocket_one, int *bottom_rocket_one, int *top_rocket_two,
                       int *mid_rocket_two, int *bottom_rocket_two, int *player_two_score, int *x_ball,
                       int *y_ball) {
    *player_two_score += 1;
    *x_ball = 2;
    *y_ball = 13;
    *top_rocket_one = 12;
    *mid_rocket_one = 13;
    *bottom_rocket_one = 14;
    *top_rocket_two = 12;
    *mid_rocket_two = 13;
    *bottom_rocket_two = 14;
    if (*player_two_score == 21) {
        endwin();
        printf("\t\t\t\t Player TWO Scored!\n\t\t\t\t __________________\n");
        printf(
            "\t\t\t\t| 2222       1111  |\n\t\t\t\t|222222     111111 "
            "|\n\t\t\t\t|22  22    11  111 |\n\t\t\t\t|2   22    1   111 "
            "|\n\t\t\t\t|   22         111 |\n\t\t\t\t|  22          111 "
            "|\n\t\t\t\t|2222222       111 |\n\t\t\t\t|22222222     "
            "11111|\n\t\t\t\t __________________\n\n");
    }
}

void change_dir(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
                int mid_rocket_two, int bottom_rocket_two, int *x_ball, int *y_ball, char *move_ball) {
    if (*x_ball == 2) {
        if (*y_ball == top_rocket_one || *y_ball == mid_rocket_one || *y_ball == bottom_rocket_two) {
            if (*move_ball == 'c') {
                *move_ball = 'a';
            } else if (*move_ball == 'd') {
                *move_ball = 'b';
            }
        }
    } else if (*x_ball == 78) {
        if (*y_ball == top_rocket_two || *y_ball == mid_rocket_two || *y_ball == bottom_rocket_two) {
            if (*move_ball == 'b') {
                *move_ball = 'd';
            } else if (*move_ball == 'a') {
                *move_ball = 'c';
            }
        }
    }
    if (*y_ball == 1) {
        if (*move_ball == 'c') {
            *move_ball = 'd';
        } else if (*move_ball == 'a') {
            *move_ball = 'b';
        }
    }
    if (*y_ball == 24) {
        if (*move_ball == 'd') {
            *move_ball = 'c';
        } else if (*move_ball == 'b') {
            *move_ball = 'a';
        }
    }
    if ('a' == *move_ball) {
        *x_ball += 1;
        *y_ball -= 1;
    }
    if ('b' == *move_ball) {
        *x_ball += 1;
        *y_ball += 1;
    }
    if ('c' == *move_ball) {
        *x_ball -= 1;
        *y_ball -= 1;
    }
    if ('d' == *move_ball) {
        *x_ball -= 1;
        *y_ball += 1;
    }
}

void game(int top_rocket_one, int mid_rocket_one, int bottom_rocket_one, int top_rocket_two,
          int mid_rocket_two, int bottom_rocket_two, int x_ball, int y_ball, int player_one_score,
          int player_two_score, char move_ball) {
    while (player_one_score != 21 && player_two_score != 21) {
        nodelay(stdscr, TRUE);
        refresh();
        if (control(&top_rocket_one, &mid_rocket_one, &bottom_rocket_one, &top_rocket_two, &mid_rocket_two,
                    &bottom_rocket_two) == 0) {
            endwin();
            break;
        }
        change_dir(top_rocket_one, mid_rocket_one, bottom_rocket_one, top_rocket_two, mid_rocket_two,
                   bottom_rocket_two, &x_ball, &y_ball, &move_ball);
        if (x_ball == 0) {
            player_two_scored(&top_rocket_one, &mid_rocket_one, &bottom_rocket_one, &top_rocket_two,
                              &mid_rocket_two, &bottom_rocket_two, &player_two_score, &x_ball, &y_ball);
            continue;
        } else if (x_ball == 79) {
            player_one_scored(&top_rocket_one, &mid_rocket_one, &bottom_rocket_one, &top_rocket_two,
                              &mid_rocket_two, &bottom_rocket_two, &player_one_score, &x_ball, &y_ball);
            continue;
        }
        clear();
        field(top_rocket_one, mid_rocket_one, bottom_rocket_one, top_rocket_two, mid_rocket_two,
              bottom_rocket_two, x_ball, y_ball, player_one_score, player_two_score);
        usleep(75000);
        refresh();
    }
}
