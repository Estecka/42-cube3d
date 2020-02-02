We are in clip space, after the perspective matrix has been applied.
We are working with the cartesian coordinates of the projection.

Let there be a triangle ABC.
_Since all meshs are going to be squares, we may instead want to directly work with a quadrilater, ABCD._
Let there be a point P, whose XY coordinates match the current pixel, and which lands on the plane ABC.

**Is the figure backfaced ?**
**Does P land on the figure ?**
**What is the Z coordinate of P ?**
**Where does P land on the UV map ?**

-------

Let N be the Normale of A^B and A^C *in clip space specifically*.
_(Projection matrices are unable to properly transform Z components in a relevant fashion. Thus calculating the normal in world space ahead of time then applying the perspective matrix to it would yield a different, unnacurate result.)_
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

**If both Ty's or both Tx's have the same sign, and are either below -1 or above 1, the figure should be skipped.**
**If P does not have both coordinate included in these bounds, the pixel should be skipped.**

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

Let M be the perspective projection matrix.
`[m00   0 m20 m30]`
`[  0 m11 m21 m31]`
`[  0   0 m22 m32]`
`[  0   0 m23   0]`

For this section, we need to work using homogeneous coordinates instead of cartesian coordinates.
We already know the homogeneous coordinates of ABC.
[Cartesian to Homegeneous](Unproject.md)
The homegeneous coordinates of P are:
`P *= -m31*(m22/m23 - Pz)`

Let there be a UV space, whose X and Y axes are B^A and B^C respectively.
_B is used as origin so that it can be consistent with ABCD_
We arbitrarily use O^P as the Z axis. (The exact Z axis does not matter, as long as it is linearly independ from ABC.)

The transformation from UV space to homegeneous clip space can be represented with a affine 4x4 matrix:
`[BAx BCx OPx Bx]`
`[BAy BCy OPy By]`
`[BAz BCz OPz Bz]`
`[  0   0   0  1]`
But by ignoring translation, we can simplify computation and use a linear 3x3 matrix instead
Let F be this matrix :
`[BAx BCx OPx]`
`[BAy BCy OPy]`
`[BAz BCz OPz]`
Let F' be the inverse of this matrix.
[Source](https://www.mathsisfun.com/algebra/matrix-inverse.html)
[Test](Inverse3x3.md)

**The coordinates of homegeneous P in UV space are :**
`UV = F' * (P - B)`

--------

Unused sources
[Inverse 4x4](https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform)
