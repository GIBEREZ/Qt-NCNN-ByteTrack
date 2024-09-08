//
// Created by 绮名桑 on 2024/6/15.
//

#ifndef WIFI_QT_GUI_HPP
#define WIFI_QT_GUI_HPP

#include <QMainWindow>
#include <QtMultimedia>
#include <vector>
#include <iostream>
#include <thread>
#include <filesystem>
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include <QPlainTextEdit>
#include <utility>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include "TcpSocket.hpp"
#include "ui.hpp"
#include "ncnn_yolo.hpp"
#include "TcpSocket.hpp"
#include "ByteTrack/BYTETracker.h"

class TcpUI;
class GUI;

// FolderManager 类负责处理文件夹相关操作
class FolderManager {
public:
    // 构造函数，接收一个文件夹路径作为参数
    explicit FolderManager(std::filesystem::path  folderPath);
    // 检查文件夹是否存在
    bool exists() const;
    std::filesystem::path path;
private:
};

// Model_List 类继承自 FolderManager，用于处理模型文件的列表搜索
class Model_List : public FolderManager {
public:
    // 构造函数，接收一个文件夹路径作为参数
    explicit Model_List(std::filesystem::path folderPath);
    // 获取匹配的 .bin 和 .param 文件对的前缀
    std::vector<std::string> getBinAndParamPairs();
private:
    // 获取具有指定扩展名的文件前缀
    std::unordered_set<std::string> getFilePrefixesWithExtension(const std::string& extension);
};

// LogWidget类 日志类，继承QPlainTextEdit对象，派生实现其他功能
class LogWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit LogWidget(QPlainTextEdit *qPlainTextEdit);
    void appendLog(const QString &message);
private:
    QPlainTextEdit *qPlainTextEdit;
};

namespace UI {
    class DrawQView : public QGraphicsView {
        Q_OBJECT
    public:
        explicit DrawQView();
        // 重写监听事件禁用鼠标滚动处理
        void wheelEvent(QWheelEvent *event) override;
        void setDrawQViemRect();
        void onUpdateAABB(const std::vector<STrack>& output_stracks);
        // 目标检测
        void draw_AABB(const std::vector<STrack>& output_stracks);
        // 目标分割
        void draw_seg();
        // 绘制内容清空
        void draw_clear();
        // 缩放因子
        float scaleX;
        float scaleY;
    protected:
        // 场景变量
        QGraphicsScene scene;
    };

    class YOLOThread : public QThread {
        Q_OBJECT
    public:
        bool state = false;
    public:
        explicit YOLOThread(GUI *gui, QVideoSink *videoSink, QObject *parent);
        void updateByteTrack(BYTETracker &tracker, std::vector<STrack> &output_stracks);
        void run() override;
        void pause();
        void resume();
    signals:
        void updateAABB(const std::vector<STrack>& output_stracks);
    private:
        GUI *gui;
        QVideoSink *videoSink;
        DrawQView *drawQView;
        QMutex mutex;
        QWaitCondition waitCondition;
        bool paused = false;
    };

    class VideoWidget : public QWidget {
        Q_OBJECT
    public:
        VideoWidget(QWidget *parent, GUI *gui);
        void setVideoFrame(const QImage &frame);
        void setVideoUrl(const QUrl qUrl);
    public slots:
        void processFrame(const QVideoFrame &frame);
        void play();
        void pause();
        void clear();
    protected:
        void paintEvent(QPaintEvent *event) override;
    private:
        GUI *gui;
        QImage m_frame;
        QMediaPlayer *player;
        QVideoSink *videoSink;
        QString VideoTimer;
        YOLOThread *yoloThread;
    };
}

class GUI : public QMainWindow{
    Q_OBJECT
public:
    QMainWindow *ui;
    Ui_MainWindow *uiMainWindow;
    UI::VideoWidget *pVideoWidget;
    bool Model_flag = false;
    TcpUI* tcpUi;
    YOLO *yolo;
    LogWidget *logWidget;
    explicit GUI();
    void UI_init();
private:
};

#endif //WIFI_QT_GUI_HPP
