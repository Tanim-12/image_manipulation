#ifndef PROCESSING_H
#define PROCESSING_H

#include "image.h"

Image* grayscale(Image *img);
Image* brightness(Image *img, int value);
Image* invert(Image *img);
Image* horizontalFlip(Image *img);
Image* verticalFlip(Image *img);
Image* rotate(Image *img);
Image* crop(Image *img, int x, int y, int cropWidth, int cropHeight);
Image* blur(Image *img);

#endif
