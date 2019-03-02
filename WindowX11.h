#ifndef __WINDOWX11_h__
#define __WINDOWX11_h__

#include <GL/glx.h>

#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>

#define USE_CHOOSE_FBCONFIG
class WindowX11{
public:
	WindowX11(){}
	~WindowX11(){}
	
	void createWindow();
	Bool WaitForMapNotify(Display *d, XEvent *e, char *arg);
	void fatalError(const char *why);
	void describe_fbconfig(GLXFBConfig fbconfig);
	
	//*****Getters*****//
	int getWidth(){return width;}
	int getHeight(){return height;}
	int getXscreen(){return Xscreen;}
	int getNumfbconfigs(){return numfbconfigs;}

	GLXContext getRenderContext(){return render_context;}
	Window getXroot(){return Xroot;}
	Window getWindowHandle(){return window_handle;}
	GLXWindow getGLXWindowHandle(){return glX_window_handle;}
	Atom getDelAtom(){return del_atom;}
	Colormap getCmap(){return cmap;}
	
	Display* getDisplay(){return display;}
	XRenderPictFormat* getPictFormat(){return pict_format;}
	GLXFBConfig* getFbconfigs(){return fbconfigs;}
	GLXFBConfig getFbconfig(){return fbconfig;}
	XVisualInfo* getVisual(){return visual;}
	int* getVisData(){return VisData;}
	//*****Getters*****//
	
	//*****Setters*****//
	void setWidth(int w){width = w;}
	void setHeight(int h){height = h;}
	void setXscreen(int screen){Xscreen = screen;}
	void setNumfbconfigs(int num){numfbconfigs = num;}
	
	void setRenderContext(GLXContext ctx){render_context = ctx;}
	void setXroot(Window w){Xroot = w;}
	void setWindowHandle(Window wh){window_handle = wh;}
	void setGLXWindowHandle(GLXWindow glxwh){glX_window_handle = glxwh;}
	void setDelAtom(Atom atom){del_atom = atom;}
	void setCmap(Colormap map){cmap = map;}
	
	void setXdisplay(Display* d){display = d;}
	void setPictFormat(XRenderPictFormat* format){pict_format = format;}
	void setFbconfigs(GLXFBConfig* fbconfs){fbconfigs = fbconfs;}
	void setFbconfig(GLXFBConfig fbconf){fbconfig=fbconf;}
	void setVisual(XVisualInfo* vis){visual = vis;}
	void setVisData(int *data){VisData[0] = data[0];}
	//*****Setters*****//
private:
	int width,height;
	int Xscreen;
	int numfbconfigs;
	
	GLXContext render_context;
	Window Xroot, window_handle;
	GLXWindow glX_window_handle;
	Atom del_atom;
	Colormap cmap;
	
	Display *display;
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

#endif
