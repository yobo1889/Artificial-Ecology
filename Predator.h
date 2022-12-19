#ifndef PREDATOR_H
#define PREDATOR_H
#include "Org.h"
#include <string>
class Predator : public Organism{
     public:
    
   public:

    Predator(emp::Ptr<emp::Random> _random, std::string species) : Organism(_random, GetSpecies())
      {
      }

    //return the species name
    std::string GetSpecies(){
        return "red";
    }

    //return an offspring of type predator
    emp::Ptr<Organism> GetOffspring(){
        emp::Ptr<Organism> offspring_pred = new Predator(*this);
        offspring_pred->SetSpecies("red");
        return offspring_pred;
    }
    
    // return the number of points required for reproduction 
    int GetReqReProduce(){
       return 41;
    }


};
#endif