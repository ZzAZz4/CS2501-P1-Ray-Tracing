#include "scenes/FirefliesApp.h"


int main () {
    srand(time(nullptr));
    FirefliesApp app;
    if (app.Construct(600, 600, 1, 1)) {
        app.Start();
    }
    return 0;
}