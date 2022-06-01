#include <curses.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <term.h>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include <thread>


typedef int I;struct P;;   float                              a,b,c;;                 int A=3, B=12;;float
C=60.0;float f=16.00000,  k=0.200;                          const float               e=f/70.0;std::vector<P>
z;struct P/*FF*/{P(int x  ,int wy)                        :g(0){t(x,wy);}             void t(int pwx,int wy){g+=
pwx;h=                    rand()%(                       wy-10)+5;}void d(            WINDOW*            W,I wx,
I wy){                    for(I x=                      0;x<B;++x)for(I y=0;          y<wy;++y           )if(y<=h-
A||y>=                    h+A/**/)                     mvwaddch(    W,y,x+g-a         ,'#');}I           g;I h;};I
r(WINDOW* W,I wx,         I wy){for                  (auto Z:z)      Z.d(W,wx,wy      );wmove(W           ,(I)b,10);
if(winch(W)=='#')         return 1;                  waddch(W,c      >0?'p':'b')      ;wrefresh(W);return 0;}I main
(){a=10,b=10,c=0;         int pwx;                  I ch;struct      winsize w;;      ioctl(STDOUT_FILENO,TIOCGWINSZ
,&w/**/                   );srand(                  time(NULL));for(I i=1;i<=ceil     (w.ws_col/C)+2;++i&&(pwx=i*C))
z./*F*/                   push_back                 ({i*(I)C,w.ws_row});initscr();    noecho();WINDOW* W=newwin(w.
ws_row,                   w.ws_col,0               ,0);nodelay(       stdscr,true);   curs_set(0
);while                   (true){if((ch=getch())!=  ERR&&ch==          0x20)c=-1.2;   if((I)b>=w.
ws_row||                  (I)b<0)goto q;for(auto&Z :z)if(Z.g-          (I)a<-B)Z.t(   pwx,w.ws_row
);werase                  (W);float M=1.0;float N= 1.0;a+=N*e;         b+=c*e;c+=k    *e;if(c>M)c=
M;if(r(W                  ,w.ws_col,w.ws_row))goto q;std::/**/         this_thread    ::sleep_for



(std::chrono::milliseconds((I)f));};q:endwin();
std::cout
   <<"Game over" <<std::endl
   << "you scored "<<((I)a)
   <<" points"<<std::endl;
return 0;
}
