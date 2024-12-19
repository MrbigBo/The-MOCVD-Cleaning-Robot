#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Frot.h"
#include "Pret.h"
#include "Prop.h"

using namespace cv;
using namespace std;

Mat src,ft_img,pe_img,po_img;
std::vector<int> site(17);
int main()
{
    src = imread("D:/desktop/robot_vi/picture_j/pic1213.jpg");
    ft_img = fort(src);
    pe_img = pret(ft_img);
    site = fi1dctr(pe_img);
    
    for ( int i = 0;i < site.size();i++ )
    {
        cout << site[i] << endl;
    }
    
    imshow("test_1",pe_img);
	waitKey(0);
	return 0;
}