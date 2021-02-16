# Basics of Artificial Inteligence Science Project
## Authors
### Jakub Gałat, Arkadiusz Dawid
## Topic
### Implementation of memetic algorithm, i.e. evolutionary algorithm, which uses local optymalization.
## Design choices
* Each specimen is described by vector of his features and his fitnes value
* Specimen features are floats
* Value of each feature is constrained in bounds (-100,100) and every feature has same constraints
* In the proces of evolution we use only mutation (without crossover)
* As a selection we use tournament selection, where best specimen always wins
* Each generation has same population size
## Algoritm
```c++
void MemeticAlgorithm::run() {

	// generate an initial population
	Population population = generatePopulation();

	for (int i = 0; i < numberOfGenerations; i++) {
		// evaluate
		evaluatePopulation(population);

		// evolve (mutate only)
		mutatePopulation(population);

		// select (tournament selection)
		population = tournamentSelection(population);

		// local memetics
		population = localSearch(population);

	}
}
```
## Contribution
### Jakub Gałat
* core program features, classes and important methods
* fitness evaluation
* local optimalization
### Arkadiusz Dawid
* evolution (specimen mutation)
* tournament selection
