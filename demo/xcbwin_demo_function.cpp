// Example for the use of the Xcbwin class
// This Code show how to draw functions

// must be compiled using the -lxcb flag!


#include "../xcbwin.h"
#include <cmath>


double testFunction(double x) {
  return sin(x) * exp(x);
}

int main (void)
{
Xcbwin W;
W.Open (800,600);

W.Blue();
W.DrawFunction(&sin, -5, 5, -2.5, 2.5);
W.Red();
W.DrawFunction(&exp, -5, 5, -2.5, 2.5);
W.Green();
W.DrawFunction(&testFunction, -5, 5, -2.5, 2.5);

W.Wait();
W.Close();
}


