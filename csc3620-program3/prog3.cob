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
    select error-trans-file assign to "invalid-transaction.dat".
    select dump-file      assign to " ".
    select indexed-file-dump-mode   assign to "indexed.dat"
      organization is indexed
      access mode is sequential
      record key is d-ckey. 

data division.

file section.
fd input-file record contains 65 to 76 characters.
01 input-record  pic x(76).

fd dump-file record contains 79 characters
    value of id is dump-file-name.
01 dump-file-record.
    10 dump-number   pic 9(2).
    10 dump-space    pic x(1).
    10 dump-key      pic x(31).
    10 dump-elements pic x(45). 

fd error-file record contains 141 characters.
01 error-file-record pic x(141).

fd error-trans-file record contains 141 characters.
01 error-trans-file-record pic x(141).

sd sort-temp  record contains 141 characters.
01 sort-temp-record.
    05 sort-key      pic x(31).
    05 sort-data     pic x(110).

fd indexed-file record contains 141 characters.
01 indexed-file-record.
    15 ckey      pic x(31).
    15 composer  pic x(20).
    15 title     pic x(25).
    15 soloist   pic x(15).
    15 orchestra pic x(20).
    15 conductor pic x(15).
    15 genre     pic x(15). 

fd indexed-file-dump-mode record contains 141 characters.
01 indexed-file-dump-mode-record.
    10 d-ckey      pic x(31).
    10 i-first.
      15 d-composer  pic x(20).
      15 d-title     pic x(25).
    10 i-rest.
      15 d-soloist   pic x(15).
      15 d-orchestra pic x(20).
      15 d-conductor pic x(15).
      15 d-genre     pic x(15).      

fd trans-file record contains 142 characters.
01 trans-file-record.
    10 t-ckey.
      15 t-label     pic x(15).
      15 t-prefix    pic x(6).
      15 t-number    pic x(10).
    10 t-data.
      15 t-composer  pic x(20).
      15 t-title     pic x(25).
      15 t-soloist   pic x(15).
      15 t-orchestra pic x(20).
      15 t-conductor pic x(15).
      15 t-genre     pic x(15).
    10 t-code.
      15 t-trans     pic x(1).


working-storage section.
 
01 input-area.
    05 input-area-1   pic x(76).
    05 input-area-2   pic x(65).

01 trans-input-area.
    05 t-area-1       pic x(76).
    05 t-area-2       pic x(66).

01 file-names.
    05 dump-file-name  pic x(50).
    05 dump-file-title pic x(31).

01 file-flags.
    05 input-file-flag     pic x(1) value "N".
       88 input-file-eof            value "Y".
    05 sort-file-flag      pic x(1) value "N".
       88 sort-file-eof             value "Y".
    05 trans-file-flag     pic x(1) value "N".
       88 trans-file-eof            value "Y".
    05 indexed-file-flag   pic x(1) value "N".
       88 indexed-file-eof          value "Y".

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

     move "Original Indexed File" to dump-file-title.
     move "original-dump.dat" to dump-file-name.
     perform 400-dump-file.
    
     perform 300-transaction-file.

     move "Updated Indexed File" to dump-file-title.
     move "updated-dump.dat" to dump-file-name.
     perform 400-dump-file.

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

******************************************
*Transaction File Section
* --These procedures deal with iterating
*   through the transaction file and 
*   performing the appropiate operations
*   (adding, removing and changing
*   records)
******************************************
300-transaction-file section.

***the main entry point for this section
301-open.
    open i-o indexed-file.
    open input trans-file.
    open output error-trans-file.
    perform 302-read-transaction until trans-file-eof.
    close indexed-file.
    close trans-file.
    close error-trans-file.
    go to 390-done.

***reads and processes the transaction file
302-read-transaction.
    read trans-file into t-area-1
       at end move "Y" to trans-file-flag.
    read trans-file into t-area-2 
       at end move "Y" to trans-file-flag.
    move trans-input-area to trans-file-record.
    inspect trans-file-record replacing all "~" by SPACES.

    if (t-trans is equal to "A") then perform 310-Add 
    else if (t-trans is equal to "D") then perform 311-Delete 
    else if (t-trans is equal to "C") then perform 312-Change 
    else perform 314-invalid-key.

***Add Transaction
310-Add.
    move trans-file-record to indexed-file-record.
    write indexed-file-record 
       invalid key perform 314-invalid-key.

***Remove Transaction
311-Delete.
    move trans-file-record to indexed-file-record.
    delete indexed-file
       invalid key perform 314-invalid-key.

***Change Record Transaction
312-Change.
    move t-ckey to ckey.
    read indexed-file invalid key perform 314-invalid-key.
    if (t-composer is not equal to SPACES) then
       move t-composer to composer.
    if (t-title is not equal to SPACES) then
       move t-title to title.
    if (t-soloist is not equal to SPACES) then
       move t-soloist to soloist.
    if (t-orchestra is not equal to SPACES) then
       move t-orchestra to orchestra.
    if (t-conductor is not equal to SPACES) then
       move t-conductor to conductor.
    if (t-genre is not equal to SPACES) then
       move t-genre to genre.
    write indexed-file-record 
       invalid key perform 314-invalid-key.

***All invalid key errors are stored in this one file
314-invalid-key.
    move trans-file-record to error-trans-file-record.
    write error-trans-file-record after advancing 1 line.

**End of Section
390-done.
    exit.


******************************************
*Dump File Section
* --These procedures 
*   are used to dump the indexed-file
*   using the file name denoted by
*   dump-file-name
******************************************
400-dump-file section.

***Gives the file a header and prepares it for dump
401-dump-indexed-file.
    move "N" to indexed-file-flag.
    open input indexed-file-dump-mode.
    open output dump-file.
 
    move 0 to dump-number
    move SPACES to dump-space.
    move dump-file-title to dump-key.
    move SPACES to dump-elements.
    write dump-file-record after advancing 1 line.

    perform 410-write-to-file until indexed-file-eof.

    close indexed-file-dump-mode.
    close dump-file.
    go to 499-done.

***Dumps the file
410-write-to-file.
    add 1 to dump-number.
    read indexed-file-dump-mode at end move "Y" to indexed-file-flag.
    move d-ckey to dump-key.
    move i-first to dump-elements.
    write dump-file-record after advancing 1 line.

***End of Section
499-done.
    exit.

