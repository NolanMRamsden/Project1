/*
 * Profile.c
 *
 *  Created on: 2014-10-09
 *      Author: Gavin
 */

/*
 * Initializes the profiles that will be used in the game
 */
#include "../Headers/headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Profile.h"
#include "../Headers/Level.h"


Profile* profile_1 = NULL;
Profile* profile_2 = NULL;
Profile* profile_3 = NULL;
Profile* current_profile = NULL;
Profile* anon_profile = NULL;

void initAnonProfile()
{
	anon_profile = malloc(sizeof(Profile));
	(*anon_profile).score = 0;
	(*anon_profile).bricks_hit = 0;
	(*anon_profile).paddle_hits = 0;
	(*anon_profile).buffs_caught = 0;
	(*anon_profile).current_level = 0;
	(*anon_profile).name = "anonymous"; // This currently will never show up, put in just in case
	(*anon_profile).id = 9;
	current_profile = anon_profile;


	return;
}

void initProfiles()
{

	profile_1 = malloc(sizeof(Profile));
	profile_2 = malloc(sizeof(Profile));
	profile_3 = malloc(sizeof(Profile));



	initProfile(profile_1, 1);
	initProfile(profile_2, 2);
	initProfile(profile_3, 3);

	// Set the current profile to a temporary anonymous profile


	 printf("finished init! \n");
	 printf("profile 1 score: %i \n", (*profile_1).score);
	 printf("profile 2 score: %i \n", (*profile_2).score);

	 return;
}

void reloadProfiles()
{
	reloadProfile(profile_1, 1);
	reloadProfile(profile_2, 2);
	reloadProfile(profile_3, 3);

	return;
}

void reloadProfile(Profile* profile, int profile_number)
{
	(*profile).score = get_score_from_sd_card(profile_number);
	memset((*profile).name, 0, 50); // Clearing the 50 chars of the string
	get_name_from_sd_card((*profile).name, profile_number);

	return;
}

void initProfile(Profile* profile, int profile_number)
{
	(*profile).score = get_score_from_sd_card(profile_number);
	(*profile).bricks_hit = get_bricks_hit_from_sd_card(profile_number);
	(*profile).paddle_hits = get_paddle_hits_from_sd_card(profile_number);
	(*profile).buffs_caught = get_buffs_caught_from_sd_card(profile_number);
	(*profile).current_level = get_current_level_from_sd_card(profile_number);

	(*profile).name = malloc(50 * sizeof(char));
	(*profile).id = profile_number;

	get_name_from_sd_card((*profile).name, profile_number);

	return;
}

void get_name_from_sd_card(char* name, int profile_number)
{
	short int file_handle;
	int i = 0;

	switch(profile_number)
	{
		case 1:
			file_handle = sdcard_fopen("p/1/n.txt");
			break;
		case 2:
			file_handle = sdcard_fopen("p/2/n.txt");
			break;
		case 3:
			file_handle = sdcard_fopen("p/3/n.txt");
			break;
		default:
			file_handle = sdcard_fopen("p/1/n.txt");
			break;
	}
	sdcard_ReadFile(name, file_handle);
	while(true)
	{
		if(name[i] == '/')
		{
			name[i] = NULL;
			break;
		}

		if(i > 100){
			break;
		}

		i++;
	}

	sprintf(name, "%s", name);

	sdcard_fclose(file_handle);

	return;
}
/**
 * Retrieves an integer score from the SD card
 */
int get_score_from_sd_card(int profile_number)
{

	char * read_data = malloc(50 * sizeof(char));

	int score = 0;
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			file_handle = sdcard_fopen("p/1/s.txt");
			break;
		case 2:
			file_handle = sdcard_fopen("p/2/s.txt");
			break;
		case 3:
			file_handle = sdcard_fopen("p/3/s.txt");
			break;
		default:
			file_handle = sdcard_fopen("p/1/s.txt");
	}

	if(profile_number == 3){
		printf("File handle: %hi \n", file_handle);
	}
	sdcard_ReadFile(read_data, file_handle); // Reads the score file into the supplied character buffer

	// Convert the char array to an integer score
	score = atoi(read_data);

	free(read_data);
	read_data = NULL;
	sdcard_fclose(file_handle);

	return score;
}

/**
 * Retrieves paddle hits from the SD card
 */
int get_paddle_hits_from_sd_card(int profile_number)
{

	char * read_data = malloc(50 * sizeof(char));

	int paddle_hits = 0;
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			file_handle = sdcard_fopen("p/1/ph.txt");
			break;
		case 2:
			file_handle = sdcard_fopen("p/2/ph.txt");
			break;
		case 3:
			file_handle = sdcard_fopen("p/3/ph.txt");
			break;
		default:
			file_handle = sdcard_fopen("p/1/ph.txt");
			break;
	}

	if(profile_number == 3){
		printf("File handle: %hi \n", file_handle);
	}
	sdcard_ReadFile(read_data, file_handle); // Reads the score file into the supplied character buffer

	// Convert the char array to an integer score
	paddle_hits = atoi(read_data);

	free(read_data);
	read_data = NULL;
	sdcard_fclose(file_handle);

	return paddle_hits;
}

/**
 * Retrieves current level from the SD card
 */
int get_current_level_from_sd_card(int profile_number)
{

	char * read_data = malloc(50 * sizeof(char));

	int current_level = 0;
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			file_handle = sdcard_fopen("p/1/l.txt");
			break;
		case 2:
			file_handle = sdcard_fopen("p/2/l.txt");
			break;
		case 3:
			file_handle = sdcard_fopen("p/3/l.txt");
			break;
		default:
			file_handle = sdcard_fopen("p/1/l.txt");
			break;
	}

	if(profile_number == 3){
		printf("File handle: %hi \n", file_handle);
	}
	sdcard_ReadFile(read_data, file_handle); // Reads the score file into the supplied character buffer

	// Convert the char array to an integer score
	current_level = atoi(read_data);

	free(read_data);
	read_data = NULL;
	sdcard_fclose(file_handle);

	return current_level;
}

/**
 * Retrieves brick hits from the SD card
 */
int get_bricks_hit_from_sd_card(int profile_number)
{

	char * read_data = malloc(50 * sizeof(char));

	int brick_hits = 0;
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			file_handle = sdcard_fopen("p/1/bh.txt");
			break;
		case 2:
			file_handle = sdcard_fopen("p/2/bh.txt");
			break;
		case 3:
			file_handle = sdcard_fopen("p/3/bh.txt");
			break;
		default:
			file_handle = sdcard_fopen("p/1/bh.txt");
			break;
	}

	if(profile_number == 3){
		printf("File handle: %hi \n", file_handle);
	}
	sdcard_ReadFile(read_data, file_handle); // Reads the score file into the supplied character buffer

	// Convert the char array to an integer score
	brick_hits = atoi(read_data);

	free(read_data);
	read_data = NULL;
	sdcard_fclose(file_handle);

	return brick_hits;
}

/**
 * Retrieves buffs caught from the SD card
 */
int get_buffs_caught_from_sd_card(int profile_number)
{

	char * read_data = malloc(50 * sizeof(char));

	int balls_caught = 0;
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			file_handle = sdcard_fopen("p/1/bc.txt");
			break;
		case 2:
			file_handle = sdcard_fopen("p/2/bc.txt");
			break;
		case 3:
			file_handle = sdcard_fopen("p/3/bc.txt");
			break;
		default:
			file_handle = sdcard_fopen("p/1/bc.txt");
			break;
	}

	if(profile_number == 3){
		printf("File handle: %hi \n", file_handle);
	}
	sdcard_ReadFile(read_data, file_handle); // Reads the score file into the supplied character buffer

	// Convert the char array to an integer score
	balls_caught = atoi(read_data);

	free(read_data);
	read_data = NULL;
	sdcard_fclose(file_handle);

	return balls_caught;
}

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

char* convert_string_to_string_for_write(char* name, char file_name[], char name_string[])
{
	int i = 0;
	int j = 0;
	char read_data[200] = {0};

	// Covert string to string (will cut it off at the null terminator)
	sprintf(name_string, "%s", name);

	// Move i to point to the last + 1 element of the score
	for(i = 0; name_string[i] != NULL; i++);

	// Open the score file
	short int file_handle = sdcard_fopen(file_name, true);

	// Read the file, retrieve it's file size, and delete everything
	sdcard_ReadFile(read_data, file_handle);

	// Move j pointer to the end of the data read from buffer
	for(j = 0; read_data[j] != NULL; j++);

	// Fill up the necessary space with garbage characters, so that a write will be triggered
	for(i; i < j; i++)
	{
		name_string[i] = '/';
	}
	sdcard_fclose(file_handle);

	return name_string;
}

void write_score_to_sd_card(int score, int profile_number)
{
	char score_string[100] = {0};
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			convert_integer_to_string_for_write(score, "p/1/s.txt", score_string);
			file_handle = sdcard_fopen("p/1/s.txt", true);
			break;

		case 2:
			convert_integer_to_string_for_write(score, "p/2/s.txt", score_string);
			file_handle = sdcard_fopen("p/2/s.txt", true);
			break;

		case 3:
			convert_integer_to_string_for_write(score, "p/3/s.txt", score_string);
			file_handle = sdcard_fopen("p/3/s.txt", true);
			break;

		default:
			convert_integer_to_string_for_write(score, "p/1/s.txt", score_string);
			file_handle = sdcard_fopen("p/1/s.txt", true);
			break;

	}

	sdcard_WriteFile(score_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored score_string: %s \n", score_string);

	return;
}

void write_bricks_hit_to_sd_card(int value, int profile_number)
{
	char value_string[100] = {0};
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			convert_integer_to_string_for_write(value, "p/1/bh.txt", value_string);
			file_handle = sdcard_fopen("p/1/bh.txt", true);
			break;

		case 2:
			convert_integer_to_string_for_write(value, "p/2/bh.txt", value_string);
			file_handle = sdcard_fopen("p/2/bh.txt", true);
			break;

		case 3:
			convert_integer_to_string_for_write(value, "p/3/bh.txt", value_string);
			file_handle = sdcard_fopen("p/3/bh.txt", true);
			break;

		default:
			convert_integer_to_string_for_write(value, "p/1/bh.txt", value_string);
			file_handle = sdcard_fopen("p/1/bh.txt", true);
			break;

	}

	sdcard_WriteFile(value_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored value: %s \n", value_string);

	return;
}

void write_current_level_to_sd_card(int value, int profile_number)
{
	char value_string[100] = {0};
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			convert_integer_to_string_for_write(value, "p/1/l.txt", value_string);
			file_handle = sdcard_fopen("p/1/l.txt", true);
			break;

		case 2:
			convert_integer_to_string_for_write(value, "p/2/l.txt", value_string);
			file_handle = sdcard_fopen("p/2/l.txt", true);
			break;

		case 3:
			convert_integer_to_string_for_write(value, "p/3/l.txt", value_string);
			file_handle = sdcard_fopen("p/3/l.txt", true);
			break;

		default:
			convert_integer_to_string_for_write(value, "p/1/l.txt", value_string);
			file_handle = sdcard_fopen("p/1/l.txt", true);
			break;

	}

	sdcard_WriteFile(value_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored value: %s \n", value_string);

	return;
}

void write_paddle_hits_to_sd_card(int value, int profile_number)
{
	char value_string[100] = {0};
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			convert_integer_to_string_for_write(value, "p/1/ph.txt", value_string);
			file_handle = sdcard_fopen("p/1/ph.txt", true);
			break;

		case 2:
			convert_integer_to_string_for_write(value, "p/2/ph.txt", value_string);
			file_handle = sdcard_fopen("p/2/ph.txt", true);
			break;

		case 3:
			convert_integer_to_string_for_write(value, "p/3/ph.txt", value_string);
			file_handle = sdcard_fopen("p/3/ph.txt", true);
			break;

		default:
			convert_integer_to_string_for_write(value, "p/1/ph.txt", value_string);
			file_handle = sdcard_fopen("p/1/ph.txt", true);
			break;

	}

	sdcard_WriteFile(value_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored value: %s \n", value_string);

	return;
}

void write_buffs_caught_to_sd_card(int value, int profile_number)
{
	char value_string[100] = {0};
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			convert_integer_to_string_for_write(value, "p/1/bc.txt", value_string);
			file_handle = sdcard_fopen("p/1/bc.txt", true);
			break;

		case 2:
			convert_integer_to_string_for_write(value, "p/2/bc.txt", value_string);
			file_handle = sdcard_fopen("p/2/bc.txt", true);
			break;

		case 3:
			convert_integer_to_string_for_write(value, "p/3/bc.txt", value_string);
			file_handle = sdcard_fopen("p/3/bc.txt", true);
			break;

		default:
			convert_integer_to_string_for_write(value, "p/1/bc.txt", value_string);
			file_handle = sdcard_fopen("p/1/bc.txt", true);
			break;

	}

	sdcard_WriteFile(value_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored value: %s \n", value_string);

	return;
}

void write_name_to_sd_card(char* name, int profile_number)
{
	char name_string[100] = {0};
	short int file_handle;

	switch(profile_number)
	{
		case 1:
			convert_string_to_string_for_write(name, "p/1/n.txt", name_string);
			file_handle = sdcard_fopen("p/1/n.txt", true);
			break;

		case 2:
			convert_string_to_string_for_write(name, "p/2/n.txt", name_string);
			file_handle = sdcard_fopen("p/2/n.txt", true);
			break;

		case 3:
			convert_string_to_string_for_write(name, "p/3/n.txt", name_string);
			file_handle = sdcard_fopen("p/3/n.txt", true);
			break;
		default:
			convert_string_to_string_for_write(name, "p/1/n.txt", name_string);
			file_handle = sdcard_fopen("p/1/n.txt", true);
			break;

	}

	sdcard_WriteFile(name_string, file_handle);
	sdcard_fclose(file_handle);
	printf("Stored name_string: %s \n", name_string);

	return;
}

void delete_profile(int profile_number)
{
	// If deleting the current profile, we must switch over to the anonymous user
	if(profile_number == (*current_profile).id)
	{
		current_profile = anon_profile;
	}
	switch(profile_number)
	{
		case 1:
			(*profile_1).name = "new_profile";
			(*profile_1).score = 0;
			profile_1->bricks_hit = 0;
			profile_1->buffs_caught = 0;
			profile_1->paddle_hits = 0;
			profile_1->current_level = 0;
			write_score_to_sd_card(0, 1);
			write_bricks_hit_to_sd_card(0, 1);
			write_paddle_hits_to_sd_card(0, 1);
			write_buffs_caught_to_sd_card(0, 1);
			write_current_level_to_sd_card(0, 1);

			write_name_to_sd_card("new_profile", 1);
			break;
		case 2:
			(*profile_2).name = "new_profile";
			(*profile_2).score = 0;
			profile_2->bricks_hit = 0;
			profile_2->buffs_caught = 0;
			profile_2->paddle_hits = 0;
			profile_2->current_level = 0;
			write_score_to_sd_card(0,2);
			write_bricks_hit_to_sd_card(0, 2);
			write_paddle_hits_to_sd_card(0, 2);
			write_buffs_caught_to_sd_card(0, 2);
			write_current_level_to_sd_card(0, 2);
			write_name_to_sd_card("new_profile", 2);
			break;
		case 3:
			(*profile_3).name = "new_profile";
			(*profile_3).score = 0;
			profile_3->bricks_hit = 0;
			profile_3->buffs_caught = 0;
			profile_3->paddle_hits = 0;
			profile_3->current_level = 0;
			write_score_to_sd_card(0,3);
			write_bricks_hit_to_sd_card(0, 3);
			write_paddle_hits_to_sd_card(0, 3);
			write_buffs_caught_to_sd_card(0, 3);
			write_current_level_to_sd_card(0, 3);
			write_name_to_sd_card("new_profile", 3);
			break;
		default:
			(*profile_1).name = "new_profile";
			(*profile_1).score = 0;
			profile_1->bricks_hit = 0;
			profile_1->buffs_caught = 0;
			profile_1->paddle_hits = 0;
			profile_1->current_level = 0;
			write_score_to_sd_card(0,1);
			write_bricks_hit_to_sd_card(0, 1);
			write_paddle_hits_to_sd_card(0, 1);
			write_buffs_caught_to_sd_card(0, 1);
			write_current_level_to_sd_card(0, 1);
			write_name_to_sd_card("new_profile", 1);
			break;

	}


	return;
}

void set_current_profile(Profile* profile)
{
	current_profile = profile;
	if(current_profile->id != 9)
	{
		if(current_profile->current_level > 0)
		{
			// Read the level
			printf("Reading map \n");
			readLevel(brickmap->brickArray, current_profile->id);
			level = current_profile->current_level;

		}
	}

	return;
}

int getScore()
{
	return (*current_profile).score;
}

int getBricksHit()
{
	return (*current_profile).bricks_hit;
}

int getPaddleHits()
{
	return (*current_profile).paddle_hits;
}

int getCurrentLevel()
{
	return (*current_profile).current_level;
}

int getBuffsCaught()
{
	return (*current_profile).buffs_caught;
}

void incrementScore(int value)
{
	(*current_profile).score += value;

	return;
}

void incrementBricksHit(int value)
{
	(*current_profile).bricks_hit += value;

	return;
}

void incrementPaddleHits(int value)
{
	(*current_profile).paddle_hits += value;

	return;
}

void incrementBuffsCaught(int value)
{
	(*current_profile).buffs_caught += value;

	return;
}

void incrementCurrentLevel(int value)
{
	(*current_profile).current_level += value;

	return;
}


void writeMap(int map_array[][bricksPerRow], int profile_number, int map_number )
{

	// Read data from the map file
	char* char_map = malloc((bricksPerRow * maxRows)* sizeof(char));
	char* char_write = malloc((bricksPerRow*maxRows)*sizeof(char) + 50);
	short int file_handle;

	int i, j = 0; // Iterate through the parameter array
	int k = 0; // Iterate through the SD card data


	for (i = 0; i < maxRows; i++) {
		for (j = 0; j < bricksPerRow; j++) {
			char_map[k] = (char)(((int)'0')+map_array[i][j]);
			k++;
		}
	}

	// Avoiding manipulating strings due to some previous problems with memory
	switch(profile_number)
	{
		case 1:
			switch(map_number)
			{
				case 1:
					convert_string_to_string_for_write(char_map, "p/1/1.txt", char_write);
					file_handle = sdcard_fopen("p/1/1.txt");
					printf("%i \n", file_handle);
					break;
				case 2:
					convert_string_to_string_for_write(char_map, "p/1/2.txt", char_write);
					file_handle = sdcard_fopen("p/1/2.txt");
					break;
				case 3:
					convert_string_to_string_for_write(char_map, "p/1/3.txt", char_write);
					file_handle = sdcard_fopen("p/1/3.txt");
					break;
			}
			break;
		case 2:
			switch(map_number)
			{
				case 1:
					convert_string_to_string_for_write(char_map, "p/2/1.txt", char_write);
					file_handle = sdcard_fopen("p/2/1.txt");
					break;
				case 2:
					convert_string_to_string_for_write(char_map, "p/2/2.txt", char_write);
					file_handle = sdcard_fopen("p/2/2.txt");
					break;
				case 3:
					convert_string_to_string_for_write(char_map, "p/2/3.txt", char_write);
					file_handle = sdcard_fopen("p/2/3.txt");
					break;
			}
			break;
		case 3:
			switch(map_number)
			{
				case 1:
					convert_string_to_string_for_write(char_map, "p/3/1.txt", char_write);
					file_handle = sdcard_fopen("p/3/1.txt");
					break;
				case 2:
					convert_string_to_string_for_write(char_map, "p/3/2.txt", char_write);
					file_handle = sdcard_fopen("p/3/2.txt");
					break;
				case 3:
					convert_string_to_string_for_write(char_map, "p/3/3.txt", char_write);
					file_handle = sdcard_fopen("p/3/3.txt");
					break;
			}
			break;

		default:
			switch(map_number)
			{
				case 1:
					convert_string_to_string_for_write(char_map, "p/1/1.txt", char_write);
					file_handle = sdcard_fopen("p/1/1.txt");
					printf("%i \n", file_handle);
					break;
				case 2:
					convert_string_to_string_for_write(char_map, "p/1/2.txt", char_write);
					file_handle = sdcard_fopen("p/1/2.txt");
					break;
				case 3:
					convert_string_to_string_for_write(char_map, "p/1/3.txt", char_write);
					file_handle = sdcard_fopen("p/1/3.txt");
					break;
			}
			break;
	}

	sdcard_WriteFile(char_write, file_handle);
	sdcard_fclose(file_handle);

	return;
}

void readMap(int map_array[][bricksPerRow], int profile_number, int map_number )
{

	// Read data from the map file
	char* char_map = malloc((bricksPerRow * maxRows)* sizeof(char) + 50); // + 50: some extra room never hurt
	short int file_handle;

	// Avoiding manipulating strings due to some previous problems with memory
	switch(profile_number)
	{
		case 1:
			switch(map_number)
			{
				case 1:
					printf("reading map \n");
					file_handle = sdcard_fopen("p/1/1.txt");
					printf("%i \n", file_handle);
					break;
				case 2:
					file_handle = sdcard_fopen("p/1/2.txt");
					break;
				case 3:
					file_handle = sdcard_fopen("p/1/3.txt");
					break;
			}
			break;
		case 2:
			switch(map_number)
			{
				case 1:
					file_handle = sdcard_fopen("p/2/1.txt");
					break;
				case 2:
					file_handle = sdcard_fopen("p/2/2.txt");
					break;
				case 3:
					file_handle = sdcard_fopen("p/2/3.txt");
					break;
			}
			break;
		case 3:
			switch(map_number)
			{
				case 1:
					file_handle = sdcard_fopen("p/3/1.txt");
					break;
				case 2:
					file_handle = sdcard_fopen("p/3/2.txt");
					break;
				case 3:
					file_handle = sdcard_fopen("p/3/3.txt");
					break;
			}
			break;

		default:
			switch(map_number)
			{
				case 1:
					file_handle = sdcard_fopen("p/1/1.txt");
					break;
				case 2:
					file_handle = sdcard_fopen("p/1/2.txt");
					break;
				case 3:
					file_handle = sdcard_fopen("p/1/3.txt");
					break;
			}
			break;
	}
	sdcard_ReadFile(char_map, file_handle);
	sdcard_fclose(file_handle);

	int i, j = 0; // Iterate through the parameter array
	int k = 0; // Iterate through the SD card data


	for (i = 0; i < maxRows; i++) {
		for (j = 0; j < bricksPerRow; j++) {
			map_array[i][j] = char_map[k] - '0';
			k++;
		}
	}

	return;
}

void updateProfile(Profile* profile)
{
	if( (((*profile).id == 1) || ((*profile).id == 2)) || ( (*profile).id == 3) )
	{
		write_score_to_sd_card((*profile).score, (*profile).id);
		write_bricks_hit_to_sd_card((*profile).bricks_hit, (*profile).id);
		write_paddle_hits_to_sd_card((*profile).paddle_hits, (*profile).id);
		write_buffs_caught_to_sd_card((*profile).buffs_caught, (*profile).id);

		// Write the current level number, as well as the map for that level
		writeBrickLevel(((*currentLevel).bricks), (*profile).id);
		write_current_level_to_sd_card(level, (*profile).id);
		profile->current_level = level;


		write_name_to_sd_card((*profile).name, (*profile).id);
	}

	return;
}

void updateUI()
{
	 drawText("        ", 15, 1, 0);
	 drawText((*current_profile).name,15,1,0);
	 drawInt(level,62,1);
	 drawText("Level: ",55,1,0);

	return;
}

void writeLevel(int map_array[][bricksPerRow], int profile_number)
{
	writeMap(map_array, profile_number, 1);
}

void writeBrickLevel(Brick* brick_array[][bricksPerRow], int profile_number)
{
	int map_array[maxRows][bricksPerRow] = {0};
    int i, j = 0;
	for (i = 0; i < maxRows; i++)
	{
		for(j = 0; j < bricksPerRow; j++)
		{
			map_array[i][j] = brick_array[i][j]->health;
			// printf("health: %i \n", (brick_array[i][j].health));
		}
	}
	printf("saving this level: \n");
	// printIntArray(map_array);
	writeMap(map_array, profile_number, 1);
}

void readLevel(int map_array[][bricksPerRow], int profile_number)
{
	readMap(map_array, profile_number, 1);
	printf("Read Level from SD CARD \n");
	// printIntArray(map_array);
}

