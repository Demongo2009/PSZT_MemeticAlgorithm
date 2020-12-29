//
// Created by demongo on 05.11.2020.
//
#include <iostream>
#include <stdlib.h>
#include "../include/memetic.h"


float eval(std::vector<float> x){
	int size = x.size();

	double fx=0;

	for(int i=0; i<size; i+=2){

		double t1 = 1.0 - x[i];
		double t2 = 10 * (x[i + 1] - x[i] * x[i]);
		fx += t1 * t1 + t2 * t2;

	}

	return fx;
}

// LBFGS++ lib requires such function signature
double evalForLocalSearch(Eigen::Matrix<double, Eigen::Dynamic, 1>& x, Eigen::Matrix<double, Eigen::Dynamic, 1>& grad){
	int size = x.size();

	double fx=0;

	for(int i=0; i<size; i+=2){

		double t1 = 1.0 - x[i];
		double t2 = 10 * (x[i + 1] - x[i] * x[i]);
		grad[i + 1] = 20 * t2;
		grad[i]     = -2.0 * (x[i] * grad[i + 1] + t1);
		fx += t1 * t1 + t2 * t2;

	}

	return fx;
}


int main(){
	std::cout<< "hello world\n";


	MemeticAlgorithm memeticAlgorithm = MemeticAlgorithm(1,100,2,-100,100,100,0.1,0.5,0.1,10,1e-6,eval,evalForLocalSearch);
	Specimen specimen = memeticAlgorithm.run();

	std::cout << "Best: " << "\n";
	for(auto i : specimen.getValuesArray()){
	    std::cout << i << "\t";
	}
	std::cout << "\nValue: " << specimen.getFitness() << "\n";

	return 0;
}