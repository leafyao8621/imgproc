#include <stdio.h>
#include <stdlib.h>
#include <png.h>

static void calculate_hist(unsigned char *buf, int *hist) {

}

int core_hist(const char* fn, int *hist) {
    if (!fn || !hist) {
        return 1;
    }
    FILE *fin = fopen(fn, "rb");
    if (!fin) {
        return 2;
    }
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info = png_create_info_struct(png);
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    png_init_io(png, fin);
    png_set_sig_bytes(png, 0);
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
    png_bytep *row_ptr_buf = malloc(height * sizeof(png_bytep));
    unsigned char *buf = malloc(height * width * 3);
    png_bytep *iter_rpb  = row_ptr_buf;
    unsigned char *iter_b = buf;
    for (int i = 0; i < height; ++i, ++iter_rpb, iter_b += width * 3) {
        *iter_rpb = iter_b;
    }
    png_read_image(png, row_ptr_buf);
    png_destroy_read_struct(&png, &info, 0);
    fclose(fin);
    free(row_ptr_buf);
    calculate_hist(buf, hist);
    free(buf);
    return 0;
}
