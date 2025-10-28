#include "../header/sim.h"

void initSim(int wWidth, int wHeigth, const char* iFile, const char* oFile, maps* m)
{
    makeMap(m);
    initDisplay(wWidth, wHeigth);
    m->size = m->width * m->heighth;
}

void makeMap(maps* m)
{
    m->preMap = malloc(sizeof(bool) * m->size);
    m->curMap = malloc(sizeof(bool) * m->size);
}

void applyRule(maps* m, simSpec* spec)
{
    for (int i = 0; i < m->size; i++)
    {
        
    }

    memcpy(m->curMap, m->preMap, sizeof(bool) * m->size);
}

void deInitSim(maps* m)
{
    free(m->preMap);
    free(m->curMap);
    deInitDisplay();
}