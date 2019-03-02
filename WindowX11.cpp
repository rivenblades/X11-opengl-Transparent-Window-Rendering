#include "WindowX11.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void WindowX11::createWindow(){
	XEvent event;
	int x,y, attr_mask;
	XSizeHints hints;
	XWMHints *startup_state;
	XTextProperty textprop;
	XSetWindowAttributes attr = {0,};
	static char *title = "FTB's little OpenGL example - ARGB extension by WXD";

	display = XOpenDisplay(NULL);
	if (!display) {
		fatalError("Couldn't connect to X server\n");
	}
	Xscreen = DefaultScreen(display);
	Xroot = RootWindow(display, Xscreen);

	fbconfigs = glXChooseFBConfig(display, Xscreen, VisData, &numfbconfigs);
	fbconfig = 0;
	for(int i = 0; i<numfbconfigs; i++) {
		visual = (XVisualInfo*) glXGetVisualFromFBConfig(display, fbconfigs[i]);
		if(!visual)
			continue;

		pict_format = XRenderFindVisualFormat(display, visual->visual);
		if(!pict_format)
			continue;

		fbconfig = fbconfigs[i];
		if(pict_format->direct.alphaMask > 0) {
			break;
		}
	}

	if(!fbconfig) {
		fatalError("No matching FB config found");
	}

	describe_fbconfig(fbconfig);

	/* Create a colormap - only needed on some X clients, eg. IRIX */
	cmap = XCreateColormap(display, Xroot, visual->visual, AllocNone);

	attr.colormap = cmap;
	attr.background_pixmap = None;
	attr.border_pixmap = None;
	attr.border_pixel = 0;
	attr.event_mask =
		StructureNotifyMask |
		EnterWindowMask |
		LeaveWindowMask |
		ExposureMask |
		ButtonPressMask |
		ButtonReleaseMask |
		OwnerGrabButtonMask |
		KeyPressMask |
		KeyReleaseMask;

	attr_mask = 
	//	CWBackPixmap|
		CWColormap|
		CWBorderPixel|
		CWEventMask;

	width = DisplayWidth(display, DefaultScreen(display))/2;
	height = DisplayHeight(display, DefaultScreen(display))/2;
	x=width/2, y=height/2;

	window_handle = XCreateWindow(	display,
					Xroot,
					x, y, width, height,
					0,
					visual->depth,
					InputOutput,
					visual->visual,
					attr_mask, &attr);

	if( !window_handle ) {
		fatalError("Couldn't create the window\n");
	}

#if USE_GLX_CREATE_WINDOW
	fputs("glXCreateWindow ", stderr);
	int glXattr[] = { None };
	glX_window_handle = glXCreateWindow(display, fbconfig, window_handle, glXattr);
	if( !glX_window_handle ) {
		fatalError("Couldn't create the GLX window\n");
	}
#else
	glX_window_handle = window_handle;
#endif

	textprop.value = (unsigned char*)title;
	textprop.encoding = XA_STRING;
	textprop.format = 8;
	textprop.nitems = strlen(title);

	hints.x = x;
	hints.y = y;
	hints.width = width;
	hints.height = height;
	hints.flags = USPosition|USSize;

	startup_state = XAllocWMHints();
	startup_state->initial_state = NormalState;
	startup_state->flags = StateHint;

	XSetWMProperties(display, window_handle,&textprop, &textprop,
			NULL, 0,
			&hints,
			startup_state,
			NULL);

	XFree(startup_state);

	XMapWindow(display, window_handle);
	/*XIfEvent(display, &event, WaitForMapNotify, (char*)&window_handle);

	if ((del_atom = XInternAtom(display, "WM_DELETE_WINDOW", 0)) != None) {
		XSetWMProtocols(display, window_handle, &del_atom, 1);
	}*/
}

Bool WindowX11::WaitForMapNotify(Display *d, XEvent *e, char *arg)
{
	return d && e && arg && (e->type == MapNotify) && (e->xmap.window == *(Window*)arg);
}

void WindowX11::fatalError(const char *why)
{
	fprintf(stderr, "%s", why);
	exit(0x666);
}

void WindowX11::describe_fbconfig(GLXFBConfig fbconfig)
{
	int doublebuffer;
	int red_bits, green_bits, blue_bits, alpha_bits, depth_bits;

	glXGetFBConfigAttrib(display, fbconfig, GLX_DOUBLEBUFFER, &doublebuffer);
	glXGetFBConfigAttrib(display, fbconfig, GLX_RED_SIZE, &red_bits);
	glXGetFBConfigAttrib(display, fbconfig, GLX_GREEN_SIZE, &green_bits);
	glXGetFBConfigAttrib(display, fbconfig, GLX_BLUE_SIZE, &blue_bits);
	glXGetFBConfigAttrib(display, fbconfig, GLX_ALPHA_SIZE, &alpha_bits);
	glXGetFBConfigAttrib(display, fbconfig, GLX_DEPTH_SIZE, &depth_bits);

	fprintf(stderr, "FBConfig selected:\n"
		"Doublebuffer: %s\n"
		"Red Bits: %d, Green Bits: %d, Blue Bits: %d, Alpha Bits: %d, Depth Bits: %d\n",
		doublebuffer == True ? "Yes" : "No", 
		red_bits, green_bits, blue_bits, alpha_bits, depth_bits);
}
