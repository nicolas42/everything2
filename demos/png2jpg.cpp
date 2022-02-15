// g++ png2jpg.cpp -I../include && ./a.out

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int main( int argc, char* argv[] )
{
    if (argc != 3) {
        printf("usage: png2jpg input_filename output_filename\n");
        exit(1);
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    int w, h, c;
    int channels = 0;
    unsigned char *data = stbi_load(input_filename, &w, &h, &c, channels);
    if (!data) {
        printf("ERROR %s:%d %s\n", __FILE__,__LINE__,stbi_failure_reason());
        exit(1);
    }


    int quality = 90;
    int success = stbi_write_jpg(output_filename, w, h, c, data, quality);
    if (!success) {
        printf("ERROR %s:%d %s\n", __FILE__,__LINE__,stbi_failure_reason());
        exit(1);
    }


    return 0;
}









#include <string.h>


int convert_to_other_formats( int argc, char* argv[] )
{
    if (argc != 4) {
        printf("usage: convert_image <format> input_filename output_filename\n");
        exit(1);
    }

    const char *format = argv[1]; // jpg
    const char *input_filename = argv[2]; // "lenna.png";
    const char *output_filename = argv[3]; // "converted_lenna.jpg";
    FILE *file = fopen(output_filename,"r");
    if (file) { 
        printf("ERROR %s %d output file already exists.\n", __FILE__, __LINE__ );
        return 1;
    }

    int w, h, c;
    int channels = 0;
    unsigned char *data = stbi_load(input_filename, &w, &h, &c, channels);
    if (!data) {
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n",
            input_filename, stbi_failure_reason());
        exit(0);
    }

    // // just jpg output
    // int success = 0;
    // int quality = 90;
    // success = stbi_write_jpg(output_filename, w, h, c, data, quality);
    // if (!success) {
    //     fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n",
    //         input_filename, stbi_failure_reason());
    //     exit(0);
    // }




    int success = 0;

    if ( !strcmp( format, "png" ) ) {
        int stride_in_bytes = w*c; // width of a row in bytes.
        //  int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
        success = stbi_write_png( output_filename, w, h, c, data, stride_in_bytes );
    }
    else if ( !strcmp( format, "bmp" ) ) {
        //  int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
        success = stbi_write_bmp( output_filename, w, h, c, data );
    }
    else if ( !strcmp( format, "tga" ) ) {
        // int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
        success = stbi_write_tga( output_filename, w, h, c, data );
    }
    else if ( !strcmp( format, "jpg" ) ) {
        int quality = 90;
        // int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
        success = stbi_write_jpg( output_filename, w, h, c, data, quality );
    }
    // if ( !strcmp( format, "hdr" ) ) {
    //     // int stbi_write_hdr(char const *filename, int w, int h, int comp, const float *data);
    //     success = stbi_write_hdr( output_filename, w, h, c, data );
    // }

    if (!success) {
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n",
            input_filename, stbi_failure_reason());
        exit(0);
    }


    return 0;
}




// Limitations:
//    - no 12-bit-per-channel JPEG
//    - no JPEGs with arithmetic coding
//    - GIF always returns *comp=4
//
// Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)
//
// Standard parameters:
//    int *x                 -- outputs image width in pixels
//    int *y                 -- outputs image height in pixels
//    int *channels_in_file  -- outputs # of image components in image file
//    int desired_channels   -- if non-zero, # of image components requested in result

// int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
// int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
// int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
// int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
// int stbi_write_hdr(char const *filename, int w, int h, int comp, const float *data);

