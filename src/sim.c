#include "../header/sim.h"

void initSim(int wWidth, int wHeigth, maps* m, simSpec spec)
{
    m->size = m->width * m->heighth;
    makeMap(m);
    initDisplay(wWidth, wHeigth);
    readFile(m, spec);
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
        int nexttoindex[8];
        nexttoindex[0] = i  - (m->width + 1);
        nexttoindex[1] = i  - (m->width);
        nexttoindex[2] = i  - (m->width - 1);
        nexttoindex[3] = i - 1;
        nexttoindex[4] = i + 1;
        nexttoindex[5] = i  + (m->width - 1);
        nexttoindex[6] = i  + (m->width);
        nexttoindex[7] = i  + (m->width + 1);

        bool nextovalue[8];
        int count = 0;

        for (int j = 0; j < 8; j++)
        {
            if (nexttoindex[j] < 0 || nexttoindex[j] > m->size)
            {
                nextovalue[j] = 0;
            }

            else
            {
                nextovalue[j] = m->preMap[nexttoindex[j]];
            }
        }

        for (int j = 0; j < 8; j++)
        {
            if (nextovalue[j] == 1)
            {
                count++;
            }
        }

        if (m->preMap[i] == 1 && (count < 2 || count > 3))
        {
            m->curMap[i] = 0;
        }

        if (m->preMap[i] == 0 && count == 3)
        {
            m->curMap[i] = 1;
        }

    }

    memcpy(m->preMap, m->curMap, sizeof(bool) * m->size);
}

void deInitSim(maps* m)
{
    free(m->preMap);
    free(m->curMap);
    deInitDisplay();
}