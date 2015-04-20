// Copyright Johannes Falk

// example for a simple contact process
// one can choose the probability in the main
// critical value ...


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "../xcbwin.h"

double get_rand() {
  return static_cast<double>(rand()) / RAND_MAX;
}


void doContactProcess(vector<int>* sites, const double LAMBDA) {
  int width = sites->size();
  for (int i = 0; i < width; ++i) {
    int next = rand() % width;
    if (sites->at(next)) {
      if (get_rand() < (1.0/(1+LAMBDA))) {
        sites->at(next) = 0;
      } else {
        int neighbour = -1;
        if (get_rand() < 0.5) {
          neighbour = (next + width -1) % width;
        } else {
          neighbour = (next +1) % width;
        }
        sites->at(neighbour) = 1;
      }
    }
  }
}


int main() {
  srand(time(NULL));
  const int HEIGHT = 600;
  const int WIDTH = 800;
  const double LAMBDA = 3.3;
  Xcbwin Window;

  vector<int> sites(WIDTH, 1);

  Window.Open(WIDTH, HEIGHT);
  Window.Blue();
  for (int time = 0; time < HEIGHT; ++time) {
    for (int i = 0; i < WIDTH; ++i) {
      if (sites[i]) Window.DrawPoint(i, time);
    }
    doContactProcess(&sites, LAMBDA);
  }
  Window.Screenshot();
  Window.WaitForKeypress();
}

