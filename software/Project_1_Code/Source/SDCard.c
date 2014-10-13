/*
 * SDCard.c
 *
 *  Created on: 2014-09-29
 *      Author: Gavin
 */

#include "../Headers/Definitions.h"
#include <SDCard.h>
#include <altera_up_sd_card_avalon_interface.h>

/**
 * Initializes the SD Card Driver
 */
void sdcard_Init(void)
{
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
}


/**
 * Looks for an SD Card
 * Return: True if SD Card present. False otherwise.
 */
int sdcard_isPresent(void)
{
	int is_present = alt_up_sd_card_is_Present();
	return is_present;
}

/**
 * Looks for a FAT16 partition
 * Return: True if FAT16 partition exists. False otherwise.
 */
int sdcard_isFAT16(void)
{
	int is_fat16 = alt_up_sd_card_is_FAT16();
	return is_fat16;
}

/**
 * Finds the first file in the directory, stores it into file_name
 * Return: 0 (success), 1 (invalid directory), 2 (no sd card/fat16 partition), -1 (no files found)
*/
short int sdcard_FirstFile(char *directory, char *file_name)
{
	short int result = alt_up_sd_card_find_first(directory, file_name);
	return result;
}

/**
 * Uses the directory used in sdcard_get_first_file.
 * Return: Same as sdcard_FirstFile, with the addition of 3, which means that sdcard_FirstFile must be called first
 */
short int sdcard_NextFile(char *file_name)
{
	short int result = alt_up_sd_card_find_next(file_name);
	return result;
}

/**
 * Prints out a list of files in the given directory
 */
void sdcard_ListFiles(char *directory)
{
	char *file_name = NULL;

	if (!sdcard_FirstFile(directory, file_name))
	{
		printf(file_name); printf("\n");

		while(!sdcard_NextFile(file_name))
		{
			printf(file_name); printf("\n");
		}
	}
}

/**
* Opens a file for use
* Parameters: name (file name, including the directory), create_new_if_not_exist (set to True to create a file if it doesn't exist already)
* Result: Index to file record. -1 if file not opened. -2 if file has already been opened
*/
short int sdcard_fopen(char *file_name, bool create_new_if_not_exist)
{
	short int handle = alt_up_sd_card_fopen("total.txt",false);
	return handle;
}


/*
 * Returns a byte from given file
 */
short int sdcard_ReadByte(short int file_handle)
{
	short int byte = alt_up_sd_card_read(file_handle);
	return byte;
}

/*
 * Returns file size
 */
int sdcard_FileSize(short int file_handle)
{
	int size = 0;
	for(size = 0; sdcard_ReadByte(file_handle) != -1; size++);

	sdcard_fclose(file_handle);

	return size;
}

/*
 * Reads file into a char buffer
 */
void sdcard_ReadFile(char read_data[], short int file_handle)
{
	short int byte = 0;
	int size = 0;
	while(byte != -1)
	{
		byte = sdcard_ReadByte(file_handle);
		if ( byte != -1) read_data[size] = byte;

		size++;
	}

	read_data[size - 1] = '/';
}

/*
 *	Debug method for printing char buffer
 */
void printArray(char a[])
{
	printf("Print array called \n");
	int h = 0;

	printf("Print parameter: %s \n", a);
	printf("Debug value: %c \n", a[h]);
	while(a[h] != 0)
	{
		if ( a[h] > 47 && a[h] < 91 )
			printf("%c \n", a[h] );
		else
			printf("%d \n",a[h]);
		h++;
	}
}

/*
 *	Writes char buffer to file
 *	Stops when end of file character '/' detected
 */
void sdcard_WriteFile(char write_data [], short int file_handle)
{
	int byte_index = 0;
	bool result;
	while(write_data[byte_index] != 0)
	{
		result = alt_up_sd_card_write(file_handle, write_data[byte_index]);
		byte_index++;
	}
}

/* Return: File attributes. -1 if invalid file.
 */
short int sdcard_getFattributes(short int file_handle)
{
	short int att = alt_up_sd_card_get_attributes(file_handle);
	return att;
}

/*
 * Closes the file
 */
void sdcard_fclose(int short file_handle)
{
	alt_up_sd_card_fclose(file_handle);
}
