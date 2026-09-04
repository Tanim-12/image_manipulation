#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image* loadImage(const char *filename) {

    int width, height, channels; // channel mane hoilo prottek pixel e koyta color component ase
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);
    /* eikhane 3 mane ami 3ta color component nite chai
    data namer array RGB hoye ashbe, mane 3 byte/pixel...[R][G][B]
    ekhane main chobi te koyta ase oita channels e store hobe
    but amra oitake ignore kortesi... */

    //Image load hoise kina check kore nilam
    if (data == NULL) {
        printf("Image load failed: %s\n", filename);
        return NULL;
    }
    //new ekta struct type er pointer banaisi, jeta malloc use kore space nisi
    Image *img = malloc(sizeof(Image));
    img->width = width; //input deua chobir width & height ekhane (*img).width e save hobe
    img->height = height;
    img->pixels = malloc(width * height * sizeof(Pixel)); //pixel array r jonno size nise w * h * Pixel struct

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            int srcIndex = (row * width + col) * 3;   // stb_image er raw data array te ei pixel er red koi ase
            int dstIndex = row * width + col;          //eta amader Pixel array er index

            Pixel *p = &img->pixels[dstIndex];

            p->red   = data[srcIndex + 0];
            p->green = data[srcIndex + 1];
            p->blue  = data[srcIndex + 2];
        }
    }
    stbi_image_free(data);
    return img;
}

Image* copyImage(Image *img){
    Image *copy = malloc(sizeof(Image));

    copy->width = img->width;
    copy->height = img->height;

    int total_pixels = img->width * img->height;

    copy->pixels = malloc(total_pixels * sizeof(Pixel));

    for (int i = 0; i < total_pixels; i++) {
        copy->pixels[i] = img->pixels[i];
    }

    return copy;
}

Image* undo(Image *img, Image *undoImage){
    if (undoImage == NULL)
        return img;

    free(img->pixels);
    free(img);

    return undoImage;
}

void save_bmp(const char *filename, Image *img) {
    stbi_write_bmp(filename, img->width, img->height, 3, img->pixels);
}

void freeImage(Image *img) {
    free(img->pixels);
    free(img);
}
