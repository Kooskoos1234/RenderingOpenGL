#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <string>
#include "Typedefs.h"

unsigned int loadPNG(std::string name);
void prepareTextures(uint count, uint* texture);

#endif