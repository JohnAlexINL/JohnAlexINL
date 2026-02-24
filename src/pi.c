#include <stdio.h>
#include <stdlib.h>

#define DEPTH 128

typedef unsigned long long integer;
typedef _Bool bool;
enum {
	false,
	true
};

extern const integer primes[];
extern const integer primec;
extern const double piPre;

double Qabs(double n);
integer pi (integer n);
integer delta(integer x, integer y);
integer Qdistance(integer x, integer y, integer w, integer h);
integer reduce(integer *x, integer *y);

int main (int argc, char **argv)
{
	int n; integer TOP = 22; integer BOTTOM = 7; double error = Qabs( (double)(22)/7 - piPre );
	for(n=4;n<DEPTH;n++) {
		integer test = n*n;
		integer numerator = pi(test)*4;
		double result = (double)(numerator) / (test*test);
		double localError = Qabs(result - piPre); // square removes negatives
		
		if ( localError < error ) {
		// Save the current answer
			TOP = numerator;
			BOTTOM = test*test;
			error = localError;
		// Reduce our fractions
			reduce(&TOP, &BOTTOM);
			printf("    %-12lusq => %f, ~ %lu / %lu \n", test, result, TOP, BOTTOM);
		}
	}
	printf("Best match:\n    %f (%lu/%lu)\n",
		(double)(TOP)/BOTTOM,
		TOP, BOTTOM
	);
}

// ------------					Function Implementations

inline integer delta (integer x, integer y)
{
	return x > y ? (x-y) : (y-x);
}

inline integer Qdistance (integer x, integer y, integer w, integer h)
{
	integer X = delta(x,w); X*=X;
	integer Y = delta(y,h); Y*=Y;
	return X + Y;
}

inline double Qabs(double n)
{
	if ( n < 0 ) { n *= -1; }
	return n;
}

integer reduce(integer *x, integer *y)
{
	int i;
	for(i=0;i<primec;i++) {
		int r = primes[i];
		while ( *x % r == 0 && *y % r == 0 ) 
		{ *x /= r; *y /= r; }
	}
	return *x;
}

integer pi (integer N)
{
	integer score = 0, x = 0, y = 0;
	for(x=0;x<N;x++) {
    for(y=0;y<N;y++) {
        integer position = (y*N)+x;
        bool bounded = Qdistance(x,y,N,N-1) <= N*N; // -0,-1 is congruent to -0.5,-0.5
        if ( bounded ) { score++; }
    }}
	return score;
}

// ------------ 				Math Constants

const double piPre = (double)(3.141592653589793238462643383279502884197169399375105820974944592307816406286208);

const integer primec = 63; // sizeof(primes) / sizeof(primes[0]);

const integer primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311
};
