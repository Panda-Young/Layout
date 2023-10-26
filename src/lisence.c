/******************************************************************************
 * @Description: calculate date difference
 * @version: 0.1.0
 * @Author: Panda-Young
 * @Date: 2023-02-22 11:00:38
 * Copyright (c) 2023 by Panda-Young, All Rights Reserved. 
 *****************************************************************************/

#include "list.h"
#include "log.h"
#include <time.h>

#define LICENSE_DAY 9000

/**
 * @description: is leap year
 * @param {int} year
 * @return {int} 1: leap year, 0: not leap year
 */
int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @description:count day from 1/1 to year/month/day 
 * @param {int} year, month, day
 * @return {int}
 */
int count_day(struct tm *tm)
{
    int count_day = 0;
    int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(tm->tm_year + 1900)) {
        month_day[1] = 29;
    }
    for (int i = 0; i < tm->tm_mon; i++) {
        count_day += month_day[i];
    }
    count_day += tm->tm_mday;
    return count_day;
}

/**
 * @description: count day from tm1 to tm2 
 * @param {tm} *tm1, *tm2
 * @return {int}
 */
int date_diff(struct tm *tm1, struct tm *tm2)
{
    int diff = 0;
#if ANOTHER_WAY
    time_t t1 = mktime(tm1); // convert struct tm to time_t
    time_t t2 = mktime(tm2);
    int diff = (t2 - t1) / (24 * 60 * 60);
#else
    int year1 = tm1->tm_year + 1900;
    int year2 = tm2->tm_year + 1900;
    int day1 = count_day(tm1);
    int day2 = count_day(tm2);

    if (year1 == year2) {
        diff = day2 - day1;
    } else {
        diff = day2;
        for (int i = year1; i < year2; i++) {
            if (is_leap_year(i)) {
                diff += 366;
            } else {
                diff += 365;
            }
        }
        diff -= day1;
    }

    if (tm1->tm_hour > tm2->tm_hour) {
        diff -= 1;
    } else if (tm1->tm_hour == tm2->tm_hour && tm1->tm_min > tm2->tm_min) {
        diff -= 1;
    } else if (tm1->tm_hour == tm2->tm_hour && tm1->tm_min == tm2->tm_min && tm1->tm_sec > tm2->tm_sec) {
        diff -= 1;
    }
#endif
    return diff;
}

/**
 * @description: check license
 * @return {int}
 */
int32_t check_license()
{
    int license_valid = 0;
    struct tm *localtime_ptr = NULL;

    struct tm *begin_tm = (struct tm *)calloc(sizeof(struct tm), 1);
    if (begin_tm == NULL) {
        perror("malloc failed: ");
        return EALLOC;
    }
    begin_tm->tm_year = 2023 - 1900;
    begin_tm->tm_mon = 2 - 1;
    begin_tm->tm_mday = 22;
    begin_tm->tm_hour = 11;
    begin_tm->tm_min = 0;
    begin_tm->tm_sec = 38;
    begin_tm->tm_isdst = -1; // Daylight saving time -1: not set, 0: not DST, 1: DST

    time_t now_time = time(NULL);
    struct tm *now_tm = (struct tm *)calloc(sizeof(struct tm), 1);
    if (now_tm == NULL) {
        perror("malloc failed: ");
        free(begin_tm);
        return EALLOC;
    }
    localtime_ptr = localtime(&now_time);
    memcpy(now_tm, localtime_ptr, sizeof(struct tm));

    struct tm *end_tm = (struct tm *)calloc(sizeof(struct tm), 1);
    if (end_tm == NULL) {
        perror("malloc failed: ");
        free(begin_tm);
        free(now_tm);
        return EALLOC;
    }
    time_t end_time = mktime(begin_tm) + LICENSE_DAY * 24 * 60 * 60;
    localtime_ptr = localtime(&end_time);
    memcpy(end_tm, localtime_ptr, sizeof(struct tm));

    if (date_diff(begin_tm, now_tm) > LICENSE_DAY) {
        MSG_ERR("Your license has expired.\n");
        license_valid = 1;
    } else if (date_diff(begin_tm, now_tm) > LICENSE_DAY - 3) {
        MSG_INFO("Your license is about to expire in 3 days.\n");
    } else {
        MSG_INFO("Your license is valid until %d/%d/%d\n", end_tm->tm_year + 1900, end_tm->tm_mon + 1, end_tm->tm_mday);
    }

    if (now_tm != NULL) {
        free(now_tm);
        now_tm = NULL;
    }
    if (begin_tm != NULL) {
        free(begin_tm);
        begin_tm = NULL;
    }
    if (end_tm != NULL) {
        free(end_tm);
        end_tm = NULL;
    }

    return license_valid;
}
