#include <stdio.h>
#include <iup.h>

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);

    Ihandle *label = IupLabel("This is a label!");

    Ihandle *dialog = IupDialog(label);
    IupSetAttribute(dialog, "TITLE", "Label Test");
    IupSetAttribute(dialog, "SIZE", "200x100");

    IupShow(dialog);
    IupMainLoop();

    IupClose();
    return 0;
}
