#ifndef PREY_H
#define PREY_H
#include "Org.h"
#include <string>
class Prey : public Organism{
    public:
    
public:
    
    Prey(emp::Ptr<emp::Random> _random, std::string species) : Organism(_random, GetSpecies())
    {
    }

   //return the species index
   std::string GetSpecies(){
      return "blue";
    }
   //return an offspring of type prey
   emp::Ptr<Organism> GetOffspring(){
        emp::Ptr<Organism> offspring_prey = new Prey(*this);
        offspring_prey->SetSpecies("blue");
        return offspring_prey;
   }

   //return the number of points required for reproduction 
   int GetReqReProduce(){
       return 27;
   }

};
#endif