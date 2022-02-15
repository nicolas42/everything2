#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <stdio.h>
#include <math.h>

typedef struct {
	double e0, x, y, z, yz, zy, xy, xyz;
} MULTIVECTOR;

typedef struct {
	void (*init)(MULTIVECTOR *a);
	void (*product)(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
	void (*rotate)(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
	void (*print)(MULTIVECTOR v);
	void (*printv)(MULTIVECTOR v);
	char* (*str)(char* buf, MULTIVECTOR v);
}  LIB_MULTIVECTOR;

extern const LIB_MULTIVECTOR multivector;

// void init(MULTIVECTOR *a){
// 	a->e0 = 0; a->x = 0; a->y = 0; a->z = 0; a->yz = 0; a->zy = 0; a->xy = 0; a->xyz = 0; 
// }

// void product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b){
// 	c->e0 	= a.e0*b.e0 	+ a.x*b.x 	+ a.y*b.y 	+ a.z*b.z 	- a.yz*b.yz 	- a.zy*b.zy 	- a.xy*b.xy 	- a.xyz*b.xyz;
// 	c->x 	= a.e0*b.x 	+ a.x*b.e0 	- a.y*b.xy 	+ a.xy*b.y 	+ a.z*b.zy 	- a.zy*b.z 	- a.xyz*b.yz 	+ a.yz*b.xyz;
// 	c->y 	= a.e0*b.y 	+ a.y*b.e0 	+ a.x*b.xy 	- a.xy*b.x 	- a.z*b.yz 	+ a.yz*b.z 	- a.xyz*b.zy 	- a.zy*b.xyz;
// 	c->z 	= a.e0*b.z 	+ a.z*b.e0 	- a.x*b.zy 	+ a.zy*b.x 	+ a.y*b.yz 	- a.yz*b.y 	- a.xyz*b.xy 	- a.xy*b.xyz;
// 	c->yz 	= a.yz*b.e0 	+ a.e0*b.yz 	+ a.y*b.z 	- a.z*b.y 	+ a.xy*b.zy 	- a.zy*b.xy 	+ a.xyz*b.x 	+ a.x*b.xyz;
// 	c->zy 	= a.zy*b.e0 	+ a.e0*b.zy 	+ a.z*b.x 	- a.x*b.z 	+ a.yz*b.xy 	- a.xy*b.yz 	+ a.xyz*b.y 	+ a.y*b.xyz;
// 	c->xy 	= a.xy*b.e0 	+ a.e0*b.xy 	+ a.x*b.y 	- a.y*b.x 	+ a.zy*b.yz 	- a.yz*b.zy 	+ a.xyz*b.z 	+ a.z*b.xyz;
// 	c->xyz	= a.e0*b.xyz 	+ a.xyz*b.e0 	+ a.x*b.yz 	+ a.yz*b.x 	+ a.y*b.zy 	+ a.zy*b.y 	+ a.z*b.xy 	+ a.xy*b.z;
// }

// void rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b){

// 	MULTIVECTOR ab, ba, v2;
// 	init(&ab); init(&ba); init(&v2);

// 	product(&ab, a, b);
// 	product(&ba, b, a);
// 	product(&v2, v, ab);
// 	product(Rab, ba, v2);
// }

// void print(MULTIVECTOR v){
// 	printf("[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
// 			v.e0, v.x, v.y, v.z, v.yz, v.zy, v.xy, v.xyz);	
// }

// void printv(MULTIVECTOR v){
// 	printf("[%.2f %.2f %.2f]\r\n", v.x, v.y, v.z);	
// }

// char* str(char* buf, MULTIVECTOR v){
// 	sprintf(buf, "[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
// 			v.e0, v.x, v.y, v.z, v.yz, v.zy, v.xy, v.xyz);	
			
// 	return buf;
// }


// const LIB_MULTIVECTOR multivector = {
// 	.init = init,
// 	.product = product,
// 	.rotate = rotate,
// 	.print = print,
// 	.printv = printv,
// 	.str = str
// };

// /*
// int main(int argc, char **argv)
// {
// 	const double PI = 3.14159265359;
// 	double angle = PI/4;
// 	MULTIVECTOR v = {0,1,0,0}, a = {0,1,0,0}, b = {0,cos(angle), sin(angle)}, Rab = {0};
// 	multivector.rotate(&Rab, v, a, b);
// 	printf("Rotate v by twice the angle between a and b\r\n");
// 	multivector.printv(v); multivector.printv(a); multivector.printv(b); multivector.printv(Rab); 
// 	printf("\r\n");

// 	return 0;
// }
// */

#endif
