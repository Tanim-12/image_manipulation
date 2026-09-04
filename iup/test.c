#include <stdio.h>
#include <iup.h>

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);

    Ihandle *button = IupButton("Hello, IUP!", NULL);
    Ihandle *dialog = IupDialog(button);

    IupSetAttribute(dialog, "TITLE", "IUP Test");
    IupSetAttribute(dialog, "SIZE", "200x100");

    IupShow(dialog);
    IupMainLoop();

    IupClose();
    return 0;
}
