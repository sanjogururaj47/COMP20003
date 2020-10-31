#include<stdio.h>
#include<float.h>

int main(int argc, char **argv) {
	printf("Double: %.20lf, Float: %.20f", DBL_EPSILON, FLT_EPSILON);
	return 0;
}

