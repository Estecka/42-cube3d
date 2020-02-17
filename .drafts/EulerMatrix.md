We are using a right-handed system.
Positive X goes from y to z. (look up)
Positive Y goes from z to x. (look left)
Positive Z goes from x to y. (tilt left)

Let :
c = cos( α)
s = sin( α)
a = sin(-α)

Rotation X :
[1    ]
[  c a]
[  s c]

Rotation Y :
[c   s]
[  1  ]
[a   c]

Rotation Z :
[c a  ]
[s c  ]
[    1]

To inverse any of these matrix, simply transpose them.

Rotation order :
`mY * mX * mZ`
=
mY *
`[ Cx   Sx] * [Cz -Sz  ]`
`[    1   ] * [Sz  Cz  ]`
`[-Sx   Cx] * [       1]`
=
mY *
`[ Cx*Cz][-Sz*Cx][Sx]`
`[    Sz][    Cz][ 0]`
`[-Sx*Cz][-Sx*Sz][Cx]`
=
`[ Cy    Sy] * [ Cx*Cz][-Sz*Cx][Sx]`
`[     1   ] * [    Sz][    Cz][ 0]`
`[-Sy    Cy] * [-Sx*Cz][-Sx*Sz][Cx]`
=
`[Cy*Cx*Cz+Sy*-Sx*Cz][Cy*-Sz*Cx+Sy*-Sx*Sz][Cy*Sx+Sy*Cx]`
`[Sz][Cz][0]`
`[-Sy*Cx*Cz+Cy*-Sx*Cz][-Sy*Cx*-Sz+Cy*-Sx*Sz][-Sy*Sx+Cy*Cx]`
=
`[ Cz(Cy*Cx - Sy*Sx)][-Sz(Cy*Cx + Sy*Sx)][Cy*Sx + Sy*Cx]`
`[                Sz][                Cz][            0]`
`[-Cz(Sy*Cx + Cy*Sx)][ Sz(Sy*Cx - Cy*Sx)][Cy*Cx - Sy*Sx]`
