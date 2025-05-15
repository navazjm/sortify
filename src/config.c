#include "config.h"
#include "algo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CONFIG_DIR_PATH "/.config/sortify/"

/*
 * Creates the $HOME/.config/sortify directory if it does NOT exist.
 *
 */
static void ensure_config_dir_exists()
{
    const char *home_dir = getenv("HOME");
    if (!home_dir)
        return;

    size_t len = strlen(home_dir) + strlen(CONFIG_DIR_PATH) + 1;
    char *full_path = (char *)malloc(len);
    if (full_path)
    {
        snprintf(full_path, len, "%s%s", home_dir, CONFIG_DIR_PATH);
        mkdir(full_path, 0755); // Only creates if it doesn't exist
        free(full_path);
    }
}

/*
 * Returns the full path to the sortify.ini file ($HOME/.config/sortify/sortify.ini)
 *
 * @param filename ini filename to include in the full path.
 */
static char *get_config_path(const char *filename)
{
    const char *home_dir = getenv("HOME");
    if (!home_dir)
        return NULL;

    size_t len = strlen(home_dir) + strlen(CONFIG_DIR_PATH) + strlen(filename) + 1;
    char *full_path = (char *)malloc(len);
    if (full_path)
    {
        snprintf(full_path, len, "%s%s%s", home_dir, CONFIG_DIR_PATH, filename);
    }
    return full_path;
}

void srt_config_setup(SRT_Config *cfg)
{
    cfg->algo = SRT_ALGO_BUBBLE;
    cfg->animation_delay = 0;
    cfg->arr_size = 100;
    cfg->is_sound_on = true;
    cfg->is_compare_algo = false;
    cfg->algo_sec = SRT_ALGO_SELECTION;
    cfg->ini_path = get_config_path("sortify.ini");

    ensure_config_dir_exists();
}

void srt_config_teardown(SRT_Config *cfg)
{
    if (cfg->ini_path)
        free(cfg->ini_path);
}
