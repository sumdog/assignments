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
*                                                               
*  Program #1 for Hume's File Processing Class
*
*  Compiled and tested with tinycobol for Linux 
*   and Compaq Cobol on VMS
*
*  Name: Sumit Khanna
*  
*                                                               
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

01  error-check-flags.
    05  acct-num-numeric-flag       pic x(1).
        88  acct-num-is-numeric                value "Y".

    05  acct-sum-numeric-flag       pic x(1).
        88  acct-sum-is-numeric                value "Y".

    05  birthdate-numeric-flag      pic x(1).
        88  birthdate-is-numeric               value "Y".

    05  age-numeric-flag            pic x(1).
        88  age-is-numeric                     value "Y".

    05  discount-rate-numeric-flag  pic x(1).
        88  discount-rate-is-numeric           value "Y".

    05  credit-rating-flag          pic x(1).
        88 credit-rating-is-valid              value "Y".

    05  balance-numeric-flag        pic x(1).
        88  balance-is-numeric                 value "Y".

    05  interest-numeric-flag       pic x(1).
        88  interest-is-numeric                value "Y".

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

200-process-input-record-para.
    move all "N" to error-check-flags.
    move "N" to error-detected-flag.
    move input-record-in to record-echo-out.

    perform 300-check-1-para.

    perform 300-check-2-para.

******  All other checks are performed here *****

    if no-error-detected then
         perform 400-valid-record-echo-para.

    read input-file into input-record-in
         at end move "Y" to input-file-flag.


300-check-1-para.
    if last-name-in = spaces then
        move  err-msg-1 to err-msg-out
        perform 400-err-msg-para.

300-check-2-para.
    if acct-num-in = spaces then
        move err-msg-2 to err-msg-out
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


