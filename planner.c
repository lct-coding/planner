/*
 * Copyright 2020
 * File: planner.c
 * Author: Lucas
 */
/* Planner application source file */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define WND 0

#define PLANNER_CURRENT_VERSION "RES_0.1"

enum MONTHS {
	MH_JAN = 1-1,
	MH_FEB = 2-1,
	MH_MAR = 3-1,
	MH_APR = 4-1,
	MH_MAY = 5-1,
	MH_JUN = 6-1,
	MH_JUL = 7-1,
	MH_AUG = 8-1,
	MH_SEP = 9-1,
	MH_OCT = 10-1,
	MH_NOV = 11-1,
	MH_DEC = 12-1
};

void month_string(char*, int);
void menu(void);

int main(void)
{
	FILE wp[7];
	time_t tt;
	struct tm *ttm;
	char tm_month[20];

	tt = time(0);
	ttm = localtime(&tt);
	
	month_string(tm_month, ttm->tm_mon);
	system("clear");
	printf("Planner version %s\n", PLANNER_CURRENT_VERSION);
	printf("Today is %s %d %d\n", tm_month, ttm->tm_mday, ttm->tm_year+1900);

	return 0;
}

void month_string(char* str, int mon)
{
	switch (mon) {
		case MH_JAN: 
			strcpy(str, "January");
			break;
		case MH_FEB:
			strcpy(str, "February");
			break;
		case MH_MAR:
			strcpy(str, "March");
			break;
		case MH_APR:
			strcpy(str, "April");
			break;
		case MH_MAY:
			strcpy(str, "May");
			break;
		case MH_JUN:
			strcpy(str, "June");
			break;
		case MH_JUL:
			strcpy(str, "July");
			break;
		case MH_AUG:
			strcpy(str, "August");
			break;
		case MH_SEP:
			strcpy(str, "September");
			break;
		case MH_OCT:
			strcpy(str, "October");
			break;
		case MH_NOV:
			strcpy(str, "November");
			break;
		case MH_DEC:
			strcpy(str, "December");
			break;
	}
}

void menu(void)
{
	printf("\nChoose you service:\n\n");
	printf(
			"1.Check out plans\n"
			"2.Record plans\n"
			"3.Delete plans\n"
			"4.Setting\n"
			"0.Exit\n"
			);
}




















