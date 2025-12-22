#include "../header/sim.h"

void initMainMenu(windowSpec* wSpec)
{
    app->wSpec.windowWidth = LUNCHER_WINDOW_WIDTH;
    app->wSpec.windowHeight = LUNCHER_WINDOW_HEIGHT;
    app->wSpec.fps = LUNCHER_WINDOW_FPS;

    initDisplay(app->wSpec)
}

void menuMainLoop(appContex* app)
{
    
}