//
//  Randomizer.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 15/12/2022.
//

#pragma once

struct Randomizer {
    std::mt19937_64 rng;
    Randomizer() {
        unif = std::uniform_real_distribution<double>(0, 1);
    }
    double uniform() {
        return unif(rng);
    }
    void setSeed(size_t s){
        rng.seed(s);
    }
    double drawMutationEffect() {
        return mutationEffect(rng);
    }
    void setMutationEffect(double m, double sd) {
        mutationEffect = std::normal_distribution<double>(m, sd);
    }    
    int drawRandomNumber(size_t sizeVector) {
        if (sizeVector < 1) {
            return 0;
        }
        std::uniform_int_distribution<int> d(0, static_cast<int>(sizeVector) - 1);
        return d(rng);
    }
    
    std::uniform_real_distribution<double> unif;
    std::normal_distribution<double> mutationEffect;
};

