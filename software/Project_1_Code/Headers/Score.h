/*
 * Score.h
 *
 *  Created on: 2014-09-29
 *      Author: Gavin
 */

#ifndef SCORE_H_
#define SCORE_H_

typedef struct Score
{
	int score;

} Score;

int get_score_from_sd_card(char read_data[]);
void write_score_to_sd_card(int score);

// Helpers
char* convert_integer_to_string_for_write(int score, char file_name[], char score_string[]);

#endif /* SCORE_H_ */
