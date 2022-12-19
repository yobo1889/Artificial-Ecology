#include "Species.h"
#include <string>
class Blue : public Species{\
    public:
    int req_to_reproduce = 27;
public:
//checks the requirment for the Blue organism
 bool check_rep_blue(int points){
     
     if (points == req_to_reproduce) {
        return true;
     }
     return false;
   }

   //return the species index
   std::string GetOrg(){
    return "blue";
   }

};