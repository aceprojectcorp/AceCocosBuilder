#include "ZVector.h"

/*
zvec zmat44MultVec3( float *mat, zvec &in )
{
	zvec ret;
	float *v = (float*)in.v, *out = (float*)ret.v;
	float *m = mat;
	out[0] = m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12];
	out[1] = m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13];
	out[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14];

	return ret;
}
*/


int zmat44Invert( float *m, float *invOut )
{ 
	float inv[16], det; 
	int i;  
	inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10]; 
	inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10]; 
	inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9]; 
	inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9]; 

	det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12]; 
	if (det == 0.0f) return 0;  

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
	for (i = 0; i < 16; i++) invOut[i] = inv[i] * det;  
	return 1;
}


int zmat33InvertFromMat44( float *m, float *invOut )
{ 
	float inv[9], det; 
	int i;  
	inv[0] =   m[5]*m[10]*1.0f - m[5]*0.0f*0.0f - m[9]*m[6]*1.0f + m[9]*0.0f*0.0f + 0.0f*m[6]*0.0f - 0.0f*0.0f*m[10]; 
	inv[3] =  -m[4]*m[10]*1.0f + m[4]*0.0f*0.0f + m[8]*m[6]*1.0f - m[8]*0.0f*0.0f - 0.0f*m[6]*0.0f + 0.0f*0.0f*m[10]; 
	inv[6] =   m[4]*m[9]*1.0f - m[4]*0.0f*0.0f - m[8]*m[5]*1.0f + m[8]*0.0f*0.0f + 0.0f*m[5]*0.0f - 0.0f*0.0f*m[9]; 
	//inv[12] = -m[4]*m[9]*0.0f + m[4]*m[10]*0.0f + m[8]*m[5]*0.0f - m[8]*m[6]*0.0f - 0.0f*m[5]*m[10] + 0.0f*m[6]*m[9]; 

	det = m[0]*inv[0] + m[1]*inv[3] + m[2]*inv[6]; 
	if (det == 0.0f) return 0;  

	inv[1] =  -m[1]*m[10]*1.0f + m[1]*0.0f*0.0f + m[9]*m[2]*1.0f - m[9]*0.0f*0.0f - 0.0f*m[2]*0.0f + 0.0f*0.0f*m[10]; 
	inv[4] =   m[0]*m[10]*1.0f - m[0]*0.0f*0.0f - m[8]*m[2]*1.0f + m[8]*0.0f*0.0f + 0.0f*m[2]*0.0f - 0.0f*0.0f*m[10]; 
	inv[7] =  -m[0]*m[9]*1.0f + m[0]*0.0f*0.0f + m[8]*m[1]*1.0f - m[8]*0.0f*0.0f - 0.0f*m[1]*0.0f + 0.0f*0.0f*m[9]; 

	inv[2] =   m[1]*m[6]*1.0f - m[1]*0.0f*0.0f - m[5]*m[2]*1.0f + m[5]*0.0f*0.0f + 0.0f*m[2]*0.0f - 0.0f*0.0f*m[6];
	inv[5] =  -m[0]*m[6]*1.0f + m[0]*0.0f*0.0f + m[4]*m[2]*1.0f - m[4]*0.0f*0.0f - 0.0f*m[2]*0.0f + 0.0f*0.0f*m[6]; 
	inv[8] =  m[0]*m[5]*1.0f - m[0]*0.0f*0.0f - m[4]*m[1]*1.0f + m[4]*0.0f*0.0f + 0.0f*m[1]*0.0f - 0.0f*0.0f*m[5]; 

	
	det = 1.0f / det;  
	for (i = 0; i < 9; i++) invOut[i] = inv[i] * det;  
	return 1;
}

void zmat33Invert( float *in, float *out )
{
#define A(row,col)	in[col+row*3]
#define result(row,col)	out[col+row*3]
	float determinant =    +A(0,0)*(A(1,1)*A(2,2)-A(2,1)*A(1,2))
                        -A(0,1)*(A(1,0)*A(2,2)-A(1,2)*A(2,0))
                        +A(0,2)*(A(1,0)*A(2,1)-A(1,1)*A(2,0));
	float invdet = 1/determinant;
	//printf( " det=%f / %f\n", determinant, invdet );
	result(0,0) =  (A(1,1)*A(2,2)-A(2,1)*A(1,2))*invdet;
	result(1,0) = -(A(0,1)*A(2,2)-A(0,2)*A(2,1))*invdet;
	result(2,0) =  (A(0,1)*A(1,2)-A(0,2)*A(1,1))*invdet;
	result(0,1) = -(A(1,0)*A(2,2)-A(1,2)*A(2,0))*invdet;
	result(1,1) =  (A(0,0)*A(2,2)-A(0,2)*A(2,0))*invdet;
	result(2,1) = -(A(0,0)*A(1,2)-A(1,0)*A(0,2))*invdet;
	result(0,2) =  (A(1,0)*A(2,1)-A(2,0)*A(1,1))*invdet;
	result(1,2) = -(A(0,0)*A(2,1)-A(2,0)*A(0,1))*invdet;
	result(2,2) =  (A(0,0)*A(1,1)-A(1,0)*A(0,1))*invdet;

	//printf( " %f\n", result(0,0) );
#undef result
#undef A
}

zvec zmat44MultVec3( float *mat, float x, float y, float z )
{
	zvec ret;
	float *out = (float*)ret.v;
	float *m = mat;
	out[0] = m[0]*x + m[4]*y + m[8]*z + m[12];
	out[1] = m[1]*x + m[5]*y + m[9]*z + m[13];
	out[2] = m[2]*x + m[6]*y + m[10]*z + m[14];

	return ret;
}


zvec2 zmat44MultVec2( float *mat, zvec2 &in )
{
	zvec2 ret;
	float *v = (float*)in.v, *out = (float*)ret.v;
	float *m = mat;
	out[0] = m[0]*v[0] + m[4]*v[1] + m[12];
	out[1] = m[1]*v[0] + m[5]*v[1] + m[13];

	return ret;
}

zvec2 zmat44MultVec2( float *mat, float x, float y )
{
	zvec2 ret;
	float *out = (float*)ret.v;
	float *m = mat;
	out[0] = m[0]*x + m[4]*y + m[12];
	out[1] = m[1]*x + m[5]*y + m[13];

	return ret;
}

void ztmMult( float *p, const float *a, const float *b )
{// float[6] : a = a * b
	const float a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
	p[0] = a0*b[0] + a2*b[1];
	p[1] = a1*b[0] + a3*b[1];
	p[2] = a0*b[2] + a2*b[3];
	p[3] = a1*b[2] + a3*b[3];
	p[4] = a0*b[4] + a2*b[5] + a[4];
	p[5] = a1*b[4] + a3*b[5] + a[5];
}

void ztmMult2( float *p, const float *a, const float *b )
{// float[6] : b = a * b
	float bb = b[0];
	p[0] = a[0]*bb + a[2]*b[1];
	p[1] = a[1]*bb + a[3]*b[1];
	bb = b[2];
	p[2] = a[0]*bb + a[2]*b[3];
	p[3] = a[1]*bb + a[3]*b[3];
	bb = b[4];
	p[4] = a[0]*bb + a[2]*b[5] + a[4];
	p[5] = a[1]*bb + a[3]*b[5] + a[5];
}

/**
void ztmMult2( float *p, const float *a, const float *b )
{// float[6] : b = a * b
	float bb = b[0];
	p[0] = a[0]*b[0] + a[2]*b[1];
	p[1] = a[1]*b[0] + a[3]*b[1];
	p[2] = a[0]*b[2] + a[2]*b[3];
	p[3] = a[1]*b[2] + a[3]*b[3];
	p[4] = a[0]*b[4] + a[2]*b[5] + a[4];
	p[5] = a[1]*b[4] + a[3]*b[5] + a[5];
}
*/

zvec2 ztmDotVec( float *tm, zvec2 &in )
{
	return zvec2(
		tm[0]*in.x + tm[2]*in.y + tm[4],
		tm[1]*in.x + tm[3]*in.y + tm[5]
		);
}

zvec2 ztmDotVec( float *tm, float x, float y )
{
	return zvec2(
		tm[0]*x + tm[2]*y + tm[4],
		tm[1]*x + tm[3]*y + tm[5]
		);
}



////////////////////////////////////////////////////////////////////////////////////
void zqnSlerp( zvec4 *from, zvec4 *to, float t, zvec4 *res )
////////////////////////////////////////////////////////////////////////////////////
{
	float to1[4];
	float omega, cosom, sinom, scale0, scale1;
	float DELTA = 0.000001f;
	cosom = from->x*to->x + from->y*to->y + from->z*to->z + from->w*to->w;
	////// adjusts signs( pos/neg )
	if ( cosom<0.0f ) {
		cosom = -cosom;
		to1[0] = -to->x;
		to1[1] = -to->y;
		to1[2] = -to->z;
		to1[3] = -to->w;
	} else {
		to1[0] = to->x;
		to1[1] = to->y;
		to1[2] = to->z;
		to1[3] = to->w;
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

	res->x = scale0 * from->x + scale1 * to1[0];
	res->y = scale0 * from->y + scale1 * to1[1];
	res->z = scale0 * from->z + scale1 * to1[2];
	res->w = scale0 * from->w + scale1 * to1[3];
}


#define EPSILON	0.000001
////////////////////////////////////////////////////////////////////////////////////
void zvFromToRotation44( zvec *from, zvec *to, float *mat )
////////////////////////////////////////////////////////////////////////////////////
{// mat: 3*3, from/to : unit non-zero vector
	zvec v;
	float e, h, f;

	v = from->cross(*to); //zvcross( *from, *to );
	e = from->dot(*to);   //zvdot( *from, *to );
	f = (e<0)? - e:e;
	if ( f>1.0-EPSILON ) 
	{
		zvec u, v, x;
		float c1, c2, c3;
		int i, j;
		x.x = from->x>0.0f?from->x:-from->x;
		x.y = from->y>0.0f?from->y:-from->y;
		x.z = from->z>0.0f?from->z:-from->z;

		if ( x.x<x.y ) {
			if ( x.x<x.z ) { x.x = 1.0f; x.y = x.z = 0.0f; } 
			else { x.z = 1.0f; x.x = x.y = 0.0f; }
		} else {
			if ( x.y<x.z ) { x.y = 1.0f; x.x = x.z = 0.0f; } 
			else { x.z = 1.0f; x.x = x.y = 0.0f; }
		}

		u = x - *from; //zvsub( x, *from );
		v = x - *to;   //zvsub( x, *to );

		c1 = 2.0f/ u.dot(u); //2.0f / zvdot( u, u );
		c2 = 2.0f/ v.dot(v); //2.0f / zvdot( v, v );
		c3 = c1 * c2 * u.dot(v); //c1 * c2 * zvdot( u, v );

		for (i=0;i<3;i++) 
		{
			for (j=0;j<3;j++) 
			{
				mat[ j + i*4 ] = -c1 * ((float*)&u)[i] * ((float*)&u)[j] 
					- c2 * ((float*)&v)[i] * ((float*)&v)[j]
					+ c3 * ((float*)&v)[i] * ((float*)&u)[j];
			}
			mat[ i + i*4 ] += 1.0f;
			mat[ 3 + i*4 ] = 0.0f;
		}
		mat[ 0 + 3*4 ] = 0.0f;
		mat[ 1 + 3*4 ] = 0.0f;
		mat[ 2 + 3*4 ] = 0.0f;
		mat[ 3 + 3*4 ] = 1.0f;
	} else {
		float hvx, hvz, hvxy, hvxz, hvyz;
		h = 1.0f / ( 1.0f + e );
		hvx = h * v.x;
		hvz = h * v.z;
		hvxy = hvx * v.y;
		hvxz = hvx * v.z;
		hvyz = hvz * v.y;

		mat[0+0]	= e + hvx * v.x;
        mat[0+1]	= hvxy - v.z;
        mat[0+2]	= hvxz + v.y; 
		mat[0+3]	= 0.0f;

        mat[1*4+0]	= hvxy + v.z;
        mat[1*4+1]	= e + h * v.y * v.y;
        mat[1*4+2]	= hvyz - v.x;
		mat[1*4+3]	= 0.0f;

        mat[2*4+0]	= hvxz - v.y;
        mat[2*4+1]	= hvyz + v.x;
        mat[2*4+2]	= e + hvz * v.z;
		mat[2*4+3]	= 0.0f;

		mat[3*4+0] = 0.0f;
		mat[3*4+1] = 0.0f;
		mat[3*4+2] = 0.0f;
		mat[3*4+3] = 1.0f;
	}
}
#undef EPSILON
