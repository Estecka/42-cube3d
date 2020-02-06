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
mY * mX * mZ
=
mY *
`[ Cx   Sx] * [Cz -Sz  ]`
`[    1   ] * [Sz  Cz  ]`
`[-Sx   Cx] * [       1]`
