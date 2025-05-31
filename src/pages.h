#include "pages/PAGE_root.h"
#include "pages/PAGE_readme.h"
#include "pages/PAGE_bonsoir.h"
#include "pages/PAGE_controls.h"
#include "pages/PAGE_settings.h"

#ifndef PAGES_H
#define PAGES_H

#include "serv.h"

void handleReadme();
void handleRoot();
void handleBonsoir();
void handleControls();
void handleSettings();

#endif
