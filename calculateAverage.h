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
    /**Function to calculate the Life Expectancy per individual . TODO: should 1 be added to the sum? **/
    std::vector<double> lifeExpectancy;
    for (int individual = 0; individual < individuals.size(); ++individual){ // loop through every individual
        std::vector<double> lifeExpectancyPerIndividual;
        for (int i = 0; i < individuals[individual].genesMaternal.size(); ++i){ // loop through every age
            double lifeExpectancyInd =
                    individuals[individual].averageSurvivalProb[i]; // get survival prob of current age and individual
            for (int j = 1; j <= i; ++j){ // to make sure every previous survival prob is taken into account
                lifeExpectancyInd *= individuals[individual].averageSurvivalProb[i - j];
            }
            lifeExpectancyPerIndividual.push_back(lifeExpectancyInd);
        }
        double sum = std::accumulate(lifeExpectancyPerIndividual.begin(), lifeExpectancyPerIndividual.end(), 0.0);
        lifeExpectancy.push_back(sum); 
    }
    return lifeExpectancy;
}
