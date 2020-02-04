We are using a right-handed system.
Positive X goes from y to z. (look up)
Positive Y goes from z to x. (look left)
Positive Z goes from x to y. (tilt left)

Rotation order :
mZ * mY * mX


Let :
c = cos( α)
s = sin( α)
a = sin(-α)

Rotation X :
[1      ]
[  c a  ]
[  s c  ]
[      1]

Rotation Y :
[c   s  ]
[  1    ]
[a   c  ]
[      1]

Rotation Z :
[c a    ]
[s c    ]
[    1  ]
[      1]

To inverse any of these matrix, simply transpose them.
