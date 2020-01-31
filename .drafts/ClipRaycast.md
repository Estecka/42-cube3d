We are in clip space.
The projection matrix has been applied, thus the percieved picture is not hortognal.
Let M and M` be the projection matrix and its inverse, respectively.

Let there be a triangle ABC.
We may instead want to work with a quadrilater, ABCD.
Let there be a point P, whose XY coordinates match the current pixel.

_Is the figure backfaced ?_
_Does P land on the figure ?_
_What is the Z coordinate of P ?_
_Where does P land on the UV map ?_

-------

Let N be the Normale of A^B and A^C *in clip space specifically*: _(Projection matrices are unable to properly transform Z components in a relevant fashion. Thus calculating the normal in world space ahead of time then appliying the matrix would yield a different result.)_
`N = AB ⨯ AC`
`Nx = ABy*ACz - ABz*ACy`
`Ny = ABz*ACx - ABx*ACz`
`Nz = ABx*ACy - ABy*ACx`

**If Nz is either null or negative, the figure is backfaced and must be skipped.**
_Null or positive in the case of a left-hand rule._

N will be reused later on.

--------

Pure optimization, this section is not strictly required.
Let us forget the z dimension for this section.
Let's take the maximum and minimum coordinates of each points of ABC :
(In the case of a quadrilater, D is also taken into account.)
`Txmin = min(Ax, Bx, Cx, Dx)`
`Tymin = min(Ay, By, Cy, Dy)`
`Txmax = max(Ax, Bx, Cx, Dx)`
`Tymax = max(Ay, By, Cy, Dy)`

**If both Ty's or both Tx's have the same sign, and are either are below -1 or above 1, the figure should be skipped.**
**If P does not have both coordinate strictly included in these bounds, the pixel should be skipped.**

--------

Let us forget the Z dimension for this section.
For each point in the figure, we make a vector that goes from there to P. We then calculate their cross product with their matching vectors from ABC : 
`Ca = A^B ⨯ A^P = ABx*APy - ABy*APx`
`Cb = B^C ⨯ B^P = BCx*BPy - BCy*BPx`
`Cc = C^A ⨯ C^P = CAx*CPy - CAy*CPx`

In the case of a quadrilater, Cc is calculated differently, and we also need Cd :
`Cc = C^D ⨯ C^P = CDx*CPy - CDy*CPx`
`Cd = D^A ⨯ D^P = DAx*DPy - DAy*DPx`

**If any of Ca, Cb, Cc or Cd is negative, P does not land on the figure.**
_Null values are ambiguous and can be treated either way. For consistency with the previous section, they should be treated negative._

--------

The plane equation of ABC is :
`d = Nx*x + Ny*y + Nz*z`
We can find its determinant by plugging in A : 
`d = Nx*Ax + Ny*Ay + Nz*Az`
We can then plug in the known coordinates of P:
`d = Nx*Px + Ny*Py + Nz*Pz`
`0 = Nx*Px + Ny*Py + Nz*Pz - d`
`-Nz*Pz = Nx*Px + Ny*Py - d`
`Pz = -(Nx*Px + Ny*Py - d)/Nz`
**If Pz is strictly greater than the current Z-buffer, the pixel must be skipped.**
_Smaller in the case of a left-hand rule._

--------

[Source](https://www.mathsisfun.com/algebra/matrix-inverse.html)
[Source](https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform)
[Test](Inverse3x3.md)

For this section, we actually need to take a step back, right before the projection matrix was applied.
Let A'B'C' be the figure before this transformation.
`A'B'C' = C' * ABC`
_In the case of a quadrilater, it becomes a parallelogram, thus D' is not needed._
In theory, ABC were calculated from A'B'C'.
Let there be a "figure space", whose X and Y axes are B^A and B^C respectively, and whose Z axis is their cross product.
`N' = B'^A' ⨯ B'^C'`
_B is used as origin so that he can be consistent with ABCD_

The 4x4 matrix F that transforms from figure space to unprojected clip space is:
`[BAx BCx N'x Bx]`
`[BAy BCy N'y By]`
`[BAz BCz N'z Bz]`
`[  0   0   0  1]`

The inverse of this matrix is F`.

**The UV of P is :**
`UV = F' * M' * P `
