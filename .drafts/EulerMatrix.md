We are using a right-handed system.
Assuming that : 
Positive X angle goes from y to z. (look up)
Positive Y angle goes from z to x. (look left)
Positive Z angle goes from x to y. (tilt left)

Let :
c =  cos(α)
s =  sin(α)
a = -sin(α)

Rotation X :
`[1    ]`
`[  c a]`
`[  s c]`

Rotation Y :
`[c   s]`
`[  1  ]`
`[a   c]`

Rotation Z :
`[c a  ]`
`[s c  ]`
`[    1]`

To inverse any of these matrix, simply transpose them.

Rotation order :
`mY * mX * mZ`
=
mY *
`[1      ]   [Cz -Sz  ]`
`[  Cx Sx] * [Sz  Cz  ]`
`[ -Sx Cx]   [       1]`
=
mY *
`[           Cz][   -Sz][ 0]`
`[Cx*Sz + Sx*Sz][ Cx*Cz][Sx]`
`[       -Sx*Sz][-Sx*Cz][Cx]`
=
mY *
`[           Cz][   -Sz][ 0]`
`[Cx*Sz + Sx*Sz][ Cx*Cz][Sx]`
`[       -Sx*Sz][-Sx*Cz][Cx]`
=
`[ Cy   Sy]   [           Cz][   -Sz][ 0]`
`[    1   ] * [Cx*Sz + Sx*Sz][ Cx*Cz][Sx]`
`[-Sy   Cy]   [       -Sx*Sz][-Sx*Cz][Cx]`
=
`[ Cy*Cz - Sy*Sx*Sz][          -Cy*Sy][Sy*Cx]`
`[    Cx*Sz + Sx*Sz][       -Sy*Sx*Cz][   Sx]`
`[-Sy*Cz - Cy*Sx*Sz][Sy*Sz - Cy*Sx*Cz][Cy*Cx]`
=
`[ Cy*Cz - Sy*Sx*Sz][          -Cy*Sy][Sy*Cx]`
`[     Sz * (Cx+Sx)][       -Sy*Sx*Cz][   Sx]`
`[-Sy*Cz - Cy*Sx*Sz][Sy*Sz - Cy*Sx*Cz][Cy*Cx]`