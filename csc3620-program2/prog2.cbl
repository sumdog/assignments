*************************************
* Program #2 - Hume - File Processing
* Sumit Khanna
*  This program will take in
*  the files 'bank{1,2,3}.dat', sort
*  each file, merge them and then
*  place them in output files 
*  "{a,b,k,other}.out", based on the
*  account-type
*************************************

identification division.

program-id. prog2.
author.     Sumit Khanna.

environment division.

configuration section.
source-computer. Alpha-VMS.

input-output section.
file-control.
    select data-file     assign to " ".
    select sort-temp     assign to "sort.swp".
data division.

file section.
fd data-file record contains 50 characters
        value of id is input-filename.
01 data-record.
    05 acct-name   pic x(25).
    05 acct-num    pic 9(6).
    05 acct-type   pic x(1).
    05 acct-bal    pic 9(8)v999.
    05 trans-count pic 9(4).
    05 state       pic x(4).


sd sort-temp  record contains 50 characters.
01 sort-temp-record.
    05 acct-name   pic x(25).
    05 acct-num    pic 9(6).
    05 acct-type   pic x(1).
    05 acct-bal    pic 9(8)v999.
    05 trans-count pic 9(4).
    05 state       pic x(4).   

working-storage section.
 
01 file-info
    05 input-filename pic x(50).
    05 input-eof-flag pic x(1) value "N".
       88 end-of-file          value "Y".

01 counters.
    05 i           pic 9(1) usage is comp.

procedure division.

main-paragraph.

    perform sort-paragraph varying i from 1 by 1 until i > 3

    stop run.


sort-paragraph.
    
    if i = 1 then
       move "bank1.dat" to input-filename.
    if i = 2 then
       move "bank2.dat" to input-filename.
    if i = 3 then
       move "bank3.dat" to input-filename.

    open input data-file.
    read data-file at end move "Y" to input-eof-flag.
    perform sort-input-proc until end-of-file.    
    close data-file.

sort-input-proc.
    

sort-output-proc.
