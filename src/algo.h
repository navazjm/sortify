#ifndef SRT_ALGO_H
#define SRT_ALGO_H

typedef enum
{
    SRT_ALGO_BUBBLE,
    SRT_ALGO_SELECTION,
    SRT_ALGO_INSERTION,
    SRT_ALGO_MERGE,
    SRT_ALGO_QUICK,
} SRT_Algorithm;

/*
 * Get the name of the sorting algorithm
 *
 * @param algo Selected sorting algorithm enum value
 */
char *srt_algorithm_get_display_name(SRT_Algorithm algo);

#endif // SRT_ALGO_H
