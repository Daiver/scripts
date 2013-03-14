#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <fstream>
#include <vector>

int main (int argc, char** argv)
{
    std::ifstream in("/home/kirill/slamforfly/PTAM/dumps/220");
    std::vector<float> raw_data;

    //for (int i = 0; i < 6; i++)
    while (!in.eof())
    {
        float x;
        in >> x;
        //std::cout<<x;
        //std::cout<<"\n";
        raw_data.push_back(x);
    }
    in.close();
    pcl::PointCloud<pcl::PointXYZ> cloud;
    // Fill in the cloud data
    cloud.width    = raw_data.size()/3; //5
    cloud.height   = 1;
    cloud.is_dense = false;
    cloud.points.resize (cloud.width * cloud.height);
    int j = 0;
    std::cout<<cloud.points.size()<<" size\n";
    for (size_t i = 0; i < cloud.points.size (); ++i)
    {
        cloud.points[i].x = raw_data[i*3];
        cloud.points[i].y = raw_data[i*3 + 1];
        cloud.points[i].z = raw_data[i*3 + 2];
        /*cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
        cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
        cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);*/
    }

    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
    std::cerr << "Saved " << cloud.points.size () << " data points to test_pcd.pcd." << std::endl;

    for (size_t i = 0; i < cloud.points.size (); ++i)
        std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

    return (0);
}
