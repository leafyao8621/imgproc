#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

static void calculate_hist(size_t len,
                           unsigned char *buf,
                           unsigned int *hist,
                           unsigned int *histr,
                           unsigned int *histg,
                           unsigned int *histb) {
    memset(hist, 0, 256 * sizeof(unsigned int));
    memset(histr, 0, 256 * sizeof(unsigned int));
    memset(histg, 0, 256 * sizeof(unsigned int));
    memset(histb, 0, 256 * sizeof(unsigned int));
    unsigned char *iter = buf;
    for (png_uint_32 i = 0; i < len; ++i) {
        ++histr[*iter];
        ++histg[iter[1]];
        ++histb[iter[2]];
        unsigned char val = *(iter++);
        for (char j = 0; j < 2; ++j, ++iter) {
            if (val < *iter) {
                val = *iter;
            }
        }
        ++hist[val];
    }
}

int core_hist(const char* fn,
              unsigned int *hist,
              unsigned int *histr,
              unsigned int *histg,
              unsigned int *histb) {
    if (!fn || !hist) {
        return 1;
    }
    FILE *fin = fopen(fn, "rb");
    if (!fin) {
        return 2;
    }

    char header[8];
    fread(header, 1, 8, fin);

    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
        fclose(fin);
        return 3;
    }
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info = png_create_info_struct(png);
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    png_init_io(png, fin);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);
    png_get_IHDR(png,
                 info,
                 &width,
                 &height,
                 &bit_depth,
                 &color_type,
                 &interlace_type,
                 NULL,
                 NULL);
    if (color_type & PNG_COLOR_MASK_ALPHA) {
        png_set_strip_alpha(png);
    }
    png_bytep *row_ptr_buf = malloc(height * sizeof(png_bytep));
    unsigned char *buf = malloc((size_t)height * width * 3);
    png_bytep *iter_rpb  = row_ptr_buf;
    unsigned char *iter_b = buf;
    for (int i = 0; i < height; ++i, ++iter_rpb, iter_b += width * 3) {
        *iter_rpb = iter_b;
    }
    png_read_image(png, row_ptr_buf);
    png_destroy_read_struct(&png, &info, 0);
    fclose(fin);
    free(row_ptr_buf);
    calculate_hist(width * height,
                   buf,
                   hist,
                   histr,
                   histg,
                   histb);
    free(buf);
    return 0;
}
