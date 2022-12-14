//
//  Population.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 14/12/2022.
//

#include <iostream>
#include "Individual.h"
#pragma once

using indVec = std::vector<Individual>;

struct Population{
    indVec males;
    indVec females;
    indVec offspring;
    
    void makePopulation(const parameters& p);
    void reproduce(rnd_t& rng, const parameters& p);
    void mortalityRound(rnd_t& rng, std::vector<int>& ageAtDeath, const parameters& p);
    void addOffspring(const parameters& p, rnd_t& rng);
};

void Population::makePopulation(const parameters& p){ // TODO: can be constructor
    /**This function initialises the population and seperates males and females. **/
    Individual indiv = Individual(p);
    males = indVec(p.halfPopulation, indiv); // intialize males
    females = indVec(p.halfPopulation, indiv); // initialize females
}

void Population::reproduce(rnd_t& rng, const parameters& p){
    /**This function is the reproducing step of the adults.  Every female reproduces a numOfOffspringPerFemale number of offspring with
     random males. **/
    
    offspring.clear(); // to make sure the vector is empty
    // to optimize code, reserve the specific space for the offspring vector
    offspring.reserve(females.size() * p.numOfOffspringPerFemale);
    for (int j = 0; j < females.size(); ++j){ // loop through every female
        for (int i = 0; i < p.numOfOffspringPerFemale; ++i){ // loop through number of offspring to produce
            offspring.emplace_back(females[j], males[rng.drawRandomNumber(males.size())], rng, p); // reproduce
        }
    }
}

void Population::mortalityRound(rnd_t& rng, std::vector<int>& ageAtDeath, const parameters& p){
    /**This function kills of adults. **/
    for (int male = 0; male < males.size();){
        bool die = males[male].dies(rng, p); // check if current male will die
        if (die){ // if this is the case, remove the male from the vector
            ageAtDeath.push_back(males[male].age);
            males[male] = males.back();
            males.pop_back();
        } else {
            ++male;
        }
    }
    
    // females
    for (int female = 0; female < females.size();){
        bool die = females[female].dies(rng, p); // check if current female will die
        if (die){ // if this is the case, remove female from vector
            ageAtDeath.push_back(females[female].age);
            females[female] = females.back();
            females.pop_back();
        } else {
            ++female;
        }
    }
}

void Population::addOffspring(const parameters& p, rnd_t& rng){
    /**This function adds (random) offspring to the adult vectors untill the vectors are at their maximum again. **/
    while (males.size() < (p.halfPopulation)){
        int randIndex = rng.drawRandomNumber(offspring.size());
        males.push_back(offspring[randIndex]); // add a random offspring to the males vector
        offspring[randIndex] = offspring.back(); // TODO: FB: maybe make function for this removal
        offspring.pop_back(); // make sure to remove the offspring to prevent repetition
    }
    
    while (females.size() < (p.halfPopulation)){
        int randIndex = rng.drawRandomNumber(offspring.size());
        females.push_back(offspring[randIndex]); // add a random offspring to the males vector
        offspring[randIndex] = offspring.back();
        offspring.pop_back(); // make sure to remove the offspring to prevent repetition
    }
}


