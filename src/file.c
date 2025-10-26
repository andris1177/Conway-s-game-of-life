#include "../header/file.h"

void readFile(maps map, const char* fName)
{
    FILE* file;

    file = fopen(fName, "r");

    char row[256];

    while(fgets(row, sizeof(row, file)))
    {
        printf("%s", row);
    }

    fclose(file);
}