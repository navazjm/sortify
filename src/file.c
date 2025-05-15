#include "file.h"
#include <stdio.h>

bool srt_file_exists(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}
