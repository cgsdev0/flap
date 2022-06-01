#include <term.h>
#include <iostream>

#include <curses.h>
#include <sys/ioctl.h>  //ioctl() and TIOCGWINSZ
#include <unistd.h>     // for STDOUT_FILENO
// ...
//
#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout, std::endl
#include <thread>    // std::this_thread::sleep_for
#include <vector>

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <cmath>

float px, py;
float vel;

const int PIPE_GAP = 3;
const int PIPE_WIDTH = 12;
const float PIPE_SPACING = 60.0;

const float framerate = 16.0;

const float fudge_ratio = framerate / 70.0;

class Pipe {
   public:
    Pipe(int x, int wy) {
        pos_x = x;
        gap_y = rand() % (wy - 10) + 5;
    }

    void teleport(int pwx, int wy) {
        this->pos_x += pwx;
        this->gap_y = rand() % wy;
    }

    void draw(WINDOW* win, int wx, int wy) {
        for (int x = 0; x < PIPE_WIDTH; ++x) {
            for (int y = 0; y < wy; ++y) {
                if (y > gap_y - PIPE_GAP && y < gap_y + PIPE_GAP) continue;
                mvwaddch(win, y, x + pos_x - px, '#');
            }
        }
    }

    int pos_x;
    int gap_y;
};

std::vector<Pipe> pipes;

void predraw(WINDOW* win, int wx, int wy) { werase(win); }

int draw_and_check_for_collisions(WINDOW* win, int wx, int wy) {
    for (auto pipe : pipes) {
        pipe.draw(win, wx, wy);
    }
    wmove(win, (int)py, 10);
    if (winch(win) == '#') {
        return 1;
    }
    if (vel > 0) {
        waddch(win, 'p');
    } else {
        waddch(win, 'b');
    }
    wrefresh(win);
    return 0;
}

void physics() {
    float MAX_VEL = 1.0;
    float SCROLL_SPEED = 1.0;

    px += SCROLL_SPEED * fudge_ratio;
    py += vel * fudge_ratio;
    vel += 0.2 * fudge_ratio;
    if (vel > MAX_VEL) {
        vel = MAX_VEL;
    }
}

int main() {
    px = 10;
    py = 10;
    vel = 0;
    int pwx;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    srand(time(NULL));

    for (int i = 1; i <= ceil(w.ws_col / PIPE_SPACING) + 2; ++i) {
        pipes.push_back({i * (int)PIPE_SPACING, w.ws_row});
        pwx = i * PIPE_SPACING;
    }

    initscr();
    noecho();

    WINDOW* win = newwin(w.ws_row, w.ws_col, 0, 0);
    nodelay(stdscr, true);
    curs_set(0);

    int ch;
    while (true) {
        if ((ch = getch()) != ERR) {
            if (ch == 0x20) {  // space
                vel = -1.2;
            }
        }
        if ((int)py >= w.ws_row || (int)py < 0) {
            endwin();
            std::cout << "Game over" << std::endl;
            std::cout << "you scored " << ((int)px) << " points" << std::endl;
            return 1;
        }
        for (auto& pipe : pipes) {
            if (pipe.pos_x - (int)px < -PIPE_WIDTH) {
                pipe.teleport(pwx, w.ws_row);
            }
        }
        predraw(win, w.ws_col, w.ws_row);
        physics();
        if (draw_and_check_for_collisions(win, w.ws_col, w.ws_row)) {
            endwin();
            std::cout << "Game over" << std::endl;
            std::cout << "you scored " << ((int)px) << " points" << std::endl;
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((int)framerate));
    };

    endwin();
    return 0;
}
