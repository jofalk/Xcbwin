// Copyright Johannes Falk

// Code for a simple Random-Walk

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "../xcbwin.h"

// unfortunately there is no standard delay in C++,
// so we have to use preprocessor-macros to distinguish
// between Windows and Linux
// (taken from Stackoverflow http://stackoverflow.com/a/15861509/4570764
// suggested by User: Dzenan)
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif


void delay() {
  Sleep(5);  // maybe one has to modify this time
}

double get_rand() {
  return static_cast<double>(rand()) / RAND_MAX;
}

int main() {
  srand(time(NULL));
  const int WIDTH = 600;
  const int HEIGHT = 600;
  Xcbwin win;
  win.Open(WIDTH, HEIGHT);
  win.Black();
  int xPos = WIDTH/2;  // Start-x
  int yPos = HEIGHT/2;  // Start-y
  win.DrawPoint(xPos, yPos);
  while (!win.KeyIsPressed()) {  // Walk is done, until Key is pressed
    double random = get_rand();  // Cho0se the direction
    if (random < 0.25) {  // According to random, the position is changed.
      xPos = (xPos+1)%HEIGHT;
    } else if (random < 0.5) {
      xPos = (xPos-1+HEIGHT)%HEIGHT;
    } else if (random < 0.75) {
      yPos = (yPos+1)%WIDTH;
    } else {
      yPos = (yPos-1+WIDTH)%WIDTH;
    }
    win.DrawPoint(xPos, yPos);
    win.Flush();  // Force each Point to be drawn
    delay();
  }
  win.Screenshot();
  win.WaitForKeypress();
  win.Close();
}
