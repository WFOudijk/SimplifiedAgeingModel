//
//  Individual.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 07/12/2022.
//
#pragma once

#include <cassert>
#include "parameters.h"
#include "rnd_t.h"

#include <array>

const int numAgeClasses = 20;

struct Individual {
    /**Structure Individual with age, maternal genes and paternal genes. Every gene contains a number which
     represents the survival probability. The function calculateSurvivalProb() calculates the average survival probability per gene/ age
    over both parents survival probability per gene/ age. **/
    int age;
    // the genes are the survival probability rates per age;
    std::array<double, numAgeClasses> genesMaternal;
    std::array<double, numAgeClasses> genesPaternal;
    
    // to calculate the average survival probability by avereging
    // the mothers and fathers survival probability
    std::array<double, numAgeClasses> averageSurvivalProb;
    
    Individual(){ // default constructor with numAgeClasses genes all starting at 0.95
        genesMaternal.fill(0.95);
        genesPaternal.fill(0.95);
        age = 0; // age is equal to zero upon initialization
        calculateAverageSurvivalProb();
    }
    
    Individual(double initVal) { // Constructor to change the initial survival probability rate the genes should start at.
        genesMaternal.fill(initVal);
        genesPaternal.fill(initVal);
        calculateAverageSurvivalProb();
        age = 0;
    }
    
    Individual(const Individual& other){ // copy constructor
        age = other.age;
        genesMaternal = other.genesMaternal;
        genesPaternal = other.genesPaternal;
        averageSurvivalProb = other.averageSurvivalProb;
    }
    
    Individual(const Individual& mother, const Individual& father, rnd_t& rng, const parameters& p){
        /**Constructor to reproduce and create offspring (with potential mutations). **/
        age = 0;
        // initialize genes array
        genesMaternal = mother.genesMaternal;
        genesPaternal = father.genesPaternal;

        //assert(genesMaternal.size() == genesPaternal.size());
        //assert(mother.genesPaternal.size() == father.genesPaternal.size());
        //assert(mother.genesMaternal.size() == father.genesMaternal.size()); // TODO: is this necessary? 

        for (int i = 0; i < numAgeClasses; ++i){ // loop through every gene
            // first, determine offsprings genome
            double geneMom = rng.uniform(); // if 1 is picked, offspring gets grandpa's allele for this gene from its mom
            genesMaternal[i] = (geneMom < 0.5) ? mother.genesPaternal[i] : mother.genesMaternal[i];
            double geneDad = rng.uniform(); // if 1 is picked, offspring gets grandpa's allele for this gene from its dad
            genesPaternal[i] = (geneDad < 0.5) ? father.genesMaternal[i] : father.genesPaternal[i];
            
            // next, check if a mutation will occur in this gene for both the allele inherited from the mother as well as father
            if (rng.uniform() < p.mutationProb){
                genesMaternal[i] += rng.drawMutationEffect();
                if (genesMaternal[i] < 0) genesMaternal[i] = 0;
                if (genesMaternal[i] > 1) genesMaternal[i] = 1;
            }
            if (rng.uniform() < p.mutationProb){
                genesPaternal[i] += rng.drawMutationEffect();
                if (genesPaternal[i] < 0) genesPaternal[i] = 0;
                if (genesPaternal[i] > 1) genesPaternal[i] = 1;
            }
        }
        calculateAverageSurvivalProb();
    }
    
    Individual& operator=(const Individual& other){
        age = other.age;
        genesMaternal= other.genesMaternal;
        genesPaternal = other.genesPaternal;
        averageSurvivalProb = other.averageSurvivalProb;
        return *this;
    }
    
    void calculateAverageSurvivalProb();
    bool dies(rnd_t& rng);
};

void Individual::calculateAverageSurvivalProb(){
    /** Function to calculate the average survival probability of an individual per age. **/
    for (int i = 0; i < genesMaternal.size(); ++i){
        double average = (genesMaternal[i] + genesPaternal[i]) / 2;
        averageSurvivalProb[i] = average;
    }
}

bool Individual::dies(rnd_t& rng){
    /**Function to calculate which individuals will die.**/
    // get the survival prob for the age the individual is
    double survivalProbForAge = averageSurvivalProb[age];
    double randomProb = rng.uniform(); // draw random number between 0 and 1
    bool dies = false;
    if (randomProb < survivalProbForAge){
        age += 1; // increment age if individual survives the mortality round
    } else { // male dies
        dies = true; // Individual will die
    }
    return dies;
}
