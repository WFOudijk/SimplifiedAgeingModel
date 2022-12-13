//
//  parameters.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 07/12/2022.
//

#include <fstream>
#pragma once

struct parameters {
    int totalPopulation;    
    double mutationProb;
    double meanMutationBias; // mutation bias
    double sdMutationalEffectSize; // mutational effect size
    int tEnd;
    
    void readParameters(const std::string& parameterFile);
    void checkParam(const std::string parID,
                    const std::string focal_parametername,
                    double& parameter,
                    std::ifstream& ifs);
};



void parameters::checkParam(const std::string parID, // member func of parameters
                 const std::string focal_parametername,
                 double& parameter,
                 std::ifstream& ifs) {
    if (parID == focal_parametername) {
        ifs >> parameter;
        std::clog << "Parameter " << parID << " is set to " << parameter << std::endl;
    }
}


void parameters::readParameters(const std::string& parameterFile){
    /**This function receives a parameter file and reads this. Next, the parameters in the file are set to the correct parameters
     in the parameters object.**/
    std::ifstream ifs(parameterFile.c_str());
    if(!ifs.is_open()){
        std::cerr << "Error. Unable to read the following parameter file: "
                    << parameterFile << std::endl;
        exit(EXIT_FAILURE);
    }
    std::clog << "Reading parameters from file: " << parameterFile << std::endl;
    for(;;){
        std::string parID;
        ifs >> parID;
        if(ifs.good()) {
            checkParam(parID, "meanMutationBias", meanMutationBias, ifs);
            checkParam(parID, "sdMutationalEffectSize", sdMutationalEffectSize, ifs);
            checkParam(parID, "mutationProbability", mutationProb, ifs);
        }
        else break;
    }
}

