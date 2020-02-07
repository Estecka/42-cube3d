## For every quad : (Mass cliping)
* Transform quad from world space to view space.
    - **Compute the figure's bounding box. figure fully outside of the frustrum are skipped.**
    - **Compute the figure's viewspace normale, and dot product with the origin. Backfaced or sidefaced quads are skipped.**
* Quickly sort the remaining quads from closest to furtheset.
    - Quads will be processed in this order, to let the z-culling discard as many pixels as possible.

## For every quad : 
* Transform quad from view space to homogeneous clip space.
* Transform quad from clip space to screen space.
    - Compute the UV to homogeneous matrix for later use.
* Transform quad from homogeneous space to cartesian space.
* Compute quad's screen bounding box.
    - **Any quad fully outside the screen is skipped.**
    - Bounding box is kept for later use.
* Compute and store the quad's plane equation.
* Compute and store the homogeneous to UV matrix.

## For every pixel :
* Every pixel outside the quad's bounding box are skipped.
* Compute the depth of the pixel.
    - Every pixel behind the z-buffer are skipped.
* Transform the pixel from cartesian screen space to homogeneous screen space.
* Compute the pixel's UV
    - Pixels outside of the unit range are skipped.
* Paint the z-buffer.
* Sample the texture and paint the render texture.