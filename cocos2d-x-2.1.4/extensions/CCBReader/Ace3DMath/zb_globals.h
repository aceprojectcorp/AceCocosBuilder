////////////////////////////////////////////////////////////////////////////////////
#ifndef __ZB_GLOBALS_HEADER
#define __ZB_GLOBALS_HEADER
////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
	#include <string>
	#include <vector>
	//#include <queue>
	//#include <hash_map>
	//#include <unordered_map>
	#include <algorithm>
#endif //__cplusplus

#ifdef _WINDOWS
	#ifdef __cplusplus
		#include <afxwin.h>         // MFC core and standard components
		#include <afxext.h>         // MFC extensions
		#include <afxdisp.h>        // MFC Automation classes
		#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
		#include <afxcmn.h>
		#include <afxsock.h>
	#endif //__cplusplus

	#include <gl/glew.h>
	#include <gl/gl.h>			// standard OpenGL include
	#include <gl/glext.h>
	#include <gl/wglext.h>
	#include <gl/glu.h>			// OpenGL Utilities
	#include <gl/GLAux.h>		// OpenGL Auxiliary

	#pragma comment(lib, "OpenGL32.Lib")
	#pragma comment(lib, "Glu32.lib")
	#pragma comment(lib, "GlAux.Lib")	// OpenGL Auxiliary Library
	#pragma comment(lib, "glew32.Lib")

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////
/**
* version definition
*/
#define __ZBTECH_VERSION		(0x320)
////////////////////////////////////////////////////////////////////////////////////
/**
* common definitions
*/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef long long s64;

#ifndef NULL
#define NULL	(0)
#endif

#ifndef TRUE
#define TRUE	(1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif

#ifndef BOOL
//typedef int BOOL;
#endif

#define __OFSTOF(type, field)    ((unsigned long) &(((type *) 0)->field))

#ifndef __INLINE
#ifdef _WINDOWS
	#define __INLINE	static __inline
#else
	#define	__INLINE	static __inline__
#endif
#endif

#define zcalloc( a, b )		calloc( a, b )
#define zalloc( a )			malloc( a )
#define __MEM_RELEASE( a )	{ if (a) free(a); a = NULL; }

#ifndef zPI
#define zPI			3.141592653589793238462643f
#endif
#ifndef zPI180
// ¥ð / 180
#define zPI180		0.0174532925199432957692369076848861f
#endif
#ifndef z180PI
// 180 / ¥ð
#define z180PI		57.295779513082320876798161804285f
#endif
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
#include "zb_debug.h"
////////////////////////////////////////////////////////////////////////////////////
#endif //__ZB_GLOBALS_HEADER
////////////////////////////////////////////////////////////////////////////////////

