#include "../header/sim.h"

void initSim(int wWidth, int wHeigth, maps* m, simSpec* spec)
{
    initDisplay(wWidth, wHeigth);
    readFile(m, spec);
}

void makeMap(maps* m)
{
    m->curMap = malloc(sizeof(bool*) * m->height);
    m->preMap = malloc(sizeof(bool*) * m->height);

    for (int i = 0; i < m->height; i++)
    {
        m->curMap[i] = (bool *)malloc(sizeof(bool) * m->width);
        m->preMap[i] = (bool *)malloc(sizeof(bool) * m->width);
    }
};

void applyRule(maps* m)
{
    int countn = 0;

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (k == 0 && l == 0)
                    {
                        continue;
                    }

                    if (k+i < 0 || l+j < 0 || k+i > (m->height-1) || l+j > (m->width-1))
                    {
                        continue;
                    }

                    else
                    {
                        if (m->preMap[i+k][j+l] == 1)
                        {
                            countn++;
                        }
                    }
                }
            }

            if (countn < 2 || countn > 3)
            {
                m->curMap[i][j] = 0;
            }

            else if (countn == 3)
            {
                m->curMap[i][j] = 1;
            }

            else
            {
                m->curMap[i][j] = m->preMap[i][j];
            }

            countn = 0;
        }
    }

    bool** tmp = m->preMap;
    m->preMap = m->curMap;
    m->curMap = tmp;
}

void deInitSim(maps* m, simSpec* spec, bool shouldWrite)
{
    if (shouldWrite)
    {
        writeFile(m, spec);
    }
    free(m->preMap);
    free(m->curMap);
    deInitDisplay();
}