/*********************************
* Class: MAGSHIMIM Final Project *
* Save and Load Functions	 	 *
**********************************/

#include "saveLoad.h"


/// <summary>
/// Saves the current frameNode to a given filePath.
/// </summary>
/// <param name="frameHead"></param>
/// <param name="filePath"></param>
void saveToFile(FrameNode* frameHead, char filePath[]) {
	FILE* file = fopen(filePath, "w");

	if (!file)
	{
		exit(1);
	}

	for (FrameNode* curr = frameHead; curr != NULL; curr = curr->next) {
		fprintf(file, "%s, %s, %d, ", curr->frame->path, curr->frame->name, curr->frame->duration);
	}
	
	fclose(file);
}


/// <summary>
/// Loads a frameNode from a given filePath
/// </summary>
/// <param name="frameHead"></param>
/// <param name="filePath"></param>
void loadFromFile(FrameNode** frameHead, char filePath[]) {
	FILE* file = fopen(filePath, "r");
	if (!file)
	{
		exit(1);
	}

	char path[STR_LEN] = { 0 };
	char name[STR_LEN] = { 0 };
	int duration = 0;


	while (fscanf(file, "%[^,], %[^,], %d, ", path, name, &duration) == 3)
	{
		if (!isValidPath(path))
			exit(1);

		insertFrameAtEnd(frameHead, createFrameNode(createFrame(name, duration, path)));
	}

	fclose(file);
}

