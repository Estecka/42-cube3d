[Source](https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix)

Let there be an arbitrary 3x3 linear matrix :
`[m00 m10 m20]`
`[m01 m11 m21]`
`[m02 m12 m22]`

Its determinant is : 
`d = m00(m11*m22 - m12*m21) - m10(m01*m22 - m02*m21) + m20(m01*m12 - m02*m11)`

Its transposed matrix is :
`[m00 m01 m02]`
`[m10 m11 m12]`
`[m20 m21 m22]`

Its adjoint matrix is:
`[m11*m22 - m21*m12][m10*m22 - m20*m12][m10*m21 - m20*m11]   [+1 -1 +1]`
`[m01*m22 - m21*m02][m00*m22 - m20*m02][m00*m21 - m20*m01] * [-1 +1 -1]`
`[m01*m12 - m11*m02][m00*m12 - m10*m02][m00*m11 - m10*m01]   [+1 -1 +1]`
=
`[m11*m22 - m21*m12][m20*m12 - m10*m22][m10*m21 - m20*m11]`
`[m21*m02 - m01*m22][m00*m22 - m20*m02][m20*m01 - m00*m21]`
`[m01*m12 - m11*m02][m10*m02 - m00*m12][m00*m11 - m10*m01]`

Its inverse matrix is : 
