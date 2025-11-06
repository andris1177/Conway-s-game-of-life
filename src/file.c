#include "../header/file.h"

void readFile(maps* map, simSpec* spec)
{
    FILE* file = fopen(spec->iFile, "r");

    if (file == NULL)
    {
        printf("Failed to open the file\n");
        exit(1);
    }

    if(
    !(fscanf(file, "width %d\n", &map->width) == 1 &&
    fscanf(file, "height %d\n", &map->height) == 1 &&
    fscanf(file, "simCount %d\n", &spec->simLength) == 1 && 
    fscanf(file, "simShowTime %lf\n", &spec->simSpeed) == 1))
    {
        printf("Failed to read the file header variables\n");
        exit(1);
    }

    makeMap(map);

    char row[map->width + 2];
    for (int i = 0; i < map->height; i++)
    {
        fgets(row, sizeof(row), file);
        for (int j = 0; j < map->width; j++)
        {
            if (row[j] == '.')
            {
                map->preMap[i][j] = 0;
                map->curMap[i][j] = 0;
            }
            
            else if (row[j] == 'x')
            {
                map->preMap[i][j] = 1;
                map->curMap[i][j] = 1;
            }
        }
    }

    fclose(file);
}

void writeFile(maps* map, simSpec* spec)
{
    FILE* file = fopen(spec->oFile, "w");

    if (file == NULL)
    {
        printf("Failed to open the file\n");
        exit(1);
    }

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