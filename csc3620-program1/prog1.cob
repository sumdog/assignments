*****************************************************************
*                                                               
*  Program #1 for Hume's File Processing Class
*
*  Compiled and tested with tinycobol for Linux 
*   and Compaq Cobol on VMS
*
*  Name: Sumit Khanna
*  
*                                                               
*****************************************************************

identification division.

program-id.   check-data.
author.       Sumit Khanna.

environment division.

configuration section.
source-computer. GNU-Linux-IA32.

input-output section.
file-control.
    select input-file      assign to "check.dat".
    select valid-file      assign to "valid.out".
    select exception-file  assign to "exception.out".

data division.

file section.

fd  input-file
        record contains 61 characters.
01  input-line              pic x(61).

fd  valid-file
        record contains 80 characters.
01  valid-report-line       pic x(80).

fd  exception-file
        record contains 80 characters.
01  exception-report-line   pic x(80).

working-storage section.

01  input-record-in.
    05  name-in.
        10  last-name-in            pic x(15).
        10  first-name-in           pic x(10).
    05  acct-num-in                 pic 9(4).
    05  acct-sum-in                 pic 9(3).
    05  birthdate-in.
        10  month-in                pic 9(2).
        10  day-in                  pic 9(2).
        10  year-in                 pic 9(4).
    05  age-in                      pic 9(3).
    05  discount-rate-in            pic v999.
    05  balance-in                  pic 9(5)v99.
    05  balance-sign-in             pic x(1).
    05  interest-in                 pic 9(4)v99.
    05  credit-rating-in            pic x(1).

01  file-eof-flags.
    05  input-file-flag             pic x(1)   value "N".
        88  end-of-input-file                  value "Y".

01  error-message-area.
    05  err-msg-1  pic x(35) value "1  Last name missing               ".
    05  err-msg-2  pic x(35) value "2  Acct number field missing       ".
    05  err-msg-3  pic x(35) value "3  Name contains invalid characters".
    05  err-msg-4  pic x(35) value "4  Acct Num/acct Sum not numeric   ".
    05  err-msg-5  pic x(35) value "5  Check sum test fails            ".
    05  err-msg-6  pic x(35) value "6  Birthdate/age not numeric       ".
    05  err-msg-7  pic x(35) value "7  Birthdate not in range          ".
    05  err-msg-8  pic x(35) value "8  Age test fails                  ".
    05  err-msg-9  pic x(35) value "9  Credit rating invalid           ".
    05  err-msg-10 pic x(35) value "10 Discount rate not numeric       ".
    05  err-msg-11 pic x(35) value "11 Discount & credit rate: no match".
    05  err-msg-12 pic x(35) value "12 Balance/interest not numeric    ".
    05  err-msg-13 pic x(35) value "13 Interest amount too large       ".

01  report-control-variables.
    05  error-detected-flag          pic x(1).
        88  error-has-been-detected            value "Y".
        88  no-error-detected                  value "N".

    05  exception-record-count      pic 9(3) value zero.
    05  valid-record-count          pic 9(3) value zero.
    05  exception-line-count        pic 9(2) value zero.
    05  valid-line-count            pic 9(2) value zero.
    05  max-exception-line-count    pic 9(2) value 66.
    05  max-valid-line-count        pic 9(2) value 66.

01  report-line-templates.
    05  record-echo-line.
        10  record-count-out        pic zz9.
        10  filler                  pic x(4) value ".   ".
        10  record-echo-out         pic x(61).

    05  error-msg-line.
        10  filler                  pic x(10) value spaces.
        10  err-msg-out             pic x(35).

*    05  exception-file-header.

*    05  exception-page-header.

*    05  valid-file-header.

*    05  valid-page-header.

*    05  exception-file-footer.

*    05  valid-file-footer.

*variables for check #3
01 check-3-variables.
     05 name-test-area       pic x(25).
     05 name-letter-area redefines name-test-area.
        10  name-char        pic x(1) occurs 25 times.
     05 next-name-char       pic x(1).
        88 valid-name-char   value "A" through "Z", "a" through "z", " ", "'", "-".
     05 name-char-index      pic S9(3) comp.
     05 valid-name-flag      pic x(1).
        88 invalid-name      value "N".
*end check #3 vars

*variables for check #5
01 check-5-variables.
     05 acct-num-check    pic 9(4).
     05 acct-num-area redefines acct-num-check.
        10 acct-digit     pic 9(1) occurs 4 times.
     05 acct-sum-check    pic 9(3).
     05 digit-index       pic S9(3) comp.
*end check #5 vars

*variables for check #6
01 check-6-variables.
    05  birthdate-in-test.
        10  month-in-test                pic 9(2).
        10  day-in-test                  pic 9(2).
        10  year-in-test                 pic 9(4).
    05  age-in-test                      pic 9(3).
*end check #6 vars

*variables for check #9
01 check-9-variables.
    05 credit-char-test                  pic x(1).
       88 credit-a                       value "A".
       88 credit-b                       value "B".
       88 credit-c                       value "C".
       88 credit-d                       value "D".
       88 credit-char-valid              value "A" through "D".
    05 check-9-flag                      pic x(1).
       88 check-9-valid                  value "Y".
*end check #9 vars

*variables for check #10
01 check-10-variables.
    05 discount-rate-test                pic v999.
    05 check-10-flag                     pic x(1).
       88 check-10-valid                 value "Y".
*end check #10 vars

*variables for check #11
01 check-11-variables.
    05 discount-value                    pic v999.
       88 discount-a                     value .125.
       88 discount-b                     value .08.
       88 discount-c                     value .02.
   05 check-11-flag                      pic x(1).
       88 check-11-valid                 value "Y".
*end check #11 vars

*variables for check #12
01 check-12-variables.
    05 interest-test                pic 9(4)v99.
    05 balance-test                 pic 9(5)v99.
*end check #12 vars

*variables for check #13
01 check-13-variables.
    05 balance-ten                  pic 9(5)v99.
*env check #13 vars     


procedure division.

100-main  section.

100-main-line-para.
    open input  input-file.
    open output valid-file.
    open output exception-file.

*    perform 150-valid-file-header-para.
*    perform 150-exception-file-header-para.

    read input-file into input-record-in
         at end move "Y" to input-file-flag.
    perform  200-process-input-record-para until end-of-input-file.

*    perform 150-valid-file-footer-para.
*    perform 150-exception-file-footer-para.

    close input-file.
    close valid-file.
    close exception-file.

    stop run.

110-reset-flags-para.
    move "N" to check-9-flag.
    move "N" to check-10-flag.
    move "N" to check-11-flag.

200-process-input-record-para.
*    move all "N" to error-check-flags.
    perform 110-reset-flags-para.
    move "N" to error-detected-flag.
    move input-record-in to record-echo-out.

    perform 300-check-1-para.

    perform 300-check-2-para.

******  All other checks are performed here *****

    perform 300-check-3-para.

    perform 300-check-4-para.

*check 4, if true, will call check 5

    perform 300-check-6-para.

* check 6, if true, will call checks 7&8

    perform 300-check-9-para.

    perform 300-check-10-para.

    if check-9-valid and check-10-valid then
         perform 300-check-11-para.

    perform 300-check-12-para.

    if no-error-detected then
         perform 400-valid-record-echo-para.

    read input-file into input-record-in
         at end move "Y" to input-file-flag.

* CHECK to see if last name exists
300-check-1-para.
    if last-name-in = spaces then
        move  err-msg-1 to err-msg-out
        perform 400-err-msg-para.

*CHECK to see if account number exists
300-check-2-para.
    if acct-num-in = spaces then
        move err-msg-2 to err-msg-out
        perform 400-err-msg-para.

*PRE split name into an array of chars - call CHECK 3a
300-check-3-para.
    move name-in to name-test-area.
    move "Y" to valid-name-flag.
    perform 305-check-3a-para varying name-char-index from 1 by 1 
      until name-char-index > 25 OR invalid-name.

    if invalid-name then
       move err-msg-3 to err-msg-out
       perform 400-err-msg-para.

*CHECK if each char in array is an A-Z, a-z, ', space or -
305-check-3a-para.
    move name-char(name-char-index) to next-name-char.
    if not valid-name-char then move "N" to valid-name-flag.

*CHECK if account number and checksum are numberic - call CHECK 5
300-check-4-para.
    if  (acct-num-in is not numeric or  acct-sum-in is not numeric) then
             move err-msg-4 to err-msg-out
             perform  400-err-msg-para
    else
             perform 300-check-5-para.

*PRE split account number checksum into an array - call CHECK 5a - check result
300-check-5-para.
    move acct-num-in to acct-num-check.
    move zero to acct-sum-check.
    perform 305-check-5a-para varying digit-index from 1 by 1 until digit-index > 4.
   
    if acct-sum-check not equal acct-sum-in then
         move err-msg-5 to err-msg-out
         perform 400-err-msg-para.

*CHECK adds up digits using check-sum algrothym for check in CHECK 5
305-check-5a-para.
    compute acct-sum-check = acct-sum-check + (6 - digit-index) * acct-digit(digit-index).

*CHECK replace spaces by zeros and check if age and birthdate are numberic - call CHECK 7&8
300-check-6-para.
    move birthdate-in to birthdate-in-test.
    move age-in to age-in-test.

    inspect birthdate-in-test replacing all spaces by zeros.
    inspect age-in-test       replacing all spaces by zeros.

    if( birthdate-in-test is numeric and age-in-test is numeric) then
       perform 300-check-7-para
       perform 300-check-8-para
    else
       move err-msg-6 to err-msg-out
       perform 400-err-msg-para.
    
*CHECK to see if m/d/y range and age is valid
300-check-7-para.
     if not ( month-in-test >= 1 and month-in-test <= 12 and
          day-in-test >= 1 and day-in-test <= 31     and
          year-in-test <= 2001 ) then
       move err-msg-7 to err-msg-out
       perform 400-err-msg-para.

*CHECK to see if age is correct
300-check-8-para.
     if ( age-in-test not equal to 2003 - year-in-test ) then
          move err-msg-8 to err-msg-out
          perform 400-err-msg-para.

*CHECK to see if credit rating is valid
300-check-9-para.
     move credit-rating-in to credit-char-test.
     if ( not credit-char-valid ) then
          move "N" to check-9-flag
          move err-msg-9 to err-msg-out
          perform 400-err-msg-para
     else
          move "Y" to check-9-flag.

*CHECK to see if discount rate is numeric
300-check-10-para.
     move discount-rate-in to discount-rate-test.
     inspect discount-rate-test replacing all spaces by zeros.
     if not discount-rate-test is numeric then
        move "N" to check-10-flag
       move err-msg-10 to err-msg-out
        perform 400-err-msg-para
     else
        move "Y" to check-10-flag.

*CHECK to see if discount rating (replaced with zeros) corsponds with credit rating
300-check-11-para.
    move discount-rate-test to discount-value.

    if (credit-a and discount-a) or
       (credit-b and discount-b) or
       (credit-c and discount-c) or
       (credit-d and discount-value is numeric) then
     move "Y" to check-11-flag
    else
      move err-msg-11 to err-msg-out
      perform 400-err-msg-para.

*CHECK to see if Balance and Interest fields are numeric - call CHECK 13
300-check-12-para.
    move interest-in to interest-test.
    move balance-in  to balance-test.
    
    inspect interest-test replacing all spaces by zeros.
    inspect balance-test  replacing all spaces by zeros.

    if( interest-test is numeric and balance-test is numeric ) then
        perform 300-check-13-para
    else
        move err-msg-12 to err-msg-out
        perform 400-err-msg-para.

*CHECK if bal-sign argument is valid
300-check-13-para.
    multiply .1 by balance-test giving balance-ten.

    if balance-sign-in = '-'  and interest-test > balance-test then
       move err-msg-13 to err-msg-out
       perform 400-err-msg-para.

400-err-msg-para.
    if no-error-detected then perform 400-exception-record-echo-para.
    write exception-report-line from error-msg-line
                                after advancing 1 line.

    add 1 to exception-line-count.
*    if (exception-line-count > max-exception-line-count) then
*         move zero to exception-line-count
*         write exception-report-line from exception-page-header
*                                after advancing page.


400-exception-record-echo-para.
    add 1 to exception-record-count.
    move exception-record-count to record-count-out.
    write exception-report-line from record-echo-line
                                after advancing 2 lines.
    move "Y" to error-detected-flag.
    add 2 to exception-line-count.
*    if (exception-line-count > max-exception-line-count) then
*         move zero to exception-line-count
*         write exception-report-line from exception-page-header
*                                after advancing page.

400-valid-record-echo-para.
    add 1 to valid-record-count.
    move valid-record-count to record-count-out.
    write valid-report-line from record-echo-line
                                after advancing 2 lines.
    add 2 to valid-line-count.
*    if (valid-line-count > max-valid-line-count) then
*         move zero to valid-line-count
*         write valid-report-line from valid-page-header
*                                after advancing page.


*****************************************************************
*                                                               
*  Program #1 for Hume's File Processing Class
*
*  Compiled and tested with tinycobol for Linux 
*   and Compaq Cobol on VMS
*
*  Name: Sumit Khanna
*  
*                                                               
*****************************************************************

identification division.

program-id.   check-data.
author.       Sumit Khanna.

environment division.

configuration section.
source-computer. GNU-Linux-IA32.

input-output section.
file-control.
    select input-file      assign to "check.dat".
    select valid-file      assign to "valid.out".
    select exception-file  assign to "exception.out".

data division.

file section.

fd  input-file
        record contains 61 characters.
01  input-line              pic x(61).

fd  valid-file
        record contains 80 characters.
01  valid-report-line       pic x(80).

fd  exception-file
        record contains 80 characters.
01  exception-report-line   pic x(80).

working-storage section.

01  input-record-in.
    05  name-in.
        10  last-name-in            pic x(15).
        10  first-name-in           pic x(10).
    05  acct-num-in                 pic 9(4).
    05  acct-sum-in                 pic 9(3).
    05  birthdate-in.
        10  month-in                pic 9(2).
        10  day-in                  pic 9(2).
        10  year-in                 pic 9(4).
    05  age-in                      pic 9(3).
    05  discount-rate-in            pic v999.
    05  balance-in                  pic 9(5)v99.
    05  balance-sign-in             pic x(1).
    05  interest-in                 pic 9(4)v99.
    05  credit-rating-in            pic x(1).

01  file-eof-flags.
    05  input-file-flag             pic x(1)   value "N".
        88  end-of-input-file                  value "Y".

01  error-message-area.
    05  err-msg-1  pic x(35) value "1  Last name missing               ".
    05  err-msg-2  pic x(35) value "2  Acct number field missing       ".
    05  err-msg-3  pic x(35) value "3  Name contains invalid characters".
    05  err-msg-4  pic x(35) value "4  Acct Num/acct Sum not numeric   ".
    05  err-msg-5  pic x(35) value "5  Check sum test fails            ".
    05  err-msg-6  pic x(35) value "6  Birthdate/age not numeric       ".
    05  err-msg-7  pic x(35) value "7  Birthdate not in range          ".
    05  err-msg-8  pic x(35) value "8  Age test fails                  ".
    05  err-msg-9  pic x(35) value "9  Credit rating invalid           ".
    05  err-msg-10 pic x(35) value "10 Discount rate not numeric       ".
    05  err-msg-11 pic x(35) value "11 Discount & credit rate: no match".
    05  err-msg-12 pic x(35) value "12 Balance/interest not numeric    ".
    05  err-msg-13 pic x(35) value "13 Interest amount too large       ".

01  report-control-variables.
    05  error-detected-flag          pic x(1).
        88  error-has-been-detected            value "Y".
        88  no-error-detected                  value "N".

    05  exception-record-count      pic 9(3) value zero.
    05  valid-record-count          pic 9(3) value zero.
    05  exception-line-count        pic 9(2) value zero.
    05  valid-line-count            pic 9(2) value zero.
    05  max-exception-line-count    pic 9(2) value 66.
    05  max-valid-line-count        pic 9(2) value 66.

01  report-line-templates.
    05  record-echo-line.
        10  record-count-out        pic zz9.
        10  filler                  pic x(4) value ".   ".
        10  record-echo-out         pic x(61).

    05  error-msg-line.
        10  filler                  pic x(10) value spaces.
        10  err-msg-out             pic x(35).

*    05  exception-file-header.

*    05  exception-page-header.

*    05  valid-file-header.

*    05  valid-page-header.

*    05  exception-file-footer.

*    05  valid-file-footer.

*variables for check #3
01 check-3-variables.
     05 name-test-area       pic x(25).
     05 name-letter-area redefines name-test-area.
        10  name-char        pic x(1) occurs 25 times.
     05 next-name-char       pic x(1).
        88 valid-name-char   value "A" through "Z", "a" through "z", " ", "'", "-".
     05 name-char-index      pic S9(3) comp.
     05 valid-name-flag      pic x(1).
        88 invalid-name      value "N".
*end check #3 vars

*variables for check #5
01 check-5-variables.
     05 acct-num-check    pic 9(4).
     05 acct-num-area redefines acct-num-check.
        10 acct-digit     pic 9(1) occurs 4 times.
     05 acct-sum-check    pic 9(3).
     05 digit-index       pic S9(3) comp.
*end check #5 vars

*variables for check #6
01 check-6-variables.
    05  birthdate-in-test.
        10  month-in-test                pic 9(2).
        10  day-in-test                  pic 9(2).
        10  year-in-test                 pic 9(4).
    05  age-in-test                      pic 9(3).
*end check #6 vars

*variables for check #9
01 check-9-variables.
    05 credit-char-test                  pic x(1).
       88 credit-a                       value "A".
       88 credit-b                       value "B".
       88 credit-c                       value "C".
       88 credit-d                       value "D".
       88 credit-char-valid              value "A" through "D".
    05 check-9-flag                      pic x(1).
       88 check-9-valid                  value "Y".
*end check #9 vars

*variables for check #10
01 check-10-variables.
    05 discount-rate-test                pic v999.
    05 check-10-flag                     pic x(1).
       88 check-10-valid                 value "Y".
*end check #10 vars

*variables for check #11
01 check-11-variables.
    05 discount-value                    pic v999.
       88 discount-a                     value .125.
       88 discount-b                     value .08.
       88 discount-c                     value .02.
   05 check-11-flag                      pic x(1).
       88 check-11-valid                 value "Y".
*end check #11 vars

*variables for check #12
01 check-12-variables.
    05 interest-test                pic 9(4)v99.
    05 balance-test                 pic 9(5)v99.
*end check #12 vars

*variables for check #13
01 check-13-variables.
    05 balance-ten                  pic 9(5)v99.
*env check #13 vars     


procedure division.

100-main  section.

100-main-line-para.
    open input  input-file.
    open output valid-file.
    open output exception-file.

*    perform 150-valid-file-header-para.
*    perform 150-exception-file-header-para.

    read input-file into input-record-in
         at end move "Y" to input-file-flag.
    perform  200-process-input-record-para until end-of-input-file.

*    perform 150-valid-file-footer-para.
*    perform 150-exception-file-footer-para.

    close input-file.
    close valid-file.
    close exception-file.

    stop run.

110-reset-flags-para.
    move "N" to check-9-flag.
    move "N" to check-10-flag.
    move "N" to check-11-flag.

200-process-input-record-para.
*    move all "N" to error-check-flags.
    perform 110-reset-flags-para.
    move "N" to error-detected-flag.
    move input-record-in to record-echo-out.

    perform 300-check-1-para.

    perform 300-check-2-para.

******  All other checks are performed here *****

    perform 300-check-3-para.

    perform 300-check-4-para.

*check 4, if true, will call check 5

    perform 300-check-6-para.

* check 6, if true, will call checks 7&8

    perform 300-check-9-para.

    perform 300-check-10-para.

    if check-9-valid and check-10-valid then
         perform 300-check-11-para.

    perform 300-check-12-para.

    if no-error-detected then
         perform 400-valid-record-echo-para.

    read input-file into input-record-in
         at end move "Y" to input-file-flag.

* CHECK to see if last name exists
300-check-1-para.
    if last-name-in = spaces then
        move  err-msg-1 to err-msg-out
        perform 400-err-msg-para.

*CHECK to see if account number exists
300-check-2-para.
    if acct-num-in = spaces then
        move err-msg-2 to err-msg-out
        perform 400-err-msg-para.

*PRE split name into an array of chars - call CHECK 3a
300-check-3-para.
    move name-in to name-test-area.
    move "Y" to valid-name-flag.
    perform 305-check-3a-para varying name-char-index from 1 by 1 
      until name-char-index > 25 OR invalid-name.

    if invalid-name then
       move err-msg-3 to err-msg-out
       perform 400-err-msg-para.

*CHECK if each char in array is an A-Z, a-z, ', space or -
305-check-3a-para.
    move name-char(name-char-index) to next-name-char.
    if not valid-name-char then move "N" to valid-name-flag.

*CHECK if account number and checksum are numberic - call CHECK 5
300-check-4-para.
    if  (acct-num-in is not numeric or  acct-sum-in is not numeric) then
             move err-msg-4 to err-msg-out
             perform  400-err-msg-para
    else
             perform 300-check-5-para.

*PRE split account number checksum into an array - call CHECK 5a - check result
300-check-5-para.
    move acct-num-in to acct-num-check.
    move zero to acct-sum-check.
    perform 305-check-5a-para varying digit-index from 1 by 1 until digit-index > 4.
   
    if acct-sum-check not equal acct-sum-in then
         move err-msg-5 to err-msg-out
         perform 400-err-msg-para.

*CHECK adds up digits using check-sum algrothym for check in CHECK 5
305-check-5a-para.
    compute acct-sum-check = acct-sum-check + (6 - digit-index) * acct-digit(digit-index).

*CHECK replace spaces by zeros and check if age and birthdate are numberic - call CHECK 7&8
300-check-6-para.
    move birthdate-in to birthdate-in-test.
    move age-in to age-in-test.

    inspect birthdate-in-test replacing all spaces by zeros.
    inspect age-in-test       replacing all spaces by zeros.

    if( birthdate-in-test is numeric and age-in-test is numeric) then
       perform 300-check-7-para
       perform 300-check-8-para
    else
       move err-msg-6 to err-msg-out
       perform 400-err-msg-para.
    
*CHECK to see if m/d/y range and age is valid
300-check-7-para.
     if not ( month-in-test >= 1 and month-in-test <= 12 and
          day-in-test >= 1 and day-in-test <= 31     and
          year-in-test <= 2001 ) then
       move err-msg-7 to err-msg-out
       perform 400-err-msg-para.

*CHECK to see if age is correct
300-check-8-para.
     if ( age-in-test not equal to 2003 - year-in-test ) then
          move err-msg-8 to err-msg-out
          perform 400-err-msg-para.

*CHECK to see if credit rating is valid
300-check-9-para.
     move credit-rating-in to credit-char-test.
     if ( not credit-char-valid ) then
          move "N" to check-9-flag
          move err-msg-9 to err-msg-out
          perform 400-err-msg-para
     else
          move "Y" to check-9-flag.

*CHECK to see if discount rate is numeric
300-check-10-para.
     move discount-rate-in to discount-rate-test.
     inspect discount-rate-test replacing all spaces by zeros.
     if not discount-rate-test is numeric then
        move "N" to check-10-flag
       move err-msg-10 to err-msg-out
        perform 400-err-msg-para
     else
        move "Y" to check-10-flag.

*CHECK to see if discount rating (replaced with zeros) corsponds with credit rating
300-check-11-para.
    move discount-rate-test to discount-value.

    if (credit-a and discount-a) or
       (credit-b and discount-b) or
       (credit-c and discount-c) or
       (credit-d and discount-value is numeric) then
     move "Y" to check-11-flag
    else
      move err-msg-11 to err-msg-out
      perform 400-err-msg-para.

*CHECK to see if Balance and Interest fields are numeric - call CHECK 13
300-check-12-para.
    move interest-in to interest-test.
    move balance-in  to balance-test.
    
    inspect interest-test replacing all spaces by zeros.
    inspect balance-test  replacing all spaces by zeros.

    if( interest-test is numeric and balance-test is numeric ) then
        perform 300-check-13-para
    else
        move err-msg-12 to err-msg-out
        perform 400-err-msg-para.

*CHECK if bal-sign argument is valid
300-check-13-para.
    multiply .1 by balance-test giving balance-ten.

    if balance-sign-in = '-'  and interest-test > balance-test then
       move err-msg-13 to err-msg-out
       perform 400-err-msg-para.

400-err-msg-para.
    if no-error-detected then perform 400-exception-record-echo-para.
    write exception-report-line from error-msg-line
                                after advancing 1 line.

    add 1 to exception-line-count.
*    if (exception-line-count > max-exception-line-count) then
*         move zero to exception-line-count
*         write exception-report-line from exception-page-header
*                                after advancing page.


400-exception-record-echo-para.
    add 1 to exception-record-count.
    move exception-record-count to record-count-out.
    write exception-report-line from record-echo-line
                                after advancing 2 lines.
    move "Y" to error-detected-flag.
    add 2 to exception-line-count.
*    if (exception-line-count > max-exception-line-count) then
*         move zero to exception-line-count
*         write exception-report-line from exception-page-header
*                                after advancing page.

400-valid-record-echo-para.
    add 1 to valid-record-count.
    move valid-record-count to record-count-out.
    write valid-report-line from record-echo-line
                                after advancing 2 lines.
    add 2 to valid-line-count.
*    if (valid-line-count > max-valid-line-count) then
*         move zero to valid-line-count
*         write valid-report-line from valid-page-header
*                                after advancing page.


