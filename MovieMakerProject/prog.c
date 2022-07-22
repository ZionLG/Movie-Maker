#include <stdio.h>
#include "linkedList.h"
#include "view.h"
#include "saveLoad.h"


#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>

void myFgets(char str[], int n);
int getNumber();
void createFrameInput(FrameNode** headFrame);
void changeFrameDurationInput(FrameNode* headFrame);
void changeAllFramesDurationInput(FrameNode* headFrame);
void removeFrameInput(FrameNode** headFrame);
void changeFrameIndexInput(FrameNode** headFrame);
void saveProjectInput(FrameNode* headFrame);
void loadProjectInput(FrameNode** headFrame);
void freeList(FrameNode** head);

void clearBuffer(void);

int main(void)
{
    int choice = -1;
    FrameNode* headFrame = NULL;
	printf("\nWelcome to Liran's Movie Maker! what would you like to do?\n");
	printf("----------------------------------------------------------\n");
	printf(" [0] Create a new project\n");
	printf(" [1] Load existing project\n");

    choice = getNumber();
    clearBuffer();

    if (choice == 1)
    {
        loadProjectInput(&headFrame);
    }

    choice = -1;
	while (choice != 0)
	{
        printf("\n\tWhat would you like to do?\n");
        printf("------------------------------------------\n");
        printf(" [0] Exit\n");
        printf(" [1] Add new Frame\n");
        printf(" [2] Remove a Frame\n");
        printf(" [3] Change frame index\n");
        printf(" [4] Change frame duration\n");
        printf(" [5] Change duration of all frames\n");
        printf(" [6] List frames\n");
        printf(" [7] Play movie!\n");
        printf(" [8] Save project\n");

        choice = getNumber();
        clearBuffer();

        switch (choice)
        {
        case 0:
            printf("Goodbye!");
            break;
        case 1:
            createFrameInput(&headFrame);
            break;
        case 2:
            removeFrameInput(&headFrame);
            break;
        case 3:
            changeFrameIndexInput(&headFrame);
            break;
        case 4:
            changeFrameDurationInput(headFrame);
            break;
        case 5:
            changeAllFramesDurationInput(headFrame);
            break;
        case 6:
            printFrames(headFrame);
            break;
        case 7:
            play(headFrame);
            break;
        case 8:
            saveProjectInput(headFrame);
            break;
        default:
            printf("\nInvalid choice, please try again.\n");
            break;
        }
	}

    freeList(&headFrame);
    getchar();
	return 0;
}

/// <summary>
/// Gets the path from the user and fires the load function
/// </summary>
/// <param name="headFrame"></param>
void loadProjectInput(FrameNode** headFrame) {

    char path[STR_LEN] = { 0 };

    printf("\n Please Insert path:\n");
    printf("\n --> ");
    myFgets(path, STR_LEN);

    loadFromFile(headFrame, path);

    printf("\nFile Loaded.\n");
}


/// <summary>
/// Gets the path from the user and fires the save function
/// </summary>
/// <param name="headFrame"></param>
void saveProjectInput(FrameNode* headFrame)
{
    char path[STR_LEN] = { 0 };

    printf("\n\n---------------------------------------\n\n");
    printf("\tSave Project\n");
    printf("\n---------------------------------------\n\n");

    printf("\n Please Insert path:\n");
    printf("\n --> ");
    myFgets(path, STR_LEN);

    saveToFile(headFrame, path);

    printf("\nFile saved.\n");
}


/// <summary>
/// Gets the path and new location from the user and fires the change index function
/// </summary>
/// <param name="headFrame"></param>
void changeFrameIndexInput(FrameNode** headFrame)
{
    char name[STR_LEN] = { 0 };
    int newLocation = 0;

    printf("\n\n---------------------------------------\n\n");
    printf("\tChange Frame Index\n");
    printf("\n---------------------------------------\n\n");

    printf("\n Please Insert frame name to change:\n");
    printf("\n --> ");
    myFgets(name, STR_LEN);

    printf("\n Please Insert the new location for the frame:\n");
    newLocation = getNumber();

    changeFrameIndex(headFrame, name, newLocation);
}


/// <summary>
/// Gets the new ducation and frame name from the user and fires the 
/// change duration function
/// </summary>
/// <param name="headFrame"></param>
void changeFrameDurationInput(FrameNode* headFrame)
{
    char name[STR_LEN] = { 0 };
    int newDuration = 0;

    printf("\n\n---------------------------------------\n\n");
    printf("\change frame duration\n");
    printf("\n---------------------------------------\n\n");

    printf("\n Please Insert frame name:\n");
    printf("\n --> ");
    myFgets(name, STR_LEN);

    if (!isTakenName(headFrame, name))
    {
        printf("\n Frame doesn't exist\n");
        return;
    }


    printf("\n Please Insert the new duration:\n");
    newDuration = getNumber();

    while (newDuration <= 0)
    {
        printf(" invalid duration! Enter a number higher than 0:\n");
        newDuration = getNumber();
    }

    
    changeDuration(headFrame, name, newDuration);
}


/// <summary>
/// Gets the new duration from the user and fires the change all duration function
/// </summary>
/// <param name="headFrame"></param>
void changeAllFramesDurationInput(FrameNode* headFrame) {
    int newDuration = 0;

    printf("\n\n---------------------------------------\n\n");
    printf("\change all frames duration\n");
    printf("\n---------------------------------------\n\n");

    printf("\n Please Insert the new duration:\n");
    newDuration = getNumber();

    while (newDuration <= 0)
    {
        printf(" invalid duration! Enter a number higher than 0:\n");
        newDuration = getNumber();
    }


    changeAllDuration(headFrame, newDuration);
}

/// <summary>
/// Gets the frame name to remove, then calls the remove frame function
/// </summary>
/// <param name="headFrame"></param>
void removeFrameInput(FrameNode** headFrame)
{
    char name[STR_LEN] = { 0 };

    printf("\n\n---------------------------------------\n\n");
    printf("\tRemove a frame\n");
    printf("\n---------------------------------------\n\n");

    printf("\n Please Insert frame name:\n");
    printf("\n --> ");
    myFgets(name, STR_LEN);

    if (!isTakenName(*headFrame, name))
    {
        printf("\n Frame doesn't exist\n");
        return;
    }

    removeFrame(headFrame, name);
}

void clearBuffer(void)
{
    while (getchar() != '\n');
}


/// <summary>
/// Gets all the input from the user
/// in order to create a framem makes it frameNode and then add it
/// to the headFrame Node.
/// </summary>
/// <param name="headFrame"></param>
void createFrameInput(FrameNode** headFrame)
{
    char path[STR_LEN] = { 0 };
    char name[STR_LEN] = { 0 };
    int duration = 0;

    printf("\n\n---------------------------------------\n\n");
    printf("\tCreate a new frame\n");
    printf("\n---------------------------------------\n\n");

    printf(" Please Insert frame path:\n");
    printf("\n --> ");
    myFgets(path, STR_LEN);

    while (!isValidPath(path))
    {
        printf(" invalid path! Enter a valid path:\n");
        printf("\n --> ");
        myFgets(path, STR_LEN);
    }

    printf("\n Please Insert frame name:\n");
    printf("\n --> ");
    myFgets(name, STR_LEN);

    while (isTakenName(*headFrame, name))
    {
        printf(" invalid path! Enter a unique name:\n");
        printf("\n --> ");
        myFgets(name, STR_LEN);
    }

    printf("\n Please Insert duration for the frame:\n");
    duration = getNumber();

    while (duration <= 0)
    {
        printf(" invalid duration! Enter a number higher than 0:\n");
        duration = getNumber();
    }

    insertFrameAtEnd(headFrame, createFrameNode(createFrame(name, duration, path)));
}

int getNumber()
{
    int num = 0;
    printf("\n --> ");
    scanf("%d", &num);
    return num;
}

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
input: the buffer to read into, the number of chars to read
*/
void myFgets(char str[], int n)
{
    fgets(str, n, stdin);
    str[strcspn(str, "\n")] = 0;
}


/// <summary>
/// Frees all the frameNodes
/// </summary>
/// <param name="head"></param>
void freeList(FrameNode** head)
{
    FrameNode* curr = *head;
    FrameNode* temp = NULL;
    while (curr)
    {
        temp = curr->next;
        free(curr->frame);
        free(curr);
        curr = temp;
    }
    *head = NULL;
}
