#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

//Number of Circles
#define NUM_CIRCLES 20

//Circle Struct
struct Circle {
    int x;  //x-axis
    int y;  //y-axis
    int r;  //radius
    int cr; //red
    int cg; //green
    int cb; //blue
};

//Circle Struct
struct CircleAnimationData {
    int x;  //x-axis
    int y;  //y-axis
    int r;  //radius    
    int xv; // velocity at x axis
    int yv; //velocity at y axis
    int xd; //direction at x axis 1-forwar 0-backward
    int yd; //direction at y axis 1-forward 0-backward
};

//Circles
struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(max){
    return (rand() % max);
}

//Init circle data and start render -JS
int main(){

    //Seed random number generator
    srand(time(NULL));

    //Create Circles
    for(int i=0; i < NUM_CIRCLES; i++){
        //Radius
        int radius = getRand(50);

        //Coordinates
        int x = getRand(600) + radius;
        int y = getRand(600) + radius;

        //fill animationData
        animationData[i].x = x;
        animationData[i].y = y;
        animationData[i].r = radius;
        animationData[i].xv = getRand(10);
        animationData[i].yv = getRand(10);
        animationData[i].xd = 1;
        animationData[i].yd = 1;

        //Fill circle Struct
        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255); 
    }

    //Start JS rendering
    //emscripten_run_script("render()");
    EM_ASM({ render($0,$1); }, NUM_CIRCLES*6, 6);
}

struct Circle * getCircles(int canvasWidth, int canvasHeight){
    for(int i= 0; i<NUM_CIRCLES; i++){
        //Collision RIGHT -set x direction 0
        if(animationData[i].x + animationData[i].r >= canvasWidth) animationData[i].xd =0;

        //Collision LEFT -set x direction 1
        if(animationData[i].x - animationData[i].r <= 0) animationData[i].xd =1;

        //Collision TOP -set y direction 1
        if(animationData[i].y - animationData[i].r <= 0) animationData[i].yd =1;

        //Collision Bottom -set y direction 0
        if(animationData[i].y + animationData[i].r >= canvasHeight) animationData[i].yd =0;

        //Move Circle in Specified direction
        if(animationData[i].xd ==1 ){
            animationData[i].x += animationData[i].xv;            
        }
        else{
            animationData[i].x -= animationData[i].xv;            
        }

        if(animationData[i].yd ==1 ){
            animationData[i].y += animationData[i].yv;            
        }
        else{
            animationData[i].y -= animationData[i].yv;            
        }

        //update matching circle
        circles[i].x = animationData[i].x;
        circles[i].y = animationData[i].y;

        
    }
    return circles;
}