//
//  Population.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 14/12/2022.
//
#pragma once
#include <iostream>
#include "Individual.h"

using indVec = std::vector<Individual>;

struct Population{
    indVec males;
    indVec females;
    indVec offspring;
    
    void makePopulation(const Parameters& p);
    void reproduce(Randomizer& rng, const Parameters& p);
    void mortalityRound(Randomizer& rng, const Parameters& p, std::vector<int>& ageAtDeath);
    void addOffspring(const Parameters& p, Randomizer& rng);
};

void Population::makePopulation(const Parameters& p){
    /**This function initialises the population and initialises males and females. **/
    Individual indiv = Individual(p);
    males = indVec(p.halfPopulation, indiv); // intialize males
    females = indVec(p.halfPopulation, indiv); // initialize females
}

void Population::reproduce(Randomizer& rng,
                           const Parameters& p){
    /**This function is the reproducing step of the population.  Every female reproduces a numOfOffspringPerFemale
     number of offspring with random males. **/
    offspring.clear(); // to make sure the vector is empty
    // to optimize code, reserve the specific space for the offspring vector
    offspring.reserve(females.size() * p.numOfOffspringPerFemale);
    for (auto j = 0u; j < females.size(); ++j){ // loop through every female
        for (int i = 0; i < p.numOfOffspringPerFemale; ++i){ // loop through number of offspring to produce
            offspring.emplace_back(females[j], males[rng.drawRandomNumber(males.size())], rng, p); // reproduce
        }
    }
}

void Population::mortalityRound(Randomizer& rng,
                                const Parameters& p,
                                std::vector<int>& ageAtDeath){
    /**This function kills off adults.**/
    for (auto male = 0u; male < males.size();){
        bool die = males[male].dies(rng, p); // check if current male will die
        if (die){ // if this is the case, remove the male from the vector
            ageAtDeath.push_back(males[male].age);
            males[male] = males.back();
            males.pop_back();
        } else { // else, continue loop
            ++male;
        }
    }
    
    // same for the females
    for (auto female = 0u; female < females.size();){
        bool die = females[female].dies(rng, p); // check if current female will die
        if (die){ // if this is the case, remove female from vector
            ageAtDeath.push_back(females[female].age);
            females[female] = females.back();
            females.pop_back();
        } else { // else, continue loop
            ++female;
        }
    }
}

void Population::addOffspring(const Parameters& p,
                              Randomizer& rng){
    /**This function adds (random) offspring to the adult vectors untill the vectors are at their maximum size again. **/
    while (males.size() < (p.halfPopulation)){
        int randIndex = rng.drawRandomNumber(offspring.size());
        males.push_back(offspring[randIndex]); // add a random offspring to the males vector
        offspring[randIndex] = offspring.back();
        offspring.pop_back(); // make sure to remove the offspring to prevent repetition
    }
    // same for females
    while (females.size() < (p.halfPopulation)){
        int randIndex = rng.drawRandomNumber(offspring.size());
        females.push_back(offspring[randIndex]); // add a random offspring to the males vector
        offspring[randIndex] = offspring.back();
        offspring.pop_back(); // make sure to remove the offspring to prevent repetition
    }
}



