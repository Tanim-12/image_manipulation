#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel *pixels;
} Image;

Image* loadImage(const char *filename);
Image* copyImage(Image *img);
Image* undo(Image *img, Image *undoImage);
void save_bmp(const char *filename, Image *img);
void freeImage(Image *img);

#endif
