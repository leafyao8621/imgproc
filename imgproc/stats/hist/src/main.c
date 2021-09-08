#include "core/core.h"

int main(int argc, const char **argv) {
    int hist[256];
    core_hist("~/temp/badapple/frames/badapple0001.png", hist);
    return 0;
}
