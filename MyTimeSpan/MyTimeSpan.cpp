#include <iostream>
#include "time_span.h"
using namespace std;

/*TESTING DECLARATION*/
int totalTests = 0;
int successfulTests = 0;
#define SUCCESS_COLOR "\x1b[1;32m"
#define FAIL_COLOR "\x1b[1;31m"
#define CLEAR_COLOR "\x1b[1;0m"
void RunTest(bool (*testFn)(), char const* testName) {
    printf("Running %s ...\n", testName);
    totalTests++;
    if (testFn()) {
        printf(SUCCESS_COLOR "%s Succeeded\n" CLEAR_COLOR, testName);
        successfulTests++;
    }
    else {
        printf(FAIL_COLOR "%s Failed\n" CLEAR_COLOR, testName);
    }
}
#define RUNTEST(WHAT) RunTest(WHAT, #WHAT)
/***************************************************************************/
bool CheckValues(TimeSpan time, int hours, int minutes, int seconds)
{
    if ((time.hours() != hours) || (time.minutes() != minutes) || (time.seconds()
        != seconds))
    {
        return false;
    }
    return true;
}
bool TestZeros()
{
    TimeSpan ts(0, 0, 0);
    return CheckValues(ts, 0, 0, 0);
}
bool TestFloatSeconds()
{
    TimeSpan ts(127.86);
    return CheckValues(ts, 0, 2, 8);
}
bool TestNegativeMinute()
{
    TimeSpan ts(8, -23, 0);
    return CheckValues(ts, 7, 37, 0);
}
bool TestNegativeHour()
{
    TimeSpan ts(-3, 73, 2);
    return CheckValues(ts, -1, -46, -58);
}
bool TestUnaryNegation()
{
    TimeSpan ts(1, 2, 3);
    return CheckValues(-ts, -1, -2, -3);
}
bool TestAdd()
{
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 + ts2 + ts3 + ts4;
    return CheckValues(add_it_up, 4, 7, 5);
}
bool TestSubtract()
{
    TimeSpan ts1(8, 12, 59), ts2(1, 4, 3);
    TimeSpan sub_it_all = ts1 - ts2;
    return CheckValues(sub_it_all, 7, 8, 56);
}
bool TestAddInPlace()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, 6, 7, 8)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}
bool TestSubtractionInPlace()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, 4, 5, 6)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}
bool TestLessThan() {
    TimeSpan ts1(10, 12, 30);
    TimeSpan ts2(11, 50, 0);
    TimeSpan ts3(70, 50);
    TimeSpan ts4(1, -10, 0);
    return ts1 < ts2 && ts3 < ts4;
}
bool TestGreaterThan() {
    TimeSpan ts1(-10, -10, -10);
    TimeSpan ts2(5, 5, 5);
    TimeSpan ts3(-10, 700, 10);
    TimeSpan ts4(30, 10);
    return -ts2 > ts1 && ts3 > ts4;
}
bool TestEqual() {
    TimeSpan ts1(3, 4, 5);
    TimeSpan ts2(6, 7, 8);
    TimeSpan ts3(9, 11, 13);
    return ts3 == (ts1 + ts2);
}
bool TestUnequal() {
    TimeSpan ts1(10, 10, 10);
    TimeSpan ts2(11, -50, 10);
    return !(ts1 != ts2);
}
bool TestLessThanOrEqual() {
    TimeSpan ts1(8, 9, 10);
    TimeSpan ts2(7, 120, 10);
    return ts1 < ts2 || ts1 == ts2;
}
bool TestGreaterThanOrEqual() {
    TimeSpan ts1(12, 10, -120);
    TimeSpan ts2(12, 8, 0);
    return ts1 > ts2 || ts1 == ts2;
}
int main()
{
    /* RUN TEST */
    RUNTEST(TestZeros);
    RUNTEST(TestUnaryNegation);
    RUNTEST(TestFloatSeconds);
    RUNTEST(TestNegativeMinute);
    RUNTEST(TestNegativeHour);
    RUNTEST(TestAdd);
    RUNTEST(TestAddInPlace);
    RUNTEST(TestSubtract);
    RUNTEST(TestSubtractionInPlace);
    RUNTEST(TestLessThan);
    RUNTEST(TestGreaterThan);
    RUNTEST(TestEqual);
    RUNTEST(TestUnequal);
    RUNTEST(TestLessThanOrEqual);
    RUNTEST(TestGreaterThanOrEqual);
    if (successfulTests < totalTests) printf(FAIL_COLOR);
    printf("%d/%d tests succeeded\n\n", successfulTests, totalTests);
    printf(CLEAR_COLOR); 
    /************************************************************/
    /* Professor's Test Cases */
    cout << "Testing Arithmetic Operations" << endl;
    if (TestZeros()) {
        cout << "Passed: Test with zero" << endl;
    }
    else {
        cout << "Failed: Test With zero" << endl;
    }
    if (TestFloatSeconds()) {
        cout << "Passed: Test with float seconds" << endl;
    }
    else {
        cout << "Failed: Test with float seconds" << endl;
    }
    if (TestNegativeHour()) {
        cout << "Passed: Test with negative hours" << endl;
    }
    else {
        cout << "Failed: Test with negative hours" << endl;
    }
    if (TestNegativeMinute()) {
        cout << "Passed: Test with negative minutes" << endl;
    }
    else {
        cout << "Failed: Test with negative minutes" << endl;
    }
    if (TestUnaryNegation()) {
        cout << "Passed: Test with unary negation" << endl;
    }
    else {
        cout << "Failed: Test with unary negation" << endl;
    }
    if (TestAdd()) {
        cout << "Passed: Test with adding time span" << endl;
    }
    else {
        cout << "Failed: Test with adding time span" << endl;
    }
    if (TestSubtract()) {
        cout << "Passed: Test with subtracting time span" << endl;
    }
    else {
        cout << "Failed: Test with subtracting time span" << endl;
    }
    if (TestAddInPlace()) {
        cout << "Passed: Test with addition assignment time span" << endl;
    }
    else {
        cout << "Failed: Test with addition assignment time span" << endl;
    }
    if (TestSubtractionInPlace()) {
        cout << "Passed: Test with subtraction assignment time span" << endl;
    }
    else {
        cout << "Failed: Test with subtraction assignment time span" << endl;
    }
    if (TestLessThan()) {
        cout << "Passed: Test with less than operator" << endl;
    }
    else {
        cout << "Failed: Test with less than operator" << endl;
    }
    if (TestGreaterThan()) {
        cout << "Passed: Test with greater than operator" << endl;
    }
    else {
        cout << "Failed: Test with greater than operator" << endl;
    }
    if (TestEqual()) {
        cout << "Passed: Test with equal operator" << endl;
    }
    else {
        cout << "Failed: Test with equal operator" << endl;
    }
    if (TestUnequal()) {
        cout << "Passed: Test with unequal operator" << endl;
    }
    else {
        cout << "Failed: Test with unequal operator" << endl;
    }
    if (TestLessThanOrEqual()) {
        cout << "Passed: Test with less than or equal operator" << endl;
    }
    else {
        cout << "Failed: Test with less than or equal operator" << endl;
    }
    if (TestGreaterThanOrEqual()) {
        cout << "Passed: Test with greater than or equal operator" << endl;
    }
    else {
        cout << "Failed: Test with greater than or equal operator" << endl;
    }
    cout << "\nTesting Formating" << endl;
    TimeSpan defaultTime;
    cout << defaultTime << std::endl;
    TimeSpan fromSeconds1(3665); 
    cout << fromSeconds1 << endl;
    TimeSpan fromSeconds2(-190); 
    cout << fromSeconds2 << endl;
    TimeSpan fromSeconds3(380.5); 
    cout << fromSeconds3 << endl;
    TimeSpan fromSeconds4(127.86);
    cout << fromSeconds4 << endl;
    TimeSpan fromHoursMinutesSecond1(3, -90, 120); 
    cout << fromHoursMinutesSecond1 << endl;
    TimeSpan fromHoursMinutesSecond2(8, -23, 0); 
    cout << fromHoursMinutesSecond2 << endl;
    TimeSpan fromHoursMinutesSecond3(-3, 73, 2); 
    cout << fromHoursMinutesSecond3 << endl;
    TimeSpan fromMinutesSeconds1(7, -3);
    cout << fromMinutesSeconds1 << endl;
    TimeSpan fromMinutesSeconds2(7.0, -3.6);
    cout << fromMinutesSeconds2 << endl;
    TimeSpan fromMinutesSeconds3(-3, 5);
    cout << fromMinutesSeconds3 << endl;
    TimeSpan fromFloats1(1.5, 30.75, 45.3);
    cout << fromFloats1 << endl;
    TimeSpan fromDoubles1(1.5, 4.0, -10.0); 
    cout << fromDoubles1 << endl;
    TimeSpan a1(1, 4, 3);
    TimeSpan a2(8, 12, 59);
    TimeSpan a3 = a1 + a2;
    cout << a3 << endl;
    TimeSpan a4(5);
    TimeSpan a5(7, 0);
    TimeSpan a6(4, 0, 0);
    TimeSpan a7 = a4 + a5 + a6;
    cout << a7 << endl;
    TimeSpan a8 = a2 - a1;
    cout << a8 << endl;
    TimeSpan a9(5, 6, 7);
    TimeSpan a10(1, 1, 1);
    a9 += a10;
    cout << a9 << endl;
    TimeSpan a11(3.5, 5.9, 10.0);
    TimeSpan a12(4, 2, 51);
    a11 += a12;
    cout << a11 << endl;
    TimeSpan a13(9, 10, 55);
    TimeSpan a14(4, 2, 51);
    a13 -= a14;
    cout << a13 << endl;
    TimeSpan original(2.0, 3.0, 4.5);
    TimeSpan negated = -original;
    cout <<  original << endl;
    cout <<  negated << endl;
    TimeSpan a15(10, 10, 10);
    TimeSpan a16(10, 11, -50);
    cout << ((a15 == a16) ? "The two timespans are equal" : "The two timespans are not equal") << endl;
    cout << ((a15 != a16) ? "The two timespans are not equal" : "The two timespans are equal") << endl;
    cout << "Please input the desired time span: ";
    TimeSpan ts;
    cin >> ts;
    cout << ts;
    return 0;
}