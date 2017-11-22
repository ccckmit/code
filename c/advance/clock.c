/*
Beginning C, Third Edition
 By Ivor Horton
 ISBN: 1-59059-253-0
 Published: Apr 2004
 Publisher: apress

*/

#include <stdio.h>
#include <time.h>

void main()
{
  long count = 100000000;          /* Number of loop iterations */
  long i = 0;                      /* Loop counter              */
  time_t calendar = 0;             /* Holds calendar time       */
  clock_t now = 0;                 /* Holds initial clock time  */
  int interval = 3;                /* Seconds interval for o/p  */
  int elapsed = 0;                 /* Elapsed clock time secs.  */

  calendar = time(NULL);           /* Get current calendar time */
  now = clock();                   /* Get current clock time    */
  printf("Initial clock time = %d Initial calendar time = %d\n",
                                                       now, calendar);
    
    for(i = 0L ; i<count ; i++)
    {
      elapsed = (clock()-now)/CLOCKS_PER_SEC;
      if(elapsed>=interval)
      {
        interval += 3;
        printf("\nElapsed = %ld seconds  iterations = %ld", elapsed, i);
      }
    }

  printf("\nCPU time for %ld interations is %.2lf seconds\n",
                                count, (double)(clock()-now)/CLOCKS_PER_SEC );
  printf("\Final clock time = %d Final calendar time = %d\n",
                                                       clock(), time(NULL));
  printf("\nElapsed calendar time to execute the program is %lf\n",
                                           difftime(time(NULL), calendar));
}