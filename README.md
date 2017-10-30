# GeneticAlgorithm

A C++ library for perform genetic algorithms

## Features
* Uses standard C++11 library.
* Includes cross over and mutation breeding for doubles in a range
* Light weight design.
* Simple design and usage.

## Installation
None required; simply dowload the library, then include it in the main.cpp

## Usage Examples
### Cross Over and Mutation Breeding for Doubles in a Range
To produce the offspring of 0.5 and 0.25 in the range 0 to 1, with a bit resoltion of 4
```c++
double value1 = 0.5;
double value2 = 0.25;
double minValue = 0.0;
double maxValue = 1.0;
int bitResoluion = 4;
double result = breedInRange(value1, value2, minValue, maxValue, bitResoluion);

cout << "\nBreeding " << value1 << " and " << value2 << " with a bit resolution of " << bitResoluion << "\n";
cout << "gives " << result << "\n";

```

Output may be different, depending on the seed of the RNG
```console
Breeding 0.5 and 0.25 with a bit resolution of 4
gives 0.3125
```
Note that the above value was obtained due to the first 2 bits comming from value2, and a mutation on the last bit

### Optimization
Given the function
```c++
double f(double x){
	return x*x*x-2*x*x;
}
```

The following code will find the maximum in the range x=[-1,3]
```c++
int population = 10;
int generations = 1000;
double minRange = -1.0;
double maxRange = 3.0;
int bitResolution = 10;

double result = geneticOptimize(&f, population, generations, minRange, maxRange, bitResolution);
cout << "\nThe optimal value found for f(x)=x^3-2*x^2 in the range x=[-1,3] is\n";
cout << "x=" << result << " which gives f(x)=" << f(result) << "\n";
```

Output may be different, depending on the seed of the RNG
```console
The optimal value found for f(x)=x^3-2*x^2 in the range x=[-1,3] is
x=2.99609 which gives f(x)=8.94151
```

## Notes
* There are some commented-out code snippets that allow for verbose operation
