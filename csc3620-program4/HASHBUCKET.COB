***********************************************************
*                                                         *
*          This program creates a hashing file using a    *
*   one-pass load (instead of a "two-pass load").  A user *
*   must enter source input filename, maximum number of   *
*   buckets, bucket size, and a (prime) number used for   *
*   hashing key values.  Collisions are handled by "con-  *
*   spill" search from the home bucket.  Linked lists of  *
*   buckets are built as necessary as overflows occur.    *
*   Created: 4-3-1998    Last Modified: 4-3-2003          *
*                                                         *
***********************************************************

identification division.
program-id. Hashing.
Author. David Hume.

environment division.
configuration section.
source-computer.  vax-11.

input-output section.
file-control.
     select hash-file assign to "hashbucket.dat"
         organization is relative
         access mode is dynamic
         relative key is target-bucket.
     select print-file assign to "hashbucket.out"
         organization is sequential.
     select input-file assign to "disk$research:[dhume.362]  .dat"
         organization is sequential.

data division.
file section.
fd  hash-file.
01  hash-bucket.
    05 link-field              pic 9(3).
    05 record-slot    occurs 10 times.
       10  record-number       pic 9(3).
       10  hash-value          pic 9(3).
       10  rec-status          pic x(3).
           88 unused-rec-slot   value spaces.
           88 occupied-rec-slot value "OCC".
           88 deleted-rec-slot  value "DEL".
       10  rec-data-area.
           15  acct-no         pic 9(5).
           15  customer-name   pic x(20).
           15  other-data      pic x(47).

fd  print-file.
01  print-line                 pic x(80).
    
fd  input-file
    value of id  vax-input-file-name.
01  input-record.
       05  acct-no-in          pic 9(5).
       05  customer-name-in    pic x(20).
       05  other-data-in       pic x(47).

working-storage section.
01  index-variables.
    05  i                       pic s9(3) comp sync.
    05  b-indx                  pic s9(3) comp sync.

01  program-file-variables.
    05  input-file-flag         pic x(1)  value "Y".
    05  trans-file-flag         pic x(1)  value "Y".
    05  vax-input-file-name     pic x(40).

01  hash-file-variables.
    05  max-no-buckets          pic 9(3).
    05  bucket-size             pic 9(3).
    05  hash-key-field          pic 9(5) comp.
    05  target-bucket           pic 9(3).
    05  quotient                pic 9(3).
    05  hash-value-calc         pic 9(3).
    05  save-address            pic 9(3).
    05  new-bucket-address      pic 9(3).
    05  prime-number            pic 9(3).

01  add-record-flags.
    05  record-found-flag       pic x(1).
        88 record-found          value "Y".
        88 record-not-found      value "N".
    05  end-of-chain-flag       pic x(1).
        88 end-of-chain          value "Y".
    05  unused-slot-flag        pic x(1).
        88 unused-slot-found     value "Y".
    05  extend-chain-flag       pic x(1).
        88 cannot-extend-chain   value "N".
        88 can-extend-chain      value "Y".
    05  deleted-slot-flag       pic x(1).
        88 deleted-slot-found    value "Y".
    05  record-inserted-flag    pic x(1).
        88  record-inserted      value "Y".
        88  record-not-inserted  value "N".
    05  bucket-full-flag        pic x(1).
        88  bucket-full          value "Y".
        88  bucket-not-full      value "N".

01  bucket-output-line.
    05 filler                   pic x(2) value spaces.
    05 bucket-number-out        pic 9(3).
    05 filler                   pic x(4) value spaces.
    05 link-field-out           pic 9(3).

01  record-output-line.
    05 filler                   pic x(14) value spaces.
    05 record-number-out        pic 9(3).
    05 filler                   pic x(2)  value spaces.
    05 hash-value-out           pic x(3).
    05 filler                   pic x(2)  value spaces.
    05 record-status-out        pic x(3).
    05 filler                   pic x(2)  value spaces.
    05 acct-no-out              pic x(5).
    05 filler                   pic x(2)  value spaces.
    05 customer-name-out        pic x(20).

procedure division.
main-line-para.
    open output print-file.
    perform define-hash-file-size-para.
    perform define-vax-filenames-para.
    perform initialize-hash-file.
    perform load-input-file-para.
    perform print-hash-file.
    close print-file.
    stop run.

define-hash-file-size-para.
    display "Enter max number of buckets & <Ret>:".
    accept  max-no-buckets with conversion.
    display "Enter bucket size between 1 and 10 & <Ret>:".
    accept bucket-size with conversion.
    display "Enter prime number & <Ret>:".
    accept  prime-number with conversion.

define-vax-filenames-para.
    display "Enter vax filename for input file to create hash file & <Ret>:".
    accept vax-input-file-name.


initialize-hash-file.
    open output hash-file.
    perform initialize-bucket-para varying i from 1 by 1
                                   until i > max-no-buckets.
    close hash-file.

initialize-bucket-para.
    move i to target-bucket.
    perform initialize-record-slot-para varying b-indx from 1 by 1
                                        until b-indx > bucket-size.
    move zero to link-field.
    write hash-bucket invalid key perform write-error-para.

initialize-record-slot-para.
    move spaces to record-slot(b-indx).
    compute record-number(b-indx) = bucket-size*(i - 1) + b-indx.

print-hash-file.
    open input hash-file.
    perform print-bucket varying i from 1 by 1 until i > max-no-buckets.
    close hash-file.

print-bucket.
    move i to target-bucket.
    read hash-file invalid key perform read-error-para.
    move i to bucket-number-out.
    move link-field to link-field-out.
    write print-line from bucket-output-line after advancing 2 lines.
    perform print-record-slot varying b-indx from 1 by 1
                                             until b-indx > bucket-size.

print-record-slot.
    move record-number(b-indx) to record-number-out.
    move hash-value(b-indx) to hash-value-out.
    move rec-status(b-indx) to record-status-out.
    move acct-no(b-indx) to acct-no-out.
    move customer-name(b-indx) to customer-name-out.
    write print-line from record-output-line after advancing 1 line.

load-input-file-para.
    open input input-file.
    open i-o hash-file.
    read input-file at end move "N" to input-file-flag.
    perform process-input-record until input-file-flag = "N".
    close input-file.
    close hash-file.

process-input-record.
    move acct-no-in to hash-key-field.
    perform hashing-para.
    perform add-record-para.
    read input-file at end move "N" to input-file-flag.

hashing-para.
    divide prime-number into hash-key-field giving quotient
                                 remainder target-bucket.
    add 1 to target-bucket.
    move target-bucket to hash-value-calc.
    read hash-file invalid key perform read-error-para.

add-record-para.
    move "N" to record-found-flag.
    move "N" to end-of-chain-flag.
    perform examine-next-bucket until record-found or end-of-chain.
    if   record-found then perform add-error-para
    else                   perform normal-add-para.


examine-next-bucket.
    perform examine-record-slot varying i from 1 by 1 until i > bucket-size.
    if record-not-found then
         if   link-field = 0 then move "Y" to end-of-chain-flag
         else move link-field to target-bucket
              read hash-file invalid key perform read-error-para.

examine-record-slot.
    if rec-status(i) = "OCC" and ( acct-no-in = acct-no(i) ) then
                       move "Y" to record-found-flag.

normal-add-para.
    move "Y" to extend-chain-flag.
    move "N" to record-inserted-flag.
    move hash-value-calc to target-bucket.
    read hash-file invalid key perform read-error-para.
    perform check-bucket-for-insertion
                       until record-inserted or cannot-extend-chain.
    if cannot-extend-chain then perform file-is-full-error-para
                                        stop run.

check-bucket-for-insertion.
    perform check-record-slot-for-insertion varying i from 1 by 1
                                                      until i > bucket-size.
    if (record-not-inserted) and (link-field not = 0) then
                         move link-field to target-bucket
                         read hash-file invalid key perform read-error-para
    else if (record-not-inserted) and (link-field = 0) then
                         perform extend-chain-para.

check-record-slot-for-insertion.
    if (record-not-inserted) and
       (rec-status(i) = SPACES or rec-status(i) = "DEL")
    then
       move "Y" to record-inserted-flag
       move hash-value-calc to hash-value(i)
       move "OCC" to rec-status(i)
       move acct-no-in to acct-no(i)
       move customer-name-in to customer-name(i)
       move other-data-in to other-data(i)
       rewrite hash-bucket invalid key perform rewrite-error-para.

extend-chain-para.
    move target-bucket to save-address.
    move "Y" to bucket-full-flag.
    perform find-next-bucket until (bucket-not-full) or (cannot-extend-chain).
    if can-extend-chain then perform link-new-bucket-into-chain.

find-next-bucket.
    add 1 to target-bucket.
    if (target-bucket > max-no-buckets) then move 1 to target-bucket.
    read hash-file invalid key perform read-error-para.
    if target-bucket = save-address then move "N" to extend-chain-flag.
    perform find-next-slot varying i from 1 by 1 until (i > bucket-size) or
                                                       (bucket-not-full).

link-new-bucket-into-chain.
    move target-bucket to new-bucket-address.
    move save-address to target-bucket.
    read hash-file invalid key perform read-error-para.
    move new-bucket-address to link-field.
    rewrite hash-bucket invalid key perform rewrite-error-para.
    move new-bucket-address to target-bucket.
    read hash-file invalid key perform read-error-para.

find-next-slot.
    if (rec-status(i) not = "OCC") then move "N" to bucket-full-flag.

rewrite-error-para.
    display "Rewrite error on hash file".

read-error-para.
    display "Read error on hash file".

write-error-para.
    display "write error on hash file".

add-error-para.
    display "account number: ", acct-no-in, "cannot be added".

file-is-full-error-para.
    display "Record cannot be added: file is full".
