#ifndef GENETIC_LIB
#define GENETIC_LIB

#include <iostream> //in case of outputs
#include <vector> //to hold population
#include <cstdlib> //for random

using namespace std;


//perform cross over and mutation on doubles in range by converting to a binary fraction of range
double breedInRange(double value1, double value2, double minValue, double maxValue, int bitResoluion){
	//normalize the values
	value1 = (value1-minValue)/(maxValue-minValue);
	value2 = (value2-minValue)/(maxValue-minValue);
	
	//bit arrays
	char bits1[bitResoluion];
	char bits2[bitResoluion];
	char bitsReturn[bitResoluion];
	
	//fill in bits
	for(int i = 0; i < bitResoluion; i++){
		//ensure is only fractional part
		value1 = value1 - (double)((int)value1);
		value2 = value2 - (double)((int)value2);
		//shift bits
		value1 *= 2.0;
		value2 *= 2.0;
		//take most significant bit
		bits1[i] = (char)value1;
		bits2[i] = (char)value2;
	}

	//create return bits
	//cout << "\nCross Over\n";
	for(int i = 0; i < bitResoluion; i++){
		if(rand()%2){
			bitsReturn[i] = bits1[i];
			//cout << "bit " << i << ": parent 1\n";
		}
		else{
			bitsReturn[i] = bits2[i];
			//cout << "bit " << i << ": parent 2\n";
		}
	}
	
	//mutate bits
	//cout << "\nMutated Bits\n";
	for(int i = 0; i < bitResoluion; i++){
		if(rand()%bitResoluion == 0){
			bitsReturn[i] = !bitsReturn[i];
			//cout << "bit " << i << "\n";
		}
	}
	
	//build return value
	double returnValue = 0.0;
	double temp = 1.0;
	for(int i = 0; i < bitResoluion; i++){
		temp /= 2.0;
		if(bitsReturn[i]) returnValue += temp;
	}
	//denormalize
	returnValue = (maxValue-minValue)*returnValue+minValue;

	//cout << "\n1 Value\n";
	//for(int i = 0; i < bitResoluion; i++) cout << "bit " << i << ": " << (int)bits1[i] << "\n";
	//cout << "\n2 Value\n";
	//for(int i = 0; i < bitResoluion; i++) cout << "bit " << i << ": " << (int)bits2[i] << "\n";
	//cout << "\nReturn Value\n";
	//for(int i = 0; i < bitResoluion; i++) cout << "bit " << i << ": " << (int)bitsReturn[i] << "\n";
	
	return returnValue;
}


//Perform roulette fitness selection
int fitnessSelection(vector<double> fitness){
	//get sum of fitness values
	double sum=0;
	for(auto i = fitness.begin(); i != fitness.end(); ++i ) sum += *i;
	//probability is culumative sum of normed fitnesses; thereby making their probabilities proportional to fitness
	vector<double> prob(fitness.size());
	for(int i = 0; i<fitness.size(); i++) prob[i] = fitness[i]/sum;
	
	//reuse sum
	sum = 0;
	//Generate random number
	double randomValue=((double)rand())/RAND_MAX;
	//see where it lands
	for(int i = 0; i<fitness.size(); i++){
		sum += prob[i];
		if(randomValue <= sum) return i;
	}
	//fails
	return -1;
}


//Genetic algorithm for optimization of a single input function, given a range and bit resolution
double geneticOptimize(double (*fTarget)(double), int population, int generations, double minRange, double maxRange, int bitResoluion){
	//save best result
	double bestX = minRange + (maxRange-minRange)*(rand()/(double)RAND_MAX);
	double bestY = fTarget(bestX);
	
	//generate initial population
	vector<double> creatures(population);
	for(auto creature = creatures.begin(); creature != creatures.end(); ++creature){
		*creature = minRange + (maxRange-minRange)*(rand()/(double)RAND_MAX);
	}
	vector<double> newCreatures = creatures;
	
	//perform evolution
	double temp;
	vector<double> fitness(population);
	for(int generation = 0; generation < generations; generation++){
		//cout << "\nGeneration: " << generation << "\n";
		
		//evaluate fitness of each creature
		//cout << "Values:\n";
		for(int i=0; i<population; i++){
			fitness[i] = fTarget(creatures[i]);
			//cout << "Creature: " << i << " xvalue: " << creatures[i] << " yvalue: " << fitness[i] << "\n";
			//is best?
			if(fitness[i]>bestY){
				bestX = creatures[i];
				bestY = fitness[i];
			}
		}
		//normalize fitness
		//cout << "Fitnesses:\n";
		double maxTemp=minRange, minTemp = maxRange;
		for(int i=0; i<population; i++){
			if(fitness[i]>maxTemp) maxTemp = fitness[i];
			if(fitness[i]<minTemp) minTemp = fitness[i];
		}
		
		if(maxTemp != minTemp) for(int i=0; i<population; i++) fitness[i] = (fitness[i]-minTemp)/(maxTemp-minTemp);
		//for(int i=0; i<population; i++) cout << "Creature: " << i << " fitness: " << fitness[i] << "\n";
		
		//mate
		//cout << "Mating:\n";
		int mama, papa;
		for(int creature=0; creature<population; creature++){
			//select parents
			mama = fitnessSelection(fitness);
			papa = fitnessSelection(fitness);
			//cout << "mama: " << mama << " papa: " << papa << "\n";
			
			//crossover weights
			newCreatures[creature] = breedInRange(creatures[mama], creatures[papa], minRange, maxRange, bitResoluion);
		}
		
		//update creatures
		creatures = newCreatures;
	}
	
	//cout << "best x=" << bestX << " gives f(x)=" << bestY << "\n";
	
	return bestX;
}


#endif
