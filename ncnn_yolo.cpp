//
// Created by 绮名桑 on 2024/6/18.
//

#include "ncnn_yolo.hpp"
#include "GUI.hpp"


namespace user_CV {
    QImage cvMatToQImage(const cv::Mat& mat, bool clone, bool rb_swap)
    {
        const uchar *pSrc = (const uchar*)mat.data;
        // 8位无符号整型，通道数 = 1
        if(mat.type() == CV_8UC1)
        {
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
            if(clone) return image.copy();
            return image;
        }
            // 8位无符号整型，通道数 = 3
        else if(mat.type() == CV_8UC3)
        {
            // 创建与输入 Mat 具有相同尺寸的 QImage
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            if(clone)
            {
                if(rb_swap) return image.rgbSwapped();
                return image.copy();
            }
            else
            {
                if(rb_swap)
                {
                    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
                }
                return image;
            }

        }
        else if(mat.type() == CV_8UC4)
        {
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
            if(clone) return image.copy();
            return image;
        }
        else
        {
            return QImage();
        }
    }

    cv::Mat QImageTocvMat(const QImage &image, bool clone, bool rb_swap)
    {
        cv::Mat mat;
        switch(image.format())
        {
            case QImage::Format_ARGB32:
            case QImage::Format_RGB32:
            case QImage::Format_ARGB32_Premultiplied:
                mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void *)image.constBits(), image.bytesPerLine());
                if(clone)  mat = mat.clone();
                break;
            case QImage::Format_RGB888:
                mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void *)image.constBits(), image.bytesPerLine());
                if(clone)  mat = mat.clone();
                if(rb_swap) cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
                break;
            case QImage::Format_RGBA8888_Premultiplied: {
                mat = cv::Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
                if (clone) mat = mat.clone();
                // 预乘 alpha 通道情况下，通常需要额外处理
                cv::Mat rgbaMat = mat.clone();
                cv::cvtColor(mat, mat, cv::COLOR_RGBA2RGB); // 转换为 RGB 格式（去除 alpha 通道）
                break;
            }
            case QImage::Format_Indexed8:
            case QImage::Format_Grayscale8:
                mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void *)image.bits(), image.bytesPerLine());
                if(clone)  mat = mat.clone();
                break;
        }
        return mat;
    }

    QString formatToString(QImage::Format format) {
        switch (format) {
            case QImage::Format_Invalid:
                return "Invalid";
            case QImage::Format_Mono:
                return "Mono";
            case QImage::Format_MonoLSB:
                return "MonoLSB";
            case QImage::Format_Indexed8:
                return "Indexed8";
            case QImage::Format_RGB32:
                return "RGB32";
            case QImage::Format_ARGB32:
                return "ARGB32";
            case QImage::Format_ARGB32_Premultiplied:
                return "ARGB32_Premultiplied";
            case QImage::Format_RGB16:
                return "RGB16";
            case QImage::Format_ARGB8565_Premultiplied:
                return "ARGB8565_Premultiplied";
            case QImage::Format_RGB666:
                return "RGB666";
            case QImage::Format_ARGB6666_Premultiplied:
                return "ARGB6666_Premultiplied";
            case QImage::Format_RGB555:
                return "RGB555";
            case QImage::Format_ARGB8555_Premultiplied:
                return "ARGB8555_Premultiplied";
            case QImage::Format_RGB888:
                return "RGB888";
            case QImage::Format_RGB444:
                return "RGB444";
            case QImage::Format_ARGB4444_Premultiplied:
                return "ARGB4444_Premultiplied";
            case QImage::Format_RGBX8888:
                return "RGBX8888";
            case QImage::Format_RGBA8888:
                return "RGBA8888";
            case QImage::Format_RGBA8888_Premultiplied:
                return "RGBA8888_Premultiplied";
            case QImage::Format_Grayscale8:
                return "Grayscale8";
            case QImage::Format_Alpha8:
                return "Alpha8";
            case QImage::Format_Grayscale16:
                return "Grayscale16";
            default:
                return "Unknown Format";
        }
    }

    cv::Mat draw_seg(const QImage &rgb, const vector<Object> &objects) {
        cv::Mat image = user_CV::QImageTocvMat(rgb, true, false);
        for (size_t i = 0; i < objects.size(); i++) {
            const Object &obj = objects[i];
            for (int y = 0; y < image.rows; y++) {
                uchar* image_ptr = image.ptr(y);
                const float* mask_ptr = obj.mask.ptr<float>(y);
                for (int x = 0; x < image.cols; x++) {
                    if (mask_ptr[x] >= 0.5)
                    {
                        image_ptr[0] = cv::saturate_cast<uchar>(image_ptr[0] * 0.5 + colors[i][2] * 0.5);
                        image_ptr[1] = cv::saturate_cast<uchar>(image_ptr[1] * 0.5 + colors[i][1] * 0.5);
                        image_ptr[2] = cv::saturate_cast<uchar>(image_ptr[2] * 0.5 + colors[i][0] * 0.5);
                    }
                    image_ptr += 3;
                }
            }
        }
        return image;
    }
}

namespace Operator{
    static float fast_exp(float x)
    {
        union {
            uint32_t i;
            float f;
        } v{};
        v.i = (1 << 23) * (1.4426950409 * x + 126.93490512f);
        return v.f;
    }

    static float sigmoid(float x)
    {
        return 1.0f / (1.0f + fast_exp(-x));
    }

    static float intersection_area(const Object& a, const Object& b)
    {
        cv::Rect_<float> inter = a.rect & b.rect;
        return inter.area();
    }

    static void generate_grids_and_stride(const int target_w, const int target_h, std::vector<int>& strides, std::vector<GridAndStride>& grid_strides) {
        grid_strides.clear();

        // 预先计算所有grid_strides所需的总大小
        size_t total_size = 0;
        for (int stride : strides) {
            total_size += (target_w / stride) * (target_h / stride);
        }
        grid_strides.reserve(total_size);

        // 生成网格和步幅
        for (int stride : strides) {
            int num_grid_w = target_w / stride;
            int num_grid_h = target_h / stride;

            for (int g1 = 0; g1 < num_grid_h; g1++) {
                for (int g0 = 0; g0 < num_grid_w; g0++) {
                    grid_strides.emplace_back(GridAndStride{g0, g1, stride});
                }
            }
        }
    }

    static void generate_proposals(std::vector<GridAndStride> grid_strides, const ncnn::Mat& pred, float prob_threshold, std::vector<Object>& objects, int num_class, int modelType)
    {
        const int num_points = grid_strides.size();
        const int reg_max_1 = 16;

        for (int i = 0; i < num_points; i++)
        {
            const float* scores = pred.row(i) + 4 * reg_max_1;

            // 查找得分最高的标签
            int label = -1;
            float score = -FLT_MAX;
            for (int k = 0; k < num_class; k++)
            {
                float confidence = scores[k];
                if (confidence > score)
                {
                    label = k;
                    score = confidence;
                }
            }
            float box_prob = sigmoid(score);
            if (box_prob >= prob_threshold)
            {
                ncnn::Mat bbox_pred(reg_max_1, 4, (void*)pred.row(i));
                {
                    ncnn::Layer* softmax = ncnn::create_layer("Softmax");

                    ncnn::ParamDict pd;
                    pd.set(0, 1);
                    pd.set(1, 1);
                    softmax->load_param(pd);

                    ncnn::Option opt;
                    opt.num_threads = 1;
                    opt.use_packing_layout = false;

                    softmax->create_pipeline(opt);

                    softmax->forward_inplace(bbox_pred, opt);

                    softmax->destroy_pipeline(opt);

                    delete softmax;
                }

                float pred_ltrb[4];
                for (int k = 0; k < 4; k++)
                {
                    float dis = 0.f;
                    const float* dis_after_sm = bbox_pred.row(k);
                    for (int l = 0; l < reg_max_1; l++)
                    {
                        dis += l * dis_after_sm[l];
                    }

                    pred_ltrb[k] = dis * grid_strides[i].stride;
                }

                float pb_cx = (grid_strides[i].grid0 + 0.5f) * grid_strides[i].stride;
                float pb_cy = (grid_strides[i].grid1 + 0.5f) * grid_strides[i].stride;

                float x0 = pb_cx - pred_ltrb[0];
                float y0 = pb_cy - pred_ltrb[1];
                float x1 = pb_cx + pred_ltrb[2];
                float y1 = pb_cy + pred_ltrb[3];

                Object obj;
                obj.rect.x = x0;
                obj.rect.y = y0;
                obj.rect.width = x1 - x0;
                obj.rect.height = y1 - y0;
                obj.label = label;
                obj.prob = box_prob;

                if (modelType == 1) {
                    obj.mask_feat.resize(32);
                    std::copy(pred.row(i) + 64 + num_class, pred.row(i) + 64 + num_class + 32, obj.mask_feat.begin());
                }

                objects.push_back(obj);
            }
        }
    }

    static void qsort_descent_inplace(std::vector<Object>& faceobjects, int left, int right)
    {
        int i = left;
        int j = right;
        float p = faceobjects[(left + right) / 2].prob;

        while (i <= j)
        {
            while (faceobjects[i].prob > p)
                i++;

            while (faceobjects[j].prob < p)
                j--;

            if (i <= j)
            {
                // swap
                std::swap(faceobjects[i], faceobjects[j]);

                i++;
                j--;
            }
        }
        {
            {
                if (left < j) qsort_descent_inplace(faceobjects, left, j);
            }
            {
                if (i < right) qsort_descent_inplace(faceobjects, i, right);
            }
        }
    }

    static void qsort_descent_inplace(std::vector<Object>& faceobjects)
    {
        if (faceobjects.empty())
            return;

        qsort_descent_inplace(faceobjects, 0, faceobjects.size() - 1);
    }

    static void nms_sorted_bboxes(const std::vector<Object>& faceobjects, std::vector<int>& picked, float nms_threshold)
    {
        picked.clear();

        const int n = faceobjects.size();

        std::vector<float> areas(n);
        for (int i = 0; i < n; i++)
        {
            areas[i] = faceobjects[i].rect.width * faceobjects[i].rect.height;
        }

        for (int i = 0; i < n; i++)
        {
            const Object& a = faceobjects[i];

            int keep = 1;
            for (int j = 0; j < (int)picked.size(); j++)
            {
                const Object& b = faceobjects[picked[j]];

                // intersection over union
                float inter_area = intersection_area(a, b);
                float union_area = areas[i] + areas[picked[j]] - inter_area;
                // float IoU = inter_area / union_area
                if (inter_area / union_area > nms_threshold)
                    keep = 0;
            }

            if (keep)
                picked.push_back(i);
        }
    }

    static std::vector<ValueIndexPair> topk(const std::vector<float>& data, int k)
    {
        std::vector<ValueIndexPair> valueIndexPairs;

        for (int i = 0; i < data.size(); ++i) {
            valueIndexPairs.push_back({data[i], i});
        }

        if (k < data.size()) {
            std::partial_sort(valueIndexPairs.begin(), valueIndexPairs.begin() + k, valueIndexPairs.end());
            valueIndexPairs.resize(k);
        } else {
            std::sort(valueIndexPairs.begin(), valueIndexPairs.end());
        }

        return valueIndexPairs;  // 返回前k个最大值及其索引
    }

    static void slice(const ncnn::Mat& in, ncnn::Mat& out, int start, int end, int axis)
    {
        ncnn::Option opt;
        opt.num_threads = 1;
        opt.use_fp16_storage = false;
        opt.use_packing_layout = false;
        opt.use_vulkan_compute = true;

        ncnn::Layer* op = ncnn::create_layer("Crop");

        // set param
        ncnn::ParamDict pd;

        ncnn::Mat axes = ncnn::Mat(1);
        axes.fill(axis);
        ncnn::Mat ends = ncnn::Mat(1);
        ends.fill(end);
        ncnn::Mat starts = ncnn::Mat(1);
        starts.fill(start);
        pd.set(9, starts);// start
        pd.set(10, ends);// end
        pd.set(11, axes);//axes

        op->load_param(pd);

        op->create_pipeline(opt);

        // forward
        op->forward(in, out, opt);

        op->destroy_pipeline(opt);

        delete op;
    }
    static void interp(const ncnn::Mat& in, const float& scale, const int& out_w, const int& out_h, ncnn::Mat& out)
    {
        ncnn::Option opt;
        opt.num_threads = 1;
        opt.use_fp16_storage = false;
        opt.use_packing_layout = false;
        opt.use_vulkan_compute = true;

        ncnn::Layer* op = ncnn::create_layer("Interp");

        // set param
        ncnn::ParamDict pd;
        pd.set(0, 2);// resize_type
        pd.set(1, scale);// height_scale
        pd.set(2, scale);// width_scale
        pd.set(3, out_h);// height
        pd.set(4, out_w);// width

        op->load_param(pd);

        op->create_pipeline(opt);

        // forward
        op->forward(in, out, opt);

        op->destroy_pipeline(opt);

        delete op;
    }
    static void reshape(const ncnn::Mat& in, ncnn::Mat& out, int c, int h, int w, int d)
    {
        ncnn::Option opt;
        opt.num_threads = 1;
        opt.use_fp16_storage = false;
        opt.use_packing_layout = false;
        opt.use_vulkan_compute = true;

        ncnn::Layer* op = ncnn::create_layer("Reshape");

        // set param
        ncnn::ParamDict pd;

        pd.set(0, w);// start
        pd.set(1, h);// end
        if (d > 0)
            pd.set(11, d);//axes
        pd.set(2, c);//axes
        op->load_param(pd);

        op->create_pipeline(opt);

        // forward
        op->forward(in, out, opt);

        op->destroy_pipeline(opt);

        delete op;
    }
    static void sigmoid(ncnn::Mat& bottom)
    {
        ncnn::Option opt;
        opt.num_threads = 1;
        opt.use_fp16_storage = false;
        opt.use_packing_layout = false;
        opt.use_vulkan_compute = true;

        ncnn::Layer* op = ncnn::create_layer("Sigmoid");

        op->create_pipeline(opt);

        // forward

        op->forward_inplace(bottom, opt);
        op->destroy_pipeline(opt);

        delete op;
    }
    static void matmul(const std::vector<ncnn::Mat>& bottom_blobs, ncnn::Mat& top_blob)
    {
        ncnn::Option opt;
        opt.num_threads = 1;
        opt.use_fp16_storage = false;
        opt.use_packing_layout = false;
        opt.use_vulkan_compute = true;

        ncnn::Layer* op = ncnn::create_layer("MatMul");

        // set param
        ncnn::ParamDict pd;
        pd.set(0, 0);// axis

        op->load_param(pd);

        op->create_pipeline(opt);
        std::vector<ncnn::Mat> top_blobs(1);
        op->forward(bottom_blobs, top_blobs, opt);
        top_blob = top_blobs[0];

        op->destroy_pipeline(opt);

        delete op;
    }

    static void decode_mask(const ncnn::Mat& mask_feat, const int& img_w, const int& img_h, const ncnn::Mat& mask_proto, const ncnn::Mat& in_pad, const int& wpad, const int& hpad, ncnn::Mat& mask_pred_result)
    {
        ncnn::Mat masks;
        matmul(std::vector<ncnn::Mat>{mask_feat, mask_proto}, masks);
        sigmoid(masks);
        reshape(masks, masks, masks.h, in_pad.h / 4, in_pad.w / 4, 0);
        slice(masks, mask_pred_result, (wpad / 2) / 4, (in_pad.w - wpad / 2) / 4, 2);
        slice(mask_pred_result, mask_pred_result, (hpad / 2) / 4, (in_pad.h - hpad / 2) / 4, 1);
        interp(mask_pred_result, 4.0, img_w, img_h, mask_pred_result);

    }
};

YOLO::YOLO() {
    blob_pool_allocator.set_size_compare_ratio(0.f);
    workspace_pool_allocator.set_size_compare_ratio(0.f);
}

int YOLO::load(const char *modeltype) {
    net.clear();
    blob_pool_allocator.clear();
    workspace_pool_allocator.clear();
    class_names.clear();
    ncnn::set_cpu_powersave(2);
    net.opt.num_threads = 1;
    net.opt = ncnn::Option();  // 继承net类

#if NCNN_VULKAN
    net.opt.use_vulkan_compute = true;
#endif
    net.opt.blob_allocator = &blob_pool_allocator;
    net.opt.workspace_allocator = &workspace_pool_allocator;
    net.opt.use_fp16_packed = false;
    net.opt.use_fp16_storage = false;
    net.opt.use_fp16_arithmetic = false;

    char parampath[256];
    char modelpath[256];
    char classpath[256];

    sprintf(parampath, "%s.param", modeltype);
    sprintf(modelpath, "%s.bin", modeltype);
    sprintf(classpath, "%s.txt", modeltype);

    int ret1 = net.load_param(parampath);
    int ret2 = net.load_model(modelpath);

    if (ret1 == 0 && ret2 == 0) {
        std::cout << "模型加载完毕" << std::endl;
    }

    std::ifstream file(classpath); // 打开文件
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            class_names.push_back(line); // 将每行存储在 std::string 类型的 vector 中
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
        return 1;
    }
    return 0;
}

int YOLO::detect(QImage& rgb, std::vector<Object>& objects) {
    int width = rgb.width();
    int height = rgb.height();

    // 将输入神经网的图片尺寸调整为32的倍数
    int w = width;
    int h = height;
    float scale = 1.f;
    if (w > h)
    {
        scale = (float)target_size / w;
        w = target_size;
        h = h * scale;
    }
    else
    {
        scale = (float)target_size / h;
        h = target_size;
        w = w * scale;
    }

    // 将 QImage 转换为 ncnn::Mat
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(rgb.convertToFormat(QImage::Format_RGB888).bits(),
                                                 ncnn::Mat::PIXEL_RGB,
                                                 width, height, w, h);

    int wpad = (w + 31) / 32 * 32 - w;
    int hpad = (h + 31) / 32 * 32 - h;
    ncnn::Mat in_pad;
    ncnn::copy_make_border(in, in_pad, hpad / 2, hpad - hpad / 2, wpad / 2, wpad - wpad / 2, ncnn::BORDER_CONSTANT, 0.f);

    in_pad.substract_mean_normalize(0, norm_vals);

    ncnn::Extractor ex = net.create_extractor();

    ex.input("images", in_pad);

    std::vector<Object> proposals;

    // 输出数据到Mat类型上
    ncnn::Mat out;
    ex.extract("output0", out);

    // 目标检测中的 Anchor Box（锚框）生成过程，通常用于生成预测的候选框，
    // 生成不同步长下的网格坐标和相应的步长信息。
    std::vector<int> strides = {8, 16, 32};
    std::vector<GridAndStride> grid_strides;
    Operator::generate_grids_and_stride(in_pad.w, in_pad.h, strides, grid_strides);
    Operator::generate_proposals(grid_strides, out, 0.84f, proposals, class_names.size(), 0);

    // 按得分从高到低对所有提案进行排序
    Operator::qsort_descent_inplace(proposals);

    // 采用NMS非极大值抑制算法应用到图像上
    std::vector<int> picked;
    Operator::nms_sorted_bboxes(proposals, picked, 0.84f);

    objects.resize(picked.size());
    for (int i = 0; i < picked.size(); i++)
    {
        objects[i] = proposals[picked[i]];

        // 将偏移调整为原始未填充
        float x0 = (objects[i].rect.x - (wpad / 2)) / scale;
        float y0 = (objects[i].rect.y - (hpad / 2)) / scale;
        float x1 = (objects[i].rect.x + objects[i].rect.width - (wpad / 2)) / scale;
        float y1 = (objects[i].rect.y + objects[i].rect.height - (hpad / 2)) / scale;

        // 修剪图像回复到原来的尺寸
        x0 = std::max(std::min(x0, (float)(width - 1)), 0.f);
        y0 = std::max(std::min(y0, (float)(height - 1)), 0.f);
        x1 = std::max(std::min(x1, (float)(width - 1)), 0.f);
        y1 = std::max(std::min(y1, (float)(height - 1)), 0.f);

        objects[i].rect.x = x0;
        objects[i].rect.y = y0;
        objects[i].rect.width = x1 - x0;
        objects[i].rect.height = y1 - y0;
    }

    // 按区域对对象排序
    struct
    {
        bool operator()(const Object& a, const Object& b) const
        {
            return a.rect.area() > b.rect.area();
        }
    } objects_area_greater;
    std::sort(objects.begin(), objects.end(), objects_area_greater);

    return 0;
}

void YOLO::result(std::vector<Object>& objects) {
    for (size_t i = 0; i < objects.size(); i++)
    {
        objects[i].class_name = QString::fromStdString(class_names[objects[i].label]);
    }
}

int YOLO::draw(cv::Mat &rgb, std::vector<Object>& objects) {
    cv::cvtColor(rgb,rgb,cv::COLOR_BGRA2BGR);
    static const unsigned char colors[19][3] = {
            { 54,  67, 244},
            { 99,  30, 233},
            {176,  39, 156},
            {183,  58, 103},
            {181,  81,  63},
            {243, 150,  33},
            {244, 169,   3},
            {212, 188,   0},
            {136, 150,   0},
            { 80, 175,  76},
            { 74, 195, 139},
            { 57, 220, 205},
            { 59, 235, 255},
            {  7, 193, 255},
            {  0, 152, 255},
            { 34,  87, 255},
            { 72,  85, 121},
            {158, 158, 158},
            {139, 125,  96}
    };
    int color_index = 0;
    for (size_t i = 0; i < objects.size(); i++)
    {
        const Object& obj = objects[i];

        const unsigned char* color = colors[color_index % 19];
        color_index++;

        cv::Scalar cc(color[0], color[1], color[2]);

        cv::rectangle(rgb, obj.rect, cc, 2);

        char text[256];

        sprintf(text, "%s %.1f%%", class_names[obj.label].c_str(), obj.prob * 100);

        int baseLine = 0;
        cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

        int x = obj.rect.x;
        int y = obj.rect.y - label_size.height - baseLine;
        if (y < 0)
            y = 0;
        if (x + label_size.width > rgb.cols)
            x = rgb.cols - label_size.width;

        cv::rectangle(rgb, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)), cc, -1);

        cv::Scalar textcc = (color[0] + color[1] + color[2] >= 381) ? cv::Scalar(0, 0, 0) : cv::Scalar(255, 255, 255);

        cv::putText(rgb, text, cv::Point(x, y + label_size.height), cv::FONT_HERSHEY_SIMPLEX, 0.5, textcc, 1);

    }
    cv::Mat blackBackground(rgb.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    for (size_t i = 0; i < objects.size(); i++) {
        const Object &obj = objects[i];
        int x0 = obj.rect.x;
        int y0 = obj.rect.y;
        int x1 = obj.rect.x + obj.rect.width;
        int y1 = obj.rect.y + obj.rect.height;
        cv::Point p1(x0, y0);          // 点p1
        cv::Point p2(x1, y1);          // 点p1
        cv::circle(rgb, p1, 3, cv::Scalar(0, 255, 120), -1);//画点，其实就是实心圆
        cv::circle(rgb, p2, 3, cv::Scalar(0, 255, 120), -1);//画点，其实就是实心圆
    }
    return 0;
}

int YOLO::detect_seg(QImage &rgb, vector<Object> &objects) {
    int width = rgb.width();
    int height = rgb.height();

    // 将输入神经网的图片尺寸调整为32的倍数
    int w = width;
    int h = height;
    float scale = 1.f;
    if (w > h)
    {
        scale = (float)target_size / w;
        w = target_size;
        h = h * scale;
    }
    else
    {
        scale = (float)target_size / h;
        h = target_size;
        w = w * scale;
    }

    // 将 QImage 转换为 ncnn::Mat
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(rgb.convertToFormat(QImage::Format_RGB888).bits(),
                                                 ncnn::Mat::PIXEL_RGB,
                                                 width, height, w, h);
    int wpad = (w + 31) / 32 * 32 - w;
    int hpad = (h + 31) / 32 * 32 - h;
    ncnn::Mat in_pad;
    ncnn::copy_make_border(in, in_pad, hpad / 2, hpad - hpad / 2, wpad / 2, wpad - wpad / 2, ncnn::BORDER_CONSTANT, 0.f);
    in_pad.substract_mean_normalize(0, norm_vals);

    ncnn::Extractor ex = net.create_extractor();
    ex.input("images", in_pad);
    ncnn::Mat out;
    ex.extract("output", out);
    ncnn::Mat mask_proto;
    ex.extract("seg", mask_proto);

    std::vector<int> strides = { 8, 16, 32 };
    std::vector<GridAndStride> grid_strides;
    Operator::generate_grids_and_stride(in_pad.w, in_pad.h, strides, grid_strides);

    std::vector<Object> proposals;
    std::vector<Object> objects8;
    Operator::generate_proposals(grid_strides, out, 0.4f, objects8, class_names.size(), 1);

    proposals.insert(proposals.end(), objects8.begin(), objects8.end());

    Operator::qsort_descent_inplace(proposals);

    std::vector<int> picked;
    Operator::nms_sorted_bboxes(proposals, picked, 0.5f);

    int count = picked.size();

    ncnn::Mat mask_feat = ncnn::Mat(32, count, sizeof(float));
    for (int i = 0; i < count; i++) {
        float* mask_feat_ptr = mask_feat.row(i);
        std::memcpy(mask_feat_ptr, proposals[picked[i]].mask_feat.data(), sizeof(float) * proposals[picked[i]].mask_feat.size());
    }

    ncnn::Mat mask_pred_result;
    Operator::decode_mask(mask_feat, width, height, mask_proto, in_pad, wpad, hpad, mask_pred_result);

    objects.resize(count);
    for (int i = 0; i < count; i++)
    {
        objects[i] = proposals[picked[i]];

        // adjust offset to original unpadded
        float x0 = (objects[i].rect.x - (wpad / 2)) / scale;
        float y0 = (objects[i].rect.y - (hpad / 2)) / scale;
        float x1 = (objects[i].rect.x + objects[i].rect.width - (wpad / 2)) / scale;
        float y1 = (objects[i].rect.y + objects[i].rect.height - (hpad / 2)) / scale;

        // clip
        x0 = std::max(std::min(x0, (float)(width - 1)), 0.f);
        y0 = std::max(std::min(y0, (float)(height - 1)), 0.f);
        x1 = std::max(std::min(x1, (float)(width - 1)), 0.f);
        y1 = std::max(std::min(y1, (float)(height - 1)), 0.f);

        objects[i].rect.x = x0;
        objects[i].rect.y = y0;
        objects[i].rect.width = x1 - x0;
        objects[i].rect.height = y1 - y0;

        objects[i].mask = cv::Mat::zeros(height, width, CV_32FC1);
        cv::Mat mask = cv::Mat(height, width, CV_32FC1, (float*)mask_pred_result.channel(i));
        mask(objects[i].rect).copyTo(objects[i].mask(objects[i].rect));
    }

    return 0;
}
