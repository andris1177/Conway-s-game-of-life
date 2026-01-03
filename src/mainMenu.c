#include "../header/sim.h"

void initMainMenu(appContex* app)
{
    app->wSpec.windowWidth = LUNCHER_WINDOW_WIDTH;
    app->wSpec.windowHeight = LUNCHER_WINDOW_HEIGHT;
    app->wSpec.fps = LUNCHER_WINDOW_FPS;

    initDisplay(&app->wSpec);
}

void menuMainLoop(appContex* app)
{
    app->aMode.mainMenu = true;
    
    while (!WindowShouldClose())
    {
        if (app->aMode.mainMenu)
        {
            drawMainMenu(&app->wSpec, &app->aMode, &app->aMode.mainMenu);
        }

        else if (app->aMode.editorMenu)
        {
            drawEditorMenu(&app->wSpec, &app->aMode, &app->aMode.editorMenu);
        }
    }
}