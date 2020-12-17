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
#include <stdbool.h>

#define PLANNER_CURRENT_VERSION "RES_0.1"
/* turn on the debug mode if you want to see the interal info */
//#define _DEBUG

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

/* Functions */
void week_month_string(char*, char*, int, int);
void menu(void);
void read_plans(void);
void record_plans(void);
void del_plans(void);
void settings(void);

/* Global variable */
bool set_opt[10] = {false}; 
bool entered;

int main(void)
{
	FILE *set_file;
	time_t tt;
	struct tm *ttm;
	char tm_month[20], tm_week[20];
	int iset;

	tt = time(0);
	ttm = localtime(&tt);
	
	week_month_string(tm_week, tm_month, ttm->tm_wday, ttm->tm_mon);
	system("clear");
	printf("Planner version %s\n", PLANNER_CURRENT_VERSION);

	if ((set_file = fopen("settings.dat", "r")) == NULL) {
		printf("Error: settings.dat not found!\n");
		return 1;
	}

	fscanf(set_file, "%d", &iset);
	set_opt[0] = (iset == 1) ? true : false;
#ifdef _DEBUG
	printf(
			"Debug: iset = %d, set_opt[0] = %s\n"
			"Debug: If iset is neither 1 or 0, file settings.dat might be broken\n",
			iset, (set_opt[0] == true) ? "true" : "false"
			);
#endif

	if (set_opt[0] == true) 
		printf("Today is %s, %s %d %d\n", tm_week, tm_month, ttm->tm_mday, ttm->tm_year+1900);
	else 
		printf("Today is %s %d %d\n", tm_month, ttm->tm_mday, ttm->tm_year+1900);

	fclose(set_file);
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

/* Menu */
void menu(void)
{
	int ch;

	if (entered == true) 
		system("clear");

	entered = true;

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

/* Read plan function */
void read_plans(void)
{
	FILE *wp[7];
	int day, i = 0;
	char fname[16], ds[16], fstr[100005]; 

	printf("Which day's plans would you want to read? [input 0-6]\n");
	scanf("%d", &day);

	week_month_string(ds, ds, day, 16);
	sprintf(fname, "day%d.pl", day);
	wp[day] = fopen(fname, "r");
	if (wp[day] == NULL) {
		printf("Fail to read the file named %s!\n", fname);
		return;
	}

	while (!feof(wp[day])) {
		fstr[i] = fgetc(wp[day]);
		i++;
	}

	system("clear");
	printf("%s\n", fstr);

	fclose(wp[day]);
	menu();
}

/* Record function */
void record_plans(void)
{
	FILE *wp[7];
	int day;
	char fname[16], ds[16], ch; 

	printf("Which day's plans would you want to record? [input 0-6]\n");
	scanf("%d", &day);

	week_month_string(ds, ds, day, 16);
	sprintf(fname, "day%d.pl", day);
	wp[day] = fopen(fname, "w");
	fprintf(wp[day], "Plans of %s\nTime  |  Plan", ds);

	printf("Please input your plans, input '#' to stop\nTime  |  Plan\n");

	do {
		ch = getchar();
		fputc(ch, wp[day]);
	} while (ch != '#');

	fclose(wp[day]);
	menu();
}

/* Delete function */
void del_plans(void)
{
	FILE *wp[7];
	int day;
	char fname[16], ds[16], ch; 

	printf("Which day's plans would you want to record? [input 0-6]\n");
	scanf("%d", &day);

	week_month_string(ds, ds, day, 16);
	sprintf(fname, "./day%d.pl", day);

	if (!remove(fname)) 
		printf("Success to remove %s!\n", fname);
	else
		printf("Fail to remove the file named %s!\n", fname);

	fclose(wp[day]);
	menu();
}

/* Setting function */
void settings(void)
{
	int ch;
	FILE *set_file = fopen("settings.dat", "w");

	system("clear");

	printf(
			"Setting\n\n"
			"1.Show weeks in the main menu [%s]\n"
			"0.Back to main menu\n",
			(set_opt[0] == true) ? "YES" : "NO"
			);

	scanf("%d", &ch);

	switch (ch) {
		case 0: menu(); break;
		case 1: 
			set_opt[0] = (set_opt[0] == true) ? false : true; 
			fprintf(set_file, "%d", (set_opt[0] == true) ? 1 : 0);
			settings();
			break;
		default: settings(); break;
	}

	fclose(set_file);
}


