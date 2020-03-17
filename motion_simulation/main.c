#include "Simulation.c"

int main(int argc, char** argv){

	runSimulation(argc,argv);

	for(int i=0;i<argc;i++){

		printf("Argument number i=%d",i);
		printf(argv[i]);
		printf("\n");

	}

	return 0;

}
