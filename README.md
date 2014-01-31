# Xcbwin


**Xcbwin - a simple C++ class for graphical outputs using XCB.**


Xcbwin is a lightweight class that provides rudimental and fast methods to produce simple graphical outputs. The Xcbwin class is written for the "Computational Physics" lecture given at the University of Wuerzburg (Germany). Hence it is designed to be easy to use even by students, that are new to C++. 

Currently the class provides methods to:


*  Draw lines, circles, points, rectangles and text
*  Plot functions
*  Save screenshot of drawing
*  Change the color
*  Handle keyboard events


The Xcbwin-class is based on the [Xwindow-class](http://www.physik.uni-wuerzburg.de/~hinrichsen/teaching/CP/Material/Quelltexte/xwindows) that was written using Xlib. 
Xcbwin is designed to be downwardly compatible to the Xwindow-class, but uses [XCB](http://xcb.freedesktop.org/) (X protocol C-language Binding) which is intended to be a replacement for Xlib in the future.


To be easy to compile the Xcbwin-class consists only of one file. This can be downloaded here:

**[Download xcbwin.h](https://raw.github.com/jofalk/Xcbwin/master/xcbwin.h)**



## Usage

It's easy and almost self-explanatory how to use Xcbwin:

```C++
#include "xcbwin.h"
int main() {

Xcbwin Window;
Window.Open(400,400); //Opens a Window of size 400x400
Window.Black(); //Sets the drawing-color to black
Window.DrawRectangle(20,20,30,30); //Draws a Rectangle
Window.Wait(); // Waits for a keypress-event
Window.Screenshot(); //Saves a screenshot of the drawing
Window.Close(); //Closes the Window

}

```

To compile ỳou have to link the xcb-library:
```
g++ mycode.cpp -lxcb
```


For a better example look at the "demo" folder.


##Contributions

If you have some good ideas or suggestions how to improve the Xcbwin class please do not hesitate to fork the project or get in touch. 
Currently the official Xcb-documentation is sometimes not very helpful. Hence a lot of the code was written by "try and error" and there are many flaws that need to be corrected. So even if you just have criticism please get in touch :-) .


## License

Xcbwin is published under the MIT license. See the LICENSE file for more info.


##Contact

If you have any trouble using this class, feel free to contact the author @jofalk.

