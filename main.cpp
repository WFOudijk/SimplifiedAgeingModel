//
//  main.cpp
//  AgeingModel
//
//  Created by Willemijn Oudijk on 06/12/2022.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <string>
#include "Individual.h"
#include "parameters.h"
#include "Randomizer.h"
#include "outputGenerator.h"
#include "Population.h"

int main(int argc, const char * argv[]) {
    // obtain seed from system clock
    std::chrono::high_resolution_clock::time_point tp =
        std::chrono::high_resolution_clock::now();
    unsigned seed = static_cast<unsigned>(tp.time_since_epoch().count());
    std::cout << "The seed is: " << seed << std::endl;
    // create and seed pseudo-random number generator
    Randomizer rng;
    rng.setSeed(seed);
    
    Parameters p; // make parameters object
    
    // read parameter file
    std::string parameterFile;
    if (argc > 1){
        parameterFile = argv[1];
        p.readParameters(parameterFile); // sets parameters from file
    }
    
    // set the mutationEffect distribution with mean and sd of mutation
    rng.setMutationEffect(p.meanMutationBias, p.sdMutationalEffectSize);

    Population pop;
    pop.makePopulation(p); // initialise population
    
    auto t_start = std::chrono::system_clock::now();
    
    for (int t = 0; t < p.tEnd; ++t){
        std::vector<int> ageAtDeath; // to keep track of the death ages
        pop.reproduce(rng, p); // reproduce to make offspring
        pop.mortalityRound(rng, p, ageAtDeath); // mortality round of the adults
        pop.addOffspring(p, rng); // adding offspring to the adults        
        // output
        if (t % p.outputTime == 0) { // to prevent every time step of being outputted
            std::cout << t << std::endl;
            createOutputAgeDeath(t, p, ageAtDeath); // generate data for average death age
            createOuputForGGPlot(pop.males, pop.females, t, p); // generate data for ggplot            
        }
    }
    createOutputLifeExpectancy(pop.males, pop.females, p); // generate data for LE plot
    
    // to print the duration of the program to the terminal
    auto t_now = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_t = t_now - t_start;
    std::cout << "Finished. The program took: " << diff_t.count() << " seconds" << std::endl;
    t_start = t_now;
    return 0;
}
