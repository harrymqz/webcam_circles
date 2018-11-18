# webcam_circles
Circle detection from online webcam images

# My notes: How Hough circle transform works 

The Hough transform is a popular technique to detect form, whenever it can be represented in a math form.
In the circle detection case we need three parameters to define a circle: C:(Xcenter, Ycenter, r), I mean XY position in R2 dimension and radius.

### References
- [https://www.aprenderpython.net/la-transformada-linea-hough/](https://www.aprenderpython.net/la-transformada-linea-hough/)
- [https://en.wikipedia.org/wiki/Hough_transform#Theory](https://en.wikipedia.org/wiki/Hough_transform#Theory)
- [https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html#hough-circle](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html#hough-circle)
- [https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#hough-lines](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#hough-lines)