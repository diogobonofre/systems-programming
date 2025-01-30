#include <X11/X.h>
#include <X11/Xlib.h>

#include <stdio.h>

int main()
{
	// establish connection with xorg server
	Display *display = XOpenDisplay(NULL);

	if (display == NULL) {
		printf("error: unable to establish connection with xorg");
	}
  
	// return information about the display
	int screenDefault = XDefaultScreen(display);
	int screenCount = XScreenCount(display);
	int screenWidth = XDisplayWidth(display, screenDefault);
	int screenHeight = XDisplayHeight(display, screenDefault);

	// log display information
	printf("default screen number: %d\n", screenDefault);
	printf("screen count: %d\n", screenCount);
	printf("screen dimensions: %dx%d\n", screenWidth, screenHeight);

	// create window
	Window window = XCreateSimpleWindow(display, XDefaultRootWindow(display), 0, 0, 250, 250, 1,
					    BlackPixel(display, 0), WhitePixel(display, 0));

	// map window to display
	XMapWindow(display, window);
	XSelectInput(display, window, ExposureMask);

	XEvent event;
	for (;;) {
		XNextEvent(display, &event);
		if (event.type == Expose) {
			XDrawString(display, window, DefaultGC(display, 0), 100, 100, "Xorg Window Created!", 20);
		}
	}
	
	return 0;
}
