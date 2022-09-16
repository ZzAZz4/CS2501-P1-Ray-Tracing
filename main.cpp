#include "RayTracingApp.h"


int main () {
    RayTracingApp app;
    if (app.Construct(600, 600, 1, 1)) {
        app.Start();
    }
    return 0;
}