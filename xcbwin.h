/*! 
 *  \brief     A small class to produce graphic outputs
 *  \details   This class is provided for the computational physics lecture at the University Würzburg. It's a easy tool for the students to produce simple graphic outputs.
 For bugreports please contact the author.
 *  \author    Johannes Falk, jfalk@physik.uni-wuerzburg.de
 *  \version   0.1 (alpha)
 *  \date      27.11.2013
 *  \bug  no known bugs     
 *  \todo create function to draw circles
 *  \todo create function to write text
 *  \attention lo compile this class, you need to add the xcb-library using the -lxcb flag
 */



#ifndef _XCBWIN_XCBWIN_H_
#define _XCBWIN_XCBWIN_H_


#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>




class Xcbwin{


public:
 
  //! Construktor
  /** Constructor of the Xcbwin-Class. It opens a connection to the X-Server
      \param v set this to true to get verbose mode
  */
  explicit Xcbwin( bool v = false);

  //! Destructor
  /** Destructor, that is called, if an Xcbwin Object is destroyed.
      It frees the used memory and closes the connection
  */
  ~Xcbwin();

  //! Opens a new Window
  /** 
      \param width the width of the window
      \param height the height of the window
  */
  void Open( uint16_t width, uint16_t height);

  //! Draws a point
  /** Draws a Point at given position using the color set by SetColor()
      \param x x-Position of the point
      \param y y-Position of the point
      \sa SetColor(sColor scol)
  */
  void DrawPoint( int x,  int y) const;



  //! Draws a line with the given specifications

  

  void DrawLine( int x0, int y0, int x1, int y1) const;



  //! Draws a rectangle with the given specifications
  /** 
      \param x x-Position of the edge
      \param y y-Position of the edge
      \param width of the rectangle
      \param height height of the rectangle
  */
  
  void DrawRectangle( int16_t x, int16_t y, uint16_t width, uint16_t height) const;

  //! Draw a filled rectangle with the given specifications
  /** 
      \param x x-Position of the edge
      \param y y-Position of the edge
      \param width of the rectangle
      \param height height of the rectangle
  */
  void DrawFilledRectangle( int16_t x, int16_t y, uint16_t width, uint16_t height) const;

  //! Set the color that is used for the next paintings
  /** 
      \param scol a predefined color
      \sa sColor
  */
  // void SetColor(sColor scol) const;

  //! Sets the color
  /** Generates continuous color-scale in the range of 0-1 and sets the color to c
      \param c the position on the color scale (c = [0:1])
  */
  void SetColor( double c) const;

  //! Sets the color to the defined rgb value
  /** 
      \param r value of red
      \param g value of green
      \param b value of blue
  */
  void SetColor(int r, int g, int b) const;

  void Red (void) 	{ SetColor(65535, 0, 0); }
  void Yellow (void) 	{ SetColor(65535, 65535, 0); }
  void Green (void)	{ SetColor(0, 65535, 0); }
  void Blue (void)	{ SetColor(0, 0, 65535); }
  void Violet (void)	{ SetColor(65535, 0, 65535); }
  void Black (void) 	{ SetColor(0, 0, 0); }
  void Grey (void)	{ SetColor(20000, 20000, 20000); }
  void LightGrey (void)	{ SetColor(40000, 40000, 40000); }
  void White (void)	{ SetColor(65535, 65535, 65535); }





  

  //! Waits for a key-press and handles expose-events
  /** Stops the code until a key is pressed. While code is stopped, the expose events
      initialize a new drawing of the canvas */
  void Waitev() const;

  //! Closes the connection. Should be called at the end of the program
  void Close();
  
  //! Same as waitev
  /** \sa waitev() */
  void Wait()const;


  char WaitForKeypress() const;

  
  //! Flush the canvas
  /** Draws the canvas again.
      Do not use this to often since it slows down the program */
  void Flush() const;

  void Clear();


 

private:
  uint16_t width; /**< width of the window */
  uint16_t height; /**< height of the window */
  const bool VERBOSE; /**< is verbose-mode switched on */
  bool closed; /**< used to save is connection was closed correctly.
                  Otherwise this is done by the destructor*/
  xcb_screen_t        *screen; /**< holds the used screen */
  xcb_window_t         window; /**< holds the id of the  window */
  
  xcb_gcontext_t       gcontext; /**< holds the id of the context */
 
  xcb_pixmap_t pixmap; /**< holds the id of the pixmap */

  /** cookie that is used to do a x-server request*/
  xcb_intern_atom_cookie_t wm_protocols_cookie;

  /** cookie that is used to da a x-server request*/
  xcb_intern_atom_cookie_t wm_delete_window_cookie;

  /** holds the reply of a x-server request */ 
  xcb_intern_atom_reply_t* protocols_reply;

  /** holds the reply of a x-server request */

  xcb_intern_atom_reply_t* delete_window_reply;

  /** holds the id of the used colormap */
  xcb_colormap_t colormapId; 

  xcb_connection_t *connection; /**< holds the connection*/

  /**private function used to set color */
  void SetColor( uint32_t color) const;


};


//////////////////////////////////////////////////////////////////////////////
//	Hier ist xcbwin.cpp eingeschoben
//////////////////////////////////////////////////////////////////////////////


// .cpp file belonging to Xcbwin class
// for further information see header file


#include <iostream>
#include <cstring>
#include <cmath>
#include <xcb/xcb.h>
//#include "xcbwin.h"
#include <unistd.h>
#include <inttypes.h>
//#include <png.h> //currently not used

using namespace std;




Xcbwin::Xcbwin(bool v):VERBOSE(v), closed(true) {

  this->connection = xcb_connect(NULL, NULL); //returns a pointer to the x-server (Displayname, Screennumber)
  if (xcb_connection_has_error(connection)){ // test for possible errors
    cout << "Cannot open display\n" << endl;
    exit(1);}

  screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data; //get screen
  if (VERBOSE){ // print some information if in verbose-mode
    cout << "\n" << endl;
    cout << "Screen-Information" << endl;
    cout << " width: " << screen->width_in_pixels << endl;
    cout << "height: " << screen->height_in_pixels << endl;
  }

   
  /// first generate a new context
}

void Xcbwin::Open(const uint16_t width,const  uint16_t height){
  this->width = width; //set variables to member-variables
  this->height = height;
  //_______________
  //First we generate a window
  //________________
  window = xcb_generate_id(connection); //use the connectin to generate unique id for the window
  // don't change w again!
  uint32_t mask = XCB_CW_BACK_PIXEL |XCB_CW_BORDER_PIXEL| XCB_CW_EVENT_MASK; // define basic settings for the window
  uint32_t values[4];
  values[0] = screen->white_pixel;
  values[1] = screen->white_pixel;
  values[2] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

  xcb_create_window (connection,                             /* Connection          */
                     screen->root_depth, /* depth (same as root)*/
                     window,                           /* window Id           */
                     screen->root,                  /* parent window       */
                     0, 0,                          /* x, y                */
                     this->width, this->height,                      /* width, height       */
                     10U,                            /* border_width        */
                     XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                     screen->root_visual,           /* visual              */
                     mask,values);                      /* use the options defined in mask and values */
  closed = false; // set closed to false -> gets checked by destructor
  
  //______________
  //now we set the colormap
  //______________
  colormapId = screen->default_colormap;
  xcb_create_colormap (connection, XCB_COLORMAP_ALLOC_NONE, colormapId, window, screen->root_visual);

	
  xcb_map_window (connection, window); // maps the window an the screen



  
  //________________
  //next we generate a pixmap.
  //the pixmap stores every painting to recover it, if the window was covered
  //________________
  pixmap = xcb_generate_id(connection);
  xcb_create_pixmap(connection,screen->root_depth,pixmap,window,this->width,this->height);
  

  //______________
  //now we generate a context.
  //a context is something like a pen, with a defined color and size
  //______________

  gcontext = xcb_generate_id(connection);
	

  mask = XCB_GC_FOREGROUND|XCB_GC_BACKGROUND| XCB_GC_LINE_WIDTH| XCB_GC_GRAPHICS_EXPOSURES;
  values[0] = screen->white_pixel;
  values[1] = screen->white_pixel;
  values[2] = 1;
  values[3] = 0;
  xcb_create_gc(connection,gcontext,pixmap,mask,values);
  DrawFilledRectangle(0,0,this->width, this->height); //set initial pixmap color to white
  Flush();

  Black();

  //some x-window magic to handle close events
  wm_protocols_cookie = xcb_intern_atom(connection, 1, 12,"WM_PROTOCOLS");
  protocols_reply = xcb_intern_atom_reply(connection, wm_protocols_cookie, 0);

  wm_delete_window_cookie = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
  delete_window_reply = xcb_intern_atom_reply(connection, wm_delete_window_cookie, 0);
  // 
  
  
}




void Xcbwin::DrawPoint(int x, int y) const{

  xcb_point_t point[1]; //save the point in a array
  point[0].x = (uint16_t) x;
  point[0].y = (uint16_t) y;
  //Auskommentiert von Hinrichsen, da nicht benutzt
  //xcb_void_cookie_t cook = 
  xcb_poly_point (connection, XCB_COORD_MODE_ORIGIN, pixmap, gcontext, 1, point); //paint point to pixmap
 
  xcb_copy_area(connection,pixmap,window,gcontext,(uint16_t)x,(uint16_t)y,(uint16_t)x,(uint16_t)y,1,1); //copy pixmap to screen
  xcb_generic_event_t *event = xcb_poll_for_event(connection);
  if(event){ //if windows was exposed, we draw everything again
    if((event->response_type & ~0x80)== XCB_EXPOSE)Flush();
  }
  free(event);
}


void Xcbwin::DrawLine(int x0, int y0, int x1, int y1) const {

  xcb_point_t point[2] ;
  point[0].x = (uint16_t) x0;
  point[0].y = (uint16_t) y0;

  point[1].x = (uint16_t) x1;
  point[1].y = (uint16_t) y1;

  xcb_poly_line (connection, XCB_COORD_MODE_ORIGIN, pixmap, gcontext, 2, point); //paint line to pixmap

  xcb_copy_area(connection,pixmap,window,gcontext,0,0,0,0,this->width,this->height); //copy pixmap to screen
   

  Flush();


}




void Xcbwin::DrawRectangle(int16_t x,int16_t y, uint16_t width, uint16_t height) const{ //can be used to draw rectangles and lines

  xcb_rectangle_t      rectangles[] = { //saves properties of rectangle to array
    { x, y, width, height}};
 
  //Auskommentiert von Hinrichsen, da nicht benutzt
  //xcb_void_cookie_t cook = 
  xcb_poly_rectangle (connection, pixmap, gcontext, 1, rectangles);/// Draws a rectangle (only the border)
  xcb_copy_area(connection,pixmap,window,gcontext,0,0,0,0,this->width,this->height); //copy pixmap to screen

  Flush();
  
}


void Xcbwin::DrawFilledRectangle(int16_t x,int16_t y, uint16_t width, uint16_t height) const{ //can be used to draw rectangles and lines
  // same as DrawRectangle
  xcb_rectangle_t      rectangles[] = {
    { x, y, width, height}};
 
  //Auskommentiert von Hinrichsen, da nicht benutzt
  //xcb_void_cookie_t cook = 
  xcb_poly_fill_rectangle (connection, pixmap, gcontext, 1, rectangles);/// Draws a rectangle (only the border)
  xcb_copy_area(connection,pixmap,window,gcontext,0,0,0,0,this->width,this->height); //copy pixmap to screen

  Flush();
 
}








void Xcbwin::Wait() const { //Just to be compatible to XWindow
  Waitev();
}

void Xcbwin::Waitev() const {

  
  xcb_generic_event_t *event;
  while((event = xcb_wait_for_event(connection))) //wait until event occurs
  {
    switch((*event).response_type & ~0x80)
    {
      case XCB_EXPOSE: //if expose event we copy the pixmap to the screen
        {
          xcb_expose_event_t *ev = reinterpret_cast<xcb_expose_event_t*> (event);
          xcb_copy_area(connection,pixmap,window,gcontext,ev->x,ev->y,ev->x,ev->y,ev->width,ev->height);
          xcb_flush(connection);
          free(ev);
        }
        break;
	// case XCB_CLIENT_MESSAGE: // can be used to generate an event, if the kill button was pressed
      
        
	//   if((*(xcb_client_message_event_t*)event).data.data32[0] == (*delete_window_reply).atom)
	//     {
	//       puts("Kill was pressed");
	//       exit(0);
	//       // xcb_change_property(c, XCB_PROP_MODE_REPLACE, w, (*protocols_reply).atom, 4,32,1,&(*protocols_reply).atom);
	//       return ;
	//     }
	//   exit(0);
	//   break;
      case XCB_KEY_PRESS:
        // if any key was pressed, return
        free(event);
        return;
        break;

      default:
        free(event);
        break;
    }
  }
  
}



char Xcbwin::WaitForKeypress() const {

  
 xcb_generic_event_t *event;
  while((event = xcb_wait_for_event(connection))) //wait until event occurs
  {
    switch((*event).response_type & ~0x80)
    {
      case XCB_EXPOSE: //if expose event we copy the pixmap to the screen
        {
          xcb_expose_event_t *ev = reinterpret_cast<xcb_expose_event_t*> (event);
          xcb_copy_area(connection,pixmap,window,gcontext,ev->x,ev->y,ev->x,ev->y,ev->width,ev->height);
          xcb_flush(connection);
          free(ev);
        }
        break;
	// case XCB_CLIENT_MESSAGE: // can be used to generate an event, if the kill button was pressed
      
        
	//   if((*(xcb_client_message_event_t*)event).data.data32[0] == (*delete_window_reply).atom)
	//     {
	//       puts("Kill was pressed");
	//       exit(0);
	//       // xcb_change_property(c, XCB_PROP_MODE_REPLACE, w, (*protocols_reply).atom, 4,32,1,&(*protocols_reply).atom);
	//       return ;
	//     }
	//   exit(0);
	//   break;
      case XCB_KEY_PRESS:
        {
        // if any key was pressed, return
        xcb_key_press_event_t *bp = reinterpret_cast<xcb_key_press_event_t*> (event);
              
        cout << bp->detail << endl;
        free(event);
        return 0;
        }
        break;

      default:
        free(event);
        break;
    }
  }
  
  
}


void Xcbwin::Flush() const { //Flush the connection and copy pixmap to screen
  xcb_flush(connection);
  xcb_copy_area(connection,pixmap,window,gcontext,0,0,0,0,this->width,this->height);
  

}


Xcbwin::~Xcbwin(){ // if connection is not yet closed, do it
  xcb_free_pixmap(connection,pixmap);
  if(!closed) Xcbwin::Close();
}

void Xcbwin::Close(){ //Close connection
  if(connection){
    xcb_disconnect(connection);
    closed = true;
    
  }
}

void Xcbwin::SetColor( uint32_t color) const
{ xcb_change_gc(connection, gcontext, XCB_GC_FOREGROUND, &color); } //sets the foreground color


void Xcbwin::SetColor( double c) const // taken from xwindows to generate continuous color-scale
{
  double c1=c-floor(c);
  double c2=c1+1.0/3-floor(c1+1.0/3);
  double c3=c2+1.0/3-floor(c2+1.0/3);
  int r = 255-(c1<0.5 ? static_cast<int>(512*c1) : 511-static_cast<int>(512*c1));
  int g = 255-(c2<0.5 ? static_cast<int>(512*c2) : 511-static_cast<int>(512*c2));
  int b = 255-(c3<0.5 ? static_cast<int>(512*c3) : 511-static_cast<int>(512*c3));
  SetColor(static_cast<uint32_t>(r<<16 | g<<8 | b));
}







void Xcbwin::SetColor(int r, int g, int b) const { //sets color to given rgb value
  
  xcb_alloc_color_reply_t *reply = xcb_alloc_color_reply (connection,xcb_alloc_color (connection,colormapId,(uint16_t)r,(uint16_t)g,(uint16_t)b),NULL ); //calculate pixel-value, that produces the requested rgb color.
  if (!reply) {
    free(reply);
    return;
  }
  Xcbwin::SetColor(reply->pixel);
  free(reply);

}


void Xcbwin::Clear() {
  White();
 DrawFilledRectangle(0,0,this->width, this->height); //set initial pixmap color to white
  Flush();
  Black();
}




#endif // _XCBWIN_XCBWIN_H_

