#include <emscripten.h>
#include <stdio.h>

//Declare a reusable JS Function
EM_JS(void, jsFunction, (int n),{
    console.log("Call from EM JS: "+n)
})

int main(){
    printf("WASM Ready\n");

    //Call JS Function

    emscripten_run_script("console.log('Hello from C!');");

    emscripten_async_run_script("console.log('Hello from C! -Async');",2000);

    //Get return value from js Function -INT
    int jsVal = emscripten_run_script_int("getNum()");

    //Get return value from js Function -INT
    char * jsValString = emscripten_run_script_string("getNumString()");

    printf("value from getNum() = %d\n",jsVal);

    printf("value from getNumString() = %s\n",jsValString);

    //Exacute EM_JS Function
    jsFunction(144);

    return 1;
}

 