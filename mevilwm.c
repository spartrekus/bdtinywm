
// features border with "D" and "0" keys
// few other features
// Win4 C to activate a new console
// Win4 W Close Window 
// (fork of tinywm 1.3)

#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // system
#include <unistd.h>
#include <dirent.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 	0xd75c, 0xd75c, 0xd75c,		  /* 0. light gray */
// 	0xbefb, 0xbaea, 0xbefb,		  /* 1. mid gray */
// 	0xaefb, 0xaaea, 0xaefb,		  /* 2. dark gray */
// 	0xefbe, 0xefbe, 0xefbe,		  /* 3. white */
// 	0x8617, 0x8207, 0x8617,		  /* 4. darkest gray */

int main( int argc, char *argv[])
{
	chdir( getenv( "HOME" ));
	char cwd[4096];
	printf( "Current path is %s\n", getcwd( cwd, 4096 ));

	Display * dpy;
	Window root;
	XWindowAttributes attr;
	XButtonEvent start;
	XEvent ev;

	if(!(dpy = XOpenDisplay(0x0))) 
		return 1;

	root = DefaultRootWindow(dpy);

	XGrabButton( dpy, 1, Mod1Mask, root, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton( dpy, 3, Mod1Mask, root, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None);

	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("F1")), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("h")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("j")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("k")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("l")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("i")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("d")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("o")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("r")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("0")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("c")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("w")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync); 
	XGrabKey( dpy, XKeysymToKeycode( dpy, XStringToKeysym("5")),  Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);

	int foox, fooy;

	printf( "For...\n");
	for(;;)
	{

		XNextEvent( dpy, &ev);

		if ( ev.xkey.subwindow != None)
			printf( "> Subwindow: %d\n", ev.xkey.subwindow );

		if ( ev.type == KeyPress && ev.xkey.subwindow != None)
		{   
			printf( "Subwindow: %d\n", ev.xkey.subwindow );
			printf( "Keycode:   %d\n", ev.xkey.keycode );
			if ( ev.xkey.keycode == 31 ) 
			{
				printf( "key pressed %d\n" , ev.xkey.keycode ); 
				printf( "Subwindow: %d\n", ev.xkey.subwindow );
				printf( "> Subwindow: %d\n", ev.xkey.subwindow );
				printf( "> Window: %d\n", ev.xmotion.window );
				printf( "> Root: %d\n", ev.xmotion.root );
			}

			else if ( ( ev.xkey.keycode >= 43 ) && ( ev.xkey.keycode <= 46 ) )
			{
				XGetWindowAttributes( dpy, ev.xkey.subwindow, &attr );
				foox = 0 ; fooy = 0;  
				if ( ev.xkey.keycode == 43 ) foox = -20 ;
				if ( ev.xkey.keycode == 44 ) fooy = 20 ;
				if ( ev.xkey.keycode == 45 ) fooy = -20 ;
				if ( ev.xkey.keycode == 46 ) foox = 20 ;
				XMoveWindow( dpy, ev.xkey.subwindow , attr.x + foox , attr.y + fooy );
			}

			else if ( ev.xkey.keycode == 27 ) 
			{
				printf( "> Subwindow: %d\n", ev.xkey.subwindow );
				system(  " cd ; fxrun 2>/dev/null &   " ); 
			}

			else if ( ev.xkey.keycode == 25 ) 
			{
				printf( "> Subwindow: %d\n", ev.xkey.subwindow );
				XDestroyWindow( dpy, ev.xkey.subwindow );
			}

			else if ( ev.xkey.keycode == 32 ) 
			{
				printf( "> Subwindow: %d\n", ev.xkey.subwindow );
				system(  " cd ; cd lectures ; rox  2>/dev/null &   " ); 
			}

			else if ( ev.xkey.keycode == 40 ) 
			{
				printf( "D-key\n" );
				XSetWindowBorderWidth(     dpy, ev.xkey.subwindow , 20 );
				XSetWindowBorder(          dpy, ev.xkey.subwindow , 0x8617 );
			}
			else if ( ev.xkey.keycode == 19 ) 
			{
				printf( "0-key\n" );
				XSetWindowBorderWidth(     dpy, ev.xkey.subwindow , 0 );
				XSetWindowBorder(          dpy, ev.xkey.subwindow , 0x8617 );
			}

			else if ( ev.xkey.keycode == 54 ) 
			{
				printf( "key pressed %d\n" , ev.xkey.keycode ); 
				system ( " cd ; screen -d -m xterm -fs 15 -fa 15 -bg black -fg yellow " );
			}

			else
			{
				printf( "XRaiseWindow\n" );
				XRaiseWindow(dpy, ev.xkey.subwindow);
			}
		}


		else if( ev.type == ButtonPress && ev.xbutton.subwindow != None)
		{
			printf( "XGrabPointer\n" );
			XGrabPointer(dpy, ev.xbutton.subwindow, True, PointerMotionMask|ButtonReleaseMask, GrabModeAsync,
					GrabModeAsync, None, None, CurrentTime);
			XGetWindowAttributes( dpy, ev.xbutton.subwindow, &attr );
			start = ev.xbutton;
		}


		else if ( ev.type == MotionNotify )
		{
			printf( "MotionNotify\n" );
			int xdiff, ydiff;

			while( XCheckTypedEvent( dpy, MotionNotify, &ev));

			xdiff = ev.xbutton.x_root - start.x_root;
			ydiff = ev.xbutton.y_root - start.y_root;
			XRaiseWindow(dpy, ev.xmotion.window);
			printf( "StarButton %d\n", start.button );


			if (  start.button == 1 )
			{
				printf( "XMoveWindow\n" );
				XRaiseWindow( dpy , ev.xmotion.window );
				XMoveWindow( dpy, ev.xmotion.window , attr.x + xdiff , attr.y + ydiff  );
				XSetInputFocus( dpy , ev.xmotion.window, RevertToNone , CurrentTime );
			}

			else 
			{
				XMoveResizeWindow( dpy, ev.xmotion.window,
						attr.x + ( start.button==1 ? xdiff : 0),
						attr.y + ( start.button==1 ? ydiff : 0),
						MAX(1, attr.width +  ( start.button==3 ? xdiff : 0)),
						MAX(1, attr.height + ( start.button==3 ? ydiff : 0)));
			}

		}

		else if(ev.type == ButtonRelease)
		{
			printf( "Un-XGrabPointer\n" );
			XUngrabPointer( dpy, CurrentTime);
		}

	}
}




