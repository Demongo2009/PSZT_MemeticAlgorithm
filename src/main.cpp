//
// Created by demongo on 05.11.2020.
//
#include <iostream>
#include <stdlib.h>
#include "../include/memetic.h"


float eval(std::vector<float> v){
	float x = v[0];

	return powf(x-2,2) + 1;
}

// LBFGS++ lib requires such function signature
double evalForLocalSearch(Eigen::Matrix<double, Eigen::Dynamic, 1>& x, Eigen::Matrix<double, Eigen::Dynamic, 1>& grad){
	int size = x.size();

	double fx=0;

	for(int i=0; i<size; i++){

		grad[i] = 2 * x[i] - 4;
		fx += powf(x[i]-2,2) +1 ;

	}

	return fx;
}


int main(){
	std::cout<< "hello world\n";


	MemeticAlgorithm memeticAlgorithm = MemeticAlgorithm(1,100,1,-100,100,100,0.1,0.5,0.1,10,1e-6,eval,evalForLocalSearch);
	Specimen specimen = memeticAlgorithm.run();

	std::cout << "Best: " << *specimen.getValuesArray().begin() << " Value: " << specimen.getFitness() << "\n";

	return 0;
}