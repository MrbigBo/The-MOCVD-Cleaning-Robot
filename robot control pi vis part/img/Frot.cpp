#include "Frot.h"

cv::Size dsize = cv::Size(0 , 0);
cv::Mat fort(cv::Mat src)
{
    //circles_para
    int radius = 650;
    // int min_radius = 10;
    // double dp = 1;
    // double minDist = 500;
    // double  param1 = 100;
    // double  param2 = 100;   
    //draw_circles_para
    int ix,iy,x_max,x_min,y_max,y_min;
    //mask_para
    int i,j;
    int cx = src.cols / 2;
    int cy = src.rows / 2;
    
    cv::Mat pre_img;
    // 返回图片尺寸
    std::cout << "x al" << src.cols << "y al" << src.rows << std::endl;
    //cv::resize(croppedImage , croppedImage , dsize ,0.5 , 0.5);
    // 霍夫检测
    // std::vector<cv::Vec3f> circles;
    // HoughCircles(pre_img, circles, cv::HOUGH_GRADIENT, dp, minDist, param1, param2, min_radius);
    // cv::Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
    // cv::circle(pre_img, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
    // cv::circle(pre_img, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);

    ix = cx;
    iy = cy;
    x_max = ix + radius;
    x_min = ix - radius;
    y_max = iy + radius;
    y_min = iy - radius;

    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());
    for (i = 0 ; i < src.cols; i++)
    {
        for (j = 0; j < src.rows; j++)
        {
            int radnow = sqrt(( j - ix)*( j - ix)+(i - iy)*(i - iy));
            if (radnow < radius)
            {
                dst.at<cv::Vec3b>(j ,i)[0] = src.at<cv::Vec3b>(j ,i)[0];
                dst.at<cv::Vec3b>(j ,i)[1] = src.at<cv::Vec3b>(j ,i)[1];
                dst.at<cv::Vec3b>(j ,i)[2] = src.at<cv::Vec3b>(j ,i)[2];
            }
            else
            {
                dst.at<cv::Vec3b>(j ,i)[0] = 255;
                dst.at<cv::Vec3b>(j ,i)[1] = 255;
                dst.at<cv::Vec3b>(j ,i)[2] = 255;               
            }
        }
    }

    cv::Rect roiRect(y_min ,x_min, 2 * radius, 2 * radius);
    cv::Mat croppedImage = dst(roiRect);

    return croppedImage;
} 