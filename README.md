GGA
===

GGA - Generic Genetic Algorithm

This is a simple library to solve problems using GA. It requires a modern C++ compiler, with C++11 enabled. It should be as portable as your compiler.

#Examples

##Simples

A simple example where the genes are a double value, and the fitness function is sin(genes).
Crossover generates two children. One with a value larger than the parents, and another with the value smaller. Mutation adds a random number to fitness

##Boolean

A slightly more intricate example where the gene is enconded in a boolean vector, with fitting function as sin(genes/10.0) 
The crossover children will have, on average, half the genes from each parent, whereas mutation is changing the value some gene fields.

#Usage

This is a template library. The base class, T, must contain implement the following fields:

##Empty constructor
```C++
T()
```

##Fitness value

Plain double precision value, where the fitness of the indivitual must be stored.

```C++
double fitness;
```

##CrossOver function

Function that receives another individual and returns the original individual, bi and two children. These children must already have its fitness calculated.

```C++
std::array<T,4> CrossOver(const T& bi);
```

##Mutate function

Function that mutates the individual with probability p. How this mutation will be done depends on the user.

```C++
void Mutate(double p);
```
