#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>


class Particles{
   
public:

     double xPosition;
     double yPosition;
private:
     double Speed;
     double speedDirection;
private:
     void init();
public:
   void changeColor(unsigned char *red, unsigned char *green, unsigned char *blue, int elapsed);
   Particles();
   void update(int elapsed);
};


Particles::Particles(): xPosition(0),yPosition(0) {}

void Particles::init() {
    srand(time(NULL));
    xPosition = 0;
    yPosition = 0;

        speedDirection = ((2.0 * M_PI * rand())/RAND_MAX) - 1;
        Speed = ((0.01 * rand())/RAND_MAX);
        Speed *= Speed;
}
void Particles::changeColor(unsigned char *red, unsigned char *green, unsigned char *blue, int elapsed)
{
        *red += ((1+ sin(elapsed*0.001)) * 128);
        *green += ((1+ sin(elapsed*0.001)) * 128);
        *blue += ((1+ sin(elapsed*0.001)) * 128);

}
void Particles::update(int elapsed){

      speedDirection += elapsed*0.0003;
      
      double xSpeed = Speed * cos(speedDirection);
      double ySpeed = Speed * sin(speedDirection);
      xPosition += xSpeed * elapsed;
      yPosition += ySpeed * elapsed;
    if (xPosition < -1 || xPosition > 1 || yPosition < -1 || yPosition > 1){
        init();
    }
    if (rand() < RAND_MAX/100){
        init();
    }
}