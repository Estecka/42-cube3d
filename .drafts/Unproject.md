Let there be a point P.
Let there be a perspective projection matrix M:
`[- - - -]`
`[- - - -]`
`[0 0 E G]`
`[0 0 F 0]`

The homogeneous projection of P is P':
`[-]`
`[-]`
`[EPz + G]`
`[FPz]`

The cartesian projection of P is P":
`[-]`
`[-]`
`[E/F + G/FPz]`
`[1]`

We know P".
We know all values of M.
We are looking for P".
`P'w = FPz`

` P"z   =     E/F + G/FPz`
` P"z   =     E/F + G/P'w`
` 0     =     E/F + G/P'w - P"z`
`-G/P'w =     E/F - P"z`
`-P'w/G =  1/(E/F - P"z)`
` P'w   = -G/(E/F - P"z)`

`P' = P" * -G(E/F - P"z)`
