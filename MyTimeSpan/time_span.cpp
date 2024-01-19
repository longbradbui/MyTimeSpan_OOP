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
    SetTime(0.0, 0.0, seconds);
}

TimeSpan::TimeSpan(double minutes, double seconds) {
    SetTime(0.0, minutes, seconds);
}

TimeSpan::TimeSpan(double hours, double minutes, double seconds) {
    SetTime(hours, minutes, seconds);
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
    SetTime(0.0, 0.0, 0.0);
}

void TimeSpan::SetTime(double hours, double minutes, double seconds) {
    double total_seconds = hours * 3600 + minutes * 60 + seconds;
    StandardizeTime(round(total_seconds));
}

void TimeSpan::StandardizeTime(int seconds)
{
    this->seconds_ = seconds % 60;
    this->minutes_ = (seconds / 60) % 60;
    this->hours_ = seconds / 3600;
}

TimeSpan TimeSpan::operator+(const TimeSpan& rhs) const
{
    TimeSpan result = *this;
    result.seconds_ += rhs.seconds_;
    result.minutes_ += +rhs.minutes_ + result.seconds_ / 60;
    result.seconds_ %= 60;
    result.hours_ += rhs.hours_ + result.minutes_ / 60;
    result.minutes_ %= 60;
    return result;
}

TimeSpan TimeSpan::operator-(const TimeSpan& rhs) const {
    TimeSpan result = *this;
    result.seconds_ -= rhs.seconds_;
    result.minutes_ -= rhs.minutes_;
    result.hours_ -= rhs.hours_;
    // Adjust for borrowing
    while (result.seconds_ < 0) {
        result.seconds_ += 60;
        result.minutes_--;
    }
    while (result.minutes_ < 0) {
        result.minutes_ += 60;
        result.hours_--;
    }
    return result;
}

TimeSpan TimeSpan::operator+=(TimeSpan const& rhs)
{
    int total_seconds_lhs = this->hours() * 3600 + this->minutes() * 60 + this->seconds();
    int total_seconds_rhs = rhs.hours() * 3600 + rhs.minutes() * 60 + rhs.seconds();
    *this = TimeSpan(total_seconds_lhs + total_seconds_rhs);
    return *this;
}

TimeSpan TimeSpan::operator-=(TimeSpan const& rhs)
{
    int total_seconds_lhs = hours() * 3600 + minutes() * 60 + seconds();
    int total_seconds_rhs = rhs.hours() * 3600 + rhs.minutes() * 60 + rhs.seconds();
    *this = TimeSpan(total_seconds_lhs - total_seconds_rhs);
    return *this;
}

TimeSpan operator-(TimeSpan const& ts)
{
    return TimeSpan(-ts.hours_, -ts.minutes_, -ts.seconds_);
}

bool operator<(TimeSpan const& lhs, TimeSpan const& rhs)
{
    return lhs.hours() < rhs.hours() || lhs.minutes() < rhs.minutes() || lhs.seconds() < rhs.seconds();
}

bool operator>(TimeSpan const& lhs, TimeSpan const& rhs)
{
    return lhs.hours() > rhs.hours() || lhs.minutes() > rhs.minutes() || lhs.seconds() > rhs.seconds();
}

bool operator<=(TimeSpan const& lhs, TimeSpan const& rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(TimeSpan const& lhs, TimeSpan const& rhs)
{
    return (lhs > rhs) || (lhs == rhs);
}

bool operator==(TimeSpan const& lhs, TimeSpan const& rhs)
{
    return lhs.hours() == rhs.hours() && lhs.minutes() == rhs.minutes() && lhs.seconds() == rhs.seconds();
}

bool operator!=(TimeSpan const& lhs, TimeSpan const& rhs)
{
    return !(lhs == rhs);
}

ostream& operator<<(ostream& ostream, TimeSpan const& rhs)
{
    ostream << "Hours: ";
    ostream << rhs.hours();
    ostream << ", Minutes: ";
    ostream << rhs.minutes();
    ostream << ", Seconds: ";
    ostream << rhs.seconds();
    return ostream;
}

istream& operator>>(istream& istream, TimeSpan& rhs)
{
    int hours, minutes, seconds;
    istream >> hours >> minutes >> seconds;
    rhs.SetTime(hours, minutes, seconds);
    return istream;
}