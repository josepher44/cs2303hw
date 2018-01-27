/*
    PA1.c
    Author: Joe Gallagher
    joedgallagher@wpi.edu
    CS2303 Assignment #1, C2018
*/


#include <stdio.h>


/**
 * Returns whether or not a given year is a leap year
 * @param year Year to check
 * @return Char, 1 if leap year, 0 if not
*/
char isLeapYear(int year)
{
    /*
    Leap year check comparison
    True if the year is divisible by 4, unless divisible by 100 and not 400
    */
    if ((year%100 != 0 || year%400 == 0) && (year%4)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/**
 * Shifts a day index by the specified value, taking positive and negative
 * rollover into account. 
 * @param index Starting index, measured 0-6, with 0=Sunday, 1=Monday, etc.
 * @param delta Number of days to shift
 * @return Shifted index
*/
char incrementStartDay(char index, char delta)
{
    index=index+delta;
    if(index>6)
    {
        index=index-7;
    }
    else if(index<0)
    {
        index=index+7;
    }
    return index;
}


/**
* Calculates the starting day of a given year, by comparing to a reference year
* @param year Year to compare
* @return Char with vale from 0-6, with 0=Sunday, 1=Monday, etc.
*/
char startDay(int year)
{
    /*
    Declare variables. 
    -i is a loop incrementor
    -deltaYear is the difference between the input year and reference year 2018
    -dayIndex is the index of the first day of the current year, with 0=Sunday,
     1=Monday, etc. It is initialized to 1 since 2018, the reference year, 
     started on a Monday
    */
    int i;
    int deltaYear=0;
    char dayIndex=1;
    
    //Calculates the delta year. Positive values are in the future
    deltaYear=year-2018;
    
    //For case year==2018, else-if chain below does not run, use initial value
    
    //Adjust dayIndex for case year>2018
    if(year>2018)
    {
        for(i=0; i<deltaYear; i++)
        {
            /*
            At the start of this loop, dayIndex is the value of the start day
            for the year 2018+i, where i is always positive

            Check if the year being evaluated by this loop iteration is a
            leap year. If it is, the shift to the next year is +2, otherwise,
            it is +1. Increment dayIndex accordingly
            */
            if(isLeapYear(2018+i)==1)
            {
                dayIndex = incrementStartDay(dayIndex, 2);
            }
            else
            {
                dayIndex = incrementStartDay(dayIndex, 1);
            }
        }
        //At the end of this loop, dayIndex has the start day index of the target year
    }
    //Adjust dayIndex for case year<2018
    else if (year<2018)
    {
        for(i=0; i>deltaYear; i--)
        {
            /*
            At the start of this loop, dayIndex is the value of the start day
            for the year 2018+i, where i is always negative

            Check if the year being evaluated by this loop iteration is a
            leap year. If it is, the shift to the next year is +2, otherwise,
            it is +1. Increment dayIndex accordingly
            */
            if(isLeapYear(2018+i-1)==1)
            {
                dayIndex = incrementStartDay(dayIndex, -2);
            }
            else
            {
                dayIndex = incrementStartDay(dayIndex, -1);
            }
        }
        //At the end of this loop, dayIndex has the start day index of the target year
    }
    
    //return index of target year
    return dayIndex;
}


/**
* Calculates the number of days in a given month index
* @param year Year to compare, for purposes of leap year checking
* @param month Month, from 0-11, with 0=January, 1=February, etc
* @return Int value of the number of days in a month
*/
int getDaysInMonth(int year, char month)
{
    //Declare variables. daysInMonth holds the return value
    int daysInMonth;
    
    switch(month)
    {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
        {
            daysInMonth=31;
            break;
        }
        case 3:
        case 5:
        case 8:
        case 10:
        {
            daysInMonth=30;
            break;
        }
        case 1:
        {
            if (isLeapYear(year)==1)
            {
                daysInMonth=29;
                break;
            }
            else
            {
                daysInMonth=28;
                break;
            }
        }
    }
    return daysInMonth;
}


/**
* Calculates the amount to offset the starting day of a given month
* @param year Year in which to calculate the offset
* @param month Month, from 0-11, with 0=January, 1=February, etc
* @return Char with vale from 0-6, with 0=Sunday, 1=Monday, etc.
*/
char getMonthOffset(int year, char month)
{
    /*
    Declare variables. dayIndex stored the index (0-6) of the start day for
    the month being worked on. i is a loop incrementor.
    */
    char dayIndex;
    int i;
    
    dayIndex = startDay(year);
    /*Loop that adds an offset value associated with the days in each month, 
    up to the month the total value is being calculated for. The loop starts
    at i=0 representing January. 
    */
    for (i=0; i<month; i++)
    {
        /*
        At the start of each loop iteration, i represents the month to add
        Modulo 7 finds the number of days past whole weeks that the month
        runs. This increment is then added to the dayIndex Value. At the start
        of each loop, dayIndex is the offset value for the 1st day of the ith
        month. 
        */
        dayIndex = incrementStartDay(dayIndex, getDaysInMonth(year, i)%7);
    }
    //At the end of this loop, dayIndex has the index (0-6) of the start day
    //for the target month
    
    return dayIndex;
}

/**
* Prints the name of a month with correct formatting, given the numeric 0-11 
* value of a month. 
* @param year Year to be printed with the month
* @param month Month, from 0-11, with 0=January, 1=February, etc
*/
void printMonthName(int year, char month)
{
    switch (month)
    {
        case 0:
            printf("January %d\n\n", year);
            break;
        case 1:
            printf("February %d\n\n", year);
            break;
        case 2:
            printf("March %d\n\n", year);
            break;
        case 3:
            printf("April %d\n\n", year);
            break;
        case 4:
            printf("May %d\n\n", year);
            break;
        case 5:
            printf("June %d\n\n", year);
            break;
        case 6:
            printf("July %d\n\n", year);
            break;
        case 7:
            printf("August %d\n\n", year);
            break;
        case 8:
            printf("September %d\n\n", year);
            break;
        case 9:
            printf("October %d\n\n", year);
            break;
        case 10:
            printf("November %d\n\n", year);
            break;
        case 11:
            printf("December %d\n\n", year);
            break;
    }
}

/**
* Prints a complete month in the console
* @param year Year associated with the month
* @param month Month, from 0-11, with 0=January, 1=February, etc
*/
void printMonth(int year, char month)
{
    /*
    Declare variables. Offset stores the number of days to print as blank
    at the start of a month before beginning with day 1. i is a loop incrementor
    */
    char offset;
    int i;
    
    printMonthName(year, month);
    printf(" Sun   Mon   Tue   Wed   Thu   Fri   Sat\n");
    offset = getMonthOffset(year, month);
    
    /*
    Print blank spaces to shift the 1st day of the month to the correct day
    of the week
    */
    for (i=0;i<offset;i++)
    {
        /*
        At the start of each loop iteration, offset-i represents the number
        of times to print an offset spacing remaining, to shift day 1 to the
        correct day of the week
        */
        printf("      ");
    }
    
    //Print every day in the month
    for (i=1; i<getDaysInMonth(year, month)+1; i++)
    {
        /*
        At the start of this loop, i represents the day to be printed, i+offset
        represents the current day of the week. 
        */
        
        //Add extra space for single digit days to maintain alignment
        if (i<10)
        {
            printf("   %d  ",i);
        }
        else
        {
            printf("  %d  ",i);
        }
        //add a newline after saturday
        if((i+offset)%7==0)
        {
            printf("\n");
        }
    }
    /*
    At the end of this loop, i matches the day count of the target month, and
    the entire month has been printed to the terminal window
    */
    
    //provide whitespace between months
    printf("\n\n");
}

/**
* Prints the entirety of a calendar for the year input by the user
* @param year Year to print
*/
void printCalendar(int year)
{
    //declaration of variables. month is a loop incrementor
    char month;
    
    //Iterate through 12 months and print each one sequentially
    for(month=0; month<12; month++)
    {
        /*
        At the start of the loop, i represents the month to be printed
        */
        printMonth(year, month);
    }
    //At the end of this loop, the entire calendar is printed

}
    
/**
* Main class which prompts the user to enter a year, checks if the user input
* is valid, and prints a calendar representing that year to the console
* @return Arbitrary program termination return value
*/
int main(void)
{
    //declaration of variables. year stores the year the function is run on
    int year;

    //Print user prompts
    printf("                        Monthly Calendar Generator\n\n");
    printf("Please enter a year for this calendar:- ");
    scanf("%d", &year);
    
    /*
    Check if year is valid, will return true for negative numbers and non
    integer values
    */
    if(year<0)
    {
        printf("ERROR: Invalid year entered, program will terminate. "
               "Entry must be a positive integer value\n");
    }
    else
    {
        //Echo user input
        printf("Year is %d\n\n",year);
        
        //Print Calendar
        printCalendar(year);
    }

    //Terminate program
    return 0;
}
