#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Prey.h"
#include "Predator.h"


emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    // arena width and height
    const int num_h_boxes = 50;
    const int num_w_boxes = 50;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};

    emp::Random random{5};
    OrgWorld world{random};

    public:
    
    //spawns our canvas and insert organism in the grid
    AEAnimator() {

        emp::Ptr<Organism> red = new Predator(&random, "red"); //create an instance of predator organism
        emp::Ptr<Organism> blue = new Prey(&random, "blue"); //create an instance of prey organism
        
        


        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        world.Inject(*red); //inject a predator organism
        world.Inject(*blue); //inject a prey organism

        world.Resize(num_w_boxes, num_h_boxes);
        doc << "\n\n" <<" The red organism is a predator and the blue organism is a prey and they interact in a grid to simulate aritifical ecology. If a blue organism is directly below or above a red organism at any point in the simulation, that blue organism is extracted from the grid to simulate real life predator-prey relationship. The red and blue organisms both require diffrent number of points/resources to reproduce. When the red organism eats a blue organism it gains reproduction point but after all the blue organisms die the red organisms stop reproducing";
    }

    //animate the grid
    void DoFrame() override {
        canvas.Clear();
        world.Update();
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    emp::Ptr<Organism> organism = &world.GetOrg(org_num);
                    if (organism->GetSpecies() == "red") {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "red", "red");
                    }
                    else if(organism->GetSpecies() == "blue"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "blue");
                    }
                    
                }
                else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "green");
                }
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() {
    animator.Step();
}