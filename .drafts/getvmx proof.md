We are looking for an affine function `y = ax + b` such as x is the coordinate of a pixel on-screen, and y the normalized position of the pixel on the wall.
To avoid confusion with the X and Y axes of the world, I will instead refer to the input pixel coordinate as `pix` and the output normalized wall coordinate as `Wz`.

[insert graphic]
We start by working on one half of the viewfield only, for simplicity.

By dividing pix by screen_height, we get its normalized position on the screen (`Pz`), and can represent it as a plane in front of the observer :
`Pz = pix / sc_hgt`
If this plane was `1` unit away from the observer, its height would be `Pz * v_tan` instead of 1. 
With this hypotetical plane, we can use Thales to find the distance `Py` from the normalized plane to the observer : 
`Py / Pz = 1 / (Pz * v_tan)`
`Py = Pz / (Pz * v_tan)`
`Py = 1 / v_tan`

We can now use Thales again to find the normalized coordinate of the pixel on the wall (`Wz`).
Let `Wy` be the known distance from the wall to the observer.
`Wz / Wy = Pz / Py`
`Wz / Wy = Pz / (1/ v_tan)`
`Wz / Wy = Pz * v_tan`
`Wz = Wy * Pz * v_tan`

Just like that, we get a working linear function for half a vision field.
This function could also be applied to the whole field, but it needs giving a slightly different meaning to some variables : there, `Pz` and `Wz` would be normalized in the range [-1;1] instead of [0;1].
In order to keep their original meaning, let's change the formula to make these corrections.

The function to remap from [0;1] to [-1;1] is :`y = 2x - 1`
We need to wrap this function around both Pz and Wz. We'll then shape the equation back into the form of an affine function.
`2*Wz + 1 = (2 * Pz + 1) * Wy*v_tan`
`2*Wz + 1 = (2 * Pz * Wy*v_tan) + (Wy*v_tan)`
`2*Wz     = (2 * Pz * Wy*v_tan) + (Wy*v_tan + 1)`
`Wz       =((2 * Pz * Wy*v_tan) + (Wy*v_tan + 1)) / 2`
`Wz =           (Pz * Wy*v_tan) + (Wy*v_tan + 1)/2`
`Wz = ((pix/sc_hgt) * Wy*v_tan) + (Wy*v_tan + 1)/2`
`Wz =  (pix * Wy*v_tan /sc_hgt) + (Wy*v_tan/2 + 0.5)`

[...]

The vertical tangente is not readily available to us, but can be calculated like this:
`v_tan  = h_tan * aspect`
In this context, the aspect **is not** the traditional `width/height`, but is `height/width` instead.