#ifndef TIME_SPAN_H
#define TIME_SPAN_H
#include <iostream>
using namespace std;
class TimeSpan
{
private:
    int hours_;
    int minutes_;
    int seconds_;
public:
    TimeSpan();
    TimeSpan(double seconds);
    TimeSpan(double hours, double minutes, double seconds);
    TimeSpan(int hours, int minutes, int seconds);
    TimeSpan(double minutes, double seconds);
    TimeSpan(int minutes, int seconds);
    int seconds() const;
    int minutes() const;
    int hours() const;
    void DefaultTime();
    void SetTime(double seconds);
    void SetTime(double hours, double minutes, double seconds);
    void SetTime(int hours, int minutes, int seconds);
    void StandardizeTime(int seconds);
    // Overriding << and >> 
    friend istream& operator>>(istream& istream, TimeSpan& rhs);
    friend ostream& operator<<(ostream& ostream, TimeSpan const& rhs);
    // Overriding operators and unary negation
    friend TimeSpan operator+(TimeSpan lhs, TimeSpan const& rhs);
    friend TimeSpan operator-(TimeSpan lhs, TimeSpan const& rhs);
    friend TimeSpan operator-(TimeSpan const& ts);
    TimeSpan operator+=(TimeSpan const& rhs);
    TimeSpan operator-=(TimeSpan const& rhs);
    // Overriding comparisons
    friend bool operator<(TimeSpan const& lhs, TimeSpan const& rhs);
    friend bool operator>(TimeSpan const& lhs, TimeSpan const& rhs);
    friend bool operator<=(TimeSpan const& lhs, TimeSpan const& rhs);
    friend bool operator>=(TimeSpan const& lhs, TimeSpan const& rhs);
    friend bool operator==(TimeSpan const& lhs, TimeSpan const& rhs);
    friend bool operator!=(TimeSpan const& lhs, TimeSpan const& rhs);
};
#endif
