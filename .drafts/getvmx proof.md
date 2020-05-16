We are looking for an affine function `y = ax + b` such as x is the coordinate of a pixel on-screen, and y the normalized position of the pixel on the wall.
To avoid confusion with the X and Y axes of the world, I will instead refer to the input pixel coordinate as `pix` and the output normalized wall coordinate as `Wz`.

[insert graphic]

By dividing pix by screen_height, we get its normalized position on the screen (`Pz`), and can represent it as a plane in front of the observer :
`Pz = pix / sc_hgt`

If this projection was `1` unit away from the observer, its height would be `2 * v_tan` instead of 1. 
With this hypotetical plane, we can use Thales to find the distance `Py` from the fist projection. to the observer : 
`Py / 1 = 1 / (2 * v_tan)`
`Py = 1/(2*v_tan)`

The vertical tangente is not readily available, but fully unwraping it this is not going to be useful later down.
Anyways, it can be calculated like this:
`v_tan = aspect * h_tan`
`      = aspect * frustrum_left / frustrum_near`
In this context, the aspect **is not** the traditional `width/height`, but is `height/width` instead.


Let `Wy` be the (known) distance from the wall to the observer.
If we focus on only the upper half of the vision field, we can use Thales to find `Wz`
The height of the half-triangle on the projection is `Pz - 0.5`.
The height of the half-triangle on the wall is `Wz - 0.5`.
`(Wz - 0.5) / Wy = (Pz - 0.5) / Py`
`(Wz - 0.5) = Wy * (Pz - 0.5) / Py`
`Wz = 0.5 + (Wy * (Pz - 0.5) / Py)`
Now we just need to reshape this formula into an affine function, and unwrap the variables.
`Wz = 0.5 + (Wy * (Pz - 0.5) / Py)`
`   = 0.5 + ((Wy*Pz + Wy*0.5) / Py)`
`   = 0.5 + ((Wy*Pz + Wy*0.5) / Py)`
`   = 0.5 + ((Wy*Pz + Wy*0.5) / (1/(2*v_tan)))`
`   = 0.5 + ((Wy*Pz + Wy*0.5) * (2*v_tan))`
`   = 0.5 + (Wy*Pz*2*v_tan) + (Wy*0.5*2*v_tan)`
`   = (Wy*Pz*2*v_tan) + (Wy*0.5*2*v_tan) + 0.5`
`   = ((pix/sc_hgt)Wy*2*v_tan) + (0.5*Wy*2*v_tan) + 0.5`
`   = (pix*Wy*2*v_tan/sc_hgt) + (0.5*Wy*2*v_tan) + 0.5`
`   = (pix*Wy*2*v_tan/sc_hgt) + (sc_hgt*0.5*Wy*2*v_tan/sc_hgt) + 0.5`

This is our final affine function.
There, we have : 
`a = Wy * 2 * v_tan /sc_hgt`
`b = (0.5 * sc_hgt * a) + 0.5`