// Example for the use of the Xcbwin class
// This Code produces a nice rainbow


// must be compiled using the -lxcb flag!




#include "../xcbwin.h"
#include <cmath>

int main (void)
{
Xcbwin W;
W.Open (100,100);
W.Red();
W.DrawPoint(2, 2);
W.DrawFilledRectangle(20, 20, 100, 100);
/*for (int x=0; x<800; ++x)
	for (int y=0; y<600; ++y)
		{
		W.SetColor((x/300.0+sin(y/100.0)));
		
		W.DrawPoint(x,y);
		
		}*/
W.Flush();
W.Wait();

W.Screenshot();
W.Wait();
W.Close();
}


