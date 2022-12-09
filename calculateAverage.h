//
//  calculateAverage.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 09/12/2022.
//

#pragma once

std::array<double, numAgeClasses> calcAverageAcrossAgeClasses(const std::vector<Individual>& individuals) {
    /**Function to calculate the average survival probability across the age classes
     over a vector of individuals. */
    std::array<double, numAgeClasses> popAverage;
    popAverage.fill(0.0);
    
    for (const auto& i : individuals) { // loop through the individuals
        for(int j = 0; j < i.averageSurvivalProb.size(); ++j){ // loop through every age group
            popAverage[j] += i.averageSurvivalProb[j]; // sum the survival prob average of every individual for the jth age group
        }
    }
    for(auto& i : popAverage) { // loop through the averages
        i *= 1.0 / (individuals.size()); // compare the sum per age group with the size of the individuals
    }
    return popAverage; // return array with average survival probability for every age over the individuals
}

std::vector<double> calcLifeExpectancyPerIndividual(const std::vector<Individual>& individuals){
    std::vector<double> lifeExpectancy;
    for (auto individual : individuals){
        lifeExpectancy.push_back(individual.averageSurvivalProb[0]);
        //ouble counter = 1.0;
        for (int i = 1; i < individual.genesMaternal.size(); ++i){
            lifeExpectancy[i];
            lifeExpectancy.push_back(lifeExpectancy[i - 1] + individual.averageSurvivalProb[i]);
        }
    }
    
    return lifeExpectancy;
}
