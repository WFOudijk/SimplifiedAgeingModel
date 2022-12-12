//
//  outputGenerator.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 07/12/2022.
//

#include <fstream>
#include <cstdlib>
#include <vector>
#include "calculateAverage.h"
#pragma once

void createOutput(const std::vector<Individual>& individualVec){
    /**Function to create output to the terminal of Individuals in a vector.
     It calculates the average survival probability for every age or gene. **/
    for (auto individual : individualVec){ // for every individual in the vector
            // calculate average of every gene/ age
            for (int i = 0; i < individual.genesMaternal.size(); ++i) {
                std::cout << individual.averageSurvivalProb[i] << " ";
            }
            std::cout << "Age: " << individual.age << " ";
            std::cout << std::endl;
        }
    }


void createOutputForPlot(const std::vector<Individual>& males,
                         const std::vector<Individual>& females){
    /**This function creates the output for a scatter plot where age is at the x-axis and average survival probability at the y-axis. **/
    std::ofstream ofs;
    ofs.open("output.csv"); // output file
    if (!ofs.is_open()){
        std::cerr << "Error. Unable to open output file.\n";
        exit(EXIT_FAILURE);
    }
    auto female_avg = calcAverageAcrossAgeClasses(females); // calculate average survival prob per age of the females
    auto male_avg = calcAverageAcrossAgeClasses(males); // calculate average survival prob per age of the males
    
    for (int i = 0; i < female_avg.size(); ++i) { // loop through every age
        double pop_avg = (female_avg[i] + male_avg[i]) * 0.5; // calculate population average
        ofs << pop_avg << std::endl; // write this average to file
    }
    ofs.close();    
}

void createOuputForGGPlot(const std::vector<Individual>& males,
                          const std::vector<Individual>& females,
                          const int t){
    /**Function to create the output for a GGPlot. It determines the average survival probability for both the females and males,
     then it determines the population average based on this. This is written to a file, including the current time and the age. **/
    
    if (t == 0) {
        std::ofstream ofs;
        ofs.open("outputFacetWrap.csv"); // output file
        if (!ofs.is_open()){
            std::cerr << "Error. Unable to open output file.\n";
            exit(EXIT_FAILURE);
        }
        ofs.close();
    }
    
    std::ofstream ofs;
    ofs.open("outputFacetWrap.csv", std::ios::app); // output file
    if (!ofs.is_open()){
        std::cerr << "Error. Unable to open output file.\n";
        exit(EXIT_FAILURE);
    }
    auto femaleAverage = calcAverageAcrossAgeClasses(females); // calculate average survival prob per age of the females
    auto maleAverage = calcAverageAcrossAgeClasses(males); // calculate average survival prob per age of the males
    
    for (int i = 0; i < femaleAverage.size(); ++i) { // loop through every age
        double popAverage = (femaleAverage[i] + maleAverage[i]) * 0.5; // calculate population average
        ofs << t << " " << i << " " << popAverage << std::endl; // write current time, age and average to file
    }
    ofs.close();
}

void createOutputLifeExpectancy(const std::vector<double>& malesLE,
                                const std::vector<double>& femalesLE,
                                const double meanMutEffect){
    std::ofstream ofs;
    ofs.open("outputLE.csv", std::ios::app); // output file
    if (!ofs.is_open()){
        std::cerr << "Error. Unable to open output file.\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < malesLE.size(); ++i){
        ofs << meanMutEffect << " " << malesLE[i] << " " << femalesLE[i] << std::endl;
    }
}
