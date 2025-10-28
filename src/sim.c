#include "../header/sim.h"

void initSim(int wWidth, int wHeigth, const char* iFile, const char* oFile, maps* m)
{
    makeMap(m);
    initDisplay(wWidth, wHeigth);
}

void makeMap(maps* m)
{
    m->preMap = malloc(sizeof(bool) * (m->width * m->heighth));
    m->curMap = malloc(sizeof(bool) * (m->width * m->heighth));
}

void applyRule(maps* m, simSpec* spec)
{
    for (int i = 0; i < 100; i++)
    {
        
    }

    memcpy(m->curMap, m->preMap, (sizeof(bool) * (m->width * m->heighth)));
}

void deInitSim(maps* m)
{
    free(m->preMap);
    free(m->curMap);
    deInitDisplay();
}