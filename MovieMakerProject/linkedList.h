#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define STR_LEN 100
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// Frame struct
typedef struct Frame
{
	char name[STR_LEN];
	unsigned int duration;
	char path[STR_LEN];
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;


Frame* createFrame(char name[], int duration, char path[]);
FrameNode* createFrameNode(Frame* frame);
void insertFrameAtEnd(FrameNode** headFrame, FrameNode* newFrame);
void removeFrame(FrameNode** headFrame, char name[]);
int isTakenName(FrameNode* headFrame, char name[]);
void printFrames(FrameNode* headFrame);
void changeDuration(FrameNode* headFrame, char name[], int newDuration);
void changeFrameIndex(FrameNode** headFrame, char name[], int newLocation);
void changeAllDuration(FrameNode* headFrame, int newDuration);
int isValidPath(char path[]);

#endif
