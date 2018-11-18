# webcam_circles
Circle detection from online webcam images

# My notes: How Hough transformation works
Sources:
* 
* 

This _understanding_ was performed in R2 dimension.

- To represent detected circles uses three parameters: center point in X axis, center point in Y axis, and radius of the circle.

- Hough Circle Transform is sensitive to noise. Its common to blur the image with a _GaussianBlur_ method, and even convert it to greyscale color.

- OpenCV do not uses the standard Hough Transform, but a variant one called **Hough Gradient Method**. And it works in a similar way that _Hough Line Tranform_.

- Mathematical equations and his code implementation are to complex for my own understanding.

Explanation of each parameter:

  - **GAUSSIAN_BLUR_SIZE**: Used to reduce image noise in *GaussianBlur* method. Represents the number of neighbors to use, in a weight and height way. This size must be odd, positive, and its common to use the same weight and height, as a square section.
  - **GAUSSIAN_BLUR_SIGMA**: Also used to reduce image noise in *GaussianBlur* method. Standard deviation in X axis. If _0_ value is provided, it is calculated with *GAUSSIAN_BLUR_SIZE* parameter.
  - **CANNY_EDGE_TH**:  *HoughCircles* method uses *Canny* as an edge detection method, and this parameter (_param1_ in docs) is used to determine the threshold parameter. This value is the higher threshold, and the lower is equal to two times smaller.
  - **HOUGH_ACCUM_RESOLUTION**: The _dp_ parameter, is told in docs "Inverse ratio of the accumulator resolution to the image resolution". For a value equal to _1_, the resolution is the same as the input image. For a value equal to _2_, the resolution is half the width and height as the input image.
  - **MIN_CIRCLE_DIST**: Determine the minimum distance between circle centers. Too small and false neighbors could be detected; too large and close circles could be missed.
  - **HOUGH_ACCUM_TH**: Corresponding to the _param2_ parameter in docs, is told that "the accumulator threshold for the circle centers at the detection stage". Not fully understanding what that means, but seems that for small values it detects more false circles.
  - **MIN_RADIUS**: Minimum radius of circles detected
  - **MAX_RADIUS**: Maximum radius of circles detected

### References
- [https://www.aprenderpython.net/la-transformada-linea-hough/](https://www.aprenderpython.net/la-transformada-linea-hough/)
- [https://en.wikipedia.org/wiki/Hough_transform#Theory](https://en.wikipedia.org/wiki/Hough_transform#Theory)
- [https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html#hough-circle](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html#hough-circle)
- [https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#hough-lines](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#hough-lines)