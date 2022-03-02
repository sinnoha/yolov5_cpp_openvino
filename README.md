# yolov5_cpp_openvino
yolov5_openvino inferenced with cpp

# Usage
```
(base) [sinnoha@konomi bin]$ ./detect_box -h
Doc
--input_model: set .xml path
--source     : set image dir

(base) [sinnoha@konomi bin]$ ./detect_box
input_model: ../res/best.xml
source dir : ../res
------------------------------
Detecting file: test_img.png
Use 0.39212 s
classId | prob
4       : 0.974141
label name: Lid_Band
------------------------------
Detecting file: bus.jpg
Use 0.323746 s
Box not detected
------------------------------
```

# Reference
```
https://github.com/yann-qu/yolov5_cpp_openvino
https://github.com/fb029ed/yolov5_cpp_openvino
```
