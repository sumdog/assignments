*************************************
* Program #2 - Hume - File Processing
* Sumit Khanna
*  This program will take in
*  the files 'bank{1,2,3}.dat', sort
*  each file if their account
*  balance is greate than 20,000.00,
*  merge them and then
*  place them in output files 
*  "{a,b,k,o}.out", based on the
*  account-type
*************************************

identification division.

program-id. prog2.
author.     Sumit Khanna.

environment division.

configuration section.
source-computer. VAX-Alpha.

input-output section.
file-control.
    select data-file     assign to " ".
    select sort-out-file assign to " ".
    select sort-temp     assign to "sort.swp".
    select merge-temp    assign to "merge.swp".
    select sort-a        assign to "a.out".
    select sort-b        assign to "b.out".
    select sort-k        assign to "k.out".
    select sort-other    assign to "o.out".
    select out-1         assign to "bank1.out".
    select out-2         assign to "bank2.out".
    select out-3         assign to "bank3.out".
data division.

file section.
fd data-file record contains 50 characters
        value of id is input-filename.
01 data-record     pic x(50).

sd sort-temp  record contains 50 characters.
01 sort-temp-record.
    05 acct-name   pic x(25).
    05 acct-num    pic 9(6).
    05 acct-type   pic x(1).
    05 acct-bal    pic 9(8)v99.
    05 trans-count pic 9(4).
    05 state       pic x(4).   

sd merge-temp record contains 50 characters.
01 merge-temp-record.
    05 m-acct-name   pic x(25).
    05 m-acct-num    pic 9(6).
    05 m-acct-type   pic x(1).
    05 m-acct-bal    pic 9(8)v99.
    05 m-trans-count pic 9(4).
    05 m-state       pic x(4).   

fd out-1 record contains 50 characters.
01 out-1-record    pic x(50).

fd out-2 record contains 50 characters.
01 out-2-record    pic x(50).

fd out-3 record contains 50 characters.
01 out-3-record    pic x(50).

fd sort-out-file record contains 50 characters
        value of id is output-filename.
01 sort-out-record pic x(50).

fd sort-a record contains 50 characters.
01 sort-a-record   pic x(50).

fd sort-b record contains 50 characters.
01 sort-b-record   pic x(50).

fd sort-k record contains 50 characters.
01 sort-k-record   pic x(50).

fd sort-other record contains 50 characters.
01 sort-other-record   pic x(50).



working-storage section.
 
01 file-info.
    05 input-filename   pic x(50).
    05 output-filename  pic x(50).
    05 input-eof-flag   pic x(1) value "N".
       88 end-of-file            value "Y".
    05 merge-eof-flag   pic x(1) value "N".
       88 end-of-merge           value "Y".

01 counters.
    05 i           pic 9(1) usage is comp.

procedure division.


main section.

main-paragraph.
    perform sort-paragraph varying i from 1 by 1 until i > 3

    merge merge-temp
        on ascending key m-state
        on descending key m-acct-bal
        using out-1, out-2, out-3
        output procedure merge-output-proc.

    stop run.

sort-paragraph.
    if i = 1 then
       move "bank1.dat" to input-filename
       move "bank1.out" to output-filename.
    if i = 2 then
       move "bank2.dat" to input-filename
       move "bank2.out" to output-filename.
    if i = 3 then
       move "bank3.dat" to input-filename
       move "bank3.out" to output-filename.

    sort sort-temp
         on ascending key state
         on descending key acct-bal
         input  procedure sort-input-proc
         giving sort-out-file.



sort-input-proc section.
    
100-open.
    open input data-file.
    read data-file at end move "Y" to input-eof-flag.
    perform 101-release until end-of-file.    
    close data-file.
    go to 102-done.    

101-release.
     move data-record in to sort-temp-record.
*    if (acct-bal >= 20000.00) then
       release sort-temp-record.
    read data-file at end move "Y" to input-eof-flag.

102-done.
    exit.


merge-output-proc section.

200-open.
    open output sort-a.
    open output sort-b.
    open output sort-k.
    open output sort-other.
    return merge-temp at end move "Y" to merge-eof-flag.
    perform 201-return until end-of-merge.
    close sort-a.
    close sort-b.
    close sort-k.
    close sort-other.
    go to 202-done.

201-return.
    if m-acct-type = "A" then
       move merge-temp-record in to sort-a-record
       write sort-a-record after advancing 1 line
    else if m-acct-type = "B" then
       move merge-temp-record in to sort-b-record
       write sort-b-record after advancing 1 line
    else if m-acct-type = "K" then
       move merge-temp-record in to sort-k-record
       write sort-k-record after advancing 1 line
    else
       move merge-temp-record in to sort-other-record
       write sort-other-record after advancing 1 line.
    return merge-temp at end move "Y" to merge-eof-flag.


202-done.
    exit.











