// Copyright Johannes Falk

// example for directed percolation
// one can choose the probability in the main
// critical-value = 0.68

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

// this function does the percolation steps
// since google-c++-style does not allow references
// for out-parameters, we use a pointer
void doPercolationStep(vector<int>* sites, const double PROP, int time) {
  int size = sites->size();
  int even = time%2;
  for (int i = even; i < size; i += 2) {
    if (sites->at(i)) {
      if (get_rand() < PROP) sites->at((i+size-1)%size) = 1;
      if (get_rand() < PROP) sites->at((i+1)%size) = 1;
      sites->at(i) = 0;
      }
  }
}


int main() {
  srand(time(NULL));  // initialize the random-generator
  const int HEIGHT = 600;
  const int WIDTH = 800;
  // modify here
  const double PROP = 0.68;  // probability for bond to be open
  Xcbwin Window;

  vector<int> sites(WIDTH, 1);
  Window.Open(WIDTH, HEIGHT);

  for (int y = 0; y < HEIGHT; ++y) {
  for (int x = 0; x < WIDTH; ++x) {
    if (sites[x]) {
    Window.Black();
    Window.DrawPoint(x, y);
    }
  }
  doPercolationStep(&sites, PROP, y);
  }
  Window.Screenshot();
  Window.WaitForKeypress();
}
