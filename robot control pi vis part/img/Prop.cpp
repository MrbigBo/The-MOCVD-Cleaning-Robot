# include "Prop.h"
# include "Frot.h"
# include <cmath>
# include <vector>

std::vector<int> site_all(17);

struct Date {
    int dst;
    int ang;
};

Date dit_pit( cv::Point Mpoint , cv::Point Spoint)
{
    Date exa;
    int src = ( Mpoint.x * Mpoint.x ) + ( Mpoint.y * Mpoint.y ) - ( Spoint.x * Spoint.x ) + ( Spoint.y * Spoint.y );
    exa.dst = src;
    float sra = atan2( Mpoint.y - Spoint.y , Mpoint.x - Spoint.x ) + M_PI;
    float san = sra / M_PI_4;
    if (san == 8) san = 0;
    exa.ang = san;
    return exa;

}
int judgarea( cv::Point stainPosition , cv::Point Spoint)
{
    Date Fin;
    Fin = dit_pit( stainPosition , Spoint);
    if ( Fin.dst < 576) return 0;
    else if ( Fin.dst < 2209 )
    {
        return 1  + Fin.ang;
    }
    else
    {
        return 10 + Fin.ang;
    }
}

std::vector<int> fi1dctr ( cv::Mat src )
{
    int n = 0 ;
    std::vector< std::vector< cv::Point>> contours;
    std::vector< cv::Vec4i> hireachy;
    findContours(src, contours, hireachy,  cv::RETR_TREE,  cv::CHAIN_APPROX_SIMPLE,  cv::Point());
    cv::Point Spoint;
    Spoint.x = src.cols / 2;
    Spoint.y = src.rows / 2;

    std::set<int>st;
    std::set<int>::iterator it;
    for ( int i = 0 ;i < contours.size() ;i++)
    {
        if ( contours[i].size() < 50 ) continue;
		for(int j = 0 ;j < contours[i].size() ;j++) 
		{
            cv::Point P= cv::Point(contours[i][j].x,contours[i][j].y);
            int site = judgarea( P , Spoint );
            st.insert(site);
		}
    }
    for (it = st.begin(); it != st.end(); it++)
    {
        site_all[n] = (*it);
        n++;
    }
    
    // std::cout << contours[i][j].x << "****" << contours[i][j].y << std::endl; 
    return site_all;

}

