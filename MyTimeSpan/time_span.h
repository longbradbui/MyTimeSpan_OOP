#ifndef TIME_SPAN_H
#define TIME_SPAN_H
#include <iostream>
using namespace std;

class TimeSpan
{
public:
    TimeSpan();
    TimeSpan(double seconds);
    TimeSpan(double hours, double minutes, double seconds);
    TimeSpan(double minutes, double seconds);
    int seconds() const;
    int minutes() const;
    int hours() const;
    void DefaultTime();
    void SetTime(double hours, double minutes, double seconds);
    void StandardizeTime(int seconds);
    TimeSpan operator+=(TimeSpan const &rhs);
    TimeSpan operator-=(TimeSpan const &rhs);
    TimeSpan operator+(const TimeSpan &rhs) const;
    TimeSpan operator-(const TimeSpan const &rhs) const;
    friend TimeSpan operator-(TimeSpan const &ts);
    friend bool operator<(TimeSpan const &lhs, TimeSpan const &rhs);
    friend bool operator>(TimeSpan const &lhs, TimeSpan const &rhs);
    friend bool operator<=(TimeSpan const &lhs, TimeSpan const &rhs);
    friend bool operator>=(TimeSpan const &lhs, TimeSpan const &rhs);
    friend bool operator==(TimeSpan const &lhs, TimeSpan const &rhs);
    friend bool operator!=(TimeSpan const &lhs, TimeSpan const &rhs);
    friend istream& operator>>(istream &istream, TimeSpan &rhs);
    friend ostream& operator<<(ostream &ostream, TimeSpan const &rhs);
private:
    int hours_;
    int minutes_;
    int seconds_;
};
#endif
