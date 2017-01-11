////////////////////////////////////////////////////////////////////////////////////
#ifndef __ZVECTOR_HEADER
#define __ZVECTOR_HEADER
////////////////////////////////////////////////////////////////////////////////////
#include "zb_globals.h"
#include <math.h>

inline int irand() { return rand(); }
inline double drand() { return ((double)irand()) / (((double)RAND_MAX)+((double)1)); }
inline float frand() { return (float)drand(); }

inline float fscatter( float range ) // return [-0.5*range, 0.5*range)
{ return range*(frand()-0.5f); }

#define ZVECPRT(a)		a.x, a.y, a.z

template<typename T>
struct zbvec {
	union
	{
		struct { T x, y, z;	};
		struct { T radius, theta, pi; };
		T v[3];
	};

	//zbvec( T _x=(T)0, T _y=(T)0, T _z=(T)0 ) { x = _x; y = _y; z = _z; }
	zbvec() {}
	zbvec( T _x, T _y, T _z ) { x = _x; y = _y; z = _z; }
	zbvec( const zbvec &a ) { x = a.x; y = a.y; z = a.z; }

	__inline void zero() { x = y = z = (T)0; }
	
	inline zbvec operator+() const { return *this; }
	inline zbvec operator-() const { return zbvec( -x, -y, -z ); }

	inline zbvec operator +(const zbvec& a) const { return zbvec( x+a.x, y+a.y, z+a.z); }
	inline zbvec operator -(const zbvec& a) const { return zbvec( x-a.x, y-a.y, z-a.z); }
	inline zbvec operator *(const zbvec& b) const { return zbvec( y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x ); }
	inline zbvec operator *(const T a ) const { return zbvec( x*a, y*a, z*a ); }
	inline zbvec operator /(const T a ) const { T _a = ((T)1)/a; return zbvec( x*_a, y*_a, z*_a ); }

	inline void operator +=( const zbvec& a ) { x += a.x; y += a.y; z += a.z; }
	inline void operator -=( const zbvec& a ) { x -= a.x; y -= a.y; z -= a.z; }
	inline bool operator ==( const zbvec& a ) {
		if ( x != a.x ) return FALSE;
		if ( y != a.y ) return FALSE;
		if ( z != a.z ) return FALSE;
		return true;
	}
	inline bool operator !=( const zbvec& a ) {
		if ( x != a.x ) return TRUE;
		if ( y != a.y ) return TRUE;
		if ( z != a.z ) return TRUE;
		return false;
	}

	inline zbvec cross( const zbvec& b ) {
		return zbvec( y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x );
	}
	inline T dot( const zbvec &b ) const  {// added @ 20131021.1045, No
		return ( x*b.x + y*b.y + z*b.z );
	}

	inline T length_sqr() const { return ( x*x+y*y+z*z); }
	inline T length() const { return (T) sqrtf( length_sqr() ); }
	inline void make_unit( T *len = NULL ) {
		T l = length();
		if ( len ) *len = l;
		if ( l==(T)0 ) x=y=z=(T)0;
		else {
			x /= l;
			y /= l;
			z /= l;
		}
	}
	inline zbvec unit( T *len = NULL ) {
		T l = length();
		if ( len ) *len = l;
		if ( l==(T)0 ) return zbvec( (T)0, (T)0, (T)0 );
		return zbvec( x/l, y/l, z/l );
	}
	inline void lerp( const zbvec& a, const zbvec& b, float r ) {
		this = a*(1.0f-r) + b*r;
	}
	inline zbvec lerp( const zbvec& b, float r ) {
		return this*(1.0f-r) + b*r;
	}

	static inline zbvec get_max( const zbvec& a, const zbvec& b ) {
		return zbvec(
			a.x>b.x?a.x:b.x,
			a.y>b.y?a.y:b.y,
			a.z>b.z?a.z:b.z
			);
	}
	static inline zbvec get_min( const zbvec& a, const zbvec& b ) {
		return zbvec(
			a.x<b.x?a.x:b.x,
			a.y<b.y?a.y:b.y,
			a.z<b.z?a.z:b.z
			);
	}

	////// sphere coord
	inline zbvec crts2spr() { // cartesian -> sphere
		float r, theta, pi;
		r = (float)length();
		theta = r==0.0f?0.0f:acosf( ((float)z)/r ) * z180PI;
		pi = atan2f( (float)y, (float)x ) * z180PI;
		return zbvec( (T)r, (T)theta, (T)pi );
	}
	inline zbvec spr2crts() { // sphere -> cartesian
		float theta = y * zPI180;
		float pi = z * zPI180;

		return zbvec(
			(T) x*sinf(theta)*cosf(pi),
			(T) x*sinf(theta)*sinf(pi),
			(T) x*cosf(theta)
			);
	}

	////// util.
	inline zbvec scatter( float _x, float _y, float _z ) {
		return zbvec(
			x + fscatter( _x ),
			y + fscatter( _y ),
			z + fscatter( _z )
			);
	}
	inline zbvec scatter( zbvec &a ) { return scatter( a.x, a.y, a.z );	}

	////// misc.
	inline void print() { printf( "(%.4f,%.4f,%.4f)", x, y, z ); }
    
    ////// static
    
};
template<typename T> inline zbvec<T> operator* (const T f, const zbvec<T>& a ) { return zbvec<T>(f*a.x,f*a.y,f*a.z); }

typedef struct zbvec<float>		zvec;
typedef struct zbvec<int>		zvecx;
typedef struct zbvec<short>		zvecx16;

#define zvecFoward zvec(0, 0 ,1)
#define zvecUp zvec(0, 1 ,0)
static const zvec vecForward = zvecFoward;
static const zvec vecUp = zvecUp;

template<typename T>
struct zbvec2 {
	union
	{
		struct
		{
			T x, y;
		};
		T v[2];
	};

	//zbvec2() { x=0; y=0; }
	zbvec2() {}
	zbvec2( T _x, T _y ) { x = _x; y = _y; }
	zbvec2( const zbvec2 &a ) { x = a.x; y = a.y; }
	
	inline zbvec2 operator+() const { return *this; }
	inline zbvec2 operator-() const { return zbvec2( -x, -y ); }

	inline zbvec2 operator +(const zbvec2& a) { return zbvec2( x+a.x, y+a.y ); }
	inline zbvec2 operator -(const zbvec2& a) { return zbvec2( x-a.x, y-a.y ); }
	inline zbvec2 operator *(const T a ) { return zbvec2( x*a, y*a ); }
	inline zbvec2 operator /(const T a ) { T _a = ((T)1)/a; return zbvec2( x*_a, y*_a ); }

	inline void operator +=( const zbvec2& a ) { x += a.x; y += a.y; }
	inline void operator -=( const zbvec2& a ) { x -= a.x; y -= a.y; }
	inline void operator *=( const T a ) { x*=a; y*=a; }

	inline T dot( const zbvec2 &a ) { return ( x*a.x + y*a.y ); }

	inline T length_sqr() { return ( x*x + y*y ); }
	inline T length() { return (T) sqrtf( length_sqr() ); }
	inline zbvec2 unit( T *len = NULL ) { 
		T l = length();
		if ( len ) *len = l;
		if ( l==(T)0 ) return zbvec2( (T)0, (T)0 );
		return zbvec2( x/l, y/l );
	}

	inline void lerp( const zbvec2& a, const zbvec2& b, float r ) {
		x =	(T) ( ((float)a.x)*(1.0f-r) + ((float)b.x)*r );
		y = (T) ( ((float)a.y)*(1.0f-r) + ((float)b.y)*r );
	}
	inline zbvec2 lerp( const zbvec2& b, float r ) {
		return zbvec2(
			(T) ( ((float)x)*(1.0f-r) + ((float)b.x)*r ),
			(T) ( ((float)y)*(1.0f-r) + ((float)b.y)*r )
			);
	}

	////// misc.
	inline float get_degree() {	return atan2f( y, x )*z180PI;}
	inline void from_degree( float deg, float r=1.0f ) {
		float theta = deg * zPI180;
		x = (T) r*cosf( theta );
		y = (T) r*sinf( theta );
	}

	static inline zbvec2 get_max( const zbvec2& a, const zbvec2& b ) {
		return zbvec2(
			a.x>b.x?a.x:b.x,
			a.y>b.y?a.y:b.y
			);
	}
	static inline zbvec2 get_min( const zbvec2& a, const zbvec2& b ) {
		return zbvec2(
			a.x<b.x?a.x:b.x,
			a.y<b.y?a.y:b.y
			);
	}

	inline void print() { printf( "(%.4f,%.4f)", x, y ); }
};

template<typename T> inline zbvec2<T> operator* (const T f, const zbvec2<T>& a ) { return zbvec2<T>(f*a.x,f*a.y); }

typedef struct zbvec2<float>	zvec2;
typedef struct zbvec2<int>		zvec2x;
typedef struct zbvec2<short>	zvec2x16;
typedef struct zbvec2<unsigned short>	zvec2ux16;

template<typename T>
struct zbvec4 {
	union
	{
		struct
		{
			T x, y, z, w;
		};
		T v[4];
	};

	//zbvec4( T _x=(T)0, T _y=(T)0, T _z=(T)0, T _w=(T)0 ) { x = _x; y = _y; z = _z; w = _w; }
	zbvec4() {}
	zbvec4( T _x, T _y, T _z, T _w ) { x = _x; y = _y; z = _z; w = _w; }
	zbvec4( const zbvec4 &a ) { x = a.x; y = a.y; z = a.z; w = a.w; }

	inline T dot( const zvec &b ) {// added @ 20131021.1045, No
		return ( x*b.x + y*b.y + z*b.z );
	}
	//////////////////////////////////////////////////////////////////
	////// quarternion
	__inline void qn_slerp( zbvec4 &from, zbvec4 &to, T t ) {
		float to1[4];
		float omega, cosom, sinom, scale0, scale1;
		float DELTA = 0.000001f;
		cosom = from.x*to.x + from.y*to.y + from.z*to.z + from.w*to.w;
		////// adjusts signs( pos/neg )
		if ( cosom<0.0f ) {
			cosom = -cosom;
			to1[0] = -to.x;
			to1[1] = -to.y;
			to1[2] = -to.z;
			to1[3] = -to.w;
		} else {
			to1[0] = to.x;
			to1[1] = to.y;
			to1[2] = to.z;
			to1[3] = to.w;
		}

		////// calc. coeff.
		if ( (1.0f-cosom)>DELTA ) {
			omega = (float) acos(cosom);
			sinom = (float) sin(omega);
			scale0 = (float) ( sin((1.0-t)*omega) / sinom );
			scale1 = (float) ( sin(t*omega) / sinom );
		} else {
			scale0 = 1.0f - t;
			scale1 = t;
		}

		x = scale0 * from.x + scale1 * to1[0];
		y = scale0 * from.y + scale1 * to1[1];
		z = scale0 * from.z + scale1 * to1[2];
		w = scale0 * from.w + scale1 * to1[3];
	}
};

typedef struct zbvec4<float>	zvec4;
typedef struct zbvec4<short>	zvec4x16;
typedef struct zbvec4<unsigned short>	zvec4ux16;
typedef struct zbvec4<char>		zvec4x8;

template<typename T>
struct zbrect {
	zbrect() { st.x = st.y = ed.x = ed.y = (T)0; }
	zbrect( T sx, T sy, T ex, T ey ) { st.x = sx; st.y = sy; ed.x = ex; ed.y = ey; }

	zbvec2<T> st, ed;

	int is_in( T x, T y ) {
		if ( x<st.x ) return 0;
		if ( y<st.y ) return 0;
		if ( x>ed.x ) return 0;
		if ( y>ed.y ) return 0;
		return 1;
	}

	void move_offset( T dx, T dy ) {
		st.x += dx;
		ed.x += dx;
		st.y += dy;
		ed.y += dy;
	}

	void set_offset( T x, T y ) {
		zbvec2<T> cnt = GetCenter();
		cnt = zbvec2<T>(x,y) - cnt;
		move_offset( cnt.x, cnt.y );
	}

	void set_size( T w, T h ) {
		zbvec2<T> cnt = GetCenter();
		st.x = cnt.x - w*0.5f;
		ed.x = st.x + w;
		st.y = cnt.y - h*0.5f;
		ed.y = st.y + h;
	}

	inline T GetWidth() { return ( ed.x - st.x + 1); }
	inline T GetHeight() { return ( ed.y - st.y + 1); }
	zbvec2<T> GetCenter() { return zbvec2<T>( (T)((st.x+ed.x)*0.5f),(T)((st.y+ed.y)*0.5f) ); }
#ifdef __ZB_MFC
	void draw() {
		glBegin( GL_LINES );
			glVertex3f( st.x, st.y, 0.0f );
			glVertex3f( ed.x, st.y, 0.0f );
			glVertex3f( st.x, st.y, 0.0f );
			glVertex3f( st.x, ed.y, 0.0f );

			glVertex3f( ed.x, ed.y, 0.0f );
			glVertex3f( st.x, ed.y, 0.0f );
			glVertex3f( ed.x, ed.y, 0.0f );
			glVertex3f( ed.x, st.y, 0.0f );
		glEnd();
	}

	void fill() {
		glBegin( GL_TRIANGLE_STRIP );
			glVertex3f( st.x, st.y, 0.0f );
			glVertex3f( ed.x, st.y, 0.0f );
			glVertex3f( st.x, ed.y, 0.0f );
			glVertex3f( ed.x, ed.y, 0.0f );
		glEnd();
	}
#endif
};

typedef struct zbrect<float>			zrect;
typedef struct zbrect<int>				zrectx;
typedef struct zbrect<unsigned short>	zrectux16;

struct zaabb {
	zvec st, ed;
};
struct zaabbx {
	zvecx st, ed;
};

template<typename T>
struct zbobb {
	zbvec2<T> axis[2];
	zbvec2<T> pos;
	zbvec2<T> edge[4];
	float w, h;

	zbobb() {}
	zbobb( zbvec2<T> &_pos, float deg, float _w, float _h ) {
		axis[0].from_degree( deg, 1.0f );
		axis[1].from_degree( deg+90.0f, 1.0f );
		pos = _pos;
		w = _w;
		h = _h;

		get_edge();
	}

	void center_bottom( zbvec2<T> &_pos, float deg, float _w, float _h ) {
		axis[0].from_degree( deg, 1.0f );
		axis[1].from_degree( deg+90.0f, 1.0f );
		pos = _pos + axis[0]*((T)(_w*0.5f));
		w = _w;
		h = _h;

		get_edge();
	}

	void get_edge() {
		zbvec2<T> x = axis[0] * ((T) w * 0.5f );
		zbvec2<T> y = axis[1] * ((T) h * 0.5f );
		edge[0] = pos - x - y;
		edge[1] = pos + x - y;
		edge[2] = pos + x + y;
		edge[3] = pos - x + y;
	}

	int test_aabb_intersection( zbrect<T> &rt ) {
		T min, max;

		////// aabb dominated test
		// x
		min = edge[0].x;
		max = edge[0].x;
		for (int i=1;i<4;i++) {
			if ( edge[i].x<min ) min = edge[i].x;
			else if ( edge[i].x>max ) max = edge[i].x;
		}
		if ( rt.ed.x<min ) return 0;
		if ( rt.st.x>max ) return 0;

		// y
		min = edge[0].y;
		max = edge[0].y;
		for (int i=1;i<4;i++) {
			if ( edge[i].y<min ) min = edge[i].y;
			else if ( edge[i].y>max ) max = edge[i].y;
		}
		if ( rt.ed.y<min ) return 0;
		if ( rt.st.y>max ) return 0;

		////// obb dominated test
		// stx, sty / stx, edy / edx, edy / edx, sty
		zbvec2<T> ab_edge[4];
		ab_edge[0] = rt.st - pos;
		ab_edge[3] = rt.ed - pos;
		ab_edge[1] = zbvec2<T>( ab_edge[0].x, ab_edge[3].y );
		ab_edge[2] = zbvec2<T>( ab_edge[3].x, ab_edge[0].y );
		// axis[0]
		min = axis[0].dot( ab_edge[0] );
		max = min;
		for (int i=1;i<4;i++) {
			float dt = axis[0].dot( ab_edge[i] );
			if ( dt<min ) min = dt;
			else if ( dt>max ) max = dt;
		}
		if ( max<(-w*0.5f) ) return 0;
		if ( min>(w*0.5f) ) return 0;

		// axis[1]
		min = axis[1].dot( ab_edge[0] );
		max = min;
		for (int i=1;i<4;i++) {
			float dt = axis[1].dot( ab_edge[i] );
			if ( dt<min ) min = dt;
			else if ( dt>max ) max = dt;
		}
		if ( max<(-h*0.5f) ) return 0;
		if ( min>(h*0.5f) ) return 0;
		return 1;
	}

#ifdef __ZB_MFC
	void draw() {
		glBegin( GL_LINES );
			glVertex2fv( edge[0].v );
			glVertex2fv( edge[1].v );
			glVertex2fv( edge[1].v );
			glVertex2fv( edge[2].v );
			glVertex2fv( edge[2].v );
			glVertex2fv( edge[3].v );
			glVertex2fv( edge[3].v );
			glVertex2fv( edge[0].v );
		glEnd();
	}
#endif
};

typedef struct zbobb<float>		zobb;

/*
struct zmat2 {
	float m[4];
	zmat2() {
		m[0] = m[3] = 1.0f;
		m[1] = m[2] = 0.0f;
	};
	~zmat2() {
	}
};

struct ztm2 {
	union {
		struct {
			zmat2 mat;
			zvec2 ofst;
		};
		float v[6];
	};

	ztm2() {
		ofst.x = ofst.y = 0.0f;
	}
	~ztm2() {
	}
};
*/

int zmat44Invert( float *m, float *invOut );
zvec zmat44MultVec3( float *mat, zvec &in );
zvec zmat44MultVec3( float *mat, float x, float y, float z );
zvec2 zmat44MultVec2( float *mat, zvec2 &in );
zvec2 zmat44MultVec2( float *mat, float x, float y );
void ztmMult( float *p, const float *a, const float *b );
void ztmMult2( float *p, const float *a, const float *b );
zvec2 ztmDotVec( float *tm, zvec2 &in );
zvec2 ztmDotVec( float *tm, float x, float y );

__inline zvec zmat44MultVec3( float *mat, zvec &a )
{
	zvec ret;
	float *out = (float*)ret.v;
	float *m = mat;
	out[0] = m[0]*a.x + m[4]*a.y + m[8]*a.z + m[12];
	out[1] = m[1]*a.x + m[5]*a.y + m[9]*a.z + m[13];
	out[2] = m[2]*a.x + m[6]*a.y + m[10]*a.z + m[14];

	return ret;
}


// added @ 20131021.1045, No
__inline zvec zvGetNormal( zvec& a, zvec& b, zvec& c ){return (b-a).cross(c-a) ;}
__inline zvec zvGetUnitNormal( zvec& a, zvec& b, zvec& c ){	return ( zvGetNormal( a, b, c ).unit(0) );}


void zvFromToRotation44( zvec *from, zvec *to, float *mat );


////////////////////////////////////////////////////////////////////////////////////
// Quarternion
////////////////////////////////////////////////////////////////////////////////////
void zqnSlerp( zvec4 *from, zvec4 *to, float t, zvec4 *res );

////////////////////////////////////////////////////////////////////////////////////
#endif //__ZVECTOR_HEADER
////////////////////////////////////////////////////////////////////////////////////

