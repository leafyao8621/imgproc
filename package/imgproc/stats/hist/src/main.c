#include <stdio.h>
#include "core/core.h"

int main(int argc, const char **argv) {
    unsigned int hist[256];
    unsigned int histr[256];
    unsigned int histg[256];
    unsigned int histb[256];
    core_hist(argv[1], hist, histr, histg, histb);
    for (unsigned int i = 0,
         *iter = hist,
         *iterr = histr,
         *iterg = histg,
         *iterb = histb;
         i < 256;
         ++i,
         ++iter,
         ++iterr,
         ++iterg,
         ++iterb) {
        printf("%3d: %d %d %d %d\n", i, *iter, *iterr, *iterg, *iterb);
    }
    return 0;
}
