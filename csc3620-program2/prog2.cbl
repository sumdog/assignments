*************************************
* Program #2 - Hume - File Processing
* Sumit Khanna
*  This program will take in
*  the files 'bank{1,2,3}.dat', sort
*  each file and then merge them into
*  one big sorted output file called
*  'bank.out'
*************************************

identification division.

program-id. prog2.
author.     Sumit Khanna.

environment division.

configuration section.
source-computer. GNU-Linux-IA32.

input-output section.
file-control.
    select data-file1    assign to "bank1.dat".
    select data-file2    assign to "bank2.dat".
    select data-file3    assign to "bank3.dat".
    select sort-temp     assign to "sort.swp".
data division.

file section.
fd data-file1 record contains 50 characters.
01 data-record    pic x(50).

fd data-file2 record contains 50 characters.
01 data-record    pic x(50).

fd data-file3 record contains 50 characters.
01 data-record    pic x(50).

sd sort-temp  record contains 50 characters.
01 sort-temp-record.
    05 acct-name   pic x(25).
    05 acct-num    pic 9(6).
    05 acct-type   pic x(1).
    05 acct-bal    pic 9(8)v999.
    05 trans-count pic 9(4).
    05 state       pic x(4).   

working-storage section.
 
01 data-input.
    05 acct-name   pic x(25).
    05 acct-num    pic 9(6).
    05 acct-type   pic x(1).
    05 acct-bal    pic 9(8)v999.
    05 trans-count pic 9(4).
    05 state       pic x(4).


procedure division.

main-paragraph.

    stop run.


