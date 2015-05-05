// Copyright Johannes Falk

// Code for a simple Random-Walk

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../xcbwin.h"

const int WIDTH = 600;
const int HEIGHT = 600;


bool checkfortrap(const vector < vector<int> > &positions, int xPos, int yPos) {
  int check = positions[(xPos+1)%HEIGHT][yPos] +
      positions[(xPos-1+HEIGHT)%HEIGHT][yPos] +
      positions[xPos][(yPos+1)%WIDTH] +
      positions[xPos][(yPos-1+WIDTH)%WIDTH];
  if (check == 4) return true;
  return false;
}

void delay() {
  sleep(0.5);  // maybe one has to modify this time
}

double get_rand() {
  return static_cast<double>(rand()) / RAND_MAX;
}

int main() {
  srand(time(NULL));
  vector< vector<int> > positions(WIDTH, vector<int>(HEIGHT, 0));
  Xcbwin win;
  win.Open(WIDTH, HEIGHT);
  win.Red();
  int xPos = WIDTH/2;  // Start-x
  int yPos = HEIGHT/2;  // Start-y
  win.DrawPoint(xPos, yPos);
  positions[xPos][yPos] = 1;
  win.Black();
  while (!checkfortrap(positions, xPos, yPos)) {
    // Walk is done, until Key is pressed
    double random = get_rand();  // Cho0se the direction
    if (random < 0.25) {  // According to random, the position is changed.
      int newxPos = (xPos+1)%HEIGHT;
      if (!positions[newxPos][yPos]) xPos = newxPos;
    } else if (random < 0.5) {
      int newxPos = (xPos-1+HEIGHT)%HEIGHT;
      if (!positions[newxPos][yPos]) xPos = newxPos;
    } else if (random < 0.75) {
      int newyPos = (yPos+1)%WIDTH;
      if (!positions[xPos][newyPos]) yPos = newyPos;
    } else {
      int newyPos = (yPos-1+WIDTH)%WIDTH;
      if (!positions[xPos][newyPos]) yPos = newyPos;
    }
    win.DrawPoint(xPos, yPos);
    positions[xPos][yPos] = 1;
    win.Flush();  // Force each Point to be drawn
    //    delay();
  }
  std::cout << "TRAPPED" << std::endl;
  win.Screenshot();
  win.WaitForKeypress();
  win.Close();
}
