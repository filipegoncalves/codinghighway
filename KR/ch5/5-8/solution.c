#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
	int i, leap;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if (year <= 0 || !(month >= 1 && month <= 12) || !(day > 0 && day <= daytab[leap][month]))
		return -1;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if (year <= 0 || !(yearday > 0 && yearday <= (leap ? 366 : 365)) || !pmonth || !pday)
		return -1;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
	return 0;
}

int main() {
	/* Example usage */
	int a;
	if (month_day(2013, 54, &a, NULL) == -1)
		printf("month_day() reported error.\n");
	printf("%d\n", day_of_year(2013, 07, 26));
	return 0;
}
