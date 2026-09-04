#include <stdio.h>
#include <iup.h>

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);

    Ihandle *button1 = IupButton("Hello, IUP!", NULL);
    Ihandle *button2 = IupButton("Click Me Too!", NULL);

    Ihandle *vbox = IupVbox(button1, button2, NULL);
    IupSetAttribute(vbox, "MARGIN", "10x10");
    IupSetAttribute(vbox, "GAP", "10");

    Ihandle *dialog = IupDialog(vbox);

    IupSetAttribute(dialog, "TITLE", "Two Buttons Test");
    IupSetAttribute(dialog, "SIZE", "200x150");

    IupShow(dialog);
    IupMainLoop();

    IupClose();
    return 0;
}
