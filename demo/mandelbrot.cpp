
//small program to visualize the mandelbrot-set

#include <complex>
#include <iostream>
#include "../xcbwin.h"

using namespace std;
const unsigned int uiMaxSteps = 100000;
const unsigned int width = 1000;
const unsigned int height = 1000;
const unsigned int limit = 10000;
const double x_min = -2;
const double x_max = 1;
const double y_min = -2;
const double y_max = 2;

double isConvergent(complex<long double> &c) {
  complex<long double> z_n(0, 0);
  complex<long double> z_n1(c);
  for (unsigned int i = 0; i < uiMaxSteps; i++) { 
    z_n1 = z_n * z_n + c; //mandelbrot iteration
    if(abs(z_n1 - z_n) > limit ) return (i);
    z_n = z_n1;}
    
  return (uiMaxSteps*2);
}

int main (void)
{
	
  complex<long double> z0(0, 0);
  Xcbwin W;

  W.Open (width,height);

  for (int x=0; x<width; ++x)
    for (int y=0; y<height; ++y)
    {
      complex<long double> c(x_min+(x_max-x_min)*(long double)x/(width),y_min+(y_max-y_min)*(long double)y/(height));
      if(isConvergent(c) == 2*uiMaxSteps) {W.SetColor(0,0,0);}
      else {
        //the color is choosen depending on the rate of convergence
        W.SetColor(1000*isConvergent(c),1000*isConvergent(c),1000*isConvergent(c)); 
      }
      W.DrawPoint(x,y);
	
    }
  W.Screenshot(); // save screensho
}
