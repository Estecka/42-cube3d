Let there be a figure (either a triangle or a parallelogram) ABC
(In the case of a parallelogram, its axis of symmetry is BC).
Let there be a pixel P

_Does P land on ABC ?_
_Is the figure backfaced ?_
_How far away is P on the plane ABC ?_


Let 2x2 linear matrices be presented as :
`[Xx Yx]`
`[Xy Yy]`
With determinant:
`Xx*Yy - Yx*Xy`

Let there be a "figure space", using A^B as its x axis, and A^C as its Y axis.
Ignoring translation, the linear tranformation from figure space to screen space a 2x2 matrix M: 
`[ABx ACx]`
`[ABy ACy]`
With determinant: 
`d = ABx*ACy - ACx*ABy`

**If the determinant is smaller or equal to 0, the triangle is backfaced and should not be rendered.**

[Source](https://www.mathsisfun.com/algebra/matrix-inverse.html)
[Source](https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform)
The inverse of this matrix is M':
`[ ACy/d -ACx/d]`
`[-ABy/d  ABx/d]`
[Test](Inverse2x2.md)

Let P` be the position of P in figure space:
`P' = M' * (P - A)`
(Substracting A is required ahead of time, because M and M` do not handle translations.)

**If either Px or Py is negative, P does not land on ABC.**
If ABC is a triangle:      **If the sum of Px and Py is greater than 1, P does not land on ABC.**
If ABC is a parallelogram: **If Either Px or Py is greater than 1, P does not land on ABC.**

Let N be the normale of ABC
`N = AB ⨯ AC = {ABy*ACz - ABz*ACy, ABz*ACx - ABx*ACz, ABx*ACy - ABy*ACx}`
The plane equation of ABC is
`Nx*x + Ny*y + Nz*z = d`
`Nx*Ax + Ny*Ay + Nz*Az = d`

**The distance from the camera to ABC in P is :**
`Nx*x + Ny*y + Nz*z - d = 0`
`Nx*x + Ny*y - d = - Nz*z`
`-(Nx*x + Ny*y - d)/Nz = z`
**Or, considering the right-hand rule of Z facing backward :**
`(Nx*x + Ny*y - d)/Nz = z`
