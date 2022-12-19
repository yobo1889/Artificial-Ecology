#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"


class Organism {

    private:
        double points; //the increment factor for our organisms
        emp::Ptr<emp::Random> random;
        std::string species;

    public:

        

    //return the species name
    

    Organism(emp::Ptr<emp::Random> _random, std::string _species) :
        random(_random), species(_species){
            
    }

    void SetPoints(double _in) {
        points = _in;
    }
    void AddPoints(double _in) {
        points = points + _in;
    }
    int getPoint(){
        return points;
    }
    void SetSpecies(std::string sp) {
        species = sp;
    }

    //adds a point to an organism every time the update method is called
    void Process(double newPoints) {
        points = points + newPoints;
    }
    virtual std::string GetSpecies(){
        return species;
    }
    virtual  emp::Ptr<Organism> CheckReproduction(emp::Ptr<Organism> off, int req_to_reproduce){
        
        if (getPoint() == req_to_reproduce) {
            std::cout << off->GetSpecies() << std::endl;
            off->SetPoints(0); 
            SetPoints(getPoint() - req_to_reproduce);
            return off;
        }
        return nullptr; //if requirments are not met return an empty pointer
    }

    //check to see if the requirment are met for reprodiction and returns an off spring if successful
    
};
#endif