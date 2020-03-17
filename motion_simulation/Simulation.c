#include "UserInterface.c"
#include "Parser.c"
#include <stdio.h>

/*
//in UserInterface.h
struct Vector{

	double x;
	double x;
	double z;

}
*/

void runSimulation(int argc,char ** argv)
{

	printf("In run sim");

	FILE* file = fopen("Graphical_Engine/src/file.txt","w");

	struct Vector * r0 = malloc(sizeof(struct Vector));
	struct Vector * v0 = malloc(sizeof(struct Vector));

	struct Vector_of_expressions * function_of_force = malloc(sizeof(struct Vector_of_expressions));

	char* force_x = argv[1]; //= malloc(70 * sizeof(char));
	printf(argv[1]);
	char* force_y = argv[2];//malloc(70 * sizeof(char));
	char* force_z = argv[3];//malloc(70 * sizeof(char));

	function_of_force -> function_in_x_dimension = force_x;
	function_of_force -> function_in_y_dimension = force_y;
	function_of_force -> function_in_z_dimension = force_z;

	printf("After 3 argv");

	double double_value = atof(argv[4]);
	r0 -> x = double_value;
	double_value = atof(argv[5]);
	r0 -> y = double_value;
	double_value = atof(argv[6]);
	r0 -> z = double_value;

	double_value = atof(argv[7]);
	v0 -> x = double_value;
	double_value = atof(argv[8]);
	v0 -> y = double_value;
	double_value = atof(argv[9]);
	v0 -> z = double_value;


//	input(function_of_force,v0,r0);	

	//=================================================

	double t;

	//specifyTime(&t);

	t = atof(argv[10]);

	//=================================================

	double delta_t = 0.0001;

	struct Vector* r_t = malloc(sizeof(struct Vector));
	struct Vector* v_t = malloc(sizeof(struct Vector));
	struct Vector* f_t = malloc(sizeof(struct Vector));
		
	v_t -> x = v0 -> x;
	v_t -> y = v0 -> y;
	v_t -> z = v0 -> z;
	
	r_t -> x = r0 -> x;
	r_t -> y = r0 -> y;
	r_t -> z = r0 -> z;

	double t_sum = 0.0;

	printf("\nF(t = %f) = (%f,%f,%f)",t_sum,f_t -> x,f_t -> y,f_t -> z);
	printf("\nV(t = %f) = (%f,%f,%f)",t_sum,v_t -> x,v_t -> y,v_t -> z);
	printf("\nr(t = %f) = (%f,%f,%f)",t_sum,r_t -> x,r_t -> y,r_t -> z);


	while(t_sum < t){

//char* copied_string_x = copyOf(function_of_force->function_in_x_dimension	
//char* copied_string_y = copyOf(function_of_force->function_in_y_dimension
//char* copied_string_z = copyOf(function_of_force->function_in_z_dimension

//prepareStringForParsing(copied_string_x, r_t, v_t, t_sum)
//prepareStringForParsing(copied_string_y, r_t, v_t, t_sum)
//prepareStringForParsing(copied_string_z, r_t, v_t, t_sum)

	f_t -> x = parse_and_evaluate_expression(function_of_force -> function_in_x_dimension,v_t -> x, v_t -> y, v_t -> z,
						r_t -> x, r_t -> y , r_t -> z, t_sum ); 
/*	+ parse_and_evaluate_expression(function_of_force -> function_in_x_dimension,v_t -> x, v_t -> y, v_t -> z,
						r_t -> x, r_t -> y , r_t -> z, t_sum + (delta_t / 2)) +				
	parse_and_evaluate_expression(function_of_force -> function_in_x_dimension,v_t -> x, v_t -> y, v_t -> z,
						r_t -> x, r_t -> y , r_t -> z, t_sum + delta_t) ) / 3;		*/		

	f_t -> y = parse_and_evaluate_expression(function_of_force -> function_in_y_dimension,v_t -> x, v_t -> y, v_t -> z,
						r_t -> x, r_t -> y , r_t -> z, t_sum);				
	f_t -> z = parse_and_evaluate_expression(function_of_force -> function_in_z_dimension,v_t -> x, v_t -> y, v_t -> z,
						r_t -> x, r_t -> y , r_t -> z, t_sum);				

	v_t -> x = (v_t -> x) + (f_t -> x) * delta_t; // /mass;
	v_t -> y = (v_t -> y) + (f_t -> y) * delta_t; // /mass;
	v_t -> z = (v_t -> z) + (f_t -> z) * delta_t; // /mass;

	r_t -> x = (r_t -> x) + (v_t -> x) * delta_t;
	r_t -> y = (r_t -> y) + (v_t -> y) * delta_t;
	r_t -> z = (r_t -> z) + (v_t -> z) * delta_t;		

		t_sum = t_sum + delta_t;


	
	//printf("\nF(t = %f) = (%f,%f,%f)",t_sum,f_t -> x,f_t -> y,f_t -> z);
	//printf("\nV(t = %f) = (%f,%f,%f)",t_sum,v_t -> x,v_t -> y,v_t -> z);
	//printf("\nr(t = %f) = (%f,%f,%f)",t_sum,r_t -> x,r_t -> y,r_t -> z);



		//**********send information to graphical engine*************
		double num = f_t -> x;
		char out[50];
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = f_t -> y;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = f_t -> z;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = v_t -> x;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = v_t -> y;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = v_t -> z;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = r_t -> x;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = r_t -> y;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");

		num = r_t -> z;
		snprintf(out,50,"%f", num);

		fprintf(file,out);
		fprintf(file,"\n");
		

	}	

	//TUTAJ WYPISANIE WSZYSTKICH WEKTOROW KTORE POWSTALY NAM Z PRZEKSZTALCEN

	printf("====================================");
	printf("\n============ RESULTS ===============");
	printf("\nF(t = %f) = (%f,%f,%f)",t,f_t -> x,f_t -> y,f_t -> z);
	printf("\nV(t = %f) = (%f,%f,%f)",t,v_t -> x,v_t -> y,v_t -> z);
	printf("\nr(t = %f) = (%f,%f,%f)",t,r_t -> x,r_t -> y,r_t -> z);
	

	fclose(file);

}

/*
//not finished method - because is not needed
void prepareStringForParsing(char* string,struct Vector * r_t,struct Vector * v_t,double time)
{

	char* stringToReturn = malloc(sizeof(char)*500);

	char c = *string;

	while(c != '\0'){

		if(c == 'v' || c == 'V'){

			c = *(++string);
			
			if(c == 'x' || c == 'X'){

					*(stringToReturn++) = 
			
			}

		}	

		c = *(++string);

	}

}*/
