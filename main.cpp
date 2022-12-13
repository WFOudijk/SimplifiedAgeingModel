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
#include "rnd_t.h"
#include "outputGenerator.h"

int main(int argc, const char * argv[]) {
    // obtain seed from system clock
    std::chrono::high_resolution_clock::time_point tp =
    std::chrono::high_resolution_clock::now();
    unsigned seed = static_cast<unsigned>(tp.time_since_epoch().count());
    std::cout << "The seed is: " << seed << std::endl;
    // create and seed pseudo-random number generator
    rnd_t rng;
    rng.setSeed(seed);
    
    parameters p; // make parameters object
    
    // default parameter values, if no parameter file is given to the program as arugument
    // then these will be the parameter values
    p.meanMutationBias = -0.001; // the mean bias of a mutation on survival probability
    p.sdMutationalEffectSize = 0.01; // the mutational effect size on survival probability
    p.mutationProb = 0.01; // set mutation probability

    // read parameter file
    std::string parameterFile;
    if (argc > 1){
        parameterFile = argv[1];
        p.readParameters(parameterFile); // sets parameters
    }
    
    // set the mutationEffect distribution with mean and sd of mutation
    rng.setMutationEffect(p.meanMutationBias, p.sdMutationalEffectSize);
    std::cout << "mean is: " << p.meanMutationBias << " and the sd is: " << p.sdMutationalEffectSize << std::endl;
    
    // make population
    p.totalPopulation = 100; // total number of individuals present in population
    Individual indiv = Individual();
    std::vector<Individual> males(p.totalPopulation / 2, indiv); // intialize males
    std::vector<Individual> females(p.totalPopulation / 2, indiv); // initialize females
    
    p.tEnd = 10000; // end time of simulation
    
    auto t_start = std::chrono::system_clock::now();
    
    std::vector<int> ageAtDeath;
    for (int t = 0; t < p.tEnd; ++t){
        // reproduce to make offspring
        std::vector<Individual> offspringVec;
           offspringVec.reserve(females.size() * 2); // to optimize code, reserve the specific space for the offspring vector
        for (double i = 0.0; i < females.size();){
       // for (int i = 0; i < females.size(); ++i){
            if (std::fmod(i, 1) == 0.5){ // if i is a half, the previous female should reproduce again
                offspringVec.emplace_back(females[static_cast<int>(i - 0.5)], males[rng.drawRandomNumber(males.size())], rng, p); // reproduce
            } else { // otherwise (i is whole number) the ith female can reproduce
                offspringVec.emplace_back(females[i], males[rng.drawRandomNumber(males.size())], rng, p); // reproduce
            }
            i += 0.5; // to have every woman make two offspring
        }
        
        // mortality round of the males
        for (int male = 0; male < males.size();){
            bool die = males[male].dies(rng);
            if (die){
                ageAtDeath.push_back(males[male].age);
                males[male] = males.back();
                males.pop_back();
            } else {
                ++male;
            }
        }
        
        //std::cout << "male size before: " << males.size() << std::endl;
        
        // mortality round of adult females
        for (int female = 0; female < females.size();){
            bool die = females[female].dies(rng);
            if (die){
                ageAtDeath.push_back(females[female].age);
                females[female] = females.back();
                females.pop_back();
            } else {
                ++female;
            }
        }
        //std::cout << "female size before: " << females.size() << std::endl;
        //std::cout << "offspring vector size before: " << offspringVec.size() << std::endl;
        
        // fill the dead adults spots with random offspring
        while (males.size() < (p.totalPopulation/2)){
            int randIndex = rng.drawRandomNumber(offspringVec.size());
            males.push_back(offspringVec[randIndex]); // add a random offspring to the males vector
            offspringVec[randIndex] = offspringVec.back();
            offspringVec.pop_back(); // make sure to remove the offspring to prevent repetition
        }
        //std::cout << "male size after: " << males.size() << std::endl;
        //std::cout << "offspring vector size after males : " << offspringVec.size() << std::endl;
        
        while (females.size() < (p.totalPopulation/2)){
            int randIndex = rng.drawRandomNumber(offspringVec.size());
            females.push_back(offspringVec[randIndex]); // add a random offspring to the males vector
            offspringVec[randIndex] = offspringVec.back();
            offspringVec.pop_back(); // make sure to remove the offspring to prevent repetition
        }
        //std::cout << "female size after: " << females.size() << std::endl;
        //std::cout << "offspring vector size after total: " << offspringVec.size() << std::endl;
        if (t % 100 == 0) { // to prevent every time step of being outputted
            std::cout << t << " ";
            auto t_now = std::chrono::system_clock::now();
            std::chrono::duration<double> diff_t = t_now - t_start;
            std::cout << diff_t.count() << " seconds" << std::endl;
            t_start = t_now;
            //createOuputForGGPlot(males, females, t, p); // generate data for ggplot
        }
    }
    
    // to create output of an Individuals vector
    //createOutput(offspringVec);
    //createOutput(males);
    //createOutput(females);
    //createOutputForPlot(males, females);
    
    std::vector<double> LEMales = calcLifeExpectancyPerIndividual(males);
    std::vector<double> LEFemales = calcLifeExpectancyPerIndividual(females);
    //createOutputLifeExpectancy(LEMales, LEFemales, p.meanMutationBias);
    
    // to calculate the average age someone dies
    //for (auto age : ageAtDeath) std::cout << age << " ";
    std::cout << "total deaths: " << ageAtDeath.size() << std::endl;
    std::cout << "Average age to die: " << std::accumulate(ageAtDeath.begin(), ageAtDeath.end(), 0.0) / ageAtDeath.size() << std::endl; // look at age of death over time
    
    return 0;
}
