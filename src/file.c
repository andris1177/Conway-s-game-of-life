#include "../header/file.h"

void readFile(maps* map, simSpec* sSpec, windowSpec* wSpec)
{
    FILE* file = fopen(sSpec->iFile, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the input file. exiting...\n");
        freeAll();
        memReport();
        exit(ERROR_FILE);
    }

    char buffer[20];
    fgets(buffer, sizeof(buffer), file);
    char* out = strstr(buffer, "#GOLMAPFILE");
    if (out == NULL)
    {
        fprintf(stderr, "File without the required file signature is loaded. exiting...\n");
        freeAll();
        memReport();
        exit(ERROR_FILE);
    }

    int result = 0;
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %d", &wSpec->windowWidth);
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %d", &wSpec->windowHeight);
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %d", &wSpec->fps);
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %d", &map->width);
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %d", &map->height);
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %d", &sSpec->simLength);
    fgets(buffer, sizeof(buffer), file);
    result += sscanf(buffer, "%*s %lf", &sSpec->simSpeed);

    if (result != 7)
    {
        fprintf(stderr, "The file header is damaged or missing. exiting…\n");
        freeAll();
        memReport();
        exit(ERROR_FILE);
    }

    makeMap(map);

    size_t bufferSize = map->width + 3;
    char* row = safeMalloc(bufferSize * sizeof(char));
    for (int i = 0; i < map->height; i++)
    {
        fgets(row, bufferSize, file);
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

    safeFree(row);
    fclose(file);
}

void writeFile(const maps* map, const simSpec* sSpec, const windowSpec* wSpec)
{
    FILE* file = fopen(sSpec->oFile, "r");

    if (file == NULL)
    {
        printf("The exit file doesn't exist creating one.\n");
    }

    if (file != NULL)
    {
        char buffer[20];
        fgets(buffer, sizeof(buffer), file);
        char* out = strstr(buffer, "#GOLMAPFILE");
        
        if (out == NULL)
        {
            fprintf(stderr, "The exit file exists but doesn't contain the required file signature. Are you sure you didn't pass some other file? exiting...\n");
            freeAll();
            memReport();
            exit(ERROR_FILE);
        }

        else
        {
            printf("The exit file exists and is safe to erase and fill up with the new data.\n");
        }

        fclose(file);
    }

    file = fopen(sSpec->oFile, "w");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the output file. exiting...\n");
        deInitSim(map, sSpec, wSpec, false);
        exit(ERROR_FILE);
    }

    fprintf(file, "#GOLMAPFILE\n");
    fprintf(file, "windowWidth %d\n", wSpec->windowWidth);
    fprintf(file, "windowHeight %d\n", wSpec->windowHeight);
    fprintf(file, "fps %d\n", wSpec->fps);
    fprintf(file, "width %d\n", map->width);
    fprintf(file, "height %d\n", map->height);
    fprintf(file, "simCount %d\n", sSpec->simLength);
    fprintf(file, "simShowTime %g\n", sSpec->simSpeed);

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (map->preMap[i][j] == 0)
            {
                fprintf(file, ".");
            }

            else if (map->preMap[i][j] == 1)
            {
                fprintf(file, "x");
            }
        }

        fprintf(file, "\n");
    }

    fclose(file);
}