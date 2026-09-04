#include <stdlib.h>

#include "processing.h"

Image* grayscale(Image *img) {
    int total_pixels = img->width * img->height;
    for (int i = 0; i < total_pixels; i++) {
        Pixel *p = &img->pixels[i];
        // bar bar img->pixels[i].red eshob lekha lagbe,,, er che p->red lekha easier

        unsigned char gray = (unsigned char)(
            0.299 * p->red +
            0.587 * p->green +
            0.114 * p->blue );

        p->red   = gray;
        p->green = gray;
        p->blue  = gray;
    }
    return img;
}

Image* brightness(Image *img,int value) {
    int total_pixels = img->width * img->height;
    for (int i = 0; i < total_pixels; i++) {
        Pixel *p = &img->pixels[i];

        if(p->red + value >= 0 && p->red + value <= 255 )
            p->red = p->red + value ; //(*p).red

        if(p->green + value >= 0 && p->green + value <= 255 )
            p->green = p->green + value ;

        if(p->blue + value >= 0 && p->blue + value <= 255 )
            p->blue =  p->blue + value ;
    }
    return img;
}

Image* invert(Image *img){
    int total_pixels = img->width * img->height;
    for(int i = 0; i < total_pixels; i++){

        Pixel *p = &img->pixels[i];
        // bar bar img->pixels[i].red eshob lekha lagbe,,, er che p->red lekha easier

        p->red = 255 - p->red;
        p->green = 255 - p->green;
        p->blue = 255 - p->blue;
    }
    return img;
}

Image* horizontalFlip(Image *img){
    int width = img->width;
    int height = img->height;

    for(int i = 0; i < height ; i++){
        for(int j = 0; j < (width / 2 ); j++){
            int x = ( i * width ) + j;
            int y = ( (i +1) * width) - j - 1; // details on my notebook

            //Value swap
            Pixel p = img->pixels[x];
            img->pixels[x] = img->pixels[y];
            img->pixels[y] = p;
        }
    }
    return img;
}
Image* verticalFlip(Image *img){
    int width = img->width;
    int height = img->height;

    for(int i = 0; i < (height / 2); i++){ // half flip korlei hobe... full korle shb ager motoi hoye jabe
        for(int j = 0; j < width ; j++){ //but ekta row er shob element kei flip howa lagbe
            int x = ( i * width ) + j ; 
            int y = ( width * (height - i - 1) ) + j; // details on my notebook

            //value swap
            Pixel p = img->pixels[x];
            img->pixels[x] = img->pixels[y];
            img->pixels[y] = p;
        }
    }
    return img;
}

Image* rotate(Image *img){

    Image *imgNew = malloc(sizeof(Image)); //Rotate korar kaj ta new ekta chobi banaya oitar jonno kora lagbe

    imgNew->width = img->height; // Actual img er height hobe newimg er width
    imgNew->height = img->width; // Actual img er width hobe newimg er height 

    int total_pixels = imgNew->width * imgNew->height; 
    imgNew->pixels = malloc(total_pixels * sizeof(Pixel)); // sizeof pixel kora hoise karon er moddhe R G B ase... oitar space neua lagbe

    for(int i = 0; i < img->height ; i++){ //row wise
        for(int j = 0; j < img->width ; j++){ // column wise

            int oldIndex = i * img->width + j; 
            int newRow = j;
            int newCol = img->height - 1 - i;

            int newIndex = newRow * imgNew->width + newCol;
            imgNew->pixels[newIndex] = img->pixels[oldIndex];
        }
    }
    return imgNew;
}

// Details in my notebook
Image* crop(Image *img, int x, int y, int cropWidth, int cropHeight){
    Image *imgNew = malloc(sizeof(Image));

    imgNew->width = cropWidth;
    imgNew->height = cropHeight;
    imgNew->pixels = malloc(cropWidth * cropHeight * sizeof(Pixel));

    for (int i = 0; i < cropHeight; i++) {
        for (int j = 0; j < cropWidth; j++) {

            int oldIndex = (y + i) * img->width + (x + j);
            int newIndex = i * cropWidth + j;
            imgNew->pixels[newIndex] = img->pixels[oldIndex];
        }
    }
    return imgNew;
}

// Details in my notebook
Image* blur(Image *img){
    Image *imgNew = malloc(sizeof(Image));

    imgNew->width = img->width;
    imgNew->height = img->height;

    imgNew->pixels = malloc(
        imgNew->width * imgNew->height * sizeof(Pixel)
    );

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {

            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {

                    int row = i + di;
                    int col = j + dj;

                    if (row >= 0 && row < img->height &&
                        col >= 0 && col < img->width) {

                        int index = row * img->width + col;

                        red += img->pixels[index].red;
                        green += img->pixels[index].green;
                        blue += img->pixels[index].blue;

                        count++;
                    }
                }
            }
            int newIndex = i * imgNew->width + j;

            imgNew->pixels[newIndex].red = red / count;
            imgNew->pixels[newIndex].green = green / count;
            imgNew->pixels[newIndex].blue = blue / count;
        }
    }
    return imgNew;
}