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

//Circles
struct Circle circles[NUM_CIRCLES];

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
        int x = getRand(1000) + radius;
        int y = getRand(1000) + radius;

        //Fill circle Struct
        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255); 
    }


    //emscripten_run_script("render()");
    EM_ASM({ render($0,$1); }, NUM_CIRCLES*6, 6);
}

struct Circle * getCircles(){
    return circles;
}