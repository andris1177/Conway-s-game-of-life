#include "../header/sim.h"

void initSim(int wWidth, int wHeigth, maps* m, simSpec* spec)
{
    makeMap(m);
    initDisplay(wWidth, wHeigth);
    readFile(m, spec);
}

void makeMap(maps* m)
{
    m->preMap = malloc(sizeof(bool)[m->height][m->width]);
    m->curMap = malloc(sizeof(bool)[m->height][m->width]);
}

void applyRule(maps* m, simSpec* spec)
{

}

void deInitSim(maps* m)
{
    free(m->preMap);
    free(m->curMap);
    deInitDisplay();
}