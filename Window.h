#include <GL/glx.h>

#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>

class WindowX11{
public:
	WindowX11(){}
	~WindowX11(){}
private:
	int width,height;
	
	int Xscreen;
	int numfbconfigs;
	GLXContext render_context;
	Window Xroot, window_handle;
	GLXWindow glX_window_handle;
	Atom del_atom;
	Colormap cmap;
	
	Display *Xdisplay;
	XRenderPictFormat *pict_format;
	GLXFBConfig *fbconfigs, fbconfig;
	XVisualInfo *visual;
	
	int VisData[17] = {
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_DOUBLEBUFFER, True,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 16,
		None
	};
};
