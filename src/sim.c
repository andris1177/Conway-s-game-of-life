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
    for (int j = 0; j < spec->simLength; j++)
    {
        for (int i = 0; i < m->width*m->heighth; i++)
        {
            int count = 0;
            bool* neighbour[8];
            neighbour[0] = &m->preMap[i - (m->width + 1)];
            neighbour[1] = &m->preMap[i - (m->width)];
            neighbour[2] = &m->preMap[i - (m->width - 1)];
            neighbour[3] = &m->preMap[i - 1];
            neighbour[4] = &m->preMap[i + 1];
            neighbour[5] = &m->preMap[i + (m->width + 1)];
            neighbour[6] = &m->preMap[i + (m->width)];
            neighbour[7] = &m->preMap[i + (m->width - 1)];

            for (int k = 0; i < 8; k++)
            {
                if (*neighbour[k])
                {
                    count++;
                }
            }

            if ((count < 2 || count > 3) && m->preMap[i] == true)
            {
                m->curMap[i] = false;
            }
            
            if (count == 3 && m->preMap[i] == false)
            {
                m->curMap[i] = true;
            }
        }

        memcpy(m->curMap, m->preMap, (sizeof(bool) * (m->width * m->heighth)));
    }
}

void deInitSim(maps* m)
{
    free(m->preMap);
    free(m->curMap);
    deInitDisplay();
}