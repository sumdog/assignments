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
    select indexed-file   assign to "indexed.dat"
      organization is indexed
      access mode is sequential
      record key is ckey. 
 
data division.

file section.
fd input-file record contains 65 to 76 characters.
01 input-record  pic x(76).

sd sort-temp  record contains 141 characters.
01 sort-temp-record.
    05 sort-key      pic x(31).
    05 sort-data     pic x(110).

fd indexed-file record contains 141 characters.
01 indexed-file-record.
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
    05 sort-file-flag     pic x(1) value "N".
       88 sort-file-eof            value "Y".

procedure division.


main section.

main-paragraph.
     sort sort-temp
     on ascending key sort-key
     input procedure 100-input-proc
     output procedure 200-output-proc.


100-input-proc section.

101-open.
    open input input-file.
    read input-file into input-area-1 
      at end move "Y" to input-file-flag.
    read input-file into input-area-2
      at end move "Y" to input-file-flag.
    perform 102-release until input-file-eof.
    close input-file.
    go to 103-done.

102-release.
    inspect input-area replacing all "~" by SPACES.
    move input-area in to sort-temp-record.
    release sort-temp-record.
     read input-file into input-area-1 
      at end move "Y" to input-file-flag.
    read input-file into input-area-2
      at end move "Y" to input-file-flag.   

103-done.
    exit.



200-output-proc section.

201-open.
    open output indexed-file.
    perform 202-return until sort-file-eof.

202-return.
    return sort-temp 
       at end move "Y" to sort-file-flag.
    move sort-temp-record in to indexed-file-record.
    write indexed-file-record 
       invalid key perform 203-invalid-key.

203-invalid-key.

204-done.
    exit.







