#include "Species.h"
#include <string>
class Red : public Species{
     public:
     int req_to_reproduce = 41;
   public:
   //checks the requirment for the Red organism
   bool check_rep_red(int points){
    
     if (points == req_to_reproduce) {
        return true;
     }
     return false;
   }
    public:

    //return the species index
    std::string GetOrg(){
        return "red";
    }

};