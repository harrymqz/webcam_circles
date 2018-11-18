# webcam_circles
Circle detection from online webcam images

## My notes: How Hough circle transform works 

The Hough transform is a popular technique to detect form, whenever it can be represented in a math form.

In the circle detection case we need three parameters to define a circle: C:(Xcenter, Ycenter, r), I mean XY position in R2 dimension and radius.

### Some code to explain
```cpp
// Constants
const int GAUSSIAN_BLUR_SIZE = 7;
const double GAUSSIAN_BLUR_SIGMA = 2;
const double HOUGH_ACCUM_RESOLUTION = 2;
const double MIN_CIRCLE_DIST = 40;
const double CANNY_EDGE_TH = 150;
const double HOUGH_ACCUM_TH = 70;
const int MIN_RADIUS = 20;
const int MAX_RADIUS = 100;

// OpenCV video capture object
cv::VideoCapture camera;
// Open the video stream
camera.open(cam_id)

// OpenCV image object
cv::Mat image;
// Put the current image in the image variable
camera.read(image)

// OpenCV Matrix
cv::Mat gray_image;
// If input image is RGB, convert it to gray 
cv::cvtColor(image, gray_image, CV_BGR2GRAY);

// Reduce the noise so we avoid false circle detection
// https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html?highlight=gaussianblur#gaussianblur
cv::GaussianBlur( gray_image, gray_image, cv::Size(GAUSSIAN_BLUR_SIZE, GAUSSIAN_BLUR_SIZE), GAUSSIAN_BLUR_SIGMA );
// - gray_image     - input image; the image can have any number of channels, which are processed independently,
//                    but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F
// - cv:Size(...)   - output image of the same size and type as src
// - GBS            - Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd.
//                    Or, they can be zero’s and then they are computed from sigma*

// Apply the Hough Transform to find the circles
// https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghcircles#houghcircles
cv::HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, HOUGH_ACCUM_RESOLUTION, MIN_CIRCLE_DIST, CANNY_EDGE_TH, HOUGH_ACCUM_TH, MIN_RADIUS, MAX_RADIUS );
// gray_image               - 8-bit, single-channel, grayscale input image
// circles                  - Output vector of found circles. Each vector is encoded as a 3-element floating-point vector (x, y, radius)
// CV_HOUGH_GRADIENT        - Detection method to use. Currently, the only implemented method is CV_HOUGH_GRADIENT,
//                            which is basically 21HT , described in [Yuen90]
// HOUGH_ACCUM_RESOLUTION   - Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1,
//                            the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height
// MIN_CIRCLE_DIST          - Minimum distance between the centers of the detected circles. If the parameter is too small,
//                            multiple neighbor circles may be falsely detected in addition to a true one.
//                            If it is too large, some circles may be missed
// CANNY_EDGE_TH            - First method-specific parameter. In case of CV_HOUGH_GRADIENT,
//                            it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller)
// HOUGH_ACCUM_TH           - Second method-specific parameter. In case of CV_HOUGH_GRADIENT, it is the accumulator threshold for the circle
//                            centers at the detection stage. The smaller it is, the more false circles may be detected.
//                            Circles, corresponding to the larger accumulator values, will be returned first
// MIN_RADIUS               - Minimum circle radius
// MAX_RADIUS               - Maximum circle radius

// Circle center in green
// https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html?highlight=circle#circle
cv::circle(image, center, 5, cv::Scalar(0,0,255), -1, 8, 0 );
// - img – Image where the circle is drawn.
// - center – Center of the circle.
// - radius – Radius of the circle.
// - color – Circle color.
// - thickness – Thickness of the circle outline, if positive. Negative thickness means that a filled circle is to be drawn.
// - lineType – Type of the circle boundary. See the line() description.
// - shift – Number of fractional bits in the coordinates of the center and in the radius value.

// Show image
cv::imshow("Output Window", image);
```

### Questions
- What is depth CV_8U, CV_16U, CV_16S, CV_32F or CV_64F?

### References
- [https://www.aprenderpython.net/la-transformada-linea-hough/](https://www.aprenderpython.net/la-transformada-linea-hough/)
- [https://en.wikipedia.org/wiki/Hough_transform#Theory](https://en.wikipedia.org/wiki/Hough_transform#Theory)
- [https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html#hough-circle](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html#hough-circle)
- [https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#hough-lines](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#hough-lines)
- [https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html?highlight=gaussianblur#gaussianblur](https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html?highlight=gaussianblur#gaussianblur)
- [https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghcircles#houghcircles](https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghcircles#houghcircles)
- [https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html?highlight=circle#circle](https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html?highlight=circle#circle)