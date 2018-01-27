Summary:

This program takes in a user input of a year, and prints out a calendar
representative of that year to the console, taking into account all rules
associated with leap years. If the user enters an invalid year value, the
program will terminate. 



Running the program:

To compile, navigate to the directory in which PA1.c is stored within the
terminal window, and run
$ gcc -Wall -o PA1 PA1.c
To run the program following compilation, enter
$ ./PA1
Once the program launches, enter any positive integer year. 



Development challenges:

Initially, I had a hard time getting even simple programs to run and compile,
getting errors about unknown gcc tags. Eventually I found that copy/pasting
the compilation command from the assignment document was applying a different
"-" character to the tags and causing errors. Once this issue was resolved, 
development proceded pretty smoothly. In developing the logic of the program, 
I tried to find a way to minimize the number of repeated case statements, while
also avoiding functions which tie two discrete and potentially independant 
functions like month printing and offset calculation together, eventually
finding a logic which used only two. The algorithm was implemented without
major issues, aside from needing to chase a few off-by-1 errors in applying
offsets to the start of each month, and applying leap year logic. 



Loop invariants:

startDay() loop 1: This loop is run for the case where the year is in the
future. At the start of this loop, dayIndex is the value of the start day
for the year 2018+i, where i is always positive. It will increment this offset
index vaule by the shift in start day from the year 2018+i, to the year
2018+i+1. For example, for the case of the year 2018, the loop will take the
index of the day January 1st 2018, 1, representing a monday, and shift it by 1
to Tuesday, January 1st, 2019. If the year 2018+i is a leap year, the shift will
instead be 2 per loop iteration. The shift is performed by the function 
incrementStartDay(), which takes into account rollover behaviour. 

startDay() loop 2: Nearly identical to the loop above, this loop is run for the
case where the year is in the past. At the start of this loop, dayIndex is the
value of the start day for the year 2018+i, where i is always negagative. It
will increment this offset value by the shift in start day from the year
2018+i-1 (the -1 is necissary because we are interested in the year previous
to the i-1th year for the purposes of leap year checking). Here, the shift
is performed in a negative direction, -2 for a leap year, -1 for a non leap
year. The shift is performed by the function incrementStartDay(), which takes 
into account rollover behaviour. 

getMonthOffset() loop: This loop iterates upwards from january to the target
month. At the start of each loop iteration, i represents the month currently
being processed, for example, January on the 1st iteration, February on the 2nd,
etc. Each loop iteration adds the shift between the start day of that month, 
and the start day of the month that follows, by performing a modulo 7 operation
on the days in the currently processed month. Again, this is performed using
the incrementStartDay function to take rollover into account. At the conclusion
of this loop, dayIndex will have the offset value (0-6, with 0=sunday, 
1=monday, etc.) of the start day of the month entered to the function as a
parameter. 

printMonth() loop 1: This loop adds the initial blank space to the printout
of each month. Before the start of the loop, offset is set equal to the number
of days which show up as blank in that month. For example, an offset of 3 
means that the month starts with Sunday, Monday, and Tuesday blank, and begins
printing days at Wednesday. For each iteration, i represents the number of 
offset days already printed. It will execute until i=offset, so that the number 
of blank spaces printed is equal to the offset for that month. 

printMonth() loop 2: This loop picks up where the last loop left off, and begins
printing days. At the start of this loop, the console has just printed a number
of blank spaces to provide the offset without a newline, so this loop will
begin printing in the middle of a line. Offset is set to the number of blank
days at the start of the month, and is used to shift i to align with days of the
week correctly. The terminating condiiton is set to the day count of the month 
the function is being executed on plus 1, so that the last day is included in 
the loop execution. For each iteration, i, which starts at 1, represents the 
date value to be printed, and (i+offset)%7, computed late in the loop, 
represents the day index using the 0-6 convention used throughout the program. 
This loop has different behaviour at values of i<10, as it must add an extra 
space to single digit numbers to keep alignment intact. Every seven loops, 
triggered by the calculation (i+offset)%7, this loop will add a newline
character, starting the printing over at sunday for the next week. 

printYear() loop: This loop simply executes 12 times, iterating through the
months. At the start of each loop execution, i represents the index (0-11)
of the month to be printed.



References: 
Leap year calculation algorithm was derived from here: 
https://stackoverflow.com/questions/725098/leap-year-calculation
It works by checking if a year is evenly divisible by 4, using the modulo
operation. For cases where it is also divisible by 100 (modulo 100), it
must also be divisible by 400. Therefore an OR is performed between not
divisible by 100, and divisible by 400, which is then combined with the base
modulo 4 operator using AND. 
