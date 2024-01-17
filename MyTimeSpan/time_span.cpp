#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include "time_span.h"

TimeSpan::TimeSpan()
{
    this->DefaultTime();
}

TimeSpan::TimeSpan(double seconds) {
    SetTime(seconds);
}

TimeSpan::TimeSpan(double hours, double minutes, double seconds) {
    SetTime(hours, minutes, seconds);
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds) {
    SetTime(hours, minutes, seconds);
}

TimeSpan::TimeSpan(double minutes, double seconds) {
    SetTime(0.0, minutes, seconds);
}

TimeSpan::TimeSpan(int minutes, int seconds) {
    SetTime(0, minutes, seconds);
}

int TimeSpan::seconds() const
{
    return this->seconds_;
}

int TimeSpan::minutes() const
{
    return this->minutes_;
}

int TimeSpan::hours() const
{
    return this->hours_;
}

void TimeSpan::DefaultTime()
{
    this->hours_ = 0;
    this->minutes_ = 0;
    this->seconds_ = 0;
}

void TimeSpan::SetTime(double seconds) {
    StandardizeTime(static_cast<int>(round(seconds)));
}

void TimeSpan::SetTime(double hours, double minutes, double seconds) {
    StandardizeTime(static_cast<int>(round(hours * 3600 + minutes * 60 + seconds)));
}

void TimeSpan::SetTime(int hours, int minutes, int seconds) {
    StandardizeTime(hours * 3600 + minutes * 60 + seconds);
}

void TimeSpan::StandardizeTime(int seconds)
{
    this->seconds_ = seconds % 60;
    this->minutes_ = (seconds / 60) % 60;
    this->hours_ = seconds / 3600;
}

TimeSpan operator+(TimeSpan lhs, TimeSpan const &rhs)
{
    TimeSpan result;
 
    result.seconds_ = lhs.seconds_ + rhs.seconds_;

    result.minutes_ = lhs.minutes_ + rhs.minutes_ + result.seconds_ / 60;
    result.seconds_ %= 60;

    result.hours_ = lhs.hours_ + rhs.hours_ + result.minutes_ / 60;
    result.minutes_ %= 60;
 
    return result;
}

TimeSpan operator-(TimeSpan lhs, TimeSpan const &rhs)
{
    TimeSpan result;
    int total_seconds_lhs = lhs.hours() * 3600 + lhs.minutes() * 60 + lhs.seconds();
    int total_seconds_rhs = rhs.hours() * 3600 + rhs.minutes() * 60 + rhs.seconds();

    int different_seconds = total_seconds_lhs - total_seconds_rhs;

    
    
    result.seconds_ = different_seconds % 60;
    result.minutes_ = (different_seconds % 60) / 60;
    result.hours_ = different_seconds / 3600;
    return result;
}
TimeSpan TimeSpan::operator+=(TimeSpan const &rhs)
{
    int total_seconds_lhs = this -> hours() * 3600 + this -> minutes() * 60 + this -> seconds();
    int total_seconds_rhs = rhs.hours() * 3600 + rhs.minutes() * 60 + rhs.seconds();
    *this = TimeSpan(total_seconds_lhs + total_seconds_rhs);
    return *this; 
}

TimeSpan TimeSpan::operator-=(TimeSpan const &rhs)
{
    int total_seconds_lhs = this->hours() * 3600 + this->minutes() * 60 + this->seconds();
    int total_seconds_rhs = rhs.hours() * 3600 + rhs.minutes() * 60 + rhs.seconds();
    *this = TimeSpan(total_seconds_lhs - total_seconds_rhs);
    return *this;
}

TimeSpan operator-(TimeSpan const &ts)
{
    return TimeSpan(-ts.hours(), -ts.minutes(), -ts.seconds());
}

bool operator<(TimeSpan const &lhs, TimeSpan const &rhs)
{
    return lhs.hours() < rhs.hours() || lhs.minutes() < rhs.minutes() || lhs.seconds() < rhs.seconds();
}

bool operator>(TimeSpan const &lhs, TimeSpan const &rhs)
{
    return lhs.hours() > rhs.hours() || lhs.minutes() > rhs.minutes() || lhs.seconds() > rhs.seconds();
}

bool operator<=(TimeSpan const &lhs, TimeSpan const &rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(TimeSpan const &lhs, TimeSpan const &rhs)
{
    return (lhs > rhs) || (lhs == rhs);
}

bool operator==(TimeSpan const &lhs, TimeSpan const &rhs)
{
    return lhs.hours() == rhs.hours() && lhs.minutes() == rhs.minutes() && lhs.seconds() == rhs.seconds();
}

bool operator!=(TimeSpan const &lhs, TimeSpan const &rhs)
{
    return !(lhs == rhs);
}

ostream& operator<<(ostream& ostream, TimeSpan const &rhs)
{
    ostream << "Hours: ";
    ostream << rhs.hours();
    ostream << ", Minutes: ";
    ostream << rhs.minutes();
    ostream << ", Seconds: ";
    ostream << rhs.seconds();
    return ostream;
}

istream& operator>>(istream &istream, TimeSpan &rhs)
{
    int hours, minutes, seconds;
    istream >> hours >> minutes >> seconds;
    rhs.SetTime(hours, minutes, seconds);
    return istream;
}
