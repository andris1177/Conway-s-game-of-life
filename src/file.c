#include "../header/file.h"

void readFile(maps* map, simSpec* sSpec, windowSpec* wSpec)
{
    FILE* file = fopen(sSpec->iFile, "r");

    if (file == NULL)
    {
        printf("Failed to open the file\n");
        exit(-1);
    }

    char buffer[20];
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %d", &wSpec->windowWidth);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %d", &wSpec->windowHeight);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %d", &wSpec->fps);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %d", &map->width);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %d", &map->height);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %d", &sSpec->simLength);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%*s %lf", &sSpec->simSpeed);

    makeMap(map);

    char row[map->width + 12];
    for (int i = 0; i < map->height; i++)
    {
        fgets(row, sizeof(row), file);
        for (int j = 0; j < map->width; j++)
        {
            if (row[j] == '.')
            {
                map->preMap[i][j] = false;
                map->curMap[i][j] = false;
            }
            
            else if (row[j] == 'x')
            {
                map->preMap[i][j] = true;
                map->curMap[i][j] = true;
            }

            else
            {
                map->preMap[i][j] = false;
                map->curMap[i][j] = false;
            }
        }
    }

    fclose(file);
}

void writeFile(const maps* map, const simSpec* spec, const windowSpec* wSpec)
{
    FILE* file = fopen(spec->oFile, "w");

    if (file == NULL)
    {
        printf("Failed to open the file\n");
        exit(-1);
    }

    fprintf(file, "windowWidth %d\n", wSpec->windowWidth);
    fprintf(file, "windowHeight %d\n", wSpec->windowHeight);
    fprintf(file, "fps %d\n", wSpec->fps);
    fprintf(file, "width %d\n", map->width);
    fprintf(file, "height %d\n", map->height);
    fprintf(file, "simCount %d\n", spec->simLength);
    fprintf(file, "simShowTime %lf\n", spec->simSpeed);

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (map->curMap[i][j] == 0)
            {
                fprintf(file, ".");
            }

            else if (map->curMap[i][j] == 1)
            {
                fprintf(file, "x");
            }
        }

        fprintf(file, "\n");
    }

    fclose(file);
}