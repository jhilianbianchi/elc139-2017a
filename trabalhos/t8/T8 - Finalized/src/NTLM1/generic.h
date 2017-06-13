/* 

generic.h


*/



/* 
Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
*/


#define SYMBOL "-"
#define YES "1"
#define NO "0"



/* 
Constants for MD4Transform routine.
 */

typedef	unsigned char	ord8;		/* 8  bit unsigned integer */
typedef	unsigned short	ord16;		/* 16 bit unsigned integer */
typedef	unsigned long	ord32;		/* 32 bit unsigned integer */
typedef	char		int8;		/* 8  bit signed integer */
typedef	short		int16;		/* 16 bit signed integer */
typedef	long		int32;		/* 32 bit signed integer */
typedef	ord8		octet;		/* CCITT name for a byte (8 bits) */

int gbl_stop;


#define S11 3
#define SS11 29
#define S12 7
#define SS12 25
#define S13 11
#define SS13 21
#define S14 19
#define SS14 13
#define S21 3
#define SS21 29
#define S22 5
#define SS22 27
#define S23 9
#define SS23 23
#define S24 13
#define SS24 19
#define S31 3
#define SS31 29
#define S32 9
#define SS32 23
#define S33 11
#define SS33 21
#define S34 15
#define SS34 17


/* 
F, G, H and I are basic MD4 functions.
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))




/*
 ROTATE_LEFT rotates x left n bits.
*/


#define NROTATE_LEFT(x, n, m) (((x) << (n)) | ((x) >> (m)))
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))




/* Double New Functions */


#define DNFF(a, b, c, d, x, s1, s2, a1, b1, c1, d1)\
{\
(a) += F((b), (c), (d)) + (x);(a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += F((b1), (c1), (d1)) + (x);(a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}

#define DNGG(a, b, c, d, x, s1, s2, a1, b1, c1, d1)\
{\
(a) += G ((b), (c), (d)) + (x) + (unsigned int)0x5a827999; (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += G ((b1), (c1), (d1)) + (x) + (unsigned int)0x5a827999; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}

#define DNHH(a, b, c, d, x, s1, s2, a1, b1, c1, d1)\
{\
(a) += H ((b), (c), (d)) + (x) + (unsigned int)0x6ed9eba1; (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += H ((b1), (c1), (d1)) + (x) + (unsigned int)0x6ed9eba1; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}





/* Nonegal Double New Functions */


#define NDNGG(a, b, c, d, x, s1, s2, a1, b1, c1, d1)\
{\
(a) += G ((b), (c), (d)) + (x) + (unsigned int)0x5a827999; (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += G ((b1), (c1), (d1)) + (x) + diff + (unsigned int)0x5a827999; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}

#define NDNHH(a, b, c, d, x, s1, s2, a1, b1, c1, d1)\
{\
(a) += H ((b), (c), (d)) + (x) + (unsigned int)0x6ed9eba1; (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += H ((b1), (c1), (d1)) + (x) + diff + (unsigned int)0x6ed9eba1; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}

#define NDNFF(a, b, c, d, x, s1, s2, a1, b1, c1, d1)\
{\
(a) += F ((b), (c), (d)) + (x); (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += F ((b1), (c1), (d1)) + (x) +diff; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}



/* Double New Functions Zero */


#define DNFF0(a, b, c, d, s1, s2, a1, b1, c1, d1)\
{\
(a) += F ((b), (c), (d)); (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += F ((b1), (c1), (d1)); (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}

#define DNGG0(a, b, c, d, s1, s2, a1, b1, c1, d1)\
{\
(a) += G ((b), (c), (d))  + (unsigned int)0x5a827999; (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += G ((b1), (c1), (d1)) + (unsigned int)0x5a827999; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}

#define DNHH0(a, b, c, d, s1, s2, a1, b1, c1, d1)\
{\
(a) += H ((b), (c), (d)) + (unsigned int)0x6ed9eba1; (a) = NROTATE_LEFT ((a), (s1), (s2));\
(a1) += H ((b1), (c1), (d1)) + (unsigned int)0x6ed9eba1; (a1) = NROTATE_LEFT ((a1), (s1), (s2));\
}


#define RNHH0(a, b, c, d, s1, s2)\
{\
(a) = NROTATE_LEFT((a), (s2), (s1));\
(a) -= H((b), (c), (d)) + (unsigned int)0x6ed9eba1;\
}


#define RNGG0(a, b, c, d, s1, s2)\
{\
(a) = NROTATE_LEFT((a), (s2), (s1));\
(a) -= G((b), (c), (d)) + (unsigned int)0x5a827999;\
}



/* 
New FF, GG, HH transformations for rounds 1, 2, 3.
Rotation is separate from addition to prevent recomputation.
*/


#define NFF(a, b, c, d, x, s1, s2) {(a) += F((b), (c), (d)) + (x);(a) = NROTATE_LEFT ((a), (s1), (s2));}

#define NGG(a, b, c, d, x, s1, s2) { (a) += G ((b), (c), (d)) + (x)+ (unsigned int)0x5a827999; (a) = NROTATE_LEFT ((a), (s1), (s2));}

#define NHH(a, b, c, d, x, s1, s2) { (a) += H ((b), (c), (d)) + (x) + (unsigned int)0x6ed9eba1; (a) = NROTATE_LEFT ((a), (s1), (s2));}

#define NFF0(a, b, c, d, s1, s2) {  (a) += F ((b), (c), (d));  (a) = NROTATE_LEFT ((a), (s1), (s2)); }

#define NGG0(a, b, c, d, s1, s2) {  (a) += G ((b), (c), (d))+ (unsigned int)0x5a827999;  (a) = NROTATE_LEFT ((a), (s1), (s2)); }

#define NHH0(a, b, c, d, s1, s2) {  (a) += H ((b), (c), (d)) + (unsigned int)0x6ed9eba1;  (a) = NROTATE_LEFT ((a), (s1), (s2)); }




/* 
basic FF, GG, HH, transformations for rounds 1, 2, 3.
Rotation is separate from addition to prevent recomputation.
 */

#define FF(a, b, c, d, x, s) { \
 (a) += F ((b), (c), (d)) + (x); \
 (a) = ROTATE_LEFT ((a), (s)); \
  }

#define GG(a, b, c, d, x, s) { \
 (a) += G ((b), (c), (d)) + (x) + (unsigned int)0x5a827999; \
 (a) = ROTATE_LEFT ((a), (s)); \
  }

#define HH(a, b, c, d, x, s) { \
 (a) += H ((b), (c), (d)) + (x) + (unsigned int)0x6ed9eba1; \
 (a) = ROTATE_LEFT ((a), (s)); \
  }














