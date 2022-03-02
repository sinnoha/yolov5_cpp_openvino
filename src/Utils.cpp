#include "Utils.h"

using namespace std;
using namespace boost::filesystem;

InputParser::InputParser(int &argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
}

/// @author iain
const std::string &InputParser::getCmdOption(const std::string &option) const
{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end())
    {
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}

/// @author iain
bool InputParser::cmdOptionExists(const std::string &option) const
{
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}

// 根据路径和扩展名获得文件
list<string> getDirFile(const path &dir, const vector<string> *exten_lists)
{
    list<string> filesList;
    directory_iterator end;
    for (directory_iterator pos(dir); pos != end; pos++)
    {
        if (is_directory(*pos))
        {
            getDirFile(*pos, exten_lists);
        }
        else
        {
            string filesName = pos->path().string();
            if (std::find(exten_lists->begin(), exten_lists->end(), pos->path().extension()) != exten_lists->end())
            {
                filesList.push_back(filesName);
            }
        }
    }
    return filesList;
}

list<string> find_images(string source_path)
{
    list<string> filesList;
    const path dir(source_path);
    // const path dir(initial_path());
    // const path curdir(current_path());
    // cout << "Initial_path: " << initial_path() << endl << "Current_dir:  " << curdir << endl;
    const vector<string> exten_lists{".png", ".jpg"};

    filesList = getDirFile(dir, &exten_lists);
    // BOOST_FOREACH(auto str, filesList)
    //{
    //     cout << "Find file:    " << str << endl;
    // }
    // cout << "Bye-bye!" << endl;
    return filesList;
}



void print_label(cv::Mat image, cv::Rect *rect, std::string label_text, float prob, cv::Scalar fill_color)
{
    //设置绘制文本的相关参数
    int font_face = cv::FONT_HERSHEY_COMPLEX_SMALL;
    double font_scale = 2;
    int thickness = 2;
    int baseline = 0;
    //获取文本框的长宽
    cv::Size text_size = cv::getTextSize(label_text, font_face, font_scale, thickness, &baseline);

    cv::Point text_tl;
    text_tl.x = rect->tl().x - 1;
    text_tl.y = rect->tl().y - text_size.height;

    Rect text_rect(text_tl.x, text_tl.y - text_size.height, text_size.width, text_size.height * 2);
    cv::rectangle(image, text_rect, fill_color, FILLED, LINE_8, 0);

    // text_tl.x = rect->tl().x + 3;
    text_tl.y = rect->tl().y - text_size.height + 15;
    cv::putText(image, label_text, text_tl, font_face, font_scale, cv::Scalar(255, 255, 255), thickness, 8, 0);

    // print prob
    font_scale = 1;
    thickness = 1;

    // string prob_text = "prob: " + to_string(prob);
    string prob_text = to_string(prob);
    cv::Size prob_size = cv::getTextSize(prob_text, font_face, font_scale, thickness, &baseline);

    cv::Point prob_tl;
    prob_tl.x = rect->tl().x - 1;
    prob_tl.y = rect->tl().y - text_size.height * 2 - prob_size.height;

    Rect prob_rect(prob_tl.x, prob_tl.y - prob_size.height, prob_size.width, prob_size.height * 2);
    cv::rectangle(image, prob_rect, fill_color, FILLED, LINE_8, 0);

    // text_tl.x = rect->tl().x + 3;
    prob_tl.y = rect->tl().y - text_size.height * 2 - prob_size.height + 7;
    cv::putText(image, prob_text, prob_tl, font_face, font_scale, cv::Scalar(255, 255, 255), thickness, 8, 0);
}