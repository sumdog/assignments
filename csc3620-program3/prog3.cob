*************************************
* Program #3
*************************************

identification division.

program-id. prog3.
author.     Sumit Khanna.

environment division.

configuration section.
source-computer. VAX-Alpha.

input-output section.
file-control.
    select input-file     assign to "recordings.dat".
    select sort-temp      assign to "sort.swp".

data division.

file section.
fd input-file record contains 65 to 76 characters.
01 input-record  pic x(76).

sd sort-temp  record contains 141 characters.
01 sort-temp-record.
    05 ckey      pic x(31).
    05 composer  pic x(20).
    05 title     pic x(25).
    05 soloist   pic x(15).
    05 orchestra pic x(20).
    05 conductor pic x(15).
    05 genre     pic x(15).   

working-storage section.
 
01 input-area.
    05 input-area-1   pic x(76).
    05 input-area-2   pic x(65).


01 file-flags.
    05 input-file-flag    pic x(1) value "N".
       88 input-file-eof           value "Y".

procedure division.


main section.

main-paragraph.












