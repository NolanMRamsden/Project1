/*
 * Score.c
 *
 *  Created on: 2014-09-29
 *      Author: Gavin
 */

#include <stdbool.h>
#include <stdio.h>

/*
 * SD Card writing has an issue where more data than was originally read must be written. This method constructs the string to account for this
 */
/*
char* convert_integer_to_string_for_write(int score, char file_name[], char score_string[])
{
	int i = 0;
	int j = 0;
	char read_data[100] = {0};

	// Covert integer to string
	sprintf(score_string, "%d", score);

	// Move i to point to the last + 1 element of the score
	for(i = 0; score_string[i] != NULL; i++);

	// Open the score file
	short int file_handle = sdcard_fopen(file_name, true);

	// Read the file, retrieve it's file size, and delete everything
	sdcard_ReadFile(read_data, file_handle);

	// Move j pointer to the end of the data read from buffer
	for(j = 0; read_data[j] != NULL; j++);

	// Fill up the necessary space with garbage characters, so that a write will be triggered
	for(i; i < j; i++)
	{
		score_string[i] = '/';
	}
	sdcard_fclose(file_handle);

	return score_string;
}
*/
/**
 * Retrieves an integer score from the SD card
 */
/*
int get_score_from_sd_card(char read_data[])
{
	int score = 0;
	char * file_name = malloc(15);

	file_name = "TOTAL.txt";

	short int file_handle = sdcard_fopen("TOTAL.txt", true); // Open the score file
	sdcard_ReadFile(read_data, file_handle); // Reads the score file into the supplied character buffer

	// Convert the char array to an integer score
	score = atoi(read_data);
	printf("Score Retrieved: %d \n", score);

	sdcard_fclose(file_handle);

	return score;
}
*/
/*
 * Writes an integer score to the SD card
 */
/*
void write_score_to_sd_card(int score)
{
	char score_string[100] = {0};
	convert_integer_to_string_for_write(score, "TOTAL.txt", score_string);

	short int file_handle;
	file_handle = sdcard_fopen("TOTAL.txt", true);

	sdcard_WriteFile(score_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored score_string: %s \n", score_string);

}
*/




