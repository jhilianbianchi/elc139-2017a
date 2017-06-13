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
Constants for MD5Transform routine.
 */

typedef	unsigned char	ord8;		/* 8  bit unsigned integer */
typedef	unsigned short	ord16;		/* 16 bit unsigned integer */
typedef	unsigned long	ord32;		/* 32 bit unsigned integer */
typedef	char		int8;		/* 8  bit signed integer */
typedef	short		int16;		/* 16 bit signed integer */
typedef	long		int32;		/* 32 bit signed integer */
typedef	ord8		octet;		/* CCITT name for a byte (8 bits) */

int gbl_stop;


#define S11 7
#define SS11 25
#define S12 12
#define SS12 20
#define S13 17
#define SS13 15
#define S14 22
#define SS14 10
#define S21 5
#define SS21 27
#define S22 9
#define SS22 23
#define S23 14
#define SS23 18
#define S24 20
#define SS24 12
#define S31 4
#define SS31 28
#define S32 11
#define SS32 21
#define S33 16
#define SS33 16
#define S34 23
#define SS34 9
#define S41 6
#define SS41 26
#define S42 10
#define SS42 22
#define S43 15
#define SS43 17
#define S44 21
#define SS44 11



/* 
F, G, H and I are basic MD5 functions.
*/

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))



/*
 ROTATE_LEFT rotates x left n bits.
*/


#define NROTATE_LEFT(x, n, m) (((x) << (n)) | ((x) >> (m)))
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))


#define DNFF(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += F((b), (c), (d)) + (x) + (ord32)(ac);(a) = NROTATE_LEFT ((a), (s1), (s2));(a) += (b);\
(a1) += F((b1), (c1), (d1)) + (x) + (ord32)(ac);(a1) = NROTATE_LEFT ((a1), (s1), (s2));(a1) += (b1);\
}

#define DNGG(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += G ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += G ((b1), (c1), (d1)) + (x) + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}

#define DNHH(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += H ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += H ((b1), (c1), (d1)) + (x) + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}

#define DNII(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += I ((b), (c), (d)) + (x) + (ord32)(ac);  (a) = NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);\
(a1) += I ((b1), (c1), (d1)) + (x) + (ord32)(ac);  (a1) = NROTATE_LEFT ((a1), (s1), (s2));  (a1) += (b1);\
}





#define NDNGG(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += G ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += G ((b1), (c1), (d1)) + (x) + diff + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}
#define NDNHH(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += H ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += H ((b1), (c1), (d1)) + (x) + diff + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}
#define NDNFF(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += F ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += F ((b1), (c1), (d1)) + (x) +diff + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}
#define NDNII(a, b, c, d, x, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += I ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += I ((b1), (c1), (d1)) + (x) + diff + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}



#define DNFF0(a, b, c, d, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += F ((b), (c), (d)) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += F ((b1), (c1), (d1)) + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}
#define DNGG0(a, b, c, d, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += G ((b), (c), (d)) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += G ((b1), (c1), (d1)) + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}
#define DNHH0(a, b, c, d, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += H ((b), (c), (d)) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);\
(a1) += H ((b1), (c1), (d1)) + (ord32)(ac); (a1) = NROTATE_LEFT ((a1), (s1), (s2)); (a1) += (b1);\
}
#define DNII0(a, b, c, d, s1, s2, ac, a1, b1, c1, d1)\
{\
(a) += I ((b), (c), (d)) + (ord32)(ac);  (a) = NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);\
(a1) += I ((b1), (c1), (d1)) + (ord32)(ac);  (a1) = NROTATE_LEFT ((a1), (s1), (s2));  (a1) += (b1);\
}



/* 
FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
*/


#define NFF(a, b, c, d, x, s1, s2, ac) {(a) += F((b), (c), (d)) + (x) + (ord32)(ac);(a) = NROTATE_LEFT ((a), (s1), (s2));(a) += (b); }

#define NGG(a, b, c, d, x, s1, s2, ac) { (a) += G ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);   }

#define NHH(a, b, c, d, x, s1, s2, ac) { (a) += H ((b), (c), (d)) + (x) + (ord32)(ac); (a) = NROTATE_LEFT ((a), (s1), (s2)); (a) += (b);  }

#define NII(a, b, c, d, x, s1, s2, ac) { (a) += I ((b), (c), (d)) + (x) + (ord32)(ac);  (a) =NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);   }

#define NFF0(a, b, c, d, s1, s2, ac) {  (a) += F ((b), (c), (d)) + (ord32)(ac);  (a) = NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);   }

#define NGG0(a, b, c, d, s1, s2, ac) {  (a) += G ((b), (c), (d)) + (ord32)(ac);  (a) = NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);   }

#define NHH0(a, b, c, d, s1, s2, ac) {  (a) += H ((b), (c), (d)) + (ord32)(ac);  (a) = NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);   }

#define NII0(a, b, c, d, s1, s2, ac) {  (a) += I ((b), (c), (d)) + (ord32)(ac);  (a) = NROTATE_LEFT ((a), (s1), (s2));  (a) += (b);   }

#define NRHH0(a, b, c, d, s1, s2, ac) {  (a) -= (b);  (a) = NROTATE_LEFT ((a), (s2), (s1));  (a) -= (H ((b), (c), (d)) + (ord32)(ac));   }

#define NRII0(a, b, c, d, s1, s2, ac) {  (a) -= (b);  (a) = NROTATE_LEFT ((a), (s2), (s1));  (a) -= (I ((b), (c), (d)) + (ord32)(ac));   }



/* 
FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */

#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }












