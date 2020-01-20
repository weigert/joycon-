#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

/*

A simple Header that adds Mouse Manipulation Capabilities for X11 Computers.

*/

enum MOUSE_BUTTON{
  NONE,
  LEFT,
  RIGHT,
};

struct pos{
  pos(int _x, int _y):x(_x), y(_y){};
  int x;
  int y;
};

void moveMousePosX(pos shift){
  Display *display = XOpenDisplay(NULL);
  if(display == nullptr) return;
  XWarpPointer(display, None, None, 0, 0, 0, 0, shift.x, shift.y);
  XCloseDisplay(display);
}

void mouseClickX(MOUSE_BUTTON button, bool down){
    Display *display = XOpenDisplay(NULL);
    XTestFakeButtonEvent(display, button, down, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
}
