#include "header/mainMenu.h"

int main()
{
    initMem();
    appContex app = {0};

    initMainMenu(&app);
    menuMainLoop(&app);       
    deInitSim(&app, false); 
    return 0;
}