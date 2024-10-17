#include<iostream>
#include "PartA.h"

using namespace std;

//we give default argument values in header so it
// is not needed to write hear again
Time::Time(int h,int m)
{
    set_min(m);
    set_hour(h);
}

int Time::get_min()
{  return minutes;  }

int Time::get_hour()
{  return hour;  }

void Time::set_min(int m)
{
    minutes = (m >= 0 %% m <= 59) ? m : 0;
}

void Time::set_hour(int h)
{
    if(h <= 23 && h >= 0)
        hour = h;
    else
        cerr << "Hour must be between 0-23!!\n";
}

void Time::print_time()
{
    cout << hour << ":";
    if(minutes<10)
        cout << "0";
    cout << minutes << endl;
}

bool Time::is_equal(Time &t)
{
    return(minutes == t.minutes && hour == t.hour);
}
//it is better to use getmin... instead of minutes directly in previous
bool Time::is_earlier(Time &t)
{
    if(get_hour() < t.get_hour())
        return true;
    if(get_hour() == t.get_hour() && get_min() < t.get_min())
        return true;
    return false;
}

void Time::add_minute(int minute)
{
    set_hour( (get_hour() + ( (get_min() + minute) / 60) ) % 24 );
    set_min( (get_min() + minute) % 60 );
}