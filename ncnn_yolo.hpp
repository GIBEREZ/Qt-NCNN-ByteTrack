//
// Created by 绮名桑 on 2024/6/18.
//

#ifndef WIFI_QT_NCNN_YOLO_HPP
#define WIFI_QT_NCNN_YOLO_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <mat.h>
#include <vector>
#include <layer.h>
#include <net.h>
#include <cpu.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <QImage>

struct Object
{
    // 共用部分
    cv::Rect_<float> rect;
    int label;
    int track_id;
    float prob;
    QString class_name;
    // seg部分
    cv::Mat mask;
    std::vector<float> mask_feat;
};

struct GridAndStride
{
    int grid0;
    int grid1;
    int stride;
};

// topk子算法
struct ValueIndexPair {
    float value;
    int index;
    bool operator<(const ValueIndexPair& other) const {
        return value > other.value;
    }
};

namespace user_CV {
    /**
     * @brief 将 OpenCV 的 cv::Mat 类型图像转换为 QImage 类型
     * @param mat 待转换的图像，支持 CV_8UC1、CV_8UC3、CV_8UC4 三种OpenCV 的数据类型
     * @param clone true 表示与 Mat 不共享内存，更改生成的 mat 不会影响原始图像，false 则会与 mat 共享内存
     * @param rb_swap 只针对 CV_8UC3 格式，如果 true 则会调换 R 与 B RGB->BGR，如果共享内存的话原始图像也会发生变化
     * @return 转换后的 QImage 图像
    */
    QImage cvMatToQImage(const cv::Mat& mat, bool clone = true, bool rb_swap = true);
    /**
     * @brief 将 QImage 的类型图像转换为 cv::Mat 类型
     * @param image 待转换的图像，支持 Format_Indexed8/Format_Grayscale、24 位彩色、32 位彩色格式，
     * @param clone true 表示与 QImage 不共享内存，更改生成的 mat 不会影响原始图像，false 则会与 QImage 共享内存
     * @param rg_swap 只针对 RGB888 格式，如果 true 则会调换 R 与 B RGB->BGR，如果共享内存的话原始图像也会发生变化
     * @return 转换后的 cv::Mat 图像
    */
    cv::Mat QImageTocvMat(const QImage &image, bool clone = false, bool rb_swap = true);
    QString formatToString(QImage::Format format);
    cv::Mat draw_seg(const QImage& rgb, const std::vector<Object>& objects);
}

namespace Operator {
    // 快速近似计算指数值 Sigmoid激活函数常用
    static float fast_exp(float x);
    // Sigmoid激活函数
    static float sigmoid(float x);
    // 计算两个对象的矩形交集的面积，用于检测和计算矩形重叠部分
    static float intersection_area(const Object& a, const Object& b);
    // 根据目标高度宽度，循环生成网格和步幅
    static void generate_grids_and_stride(const int target_w, const int target_h, std::vector<int>& strides, std::vector<GridAndStride>& grid_strides);
    // 根据预测结果生成候选对象
    static void generate_proposals(std::vector<GridAndStride> grid_strides, const ncnn::Mat& pred, float prob_threshold, std::vector<Object>& objects, int class_num, int modelType);
    // 快速排序算法
    static void qsort_descent_inplace(std::vector<Object>& faceobjects, int left, int right);
    // 快速排序算法递归
    static void qsort_descent_inplace(std::vector<Object>& faceobjects);
    // NMS非极大值抑制算法
    static void nms_sorted_bboxes(const std::vector<Object>& faceobjects, std::vector<int>& picked, float nms_threshold);
    // topk后处理算法
    static std::vector<ValueIndexPair> topk(const std::vector<float>& data, int k);
    // ncnn框架切片算法
    static void slice(const ncnn::Mat& in, ncnn::Mat& out, int start, int end, int axis);
    // ncnn框架插值算法
    static void interp(const ncnn::Mat& in, const float& scale, const int& out_w, const int& out_h, ncnn::Mat& out);
    // ncnn框架重塑算法
    static void reshape(const ncnn::Mat& in, ncnn::Mat& out, int c, int h, int w, int d);
    // ncnn框架激活函数
    static void sigmoid(ncnn::Mat& bottom);
    // ncnn框架多矩阵乘法
    static void matmul(const std::vector<ncnn::Mat>& bottom_blobs, ncnn::Mat& top_blob);
    // 神经网络后处理中生成物体掩码（mask）的算法
    static void decode_mask(const ncnn::Mat& mask_feat, const int& img_w, const int& img_h, const ncnn::Mat& mask_proto, const ncnn::Mat& in_pad, const int& wpad, const int& hpad, ncnn::Mat& mask_pred_result);
};

class YOLO {
public:
    YOLO();
    int load(const char* modeltype);
    int detect(QImage& rgb, std::vector<Object>& objects);
    void result(std::vector<Object>& objects);
    int draw(cv::Mat& rgb, std::vector<Object>& objects);

    int detect_seg(QImage& rgb, std::vector<Object>& objects);
private:
    ncnn::Net net;
    int target_size = 640;
    float norm_vals[3] = {1 / 255.f, 1 / 255.f, 1 / 255.f};
    ncnn::UnlockedPoolAllocator blob_pool_allocator;    // 内存分配类 无锁 用于分配 blob 对象的内存
    ncnn::PoolAllocator workspace_pool_allocator;       // 内存池分配器，用于分配 workspace 对象的内存
    std::vector<std::string> class_names;
};

#endif //WIFI_QT_NCNN_YOLO_HPP
