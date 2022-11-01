#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "screen.cpp"
#include "Swarm.cpp"


using namespace std;




int main(int argc, char** argv){
    
    Screen screen;
    screen.init();
    
    if (screen.init() == false){
        cout << "Error intializing SDL window" << endl;
    }

    Swarm swarm; 
    

    while (true)
    {  
        int elapsed = SDL_GetTicks();
        swarm.update(elapsed);

        unsigned char green = (unsigned char)((1+ sin(elapsed*0.001)) * 128);
        unsigned char red = (unsigned char)((1+ sin(elapsed*0.002)) * 128);
        unsigned char blue = (unsigned char)((1+ sin(elapsed*0.003)) * 128); 

         Particles * mparticles = swarm.getParticles();


       for ( int i = 0; i < Swarm::NPARTICLES; i++){
                Particles particles = mparticles[i]; 

                int x = (particles.xPosition + 1) * Screen::Width;
                int y = (particles.yPosition + 1) * Screen::Height;
                      
                        if (rand() < RAND_MAX/100) {
                            particles.changeColor(&red,&green,&blue,elapsed);
                        }
                        
                screen.setPixel(x,y,red,green,blue);
       }
       
       screen.boxBlur();
       screen.screenUpdate();
       if(screen.processEvents() == false){
        break;
       }

    }

    screen.close();
    return 0;
}