//
//  parameters.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 07/12/2022.
//

#pragma once

struct parameters {
    int totalPopulation;    
    double mutationProb;
    double meanMutationBias; // mutation bias
    double sdMutationalEffectSize; // mutational effect size
    int tEnd; 
};
