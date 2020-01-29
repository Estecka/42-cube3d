Let there be a triangle ABC
Let there be a pixel P

_Does P land on ABC ?_
_Is the triangle backfaced ?_
_How far away is P on the plane ABC ?_


Let 3x3 affine matrix be presented as :
`[Xx Yx Tx]`
`[Xy Yy Ty]`
`[ 0  0  1]`
With determinant:
`Xx*Yy - Yx*Xy`

Let there be a "triangle space", defined by ^X = A^B and ^Y = A^C
The affine tranformation from triangle space to screen space is a 3x3 matrix : 
`[ABx ACx Ax]`
`[ABy ACy Ay]`
`[ 0   0   1]`
With determinant: 
`d = ABx*ACy - ACx*ABy`

**If the determinant is smaller or equal to 0, the triangle is backfaced and should not be rendered.**

[Source](https://www.mathsisfun.com/algebra/matrix-inverse.html)
[Source](https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform)
The inverse of this matrix is 
`[ ACy/d -ACx/d    -Ax]`
`[-ABy/d  ABx/d    -Ay]`
`[     0      0      1]`

[Test](Inverse3x3.md)