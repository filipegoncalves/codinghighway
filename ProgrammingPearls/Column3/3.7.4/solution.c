#include <stdio.h>
#include <stdlib.h>
#define LEAP_DAY 29
#define LEAP_MONTH 2
#define WEEK_LENGTH 7
#define isleap(y) (((y)%4 == 0 && (y)%100 != 0) || (y)%400 == 0)

struct date {
	int day;
	int month;
	int year;
};

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char *week[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

#define REFERENCE_DATE_WDAY 3 /* 1st jan. 1800 - wednesday */
struct date reference_date = { 1, 1, 1800 };

void days_diff_test(int day1, int month1, int year1, int day2, int month2, int year2, int expected);
void day_of_week_test(int day, int month, int year, int expected);
char **make_calendar(int, int);
int main() {
	/* Let's run a few tests */
	/* First step - test days_diff */
	/* Test nominal case... */
	days_diff_test(1, 9, 2013, 25, 9, 2013, 24);
	days_diff_test(15, 2, 2013, 25, 9, 2013, 222);
	/* Test across years */
	days_diff_test(15, 2, 2013, 25, 9, 2014, 587);
	days_diff_test(1, 3, 2012, 28, 2, 2015, 1094);
	days_diff_test(14, 3, 2013, 23, 10, 2031, 6797);
	/* Let's play with leap years */
	days_diff_test(29, 2, 2016, 1, 3, 2020, 1462);
	days_diff_test(29, 9, 2016, 11, 2, 2017, 135);
	days_diff_test(31, 12, 2019, 31, 12, 2020, 366);
	days_diff_test(1, 1, 2019, 1, 1, 2020, 365);
	
	/* Second step - test day_of_week */
	day_of_week_test(22, 12, 1799, 0);
	day_of_week_test(1, 1, 1800, 3);
	day_of_week_test(1, 9, 2013, 0);
	day_of_week_test(16, 9, 2013, 1);
	day_of_week_test(31, 12, 2099, 4);
	day_of_week_test(14, 1, 1752, 5);
	
	/* Make calendar for September 2013 */
	int i;
	char **c = make_calendar(9, 2013);
	for (i = 0; i < daytab[0][9]; i++)
		printf("%d - %s\n", i+1, c[i]);
	return 0;
}

int day_of_year(struct date *);
int days_diff(struct date *d1, struct date *d2) {
	struct date *most_recent, *least_recent;
	int days;
	int year;
	if (d1->year < d2->year || 
		(d1->year == d2->year && d1->month < d2->month) ||
		(d1->year == d2->year && d1->month == d2->month && d1->day < d2->day)) {
			least_recent = d1;
			most_recent = d2;
		}
	else {
		least_recent = d2;
		most_recent = d1;
	}
	for (days = 0, year = least_recent->year; year < most_recent->year; year++)
		days += 365 + isleap(year);
	days += day_of_year(most_recent) - day_of_year(least_recent);
	return days;
}

int day_of_year(struct date *d) {
	int i, leap, day;
	day = d->day;
	leap = isleap(d->year);
	for (i = 1; i < d->month; i++)
		day += daytab[leap][i];
	return day;
}

void days_diff_test(int day1, int month1, int year1, int day2, int month2, int year2, int expected) {
	struct date d1 = { day1, month1, year1 };
	struct date d2 = { day2, month2, year2 };
	int val;
	if ((val = days_diff(&d1, &d2)) != expected)
		fprintf(stderr, "Wrong answer for difference between %d/%d/%d and %d/%d/%d, expected was %d, but got %d instead.\n", d1.month, d1.day, d1.year, d2.month, d2.day, d2.year, expected, val);
}


int day_of_week(struct date *d) {
	return (d->year < reference_date.year) ? 
				((((WEEK_LENGTH-1)*(days_diff(d, &reference_date)))+REFERENCE_DATE_WDAY)%WEEK_LENGTH)
				:
				((days_diff(d, &reference_date)+REFERENCE_DATE_WDAY)%WEEK_LENGTH);
}

void day_of_week_test(int day, int month, int year, int expected) {
	struct date d = { day, month, year };
	int val;
	if ((val = day_of_week(&d)) != expected)
		fprintf(stderr, "Wrong answer for day of week of %d/%d/%d, expected was \"%s\", but got \"%s\" instead.\n", month, day, year, week[expected], week[val]);
}

char **make_calendar(int month, int year) {
	int days = daytab[isleap(year)][month];
	char **calendar = malloc(sizeof(char *)*days);
	struct date d = { 1, month, year };
	int i, j = day_of_week(&d);
	calendar[0] = week[j];
	j = (j+1)%WEEK_LENGTH;
	for (i = 1; i < days; i++, j = (j+1)%WEEK_LENGTH)
		calendar[i] = week[j];
	return calendar;
}
