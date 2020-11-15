# Projekt z przedmiotu Podstawy Sztucznej Inteligencji
## Autorzy
### Jakub Gałat, Arkadiusz Dawid
## Treść zadania
### Implementacja algorytmu memetycznego, tzn. algorytmu ewolucyjnego, który wykorzystuje optymizator lokalny.
## Założenia
* Każdy osobnik jest opisany przez wektor cech oraz wyliczoną dla nich wartość fitness
* Cechy osobników są liczbami rzeczywistymi
* Wartość każdej cechy jest ograniczona z góry i z dołu, przy czym każda cecha ma takie same ograniczenia
* W etapie ewolucji dokonywana jest tylko mutacja (bez krzyżowania)
* Wykorzystuje się selekcję turniejową, w której zawsze wygrywa lepszy osobnik
* Każda generacja jest tak samo liczna
## Zarys algorytmu
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
## Wkład poszczególnych autorów
### Jakub Gałat
* szkielet programu, klasy i najważniejsze metody
* obliczanie współczynnika fitness
* optymizator lokalny
### Arkadiusz Dawid
* ewolucja (mutacja osobników)
* selekcja turniejowa
