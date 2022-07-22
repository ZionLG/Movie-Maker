
#include "linkedList.h"


Frame* createFrame(char name[], int duration, char path[])
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame));

	if (!newFrame)
	{
		printf("failed to allocate memory.\n");
		exit(1);
	}

	strncpy(newFrame->name, name, STR_LEN);
	strncpy(newFrame->path, path, STR_LEN);
	newFrame->duration = duration;

	return newFrame;
}

/// <summary>
/// Checks if the given path is valid and can be opened.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
int isValidPath(char path[])
{
	FILE* file;
	if ((file = fopen(path, "rb")))
	{
		fclose(file);
		return 1;
	}

	return 0;
}


FrameNode* createFrameNode(Frame* frame)
{
	FrameNode* newFrameNode = (FrameNode*)malloc(sizeof(FrameNode));

	if (!newFrameNode)
	{
		printf("failed to allocate memory.\n");
		exit(1);
	}

	newFrameNode->frame = frame;
	newFrameNode->next = NULL;

	return newFrameNode;
}

void insertFrameAtEnd(FrameNode** headFrame, FrameNode* newFrame)
{
	if (!*headFrame)
	{
		*headFrame = newFrame;
	}
	else
	{
		FrameNode* head = *headFrame;
		while (head->next)
		{
			head = head->next;
		}
		head->next = newFrame;
	}
}

void removeFrame(FrameNode** headFrame, char name[])
{
	FrameNode* curr = *headFrame;
	FrameNode* dNode = NULL;

	if (*headFrame)
	{
		if (0 == strcmp((*headFrame)->frame->name, name))
		{
			*headFrame = (*headFrame)->next;
			free(curr->frame);
			free(curr);
		}
		else {
			while (curr->next &&
				   0 != strcmp(curr->next->frame->name, name))
			{
				curr = curr->next;
			}
			if (curr->next)
			{
				dNode = curr->next;
				curr->next = dNode->next;
				free(dNode->frame);
				free(dNode);
			}
		}
	}
}

/// <summary>
/// Goes through all the framenodes, searches for the one with the given
/// name and the one in the new location, also saves the one before them.
/// then, depends on if the first frame was chosen (to be changed or be changed to)
/// or if any other node (which depends if its changing backwards or forwards)
/// it changes the nodes before them and after them. 
/// </summary>
/// <param name="headFrame"></param>
/// <param name="name"></param>
/// <param name="newLocation"></param>
void changeFrameIndex(FrameNode** headFrame, char name[], int newLocation)
{
	FrameNode* curr = *headFrame;
	FrameNode* newIndexFrame = NULL;
	FrameNode* beforeNewIndexFrame = NULL;

	FrameNode* oldLocationFrame = NULL;
	FrameNode* beforeOldLocationFrame = NULL;
	int before = FALSE;
	int count = 0;

	while (curr)
	{
		count++;
		
		if (curr == *headFrame &&
			0 == strcmp(curr->frame->name, name))
		{
			oldLocationFrame = curr;
		}
		else if (curr->next &&
			0 == strcmp(curr->next->frame->name, name))
		{
			beforeOldLocationFrame = curr;
			oldLocationFrame = curr->next;
		}


		if (count == 1 == newLocation)
		{
			newIndexFrame = curr;
			before = TRUE;
		}
		else if (count + 1 == newLocation)
		{
			beforeNewIndexFrame = curr;
			if (curr->next)
				newIndexFrame = curr->next;

			if (!oldLocationFrame)
				before = TRUE;
		}

		curr = curr->next;
	}

	if (newIndexFrame == NULL || oldLocationFrame == NULL)
	{
		printf("Location given is bigger then the size of the node or the frame name doesnt exists");
		return;
	}

	if (beforeOldLocationFrame && beforeNewIndexFrame && before) {
		beforeOldLocationFrame->next = oldLocationFrame->next;
		oldLocationFrame->next = beforeNewIndexFrame->next;
		beforeNewIndexFrame->next = oldLocationFrame;
	}
	else if (beforeOldLocationFrame && beforeNewIndexFrame)
	{
		beforeOldLocationFrame->next = oldLocationFrame->next;
		oldLocationFrame->next = newIndexFrame->next;
		newIndexFrame->next = oldLocationFrame;
	}
	else if (before && beforeOldLocationFrame)
	{
		*headFrame = oldLocationFrame;
		beforeOldLocationFrame->next = oldLocationFrame->next;
		oldLocationFrame->next = newIndexFrame;
	}
	else
	{
		*headFrame = oldLocationFrame->next;
		oldLocationFrame->next = newIndexFrame->next;
		newIndexFrame->next = oldLocationFrame;
	}


}

void changeDuration(FrameNode* headFrame, char name[], int newDuration)
{
	FrameNode* curr = headFrame;

	while (curr &&
		0 != strcmp(curr->frame->name, name))
	{
		curr = curr->next;
	}

	if (curr)
	{
		curr->frame->duration = newDuration;
	}
}

void changeAllDuration(FrameNode* headFrame, int newDuration)
{
	FrameNode* curr = headFrame;

	while (curr)
	{
		curr->frame->duration = newDuration;
		curr = curr->next;
	}
}

int isTakenName(FrameNode* headFrame, char name[])
{
	FrameNode* curr = headFrame;

	while (curr &&
		0 != strcmp(curr->frame->name, name))
	{
		curr = curr->next;
	}

	if (curr)
	{
		return TRUE;
	}

	return FALSE;
}


void printFrames(FrameNode* headFrame)
{
	FrameNode* curr = headFrame;

	printf("\t\t%-10s%-10s%-10s\n\n", "Name", "Duration", "Path");

	while (curr)
	{
		printf("\t\t%-10s%-10d%-10s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}

}