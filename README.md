# GeneticAlgorithm

A C++ library for perform genetic algorithms

## Features
* Uses standard C++11 library.
* Includes cross over and mutation breeding for doubles in a range
* Light weight design.
* Simple design and usage.

## Installation
None required; simply dowload the library, then include it in your main.cpp

## Usage
### Creating Graphs

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

Output will be:
```console
The optimal value found for f(x)=x^3-2*x^2 in the range x=[-1,3] is
x=2.99609 which gives f(x)=8.94151
```
