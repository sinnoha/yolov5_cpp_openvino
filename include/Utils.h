#pragma once

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace boost::filesystem;

list<string> find_images(string source_path);
list<string> getDirFile(const path &dir, const vector<string> *exten_lists);

void print_label(cv::Mat image, cv::Rect *rect, std::string label_text, float prob, cv::Scalar fill_color);

class InputParser
{
public:
    InputParser(int &argc, char **argv);
    /// @author iain
    const std::string &getCmdOption(const std::string &option) const;
    /// @author iain
    bool cmdOptionExists(const std::string &option) const;

private:
    std::vector<std::string> tokens;
};