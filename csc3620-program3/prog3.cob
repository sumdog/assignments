***************************************
* Program #3
*  Sumit Khanna - Dr. Hume's 3620 
*
*  This program reads in a data 
*   file called "recordings.dat" that
*   contains a list of music data. 
*   The program sorts the data and 
*   stores it in an indexed file 
*   by ascending key. 
*  The second stage of this program
*   involves the indexed file being
*   run aganist a transaction file 
*   that will add, delete and change
*   entries. 
*  Appropiate error files will be 
*   kept to indicate invalid keys
*   and dump files will be written
*   for human readable forms of the 
*   data
***************************************

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
      access mode is dynamic
      record key is ckey. 
    select error-file     assign to "invalid-key.dat".
    select trans-file     assign to "recordings_trans.dat".


data division.

file section.
fd input-file record contains 65 to 76 characters.
01 input-record  pic x(76).

fd error-file record contains 141 characters.
01 error-file-record pic x(141).

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

fd trans-file record contains 142 characters.
01 trans-file-record.
    05 t-label     pic x(15).
    05 t-prefix    pic x(6).
    05 t-number    pic x(10).
    05 t-composer  pic x(20).
    05 t-title     pic x(25).
    05 t-soloist   pic x(15).
    05 t-orchestra pic x(20).
    05 t-conductor pic x(15).
    05 t-genre     pic x(15).
    05 t-trans     pic x(1).


working-storage section.
 
01 input-area.
    05 input-area-1   pic x(76).
    05 input-area-2   pic x(65).


01 file-flags.
    05 input-file-flag    pic x(1) value "N".
       88 input-file-eof           value "Y".
    05 sort-file-flag     pic x(1) value "N".
       88 sort-file-eof            value "Y".
    05 trans-file-flag    pic x(1) value "N".
       88 trans-file-eof           value "Y".

procedure division.


main section.

******************************************
*Entry point for program
* --sorts the data
*   --sort places data in indexed file
* --process transactions
* --done
*******************************************
main-paragraph.
     sort sort-temp
     on ascending key sort-key
     input procedure 100-input-proc
     output procedure 200-output-proc.
     stop run.

******************************************
*Input Procedure Section
*  --Input procedure for sort
*    read data from file, placing
*    first three fileds in one con-
*    catinated key and release it to the
*    sort
******************************************
100-input-proc section.

***Opens files for inital reads
101-open.
    open input input-file.
    read input-file into input-area-1 
      at end move "Y" to input-file-flag.
    read input-file into input-area-2
      at end move "Y" to input-file-flag.
    perform 102-release until input-file-eof.
    close input-file.
    go to 103-done.

***Release records to be sorted
102-release.
    inspect input-area replacing all "~" by SPACES.
    move input-area in to sort-temp-record.
    release sort-temp-record.
     read input-file into input-area-1 
      at end move "Y" to input-file-flag.
    read input-file into input-area-2
      at end move "Y" to input-file-flag.   

***End of section
103-done.
    exit.


******************************************
*Output procedure section
*  --Output procedure gets data back
*    from sort and places it in Indexed 
*    file
******************************************
200-output-proc section.

***open indexed and error file
201-open.
    open output indexed-file.
    open output error-file.
    perform 202-return until sort-file-eof.
    close error-file.
    close indexed-file.
    go to 204-done.

***pull data out of sort and write it
202-return.
    return sort-temp 
       at end move "Y" to sort-file-flag.
    move sort-temp-record in to indexed-file-record.
    write indexed-file-record 
       invalid key perform 203-invalid-key.

***write to error file for invalid keys
203-invalid-key.
    move sort-temp-record in to error-file-record.
    write error-file-record after advancing 1 line.

***End of Section
204-done.
    exit.


300-transaction-file-section.

301-open.
    open i-o indexed-file.
    open input trans-file.
    perform 302-read-transaction until trans-file-eof.
    go to 390-done.

302-read-transaction.
    read trans-file at end move "Y" to trans-file-flag.
    if (t-trans is equal to "A") then perform 310-Add 
    else if (t-trans is equal to "D") then perform 311-Delete 
    else if (t-trans is equal to "C") then perform 312-Change 
    else perform 313-Invalid.

310-Add.
    move trans-file-record to indexed-file-record.

311-Delete.
    move trans-file-record to indexed-file-record.

312-Change.
    move trans-file-record to indexed-file-record.

313-Invalid.
    move trans-file-record to indexed-file-record.

**End of Section
390-done.
    exit.



