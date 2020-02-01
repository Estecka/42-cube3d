Let there be a point P.
Let there be a perspective projection matrix M:
`[S 0 0 T]`
`[0 S 0 U]`
`[0 0 E G]`
`[0 0 F 0]`

The homogeneous projection of P is P':
`[SPx + T]`
`[SPy + U]`
`[EPz + G]`
`[FPz]`

The cartesian projection of P is P'':
`[(SPx+T)/FPz]`
`[(SPy+U)/FPz]`
`[E/F + G/FPz]`
`[1]`

We kow P''.
We know S, F, G.
We are looking for P'w.
`P'w = FPz`

` P''z  =     E/F + G/FPz`
` P''z  =     E/F + G/P'w`
` 0     =     E/F + G/P'w - P''z`
`-G/P'w =     E/F - P''z`
`-P'w/G =  1/(E/F - P''z)`
` P'w   = -G/(E/F - P''z)`
