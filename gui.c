#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

#include "gui.h"
#include "image.h"
#include "processing.h"

static Image *img = NULL;
static Image *undoImage = NULL;

static Ihandle *canvas;
static Ihandle *brightBox;
static Ihandle *cropX, *cropY, *cropW, *cropH;

static void showImage(void){
    if(img == NULL) return;
    Ihandle *ih = IupImageRGB(img->width, img->height, (unsigned char*)img->pixels);
    IupSetAttributeHandle(canvas, "IMAGE", ih);

    char size[32];
    sprintf(size, "%dx%d", img->width, img->height);
    IupSetAttribute(canvas, "RASTERSIZE", size);

    Ihandle *dlg = IupGetDialog(canvas);
    IupSetAttribute(dlg, "SIZE", NULL);   // clear the dialog's fixed size so it recomputes
    IupRefresh(dlg);                       // now recompute natural size AND resize the window
}

static void saveUndo(void){
    if(undoImage != NULL){
        freeImage(undoImage);
        undoImage = NULL;
    }
    undoImage = copyImage(img);
}

static int cb_open(Ihandle *self){
    Ihandle *dlg = IupFileDlg();
    IupSetAttribute(dlg, "DIALOGTYPE", "OPEN");
    IupSetAttribute(dlg, "EXTFILTER", "BMP Files|*.bmp|");
    IupPopup(dlg, IUP_CENTER, IUP_CENTER);

    if(IupGetInt(dlg, "STATUS") != -1){
        char *filename = IupGetAttribute(dlg, "VALUE");
        Image *newImg = loadImage(filename);
        if(newImg == NULL){
            IupMessage("Error!", "Unsupported or invalid BMP file!");
        } else {
            if(img != NULL) freeImage(img);
            if(undoImage != NULL){ freeImage(undoImage); undoImage = NULL; }
            img = newImg;
            showImage();
        }
    }
    IupDestroy(dlg);
    return IUP_DEFAULT;
}

static int cb_save(Ihandle *self){
    if(img == NULL){
        IupMessage("Error!", "No image loaded!");
        return IUP_DEFAULT;
    }
    Ihandle *dlg = IupFileDlg();
    IupSetAttribute(dlg, "DIALOGTYPE", "SAVE");
    IupSetAttribute(dlg, "EXTFILTER", "BMP Files|*.bmp|");
    IupPopup(dlg, IUP_CENTER, IUP_CENTER);

    if(IupGetInt(dlg, "STATUS") != -1){
        char *filename = IupGetAttribute(dlg, "VALUE");
        save_bmp(filename, img);
    }
    IupDestroy(dlg);
    return IUP_DEFAULT;
}

static int cb_grayscale(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    saveUndo();
    grayscale(img);
    showImage();
    return IUP_DEFAULT;
}

static int cb_invert(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    saveUndo();
    invert(img);
    showImage();
    return IUP_DEFAULT;
}

static int cb_hflip(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    saveUndo();
    horizontalFlip(img);
    showImage();
    return IUP_DEFAULT;
}

static int cb_vflip(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    saveUndo();
    verticalFlip(img);
    showImage();
    return IUP_DEFAULT;
}

static int cb_rotate(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    saveUndo();
    img = rotate(img);
    showImage();
    return IUP_DEFAULT;
}

static int cb_blur(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    saveUndo();
    img = blur(img);
    showImage();
    return IUP_DEFAULT;
}

static int cb_brightness(Ihandle *self){
    if(img == NULL){ IupMessage("Error!", "No image loaded!"); return IUP_DEFAULT; }
    int value;
    char *text = IupGetAttribute(brightBox, "VALUE");
    if(sscanf(text, "%d", &value) != 1){
        IupMessage("Error!", "Invalid brightness value!");
        return IUP_DEFAULT;
    }
    saveUndo();
    brightness(img, value);
    showImage();
    return IUP_DEFAULT;
}

static int cb_crop(Ihandle *self){
    if(img == NULL){ IupMessage("Error", "No image loaded!"); return IUP_DEFAULT; }
    int x = IupGetInt(cropX, "VALUE");
    int y = IupGetInt(cropY, "VALUE");
    int w = IupGetInt(cropW, "VALUE");
    int h = IupGetInt(cropH, "VALUE");

    if(x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > img->width || y + h > img->height){
        IupMessage("Error!", "Crop region is outside image boundaries!");
        return IUP_DEFAULT;
    }
    saveUndo();
    img = crop(img, x, y, w, h);
    showImage();
    return IUP_DEFAULT;
}

static int cb_undo(Ihandle *self){
    if(undoImage == NULL){
        IupMessage("Error", "Nothing to undo!");
        return IUP_DEFAULT;
    }
    img = undo(img, undoImage);
    undoImage = NULL;
    showImage();
    return IUP_DEFAULT;
}

static int cb_exit(Ihandle *self){
    return IUP_CLOSE;
}

Ihandle* buildInterface(void){
    Ihandle *btnOpen = IupButton("Open", NULL);
    IupSetCallback(btnOpen, "ACTION", (Icallback)cb_open);

    Ihandle *btnSave = IupButton("Save", NULL);
    IupSetCallback(btnSave, "ACTION", (Icallback)cb_save);

    Ihandle *btnGray = IupButton("Grayscale", NULL);
    IupSetCallback(btnGray, "ACTION", (Icallback)cb_grayscale);

    Ihandle *btnInvert = IupButton("Invert", NULL);
    IupSetCallback(btnInvert, "ACTION", (Icallback)cb_invert);

    Ihandle *btnHFlip = IupButton("H-Flip", NULL);
    IupSetCallback(btnHFlip, "ACTION", (Icallback)cb_hflip);

    Ihandle *btnVFlip = IupButton("V-Flip", NULL);
    IupSetCallback(btnVFlip, "ACTION", (Icallback)cb_vflip);

    Ihandle *btnRotate = IupButton("Rotate", NULL);
    IupSetCallback(btnRotate, "ACTION", (Icallback)cb_rotate);

    Ihandle *btnBlur = IupButton("Blur", NULL);
    IupSetCallback(btnBlur, "ACTION", (Icallback)cb_blur);

    Ihandle *btnUndo = IupButton("Undo", NULL);
    IupSetCallback(btnUndo, "ACTION", (Icallback)cb_undo);

    Ihandle *btnExit = IupButton("Exit", NULL);
    IupSetCallback(btnExit, "ACTION", (Icallback)cb_exit);

    brightBox = IupText(NULL);
    IupSetAttribute(brightBox, "VALUE", "0");
    Ihandle *btnBright = IupButton("Apply Brightness", NULL);
    IupSetCallback(btnBright, "ACTION", (Icallback)cb_brightness);

    cropX = IupText(NULL); IupSetAttribute(cropX, "VALUE", "0");
    cropY = IupText(NULL); IupSetAttribute(cropY, "VALUE", "0");
    cropW = IupText(NULL); IupSetAttribute(cropW, "VALUE", "100");
    cropH = IupText(NULL); IupSetAttribute(cropH, "VALUE", "100");
    Ihandle *btnCrop = IupButton("Apply Crop", NULL);
    IupSetCallback(btnCrop, "ACTION", (Icallback)cb_crop);

    canvas = IupLabel(NULL);

    Ihandle *toolbar = IupHbox(btnOpen, btnSave, btnGray, btnInvert, btnHFlip, btnVFlip, btnRotate, btnBlur, btnUndo, btnExit, NULL);
    Ihandle *brightRow = IupHbox(IupLabel("Brightness:"), brightBox, btnBright, NULL);
    Ihandle *cropRow = IupHbox(IupLabel("X:"), cropX, IupLabel("Y:"), cropY, IupLabel("W:"), cropW, IupLabel("H:"), cropH, btnCrop, NULL);

    Ihandle *vbox = IupVbox(toolbar, brightRow, cropRow, canvas, NULL);

    Ihandle *dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "Image Editing Software");
    IupSetAttribute(dlg, "SIZE", NULL);

    unsigned char testPixels[3*3*3];
    for(int i = 0; i < 3*3; i++){
        testPixels[i*3+0] = 255;
        testPixels[i*3+1] = 0;
        testPixels[i*3+2] = 0;
    }
    Ihandle *testImg = IupImageRGB(3, 3, testPixels);
    IupSetAttributeHandle(canvas, "IMAGE", testImg);
    IupSetAttribute(canvas, "RASTERSIZE", "200x200");

    return dlg;
}

void cleanupApp(void){
    if(img != NULL) freeImage(img);
    if(undoImage != NULL) freeImage(undoImage);
}

// Kept from the original single-file version: not currently wired to any
// callback, but preserved as-is so no behavior changes.
static void refreshDisplay(void) {
    if (img == NULL) return;

    Ihandle *ih = IupImageRGB(img->width, img->height, (unsigned char *)img->pixels);
    IupSetAttributeHandle(canvas, "IMAGE", ih);

    char size[32];
    sprintf(size, "%dx%d", img->width, img->height);
    IupSetAttribute(canvas, "RASTERSIZE", size);

    IupRefresh(canvas);
}
