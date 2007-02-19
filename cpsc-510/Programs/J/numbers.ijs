NB. returns the average of a list
avg=: +/ % #

a =. 12 14 8 9 28 4.
b =. avg a

NB. Number of elements above average
+/ a > b
