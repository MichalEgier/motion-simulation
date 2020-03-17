#include <stdio.h>
#include <stdlib.h>

struct Vector{

	double x;
	double y;
	double z;

};

struct Vector_of_expressions{

	char* function_in_x_dimension;
	char* function_in_y_dimension;
	char* function_in_z_dimension;

};

void specifyTime(double* specifiedTime){

	float input_time;

	printf("Please specify the time: ");

	scanf("%f",&input_time);

	*specifiedTime = (double) input_time;

}

void input(struct Vector_of_expressions* function_of_force,struct Vector* v0,struct Vector* r0)
{

	float x;
	float y;
	float z;

	printf("Please write your function F(t), where F(t) = (Fx,Fy,Fz): ");
	printf("\nFx = ");
	scanf("%s",function_of_force -> function_in_x_dimension);
	printf("\nFy = ");
	scanf("%s",function_of_force -> function_in_y_dimension);
	printf("\nFz = ");
	scanf("%s",function_of_force -> function_in_z_dimension);


	printf("\nPlease specify the initial state:\nr0 = (x,y,z)\nx = ");
	scanf("%f",&x);
	printf("\ny = ");
	scanf("%f",&y);
	printf("\nz = ");
	scanf("%f",&z);

	r0->x = (double)x;
	r0->y = (double)y;
	r0->z = (double)z;

	printf("\nv0 = (x,y,z)\nx = ");
	scanf("%f",&x);
	printf("\ny = ");
	scanf("%f",&y);
	printf("\nz = ");
	scanf("%f",&z);

	v0->x = (double)x;
	v0->y = (double)y;
	v0->z = (double)z;


}//void input(char* function_as_string,Vector* f0,Vector* v0,Vector* r0)

