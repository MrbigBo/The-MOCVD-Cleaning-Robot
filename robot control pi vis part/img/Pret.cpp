# include "Pret.h"
# include "iostream"

cv::Mat pret(cv::Mat src)
{
    cv::Mat gry;
    cv::Mat dst;
    cv::cvtColor(src ,gry, cv::COLOR_BGR2GRAY);
    cv::threshold(gry, dst, 13.5, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hireachy;
    findContours(dst, contours, hireachy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());

    cv::Mat resultImage = cv::Mat::zeros(src.size(), CV_8UC3);
    cv::Point cc;
    for (size_t t = 0; t < contours.size(); t++) {
        double area = cv::contourArea(contours[t]);
        if (area < 130 ) continue;
        cv::Rect rect = cv::boundingRect(contours[t]);
        if (rect.width >500 ) continue;
        float ratio = float(rect.width) / float(rect.height);

        if (ratio < 1.09 && ratio > 0.91) {
            int x = rect.x + rect.width / 2;
            int y = rect.y + rect.height / 2;
            cc = cv::Point(x, y);
            circle(src, cc, 14, cv::Scalar(255, 255, 255), -1, 8, 0);
        }
        
    }

    cv::Mat blur;
    cv::Mat gry1;
    cv::Mat final;
    cv::medianBlur(src ,blur , (11,11));
    cv::cvtColor(blur ,gry1, cv::COLOR_BGR2GRAY);
    cv::threshold(gry1, final, 115, 255, cv::THRESH_BINARY);

    return final;
}
    //画轮廓

    // std::vector<std::vector<cv::Point>> contours1;
    // std::vector<cv::Vec4i> hireachy1;
    // findContours(final, contours1, hireachy1, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    // cv::Mat imageContours =  cv::Mat::zeros(final.size(), CV_8UC1);
    // drawContours(imageContours, contours1, -1,255, 10, 8, hireachy1);
    // cv::imshow("tes",imageContours);  

    // cv::imshow("tes",gry);
    // cv::imshow("test",src);



