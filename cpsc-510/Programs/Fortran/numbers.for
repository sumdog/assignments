C  Fortran program to take input of
C  n numbers, determine average
C  and number of inputs above average
C  -Sumit Khanna - cpsc-510/Thompson
C
C2345678901234567890123456789
C Initalize all Vars and Formats 
       DIMENSION A(1)
       ISUM=0
       IABOVE=0
       IAVERAGE=0
C Read user input
       PRINT *, 'Enter the total number of integers and then <enter>'
       PRINT *, 'Then enter each integer, one per line'
       READ *,N,(A(I),I=1,N)
       DO 100 X=1,N,1
       ISUM=ISUM+A(X)
100    CONTINUE
C Perform Calculations
       IAVERAGE=ISUM/N
       DO 200 Y=1,N,1
       IF ( A(Y) .GT. IAVERAGE ) IABOVE=IABOVE+1
200    CONTINUE
C Show Output
       PRINT *,'Average: ',IAVERAGE
       PRINT *,'Numbers Above Average: ',IABOVE
       END
