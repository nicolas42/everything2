// Usage:
// gcc my_main.c ; ./a.out; open out.png

/* Created By: Justin Meiners (2013) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

#define STB_TRUETYPE_IMPLEMENTATION 
#include "stb_truetype.h" /* http://nothings.org/stb/stb_truetype.h */



int main(int argc, const char * argv[])
{
    /* load font file */
    long font_buffer_size;
    unsigned char* font_buffer;
    stbtt_fontinfo font_info;

    {
        FILE* font_file = fopen("font/cmunrm.ttf", "rb");
        fseek(font_file, 0, SEEK_END);
        font_buffer_size = ftell(font_file); /* how long is the file ? */
        fseek(font_file, 0, SEEK_SET); /* reset */
        font_buffer = malloc(font_buffer_size);
        fread(font_buffer, font_buffer_size, 1, font_file);
        fclose(font_file);

        if (!stbtt_InitFont(&font_info, font_buffer, 0))
        {
            printf("failed\n");
        }
    }

    int bitmap_width = 1000;
    int bitmap_height = 128;
    int line_height = 64;
    unsigned char* bitmap = calloc(bitmap_width * bitmap_height, sizeof(unsigned char));

    char* the_text = "I know how to render text.  Woah.";

    {    
        /* calculate font scaling */
        float scale = stbtt_ScaleForPixelHeight(&font_info, line_height);
        int x = 0;



        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &lineGap);
        
        ascent = roundf(ascent * scale);
        descent = roundf(descent * scale);
        
        int i;
        for (i = 0; i < strlen(the_text); ++i)
        {
            /* how wide is this character */
            int ax;
            int lsb;
            stbtt_GetCodepointHMetrics(&font_info, the_text[i], &ax, &lsb);

            /* get bounding box for character (may be offset to account for chars that dip above or below the line */
            int c_x1, c_y1, c_x2, c_y2;
            stbtt_GetCodepointBitmapBox(&font_info, the_text[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
            
            /* compute y (different characters have different heights */
            int y = ascent + c_y1;
            
            /* render character (stride and offset is important here) */
            int byteOffset = x + roundf(lsb * scale) + (y * bitmap_width);
            stbtt_MakeCodepointBitmap(&font_info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, bitmap_width, scale, scale, the_text[i]);

            /* advance x */
            x += roundf(ax * scale);
            
            /* add kerning */
            int kern;
            kern = stbtt_GetCodepointKernAdvance(&font_info, the_text[i], the_text[i + 1]);
            x += roundf(kern * scale);
        }
    }



    /* save out a 1 channel image */
    stbi_write_png("out.png", bitmap_width, bitmap_height, 1, bitmap, bitmap_width);
    
    free(font_buffer);
    free(bitmap);
    
    return 0;
}

