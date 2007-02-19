NB. Sumit Khanna / cpsc-510
NB.   numbers.ijs in J 

NB. returns the average of a list
avg=: +/ % #


NB. Number of elements above average 
NB.  a = array of numbers 
NB.  b = result of avg
+/ a > b

NB. Example

a =. 12 14 8 9 28 4.
b =. avg a
+/ a > b


