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

#define PLANNER_CURRENT_VERSION "RES_0.1"

enum WEEKS_MONTHS {
	/* weeks */
	WK_SUN,
	WK_MON,
	WK_TUE,
	WK_WED,
	WK_THU,
	WK_FRI,
	WK_SAT,

	/* mouths */
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

void week_month_string(char*, char*, int, int);
void menu(void);
void read_plans(void);
void record_plans(void);
void del_plans(void);
void settings(void);

int main(void)
{
	FILE wp[7];
	time_t tt;
	struct tm *ttm;
	char tm_month[20], tm_week[20];

	tt = time(0);
	ttm = localtime(&tt);
	
	week_month_string(tm_week, tm_month, ttm->tm_wday, ttm->tm_mon);
	system("clear");
	printf("Planner version %s\n", PLANNER_CURRENT_VERSION);
	printf("Today is %s, %s %d %d\n", tm_week, tm_month, ttm->tm_mday, ttm->tm_year+1900);

	menu();

	return 0;
}

void week_month_string(char *wk, char* str, int wek, int mon)
{
	switch (wek) {
		case WK_MON:
			strcpy(wk, "Monday");
			break;
		case WK_TUE:
			strcpy(wk, "Tuesday");
			break;
		case WK_WED:
			strcpy(wk, "Wednesday");
			break;
		case WK_THU:
			strcpy(wk, "Thursday");
			break;
		case WK_FRI:
			strcpy(wk, "Friday");
			break;
		case WK_SAT:
			strcpy(wk, "Saturday");
			break;
		case WK_SUN:
			strcpy(wk, "Sunday");
			break;
	}

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
	int ch;

	printf("\nChoose the service you want:\n\n");
	printf(
			"1.Check out plans\n"
			"2.Record plans\n"
			"3.Delete plans\n"
			"4.Setting\n"
			"0.Exit\n"
			);
	printf("Choose: ");
	scanf("%d", &ch);

	switch (ch) {
		case 1:
			read_plans();
			break;
		case 2:
			record_plans();
			break;
		case 3:
			del_plans();
			break;
		case 4:
			settings();
			break;
		default:
			return;
	}
}

void read_plans(void)
{
	FILE *wp[7];
	int day;
	char fname[16], ds[16]; 

	printf("Which day's plans would you want to read? [input 0-6]\n");
	scanf("%d", &day);

	week_month_string(ds, ds, day, 16);
	sprintf(fname, "day%d.pl", day);
	wp[day] = fopen(fname, "w");
	fprintf(wp[day], "Hello! Today is %s.\n", ds);

	fclose(wp[day]);
}
void record_plans(void)
{
}
void del_plans(void)
{
}
void settings(void)
{
}
