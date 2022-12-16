//
//  parameters.h
//  AgeingModel
//
//  Created by Willemijn Oudijk on 07/12/2022.
//
#pragma once
#include <fstream>


struct Parameters {
    // initialise the parameters
    Parameters() : totalPopulation(10000),
                   initSurvProb(0.95),
                   numOfOffspringPerFemale(1),
                   mutationProb(0.01),
                   meanMutationBias(-0.001),
                   sdMutationalEffectSize(0.01),
                   extrinsicMortRisk(0.05),
                   outputTime(250),
                   tEnd(10000){
                       halfPopulation = totalPopulation / 2;
                   }
    
    int totalPopulation; // total population size
    double halfPopulation; // to determine number of males and females
    double initSurvProb; // initial survival probability for all the genes
    int numOfOffspringPerFemale; // number of offspring a female should produce 
    double mutationProb; // probability a mutation will occur
    double meanMutationBias; // the mean bias of a mutation on survival probability
    double sdMutationalEffectSize; // the mutational effect size on survival probability
    double extrinsicMortRisk; // the extrinsic mortality risk, equal for every adult
    int outputTime; // when to output info
    int tEnd; // end of simulation
    
    void readParameters(const std::string& parameterFile);
    void checkParam(const std::string parID,
                    const std::string focal_parametername,
                    double& parameter,
                    std::ifstream& ifs);
};

void Parameters::checkParam(const std::string parID,
                 const std::string focal_parametername,
                 double& parameter,
                 std::ifstream& ifs) {
    if (parID == focal_parametername) {
        ifs >> parameter;
        std::clog << "Parameter " << parID << " is set to " << parameter << std::endl;
    }
}

void Parameters::readParameters(const std::string& parameterFile){
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
            checkParam(parID, "extrinsicMortRisk", extrinsicMortRisk, ifs);
        }
        else break;
    }
}

