/*
 * SDCard.h
 *
 *  Created on: 2014-09-29
 *      Author: Gavin
 */

#ifndef SDCARD_H_
#define SDCARD_H_

#ifndef SDCARD_H_
#define SDCARD_H_

#include <stdbool.h> // So that integers can be treated like booleans, and vice-versa

void sdcard_Init(void);
int sdcard_isPresent(void);
int sdcard_isFAT16(void);
short int sdcard_FirstFile(char *directory, char *file_name);
short int sdcard_NextFile(char *file_name);
int sdcard_FileSize(short int file_handle);
void sdcard_ReadFile(char read_data [], short int file_handle);
short int sdcard_ReadByte(short int file_handle);
void sdcard_WriteFile(char write_data [], short int file_handle);
void sdcard_ListFiles(char *directory);

short int sdcard_fopen(char *name, bool create_new_if_not_exist);
void sdcard_fclose(short int file_handle);
short int sdcard_getFattributes(short int file_handle);

void printArray(char a[]);
void printIntArray(int a[][bricksPerRow]);

typedef struct
{
	char *file_name;
	char *directory;
	short int attributes;
	short int file_handle;
	int file_size;

} File;

#endif /* SDCARD_H_ */


#endif /* SDCARD_H_ */
