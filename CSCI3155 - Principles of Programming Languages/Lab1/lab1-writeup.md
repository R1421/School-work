#Raymond Duncan
#CSCI3155
#Lab1 Writeup

2a)	The use of pi in line 4 is bound at line 3 and the use of pi at line 7 is bound at line 1.

2b)	The use of x at line 3 is bound at line 2.
	The use of x at line 6 is bound at line 5.
	The use of x at line 10 is bound at line 5.
	The use of x at line 13 is bound at line 1.

3)	The body of g is well typed.

	Lines 1-4: ((Int, Int), Int) because
		Line 3: ((Int, Int), Int) because it returns either (b,1) or (b, a+2)
			b: (Int, Int)
			a+2: Int


