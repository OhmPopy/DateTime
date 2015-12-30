#include <gtest/gtest.h>
#include <iostream>
#include <stdlib.h>

#include "DateTime.h"

int main( int argc, char **argv )
{

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
 
}

TEST(BaseTest,Can_Get_Current_Time)
{
	auto dateTime = DateTime::Now();

	ASSERT_NE(dateTime.GetYear(), 0);
}

TEST(BaseTest,Can_Instantiate_With_Custom_DateTime)
{
	auto dateTime = DateTime(1,1,2000);

	ASSERT_EQ(dateTime.GetYear(), 2000);
}

TEST(BaseTest,Can_Add_Years)
{
	auto dateTime = DateTime(1, 1, 2000);

	dateTime.AddYears(5);

	ASSERT_EQ(dateTime.GetYear(), 2005);
}

TEST(BaseTest, Can_Subtract_Years)
{
	auto dateTime = DateTime(1, 1, 2000);

	dateTime.SubtractYears(5);

	ASSERT_EQ(dateTime.GetYear(), 1995);
}

TEST(BaseTest, Can_Add_Months)
{
	auto dateTime = DateTime(1, 1, 2000);

	dateTime.AddMonths(4);

	ASSERT_EQ(dateTime.GetMonth(), 5);
}

TEST(BaseTest, Can_Subtract_Months)
{
	auto dateTime = DateTime(1, 1, 2000);

	dateTime.SubtractMonths(4);

	ASSERT_EQ(dateTime.GetMonth(), 9);
}

TEST(BaseTest, Can_Add_Days)
{
	auto dateTime = DateTime(1, 1, 2000);

	dateTime.AddDays(4);

	ASSERT_EQ(dateTime.GetDay(), 5);
}

TEST(BaseTest, Can_Subtract_Days)
{
	auto dateTime1 = DateTime(12, 27, 2015);
	dateTime1.SubtractDays(35);

	ASSERT_EQ(dateTime1.GetLongDateString(), "Sunday, November 22, 2015");
}

TEST(BaseTest, Can_Add_Hours)
{
	auto dateTime = DateTime(1, 1, 2000,1,1,1);

	dateTime.AddHours(4);

	ASSERT_EQ(dateTime.GetHour(), 5);
}

TEST(BaseTest, Can_Subtract_Hours)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1);

	dateTime.SubtractHours(7);

	ASSERT_EQ(dateTime.GetHour(), 18);
}

TEST(BaseTest, Can_Add_Minutes)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1);

	dateTime.AddMinutes(14);

	ASSERT_EQ(dateTime.GetMinute(), 15);
}

TEST(BaseTest, Can_Subtract_Minutes)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1);

	dateTime.SubtractMinutes(8);

	ASSERT_EQ(dateTime.GetMinute(), 53);
}

TEST(BaseTest, Can_Add_Seconds)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1);

	dateTime.AddSeconds(14);

	ASSERT_EQ(dateTime.GetSecond(), 15);
}

TEST(BaseTest, Can_Subtract_Seconds)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1);

	dateTime.SubtractSeconds(14);

	ASSERT_EQ(dateTime.GetSecond(), 47);
}

TEST(BaseTest, Can_Add_Milliseconds)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1,1);

	dateTime.AddMilliseconds(14);

	ASSERT_EQ(dateTime.GetMillisecond(), 15);
}

TEST(BaseTest, Can_Subtract_Milliseconds)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1, 1);

	dateTime.SubtractMilliseconds(14);

	ASSERT_EQ(dateTime.GetMillisecond(), 987);
}

TEST(BaseTest, Can_Get_Day_Of_Week_Of_Any_Date)
{
	auto dateTime = DateTime(1, 1, 2020, 1, 1, 1, 1);

	ASSERT_EQ(dateTime.GetDayOfWeek(), DayOfWeek::Wednesday);
}

TEST(BaseTest, Can_Get_Day_Of_Year_Of_Any_Date)
{
	auto dateTime = DateTime(10, 10, 1989, 1, 1, 1, 1);

	ASSERT_EQ(dateTime.GetDayOfYear(), 283);
}

TEST(BaseTest, Can_Get_Days_Of_Month_Of_Any_Date)
{
	auto dateTime = DateTime(10, 10, 1989, 1, 1, 1, 1);

	ASSERT_EQ(dateTime.GetDaysOfMonth(), 31);

	dateTime.AddMonths(2);

	ASSERT_EQ(dateTime.GetDaysOfMonth(), 31);
}

TEST(BaseTest, Can_Get_The_Name_Of_Day_Of_Any_Date)
{
	auto dateTime = DateTime(10, 10, 1989, 1, 1, 1, 1);

	auto te = dateTime.GetNameOfDay();

	ASSERT_EQ(dateTime.GetNameOfDay(), "Tuesday");

	dateTime.AddMonths(2);

	ASSERT_EQ(dateTime.GetNameOfDay(), "Sunday");
}


TEST(BaseTest, Can_Get_Month_Name_Of_Any_Date)
{
	auto dateTime = DateTime(10, 10, 1989, 1, 1, 1, 1);

	ASSERT_EQ(dateTime.GetNameOfMonth(), "October");
}

TEST(BaseTest, Can_Output_Formated_String_Of_Any_Date)
{
	auto dateTime = DateTime(10, 10, 1989, 12,30, 15, 1);

	auto re = dateTime.GetShortDateString();
	
	ASSERT_EQ(dateTime.GetShortTimeString(), "12:30:15");
	ASSERT_EQ(dateTime.GetLongTimeString(),  "12:30:15:1");
	ASSERT_EQ(dateTime.GetAsString(),        "10/10/1989 - 12:30:15");
	ASSERT_EQ(dateTime.GetShortDateString(), "10/10/1989");
	ASSERT_EQ(dateTime.GetLongDateString(),  "Tuesday, October 10, 1989");
}

TEST(BaseTest, Can_Add_Enough_Months_To_Increase_A_Year)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1, 1);

	dateTime.AddMonths(12);

	ASSERT_EQ(dateTime.GetYear(), 2001);
}

TEST(BaseTest, Can_Add_Enough_Days_To_Increase_A_Week)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1, 1);

	ASSERT_EQ(dateTime.GetDayOfWeek(), DayOfWeek::Saturday);

	dateTime.AddDays(7);

	ASSERT_EQ(dateTime.GetDayOfWeek(), DayOfWeek::Saturday);
}

TEST(BaseTest, Can_Add_Enough_Seconds_To_Increase_A_Day)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1, 1);

	dateTime.AddSeconds(86400);

	ASSERT_EQ(dateTime.GetDay(), 2);
}

TEST(BaseTest, Can_Add_Enough_Milliseconds_To_Increase_A_Minute)
{
	auto dateTime = DateTime(1, 1, 2000, 1, 1, 1, 1);

	dateTime.AddMilliseconds(60000);

	ASSERT_EQ(dateTime.GetMinute(), 2);
}

TEST(BaseTest, Can_Subtract_Enough_Months_To_Decrease_A_Year)
{
	auto dateTime = DateTime(5, 15, 2000);

	dateTime.SubtractMonths(420);

	ASSERT_EQ(dateTime.GetLongDateString(), "Saturday, May 15, 1965");
}

TEST(BaseTest,Can_Determine_Leap_Year_Of_Any_Date)
{
	auto dateTime = DateTime(1, 1, 2012, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime.IsLeapYear());
	ASSERT_TRUE(dateTime.IsLeapYear(2016));
}


TEST(CompareTest,Can_Compare_With_Greater_Than_Operator)
{
	auto dateTime1 = DateTime(1, 1, 2012, 1, 1, 1, 1);

	auto dateTime2 = DateTime(1, 1, 2011, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime1 > dateTime2);
}

TEST(CompareTest, Can_Compare_With_Less_Than_Operator)
{
	auto dateTime1 = DateTime(1, 1, 2012, 1, 1, 1, 1);

	auto dateTime2 = DateTime(1, 1, 2011, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime2 < dateTime1);
}

TEST(CompareTest, Can_Compare_With_Greater_Or_Equal_To_Operator)
{
	auto dateTime1 = DateTime(1, 1, 2011, 1, 1, 1, 1);
	auto dateTime2 = DateTime(1, 1, 2011, 1, 1, 1, 1);
	auto dateTime3 = DateTime(1, 1, 2012, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime2 >= dateTime1);
	ASSERT_TRUE(dateTime3 >= dateTime1);
}

TEST(CompareTest, Can_Compare_With_Less_Than_Or_Equal_To_Operator)
{
	auto dateTime1 = DateTime(1, 1, 2011, 1, 1, 1, 1);
	auto dateTime2 = DateTime(1, 1, 2011, 1, 1, 1, 1);
	auto dateTime3 = DateTime(1, 1, 2010, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime2 <= dateTime1);
	ASSERT_TRUE(dateTime3 <= dateTime1);
}

TEST(CompareTest, Can_Compare_With_Equal_To_Operator)
{
	auto dateTime1 = DateTime(1, 1, 2011, 1, 1, 1, 1);
	auto dateTime2 = DateTime(1, 1, 2011, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime2 == dateTime1);
}

TEST(CompareTest, Can_Compare_With_Not_Equal_To_Operator)
{
	auto dateTime1 = DateTime(1, 1, 2011, 1, 1, 1, 1);
	auto dateTime2 = DateTime(1, 1, 2015, 1, 1, 1, 1);

	ASSERT_TRUE(dateTime2 != dateTime1);
}

TEST(CompareTest, Can_Compare_TimeSpan_With_Greater_Than_Operator)
{
	auto timeSpan1 = TimeSpan(1, 1, 2012, 1, 1, 1, 1);

	auto timeSpan2 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);

	ASSERT_TRUE(timeSpan1 > timeSpan2);
}

TEST(CompareTest, Can_Compare_TimeSpan_With_Less_Than_Operator)
{
	auto timeSpan1 = TimeSpan(1, 1, 2012, 1, 1, 1, 1);

	auto timeSpan2 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);

	ASSERT_TRUE(timeSpan2 < timeSpan1);
}

TEST(CompareTest, Can_Compare_TimeSpan_With_Greater_Or_Equal_To_Operator)
{
	auto timeSpan1 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);
	auto timeSpan2 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);
	auto timeSpan3 = TimeSpan(1, 1, 2012, 1, 1, 1, 1);

	ASSERT_TRUE(timeSpan2 >= timeSpan1);
	ASSERT_TRUE(timeSpan3 >= timeSpan1);
}

TEST(CompareTest, Can_Compare_TimeSpan_With_Less_Than_Or_Equal_To_Operator)
{
	auto timeSpan1 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);
	auto timeSpan2 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);
	auto timeSpan3 = TimeSpan(1, 1, 2010, 1, 1, 1, 1);

	ASSERT_TRUE(timeSpan2 <= timeSpan1);
	ASSERT_TRUE(timeSpan3 <= timeSpan1);
}

TEST(CompareTest, Can_Compare_TimeSpan_With_Equal_To_Operator)
{
	auto timeSpan1 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);
	auto timeSpan2 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);

	ASSERT_TRUE(timeSpan2 == timeSpan1);
}

TEST(CompareTest, Can_Compare_TimeSpan_With_Not_Equal_To_Operator)
{
	auto timeSpan1 = TimeSpan(1, 1, 2011, 1, 1, 1, 1);
	auto timeSpan2 = TimeSpan(1, 1, 2015, 1, 1, 1, 1);

	ASSERT_TRUE(timeSpan2 != timeSpan1);
}


TEST(AssignmentTest, Can_Add_TimeSpan_To_Current_Date)
{
	auto dateTime1 = DateTime(5,15,2000);
	
	auto timeSpan = TimeSpan( 1, 0, 0, 0, 0, 0, 0);

	dateTime1 = dateTime1 + timeSpan;

	ASSERT_EQ(dateTime1.GetLongDateString(), "Tuesday, May 15, 2001");

	dateTime1 += timeSpan;

	ASSERT_EQ(dateTime1.GetLongDateString(), "Wednesday, May 15, 2002");
}

TEST(AssignmentTest, Can_Substract_TimeSpan_To_Current_Date)
{
	auto dateTime = DateTime(5, 15, 2000,5,4,20);

	auto timeSpan = TimeSpan(1, 1, 1, 1, 1, 1, 0);

	dateTime = dateTime - timeSpan;

	auto ye = dateTime.GetLongDateString();
	auto ti = dateTime.GetLongTimeString();

	ASSERT_EQ(dateTime.GetLongDateString(), "Wednesday, April 14, 1999");
	ASSERT_EQ(dateTime.GetLongTimeString(), "4:3:19:0");

	dateTime -= timeSpan;

	ASSERT_EQ(dateTime.GetLongDateString(), "Friday, March 13, 1998");
	ASSERT_EQ(dateTime.GetLongTimeString(), "3:2:18:0");
}

TEST(AssignmentTest, Can_Compute_TimeSpan_From_Two_Dates)
{
	auto dateTime1 = DateTime(12, 29, 2015, 1, 1, 1);

	auto dateTime2 = DateTime(9, 15, 1989, 1, 1, 1);

	auto timeSpan = dateTime1 - dateTime2;

	ASSERT_EQ(timeSpan.ToString(), "26 Years, 3 Months, 14 Days, 0 Hours, 0 Minutes, 0 Seconds, 0 Milliseconds");

	timeSpan = DateTime::CalculateTimeSpan(dateTime2, dateTime1);

	ASSERT_EQ(timeSpan.ToString(), "26 Years, 3 Months, 14 Days, 0 Hours, 0 Minutes, 0 Seconds, 0 Milliseconds");
}