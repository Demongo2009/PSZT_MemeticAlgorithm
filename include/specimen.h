//
// Created by demongo on 13.11.2020.
//

#ifndef PSZT_MEMETICALGORITHM_SPECIMEN_H
#define PSZT_MEMETICALGORITHM_SPECIMEN_H



class Specimen{
	int specimenSize;
	float fitness;

	std::vector<float> valuesArray;

public:
	Specimen():specimenSize(1),fitness(0){
		valuesArray.reserve(1);
	};

	Specimen(std::vector<float> valuesArray):fitness(0){
		this->valuesArray = valuesArray;
		this->specimenSize = valuesArray.size();
	}

	void setFitness(float fitness);

	float getFitness() const;

	std::vector<float>& getValuesArray();

	void changeValue(int num, float change, bool add);
};



#endif //PSZT_MEMETICALGORITHM_SPECIMEN_H
