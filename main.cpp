#include "Detector.h"
#include "Utils.h"

int main(int argc, char **argv)
{
    InputParser input(argc, argv);
    if (input.cmdOptionExists("-h"))
    {
        // Do stuff
        std::cout << "Doc" << std::endl;
        std::cout << "--input_model: set .xml path" << std::endl;
        std::cout << "--source     : set image dir" << std::endl;

        return 0;
    }
    std::string xml_path, images_path;
    const std::string &filename = input.getCmdOption("--input_model");
    if (!filename.empty())
    {
        // Do interesting things ...
        xml_path = filename;
    }
    else
    {
        xml_path = "../res/best.xml";
    }

    const std::string &dirname = input.getCmdOption("--source");
    if (!dirname.empty())
    {
        // Do interesting things ...
        if (*(dirname.end() - 1) == '*')
            images_path = dirname.substr(0, dirname.length() - 1);
        else
            images_path = dirname;
    }
    else
    {
        images_path = "../res";
    }

    std::cout << "input_model: " << xml_path << std::endl;
    std::cout << "source dir : " << images_path << std::endl;

    map<int, string> label_map;
    map<int, cv::Scalar> label_color_map;

    label_map[0] = "NoLid_NoBand_NoTape";
    label_map[1] = "NoLid_NoBand_Tape";
    label_map[2] = "NoLid_Band_Tape";
    label_map[3] = "Lid_NoBand";
    label_map[4] = "Lid_Band";

    // https://m.fontke.com/tool/rgb/
    label_color_map[0] = CV_RGB(64, 185, 255);
    label_color_map[1] = CV_RGB(255, 175, 26);
    label_color_map[2] = CV_RGB(223, 136, 110);
    label_color_map[3] = CV_RGB(226, 199, 67);
    label_color_map[4] = CV_RGB(188, 134, 55);

    Detector *detector = new Detector;
    // string    xml_path = "../res/best.xml";
    detector->init(xml_path, 0.5, 0.5);

    list<string> images_list = find_images(images_path);
    if (0 == images_list.size())
    {
        cout << "No image found!" << endl
             << "Exited Normally" << endl;
        return 0;
    }
    for (auto img_path_ptr = images_list.begin(); img_path_ptr != images_list.end(); ++img_path_ptr)
    {
        string::size_type iPos = (*img_path_ptr).find_last_of('/') + 1;
        string img_path = (*img_path_ptr).substr(0, iPos - 1);
        string filename = (*img_path_ptr).substr(iPos, (*img_path_ptr).length() - iPos);
        string filename_without_exten = filename.substr(0, filename.find_last_of('.'));
        string file_exten = filename.substr(filename.find_last_of('.'));

        if (string::npos != filename.find("result"))
            continue;

        // Mat src = imread("../res/test_img.png");
        Mat src = imread(*img_path_ptr);
        Mat osrc = src.clone();
        resize(osrc, osrc, Size(640, 640));
        vector<Detector::Object> detected_objects;

        int rows = src.rows;
        int cols = src.cols;
        float rows_ratio = src.rows / 640.0;
        float cols_ratio = src.cols / 640.0;

        auto start = chrono::high_resolution_clock::now();
        detector->process_frame(src, detected_objects);
        auto end = chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        cout << "------------------------------" << endl;
        cout << "Detecting file: " << filename << endl
             << "Use " << diff.count() << " s" << endl;

        if (0 == detected_objects.size())
        {
            cout << "Box not detected" << endl;
            continue;
        }

        resize(osrc, osrc, Size(cols, rows));
        for (int i = 0; i < detected_objects.size(); ++i)
        {
            int xmin = detected_objects[i].rect.x * cols_ratio;
            int ymin = detected_objects[i].rect.y * rows_ratio;
            int width = detected_objects[i].rect.width * cols_ratio;
            int height = detected_objects[i].rect.height * rows_ratio;
            //左上坐标 (x, y) 和矩形的长 (x), 宽 (y)
            Rect rect(xmin, ymin, width, height);
            cv::rectangle(osrc, rect, label_color_map[detected_objects[i].classId], 2, LINE_8, 0);

            print_label(osrc, &rect, label_map[detected_objects[i].classId], detected_objects[i].prob, label_color_map[detected_objects[i].classId]);
            cout << "classId | prob " << endl;
            cout << detected_objects[i].classId << "       : " << detected_objects[i].prob << endl;
            cout << "label name: " << label_map[detected_objects[i].classId] << endl;
        }

        imwrite((*img_path_ptr).substr(0, (*img_path_ptr).length() - file_exten.length()) + "_result" + file_exten, osrc);
        // imshow("result", osrc);
        // waitKey(0);
    }
    cout << "------------------------------" << endl;
}
