#include <iostream>
#include <stdio.h>
#include "particles.cpp"

class Swarm
{
public:
   const static int NPARTICLES = 5000;    
private:
      Particles * pParticles;
     int lastTime;
public:
    Swarm(/* args */);
    virtual ~Swarm();
    void update(int elapsed);
    
      Particles * getParticles () { return pParticles;};
};

Swarm::Swarm()
{
       
    pParticles = new Particles[NPARTICLES];


}

Swarm::~Swarm()
{
    delete [] pParticles;
}
void Swarm::update(int elapsed){
     
     int interval = elapsed - lastTime;
     for (int i = 0; i < Swarm::NPARTICLES; i++) {
		pParticles[i].update(interval);
	}
    lastTime = elapsed;
}
