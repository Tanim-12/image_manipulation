// ./build.sh imageeditor

#include <iup.h>

#include "gui.h"

int main(int argc, char **argv){
    IupOpen(&argc, &argv);

    Ihandle *dlg = buildInterface();

    IupShow(dlg);
    IupMainLoop();

    cleanupApp();

    IupClose();
    return 0;
}
