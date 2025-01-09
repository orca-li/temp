#include <cntlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct TIMEZOME_T
{
    objcnt_t seconds, minutes, hours;
} timezone_t;

typedef struct TIME_STRUCT_T
{
    int sec, min, hour;
} time_struct_t;

static void clockinit(timezone_t* zone)
{
    zone->hours = cntcnst(CNT_OBJECT);
    zone->minutes = cntcnst(CNT_OBJECT);
    zone->seconds = cntcnst(CNT_OBJECT);

    cntinit(zone->hours, NULL, 1, 24);
    cntinit(zone->minutes, NULL, 1, 60);
    cntinit(zone->seconds, NULL, 1, 60);

    cntlink(zone->hours, zone->minutes, CNT_PARENT_CHILD);
    cntlink(zone->minutes, zone->seconds, CNT_CHILD_PARENT);
}

static void clocklink(timezone_t* zone, timezone_t* peer)
{
    cntlink(zone->hours, peer->hours, CNT_PEER_TO_PEER);
    cntlink(zone->minutes, peer->minutes, CNT_PEER_TO_PEER);
    cntlink(zone->seconds, peer->seconds, CNT_PEER_TO_PEER);
}

static void clockrun(timezone_t* zone, cntsize_t h, cntsize_t m, cntsize_t s)
{
    cntadd(zone->hours, h);
    cntadd(zone->minutes, m);
    cntadd(zone->seconds, s);
}

static void gettime(timezone_t zone, time_struct_t* time)
{
    time->hour = cntvalue(zone.hours);
    time->min = cntvalue(zone.minutes);
    time->sec = cntvalue(zone.seconds);
}

static void printtime(char* timezone, time_struct_t time)
{
    printf("%s %02d:%02d:%02d\n", timezone, time.hour, time.min, time.sec);
}

int main()
{
    timezone_t Moscow, London;
    time_struct_t time;

    clockinit(&Moscow);
    clockinit(&London);

    clocklink(&Moscow, &London);

    clockrun(&London, 1, 2, 3);

    gettime(Moscow, &time);
    printtime("Moscow", time);

    clockrun(&London, 1, 2, 3);

    gettime(London, &time);
    printtime("London", time);

    gettime(Moscow, &time);
    printtime("Moscow", time);

    return 0;
}
