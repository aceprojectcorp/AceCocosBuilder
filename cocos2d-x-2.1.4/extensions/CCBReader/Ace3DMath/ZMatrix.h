////////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////////
#include "ZVector.h"
////////////////////////////////////////////////////////////////////////////////////

struct zmat4 {
	/*
	union
	{
		struct { zvec4 zv[4]; };
		float v[16];
	};
	*/
	float v[16];

	zmat4() {};
	zmat4( float *p_mat ) { memcpy( v, p_mat, sizeof(float)*16 ); }
    zmat4( float deg, zvec vec )
    {
        identity();
        rotate(deg, vec.x, vec.y, vec.z);
    }
	//zmat4( zvec4 *zvc ) { zv[0] = zvc[0];zv[1] = zvc[1];zv[2] = zvc[2];zv[3] = zvc[3];	}

	__inline void identity() {
		memset( v, 0, sizeof(float)*16 );
		v[0] = v[5] = v[10] = v[15] = 1.0f;
	}

	__inline zmat4 operator+() const { return *this; }
	__inline zmat4 operator-() const { 
		zmat4 ret;
		for (int i=0;i<16;i++) ret.v[i] = -this->v[i];
		return ret;
	}
	__inline zmat4 operator +(const zmat4& a) const {
		zmat4 ret;
		for (int i=0;i<16;i++) ret.v[i] = v[i]+a.v[i];
		return ret;
	}
	__inline zmat4 operator -(const zmat4& a) const {
		zmat4 ret;
		for (int i=0;i<16;i++) ret.v[i] = v[i]-a.v[i];
		return ret;
	}
	__inline zmat4 operator *(const float a) const {
		zmat4 ret;
		for (int i=0;i<16;i++) ret.v[i] = v[i]*a;
		return ret;
	}
	__inline zmat4 operator /(const float a) const {
		zmat4 ret;
		for (int i=0;i<16;i++) ret.v[i] = v[i]/a;
		return ret;
	}
	__inline zvec4 operator *(const zvec4& a ) const {
		zvec4 ret;
		float *out = (float*)ret.v;
		float *m = (float*)v;
		out[0] = m[0]*a.x + m[4]*a.y + m[8]*a.z + m[12]*a.w;
		out[1] = m[1]*a.x + m[5]*a.y + m[9]*a.z + m[13]*a.w;
		out[2] = m[2]*a.x + m[6]*a.y + m[10]*a.z + m[14]*a.w;
		out[3] = m[3]*a.x + m[7]*a.y + m[11]*a.z + m[15]*a.w;
		return ret;
	}
	__inline zvec operator *(const zvec& a ) const {
		zvec ret;
		float *out = (float*)ret.v;
		float *m = (float*)v;
		out[0] = m[0]*a.x + m[4]*a.y + m[8]*a.z + m[12];
		out[1] = m[1]*a.x + m[5]*a.y + m[9]*a.z + m[13];
		out[2] = m[2]*a.x + m[6]*a.y + m[10]*a.z + m[14];
		return ret;
	}

	__inline zvec multRS(const zvec& a ) const {
		zvec ret;
		float *out = (float*)ret.v;
		float *m = (float*)v;
		out[0] = m[0]*a.x + m[4]*a.y + m[8]*a.z;
		out[1] = m[1]*a.x + m[5]*a.y + m[9]*a.z;
		out[2] = m[2]*a.x + m[6]*a.y + m[10]*a.z;
		return ret;
	}

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]
	__inline zmat4 operator *(const zmat4& _b ) const {
		zmat4 ret;
		float *product = ret.v;
		const float *a = this->v;
		const float *b = _b.v;

		for (int i = 0; i < 4; i++) {
			const float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
			P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
			P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
			P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
			P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
		}
		return ret;
	}
	__inline void operator *=( /*const*/ zmat4& _b ) {
		float *product = v;
		float *a = v;
		const float *b = _b.v;
		for (int i = 0; i < 4; i++) {
			const float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
			P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
			P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
			P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
			P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
		}
	}
#undef A
#undef B
#undef P
	zmat4 inverse() {
		zmat4 ret;
		float inv[16];
		float *m = this->v;
		float det; 
		int i;  
		inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10]; 
		inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10]; 
		inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9]; 
		inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9]; 

		det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12]; 
		if (det == 0.0f) {
			ret = zmat4( (float*)this );
			return ret;
		}

		inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10]; 
		inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10]; 
		inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9]; 
		inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9]; 
		inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
		inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6]; 
		inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5]; 
		inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5]; 
		inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6]; 
		inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6]; 
		inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11] - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5]; 
		inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10] + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5]; 

	
		det = 1.0f / det;  
		for (i = 0; i < 16; i++) ret.v[i] = inv[i] * det;  
		return ret;
	}

	// modelview related
	__inline zvec right() { return zvec( -v[4], -v[5], -v[6] ).unit(); }
	__inline zvec up() { return zvec( v[8], v[9], v[10] ).unit(); }
	__inline zvec forward() { return zvec( v[0], v[1], v[2] ).unit(); }
	__inline zvec position() { return zvec( v[12], v[13], v[14] ); }
	__inline void set_pos( float x, float y, float z ) {
		v[12] = x;
		v[13] = y;
		v[14] = z;
	}
	__inline void set_pos( zvec &pos ) { 
		v[12] = pos.x;
		v[13] = pos.y;
		v[14] = pos.z;
	}
	__inline void compose( zvec &up, zvec &fwd ) {
		////// camera side
		zvec left = fwd.cross( up );
		v[0] = fwd.x; v[1] = fwd.y; v[2] = fwd.z;
		v[8] = up.x; v[9] = up.y; v[10] = up.z;
		v[4] = left.x; v[5] = left.y; v[6] = left.z;
	}
	__inline void compose_TM( zvec &up, zvec &fwd ) {
		////// object side
		zvec left = up.cross( fwd );
		v[0] = fwd.x; v[1] = fwd.y; v[2] = fwd.z;
		v[8] = up.x; v[9] = up.y; v[10] = up.z;
		v[4] = left.x; v[5] = left.y; v[6] = left.z;
	}

	zmat4 billboard() {
		zmat4 ret;
		float *out = ret.v;
		out[0] = 1.0f;	out[1] = 0.0f;	out[2] = 0.0f;	
		out[4] = 0.0f;	out[5] = 1.0f;	out[6] = 0.0f;
		out[8] = 0.0f;	out[9] = 0.0f;	out[10] = 1.0f;
		out[3] = v[3];	out[7] = v[7];	out[11] = v[11];
		out[12] = v[12];	out[13] = v[13];	out[14] = v[14];
		out[15] = v[15];
		return ret;
	}

	// gl_ wrapper
	void frustum( float left, float right, float bottom, float top, float znear, float zfar )
	{
		float temp, temp2, temp3, temp4;
		temp = 2.0f * znear;
		temp2 = right - left;
		temp3 = top - bottom;
		temp4 = zfar - znear;
		v[0] = temp / temp2;
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = 0.0f;
		v[4] = 0.0f;
		v[5] = temp / temp3;
		v[6] = 0.0f;
		v[7] = 0.0f;
		v[8] = (right + left) / temp2;
		v[9] = (top + bottom) / temp3;
		v[10] = (-zfar - znear) / temp4;
		v[11] = -1.0f;
		v[12] = 0.0f;
		v[13] = 0.0f;
		v[14] = (-temp * zfar) / temp4;
		v[15] = 0.0f;
	}
	void perspective( float fovy, float aspectRatio, float znear, float zfar )
	{
		float ymax, xmax;
		ymax = znear * tanf(fovy * zPI / 360.0f);
		xmax = ymax * aspectRatio;
		frustum( -xmax, xmax, -ymax, ymax, znear, zfar);
	}
	void lookat( zvec &eye, zvec &center, zvec &up ) {
		lookat( 
			ZVECPRT(eye),
			ZVECPRT(center),
			ZVECPRT(up)
			);
	}
	void lookat( float eyex, float eyey, float eyez,
		float centerx, float centery, float centerz,
		float upx, float upy, float upz)
	{
		float *m = v;
		float x[3], y[3], z[3];
		float mag;
    
		/* Make rotation matrix */
    
		/* Z vector */
		z[0] = eyex - centerx;
		z[1] = eyey - centery;
		z[2] = eyez - centerz;
		mag = sqrtf(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
		if (mag) {          /* mpichler, 19950515 */
			z[0] /= mag;
			z[1] /= mag;
			z[2] /= mag;
		}
    
		/* Y vector */
		y[0] = upx;
		y[1] = upy;
		y[2] = upz;
    
		/* X vector = Y cross Z */
		x[0] = y[1] * z[2] - y[2] * z[1];
		x[1] = -y[0] * z[2] + y[2] * z[0];
		x[2] = y[0] * z[1] - y[1] * z[0];
    
		/* Recompute Y = Z cross X */
		y[0] = z[1] * x[2] - z[2] * x[1];
		y[1] = -z[0] * x[2] + z[2] * x[0];
		y[2] = z[0] * x[1] - z[1] * x[0];
    
		/* mpichler, 19950515 */
		/* cross product gives area of parallelogram, which is < 1.0 for
		 * non-perpendicular unit-length vectors; so normalize x, y here
		 */
    
		mag = (float)sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
		if (mag) {
			x[0] /= mag;
			x[1] /= mag;
			x[2] /= mag;
		}
    
		mag = (float)sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
		if (mag) {
			y[0] /= mag;
			y[1] /= mag;
			y[2] /= mag;
		}

#define M(row,col)  m[col*4+row]
		M(0, 0) = x[0];
		M(0, 1) = x[1];
		M(0, 2) = x[2];
		M(0, 3) = 0.0;
		M(1, 0) = y[0];
		M(1, 1) = y[1];
		M(1, 2) = y[2];
		M(1, 3) = 0.0;
		M(2, 0) = z[0];
		M(2, 1) = z[1];
		M(2, 2) = z[2];
		M(2, 3) = 0.0;
		M(3, 0) = 0.0;
		M(3, 1) = 0.0;
		M(3, 2) = 0.0;
		M(3, 3) = 1.0;
#undef M

		translate( -eyex, -eyey, -eyez );
	}
	__inline void translate( float x, float y, float z ) {
		float *m = v;
		m[12] = m[0] * x + m[4] * y + m[8]  * z + m[12];
		m[13] = m[1] * x + m[5] * y + m[9]  * z + m[13];
		m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
		m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
	}
	__inline void translate( zvec &t ) { translate( t.x, t.y, t.z ); }
	__inline void scale( float x, float y, float z ) {
		float *m = v;
		m[0] *= x;   m[4] *= y;   m[8]  *= z;
		m[1] *= x;   m[5] *= y;   m[9]  *= z;
		m[2] *= x;   m[6] *= y;   m[10] *= z;
		m[3] *= x;   m[7] *= y;   m[11] *= z;
	}
	__inline void scale( zvec &scl ) { scale( scl.x, scl.y, scl.z ); }
	__inline void scale( float scl ) { scale( scl, scl, scl ); }

    
    void rotateFromVec(float deg, zvec vec)
    {
        rotate(deg, vec.x, vec.y, vec.z );
    }
    
	void rotate( float deg, float x, float y, float z )
    {
		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;
		zmat4 rot;
		float *m = rot.v;
		int optimized;

		s =  sinf( deg * zPI180 );
		c =  cosf( deg * zPI180 );
        //s =  sinf( deg );
        //c =  cosf( deg );

		rot.identity();
		optimized = 0;

#define M(row,col)  m[col*4+row]

		if (x == 0.0F) {
			if (y == 0.0F) {
				if (z != 0.0F) {
				optimized = 1;
				/* rotate only around z-axis */
				M(0,0) = c;
				M(1,1) = c;
				if (z < 0.0F) {
					M(0,1) = s;
					M(1,0) = -s;
				}
				else {
					M(0,1) = -s;
					M(1,0) = s;
				}
				}
			}
			else if (z == 0.0F) {
				optimized = 1;
				/* rotate only around y-axis */
				M(0,0) = c;
				M(2,2) = c;
				if (y < 0.0F) {
				M(0,2) = -s;
				M(2,0) = s;
				}
				else {
				M(0,2) = s;
				M(2,0) = -s;
				}
			}
		}
		else if (y == 0.0F) {
			if (z == 0.0F) {
				optimized = 1;
				/* rotate only around x-axis */
				M(1,1) = c;
				M(2,2) = c;
				if (x < 0.0F) {
				M(1,2) = s;
				M(2,1) = -s;
				}
				else {
				M(1,2) = -s;
				M(2,1) = s;
				}
			}
		}

		if (!optimized) {
			const float mag = sqrtf(x * x + y * y + z * z);

			if (mag <= 1.0e-4) {
				/* no rotation, leave mat as-is */
				return;
			}

			x /= mag;
			y /= mag;
			z /= mag;

			xx = x * x;
			yy = y * y;
			zz = z * z;
			xy = x * y;
			yz = y * z;
			zx = z * x;
			xs = x * s;
			ys = y * s;
			zs = z * s;
			one_c = 1.0F - c;

			/* We already hold the identity-matrix so we can skip some statements */
			M(0,0) = (one_c * xx) + c;
			M(0,1) = (one_c * xy) - zs;
			M(0,2) = (one_c * zx) + ys;

			M(1,0) = (one_c * xy) + zs;
			M(1,1) = (one_c * yy) + c;
			M(1,2) = (one_c * yz) - xs;

			M(2,0) = (one_c * zx) - ys;
			M(2,1) = (one_c * yz) + xs;
			M(2,2) = (one_c * zz) + c;
		}
#undef M

		*this *= rot;
	}
};

////////////////////////////////////////////////////////////////////////////////////

