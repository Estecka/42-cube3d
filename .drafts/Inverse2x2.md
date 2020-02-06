Let a matrix be 
`[5 9]`
`[4 6]`

Its determinant is 
`6*5 - 4*9`
`30 - 36`
`-6`

Its inverse is
`[6/-6 -9/-6]`
`[-4/-6 5/-6]`
=
`[ -1  1.5]`
`[2/3 -5/6]`

Test:
`[ -1  1.5] * [5 9]`
`[2/3 -5/6]   [4 6]`
=
`[-1*5 + 1.5*4][-1*9 + 6*1.5]`
`[5*2/3 + 4*-5/6][9*2/3 + 6*-5/6]`
=
`[-5 + 6][-9 + 9]`
`[10/3 + -20/6][18/3 + -30/6]`
=
`[1 0]`
`[0 1]`
OK

--------

Let an arbitrary matrix M be
`[m00 m10]`
`[m01 m11]`

Its determinant d is
`d = m00*m11 - m01*m10`

Its inverse is 
`[ m11/d  -m10/d]`
`[-m01/d   m00/d]`

Test:
`[m00 m10] * [ m11/d  -m10/d]`
`[m01 m11]   [-m01/d   m00/d]`
= 
`[m00*m11/d - m10*m01/d][m10*m00/d - m00*m10/d]`
`[m01*m11/d - m11*m01/d][m11*m00/d - m01*m10/d]`
= 
`[(m00*m11 - m10*m01)/d][(m10*m00 - m00*m10)/d]`
`[(m01*m11 - m11*m01)/d][(m11*m00 - m01*m10)/d]`
=
`[(m00*m11 - m10*m01)/(m00*m11 - m01*m10)][(m10*m00 - m00*m10)/(m00*m11 - m01*m10)]`
`[(m01*m11 - m11*m01)/(m00*m11 - m01*m10)][(m11*m00 - m01*m10)/(m00*m11 - m01*m10)]`
=
`[1][0/(m00*m11 - m01*m10)]`
`[0/(m00*m11 - m01*m10)][1]`
=
`[1 0]`
`[0 1]`
OK