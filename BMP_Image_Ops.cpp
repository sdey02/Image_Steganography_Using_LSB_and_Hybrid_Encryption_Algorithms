#include <stdio.h>
#include <iostream>
#include <string>

#define data_offset {0x0A};
#define width_offset {0x12};
#define height_offset {0x16};
#define bits_per_pixel_offset {0x1C};


void read_bmp(const char *bmp_image_location, unsigned char **pixels, int32_t *width, int32_t *height, int32_t *bytesPerPixel){
    FILE *bmp_image = fopen(bmp_image_location, "rb");

    int32_t dataOffset;
    fseek (bmp_image, data_offset, SEEK_SET);
    fread (&dataOffset, 4, 1, bmp_image);

    fseek (bmp_image, width_offset, SEEK_SET);
    fread (width, 4, 1, bmp_image);

    fseek (bmp_image, height_offset, SEEK_SET);
    fread (height, 4, 1, bmp_image);

    int16_t bitsPerPixel;
    fseek (bmp_image, bits_per_pixel_offset, SEEK_SET);
    fread (&bitsPerPixel, 2, 1, bmp_image);


    int * last_byte = (*height * *width) * bits_per_pixel 
}