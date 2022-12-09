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
    
    p.meanMutation = -0.001; // the mean effect of a mutation on survival probability
    p.SdMutation = 0.01; // the standard deviation of the mutation effect
    // set the mutationEffect distribution with mean and sd of mutation
    rng.setMutationEffect(p.meanMutation, p.SdMutation);
    
    // make population
    p.totalPopulation = 1000; // total number of individuals present in population
    Individual indiv = Individual();
    std::vector<Individual> males(p.totalPopulation / 2, indiv); // intialize males
    std::vector<Individual> females(p.totalPopulation / 2, indiv); // initialize females
    
    p.mutationProb = 0.01; // set mutation probability
    p.tEnd = 50000; // end time of simulation
    
    auto t_start = std::chrono::system_clock::now();
    
    for (int t = 0; t < p.tEnd; ++t){
        // reproduce to make offspring
        std::vector<Individual> offspringVec;
           offspringVec.reserve(females.size() * 2);
        //for (double i = 0.0; i < females.size();){
        for (int i = 0; i < females.size(); ++i){
           // if (std::fmod(i, 1) == 0.5){ // if i is a half, the previous female should reproduce again
            //    offspringVec.emplace_back(females[static_cast<int>(i - 0.5)], males[rng.drawRandomNumber(males.size())], rng, p); // reproduce
         //   } else { // otherwise (i is whole number) the ith female can reproduce
                offspringVec.emplace_back(females[i], males[rng.drawRandomNumber(males.size())], rng, p); // reproduce
         //   }
     //       i += 0.5; // to have every woman make two offspring
        }
        
        // mortality round of the males
        for (int male = 0; male < males.size();){
            bool die = males[male].dies(rng);
            if (die){
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
                females[female] = females.back();
                females.pop_back();
            } else {
                ++female;
            }
        }
        //std::cout << "female size before: " << females.size() << std::endl;
        //std::cout << "offspring vector size before: " << offspringVec.size() << std::endl;
        
        
        
        //  0 1 2 3 4 5 6
        //        X
        //  0 1 2 6 4 5 6
        //  0 1 2 6 4 5
        
        //  0 1 2 3 4 5 6
        //  toAdd = 3
        //  males.push_back(toAdd);
        //  toAdd = 6
        //  0 1 2 3 4 5
        
        // fill the dead adults spots with random offspring
        while (males.size() < (p.totalPopulation/2)){
            int randIndex = rng.drawRandomNumber(offspringVec.size());
            males.push_back(offspringVec[randIndex]); // add a random offspring to the males vector
            offspringVec[randIndex] = offspringVec.back();
            offspringVec.pop_back(); // make sure to remove the offspring to prevent repetition
        }
       // std::cout << "male size after: " << males.size() << std::endl;
        //std::cout << "offspring vector size after males : " << offspringVec.size() << std::endl;
        
        while (females.size() < (p.totalPopulation/2)){
            int randIndex = rng.drawRandomNumber(offspringVec.size());
            females.push_back(offspringVec[randIndex]); // add a random offspring to the males vector
            offspringVec[randIndex] = offspringVec.back();
            offspringVec.pop_back(); // make sure to remove the offspring to prevent repetition
        }
        //std::cout << "female size after: " << females.size() << std::endl;
        //std::cout << "offspring vector size after total: " << offspringVec.size() << std::endl;
        if (t % 1000 == 0) { // to prevent every time step of being outputted
            std::cout << t << " ";
            auto t_now = std::chrono::system_clock::now();
            std::chrono::duration<double> diff_t = t_now - t_start;
            std::cout << diff_t.count() << " seconds" << std::endl;
            t_start = t_now;
            createOuputForGGPlot(males, females, t); // generate data for ggplot
        }
    }
    
    // to create output of an Individuals vector
    //createOutput(offspringVec);
    createOutput(males);
    createOutput(females);
    createOutputForPlot(males, females);
    
    return 0;
}
