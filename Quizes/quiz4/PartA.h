#ifndef TIME_H
#define TIME_H

class Time
{
    public:
        Time(int h = 0,int m = 0);
        void print_time();
        void set_min(int m);
        void set_hour(int h);
        int get_min();
        int get_hour();
        bool is_equal(Time &t);
        bool is_earlier(Time &t);
        void add_minute(int minute);

    private:
        int hour;
        int minutes;
};

#endif