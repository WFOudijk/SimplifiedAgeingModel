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
    std::ofstream ofs;
    ofs.open("outputDeathAge.csv"); // output file
//    std::vector<int> ageAtDeath;
    for (int t = 0; t < p.tEnd; ++t){
        std::vector<int> ageAtDeath;
        pop.reproduce(rng, p); // reproduce to make offspring
        pop.mortalityRound(rng, ageAtDeath, p); // mortality round of the adults
        pop.addOffspring(p, rng); // adding offspring to the adults
        
        // output
        if (t % p.outputTime == 0) { // to prevent every time step of being outputted
            std::cout << t << " ";
            auto t_now = std::chrono::system_clock::now();
            std::chrono::duration<double> diff_t = t_now - t_start;
            std::cout << diff_t.count() << " seconds" << std::endl;
            t_start = t_now;
            std::cout << "total deaths: " << ageAtDeath.size() << std::endl;
            ofs << t << " "
            << p.meanMutationBias << " "
            << p.sdMutationalEffectSize << " "
            << p.extrinsicMortRisk << " "
             << std::accumulate(ageAtDeath.begin(), ageAtDeath.end(), 0.0) /
                ageAtDeath.size() << std::endl; // look at age of death over time

            createOuputForGGPlot(pop.males, pop.females, t, p); // generate data for ggplot
            
        }
    }
    std::vector<double> LEMales = calcLifeExpectancyPerIndividual(pop.males);
    std::vector<double> LEFemales = calcLifeExpectancyPerIndividual(pop.females);
    createOutputLifeExpectancy(LEMales, LEFemales, p);
    
    // to create output of an Individuals vector
    //createOutput(offspringVec);
    //createOutput(pop.males);
    //createOutput(females);
    //createOutputForPlot(males, females);
    //calcLifeExpectancy(pop.males);
    
    
    // to calculate the average age someone dies
//    std::cout << "total deaths: " << ageAtDeath.size() << std::endl; // every time step
//    std::cout << "Average age to die: "
//            << std::accumulate(ageAtDeath.begin(), ageAtDeath.end(), 0.0) / ageAtDeath.size()
//            << std::endl; // look at age of death over time
//
    return 0;
}
