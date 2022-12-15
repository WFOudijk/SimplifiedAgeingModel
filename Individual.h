//
//  Individual.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 07/12/2022.
//
#pragma once

#include "parameters.h"
#include "Randomizer.h"

#include <array>

const int numAgeClasses = 20; // the number of ages and genes every individual contains 
using arrayOfGenes = std::array<double, numAgeClasses>;

struct Individual {
    /**Structure Individual with age, maternal genes and paternal genes. Every gene contains a number which
     represents the survival probability. The function calculateSurvivalProb() calculates the average survival probability per gene/ age
    over both parents survival probability per gene/ age. **/
    unsigned int age;
    // the genes are the survival probability rates per age;
    arrayOfGenes genesMaternal;
    arrayOfGenes genesPaternal;
    // TODO: std::array<2, std::array<double, numAgeClasses>> One array of both mom and dad
    
    // to calculate the average survival probability by averaging
    // the mothers and fathers survival probability
    arrayOfGenes averageSurvivalProb;
    
    // TODO: Q: this is not default constructor anymore > how to? Need p.
    Individual(const Parameters& p) : age(0){
        // default constructor with numAgeClasses genes all starting at initSurvProb
        genesMaternal.fill(p.initSurvProb); // get this value from parameter struct
        genesPaternal.fill(p.initSurvProb);
        calculateAverageSurvivalProb();
    }
    
    Individual(const double initVal) : age(0){ // constructor to set initial survival probabilities
        genesMaternal.fill(initVal);
        genesPaternal.fill(initVal);
        calculateAverageSurvivalProb();
    }

    Individual(const Individual& other) = default; // default copy constructor is used
    
    Individual(const Individual& mother,
               const Individual& father,
               Randomizer& rng,
               const Parameters& p): age(0){
        /**Constructor to reproduce and create offspring (with potential mutations). **/
        for (int i = 0; i < numAgeClasses; ++i){ // loop through every gene
            // first, determine offsprings genome
            double geneMom = rng.uniform();
            // if 1 is picked, offspring gets grandpa's allele for this gene from its mom
            genesMaternal[i] = (geneMom < 0.5) ? mother.genesPaternal[i] : mother.genesMaternal[i];
            double geneDad = rng.uniform();
            // if 1 is picked, offspring gets grandpa's allele for this gene from its dad
            genesPaternal[i] = (geneDad < 0.5) ? father.genesMaternal[i] : father.genesPaternal[i];
            
            // next, check if a mutation will occur in this gene for both
                // the allele inherited from the mother as well as father
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
    bool dies(Randomizer& rng, const Parameters& p);
};

void Individual::calculateAverageSurvivalProb(){
    /** Function to calculate the average survival probability of an individual per age. **/
    for (int i = 0; i < genesMaternal.size(); ++i){
        double average = (genesMaternal[i] + genesPaternal[i]) * 0.5;
        averageSurvivalProb[i] = average;
    }
}

bool Individual::dies(Randomizer& rng,
                      const Parameters& p){
    /**Function to calculate which individuals will die.**/
    // get the survival prob for the age the individual is
    const double survivalProbForAge = averageSurvivalProb[age];
    double randomProb = rng.uniform(); // draw random number between 0 and 1
    bool dies = false;
    // multiply the survival probability of the individual at its age times
    // the effect of an extrinsic mortality risk on the survival probability
    double survivalProbIncExtrinsicRisk = survivalProbForAge * (1 - p.extrinsicMortRisk);
    if (randomProb < survivalProbIncExtrinsicRisk){
        age += 1; // increment age if individual survives the mortality round
    } else { // male dies
        dies = true; // Individual will die
    }
    return dies;
}
