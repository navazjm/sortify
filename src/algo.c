#include "algo.h"

char *srt_algorithm_get_display_name(SRT_Algorithm algo)
{
    switch (algo)
    {
    case SRT_ALGO_BUBBLE:
        return "Bubble Sort";
    case SRT_ALGO_SELECTION:
        return "Selection Sort";
    case SRT_ALGO_INSERTION:
        return "Insertion Sort";
    case SRT_ALGO_MERGE:
        return "Merge Sort";
    case SRT_ALGO_QUICK:
        return "Quick Sort";
    default:
        return "Unknown Sorting Alogrithm";
    }
}
