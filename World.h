#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Predator.h"
#include "Prey.h"


class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;
    int neighbour[2];

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }
  //Called everytime the Doframe() method is called in AEAnimate
  void Update() {
      emp::World<Organism>::Update();
      // call process on all organisms
      for(int i = 0; i < GetSize(); i++){
        if(!IsOccupied(i)) {
          continue;
        }

        pop[i] -> Process(1);
        if(pop[i]->GetSpecies()=="red"){ //if the organism is red check to see if there are any adjacent blue organism and kill them
         kill(i);
        }
      }     
      emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
      
      for (int i : schedule) {
        if(!IsOccupied(i)) {
          continue;
        }

      
        if(pop[i]->GetSpecies()=="blue"){
          emp::Ptr<Organism> offspring_prey = pop[i]->CheckReproduction(pop[i].DynamicCast<Prey>()->GetOffspring(),pop[i].DynamicCast<Prey>()->GetReqReProduce()); 
          if(offspring_prey) {
            DoBirth(*offspring_prey, i);  //i is the parent's grid location
          }
        }
        if(pop[i]->GetSpecies()=="red"){
          emp::Ptr<Organism> offspring_pred = pop[i]->CheckReproduction(pop[i].DynamicCast<Predator>()->GetOffspring(),pop[i].DynamicCast<Predator>()->GetReqReProduce()); 
          if(offspring_pred) {
            DoBirth(*offspring_pred, i);  //i is the parent's grid location
          }
        }
        

        emp::Ptr<Organism> organism = ExtractOrganism(i);
        emp::WorldPosition new_position = GetRandomNeighborPos(i);
        AddOrgAt(organism, new_position); //relocates an organism in the grid
      }
  }
   //pops an organism from the grid
  emp::Ptr<Organism> ExtractOrganism(int i){
    emp::Ptr<Organism> organism = pop[i];
    pop[i] = nullptr;
    return organism;
  }

  //finds adjacent grids of the i grid
  void setNeighbour(int i){
       neighbour[0] = i-1;
       neighbour[1] = i+1;
  }

  void kill(int i){
    setNeighbour(i); // set the neighbour to adjacent grids
    if(IsOccupied(neighbour[0])){
      if(pop[neighbour[0]]->GetSpecies()=="blue"){
         ExtractOrganism(neighbour[0]); //kill blue organism if found above a red organism
         std::cout << "Killed" << std::endl;
         pop[neighbour[0]]->Process(0.3); //Give reproduction points to the predator if they successfully kill a prey
      }
     
    }
    if(IsOccupied(neighbour[1])) {
      if(pop[neighbour[1]]->GetSpecies()=="blue"){
         ExtractOrganism(neighbour[1]); //kill blue organism if found below a red organism
        std::cout << "Killed" << std::endl;
        pop[neighbour[1]]->Process(0.3); //Give reproduction points to the predator if they successfully kill a prey
      }
    }
  }
};
#endif