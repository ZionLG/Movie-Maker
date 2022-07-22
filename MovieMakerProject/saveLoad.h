#ifndef SAVELOADH
#define SAVELOADH
#include "LinkedList.h"
#include <stdio.h>

void saveToFile(FrameNode* frameHead, char filePath[]);
void loadFromFile(FrameNode** frameHead, char filePath[]);
#endif