#ifndef GUI_H
#define GUI_H

#include <iup.h>

// Builds the full IUP interface (toolbar, controls, canvas) and returns
// the top-level dialog handle, ready to be shown by main().
Ihandle* buildInterface(void);

// Frees any image data still held by the GUI (called after IupMainLoop
// returns, before IupClose()).
void cleanupApp(void);

#endif
