/*
 * Profile.h
 *
 *  Created on: 2014-10-09
 *      Author: Gavin
 */

#ifndef PROFILE_H_
#define PROFILE_H_

/*
 * A User Profile
 */
typedef struct Profile
{
	char* name;
	int score;
	int id; // Used to identify the profile

} Profile;

extern Profile* profile_1;
extern Profile* profile_2;
extern Profile* profile_3;
extern Profile* anon_profile;

extern Profile* current_profile;

// x represents the the number of the profile. Generally, we will only load 3.
extern void initProfile(Profile* profile, int x);
extern void initProfiles();
extern void initAnonProfile();

extern void reloadProfile(Profile* profile, int x);
extern void reloadProfiles();

extern int getScore();
extern void incrementScore(int value);

extern void readMap(int map_array[][bricksPerRow], int profile_number, int map_number );
extern void writeMap(int map_array[][bricksPerRow], int profile_number, int map_number );

void delete_profile(int profile_number);

int get_score_from_sd_card(int profile_number);
void get_name_from_sd_card(char* name ,int profile_number);

void write_score_to_sd_card(int score, int profile_number);
void write_name_to_sd_card(char* name, int profile_number);

void set_current_profile(Profile* profile);

void updateProfile(Profile* profile); // Saves the profile to SD Card

// Helpers
char* convert_integer_to_string_for_write(int score, char file_name[], char score_string[]);
char* convert_string_to_string_for_write(char* name, char file_name[], char name_string[]);

#endif /* PROFILE_H_ */
