#include <stdio.h>
#include "application.cpp"
#include "vulkanRenderer.cpp"

int main(int argc, char* args[]) {
    printf("Start\n");

    application myApp;
    printf("App created\n");
    myApp.start();
    return 0;
}
