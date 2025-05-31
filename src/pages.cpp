#include "pages.h"

void handleReadme() {
  server.send(200, "text/html", PAGE_readme);
}

void handleRoot() {
  server.send(200, "text/html", PAGE_root);
}

void handleBonsoir() {
  server.send(200, "text/html", PAGE_bonsoir);
}

void handleControls() {
    server.send(200, "text/html", PAGE_controls);
}