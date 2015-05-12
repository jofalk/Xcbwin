# Demos for Xcbwin

**This is the demo-folder of [Xcbwin](https://raw.github.com/jofalk/Xcbwin/master)**


Xcbwin is a lightweight class that provides rudimental and fast methods to produce simple graphical outputs in Linux. In this folder you can find some simple programs that demonstrate the capability and the usage of Xcbwin.

Currently there are C++ examples with graphical output for:

*  Simple rainbow
*  Random Walk
*  Self-avoiding random walk
*  Contact Process
*  Mandelbrot set
*  Directed Percolation


## Details of the provided examples

### Simple Rainbow

This is just a sample code to test if Xcbwin is working correctly. If so, after compiling and executing the code, one should see a nice rainbow.

### Random Walk

Sample code in C++ for a [Random-walk](http://en.wikipedia.org/wiki/Random_walk) in 2D. The path is drawn in real-time on the canvas.
It is very easy to modify the code for some related purposes, e.g. calculating the mean-displacement.

### Self avoiding random walk

The standard random walk can revisit sites. The [self-avoiding walk](http://en.wikipedia.org/wiki/Self-avoiding_walk) is some modification where the path can not revisit any site.
The program stops as soon as the walk trapped itself (which happens most time quite fast).

### Contact Process

The [Contact process](http://en.wikipedia.org/wiki/Contact_process_%28mathematics%29) is a Markov process of interacting particles that is often used as a simulation of infection spreading. 
The sample code presents one simple implementation of such a stochastic process in (1+1)D.
One axis is spatial and one is temporal. 
Modifying the parameter "lambda" one can change the transition rates and observe a phase transition. At the transition point the 
system shows self-similarity.


### Mandelbrot set

The [Mandelbrot-set](http://en.wikipedia.org/wiki/Mandelbrot_set) is a well known set of complex numbers. The C++ code provided produces the image of such a Mandelbrot-set which has fractal properties.

### Directed Percolation

This code is an example of a lattice model of [Directed percolation](http://en.wikipedia.org/wiki/Directed_percolation). Similar to the Contact Process one can modify a parameter "PROP"
and observe a phase transition.

##Contributions

If you have some good ideas or suggestions for new demos, please feel free to get in touch. We are always happy abour new ideas and code samples.

## License

Xcbwin is published under the MIT license. See the LICENSE file for more info.


##Contact

If you have any trouble using this class, feel free to contact the author @jofalk.

