//
// Created by 绮名桑 on 2024/6/15.
//

#include "GUI.hpp"

GUI::GUI() {
    uiMainWindow = new Ui_MainWindow();
    this->ui = new UI::MainWindow();
    uiMainWindow->setupUi(ui);

    yolo = new YOLO();

    UI_init();

    pVideoWidget = new UI::VideoWidget(uiMainWindow->groupBox, this);

    // 应用QSS样式表
    QFile file("styles.qss");
    file.open(QIODevice::ReadOnly);
    QString styleSheet = file.readAll();
    this->ui->setStyleSheet(styleSheet);
    file.close();

    // "https://bkrc.oss-cn-beijing.aliyuncs.com/videos/b4ee9ab9715217b2d3bf0479765233f8.mp4"
    // "rtsp://admin:888888@192.168.40.100:10554/tcp/av0_0"
    connect(uiMainWindow->GetVideo_Button, &QPushButton::clicked, [this]() {
        QString urlString = uiMainWindow->Url_Edit->text();
        QUrl url = QUrl(urlString);
        if (!url.isValid()) {
            std::cout << "无效URL:" << url.toString().toStdString() << std::endl;
            return;
        }
        std::cout << "有效URL" << std::endl;

        pVideoWidget->setVideoUrl(url);
    });

    connect(uiMainWindow->SelectModel_Button, &QPushButton::clicked, [this]() {
        this->Model_flag = false;
        QString modelPath = "Model/" + uiMainWindow->comboBox_2->currentText();
        std::thread loadThread([this, modelPath] {
            yolo->load(modelPath.toLatin1().data());
            std::cout << "加载" << modelPath.toLatin1().data() << "模型已成功" << std::endl;
        });
        this->Model_flag = true;
        loadThread.detach();
    });

    connect(uiMainWindow->connect_Button, &QPushButton::clicked, [this]() {
        QString host = uiMainWindow->Host_Edit->text();
        quint16 port = uiMainWindow->Port_Edit->text().toUShort();
        // 主车IP地址192.168.40.254 端口号60000
        if (tcpUi != nullptr) {
            delete tcpUi; // 删除旧的实例
            tcpUi = nullptr;
        }
        tcpUi = new TcpUI(host, port, this);
        tcpUi->sendData("Hello, I am the Qt upper computer");
    });

    connect(uiMainWindow->Main_Button, &QPushButton::clicked, [this]() {
        uiMainWindow->stackedWidget->setCurrentIndex(0);
    });

    connect(uiMainWindow->Log_Button, &QPushButton::clicked, [this]() {
        uiMainWindow->stackedWidget->setCurrentIndex(1);
    });

    connect(uiMainWindow->min_Button, &QPushButton::clicked, [this](){
        this->ui->showMinimized();
    });

    connect(uiMainWindow->max_Button, &QPushButton::clicked, [this](){
        // 判断当前窗口是否已经最大化
        if (this->ui->isMaximized()) {
            this->ui->showNormal();
            this->uiMainWindow->gridLayout->setContentsMargins(18, 18, 18, 18);
        } else {
            this->ui->showMaximized();
            this->uiMainWindow->gridLayout->setContentsMargins(0, 0, 0, 0);
        }
    });

    connect(uiMainWindow->quit_Button, &QPushButton::clicked, [](){
        QApplication::quit();
    });
}

void GUI::UI_init() {
    // 初始化模型选择列表
    Model_List modelList("Model");
    std::vector<std::string> matchedPrefixes = modelList.getBinAndParamPairs();
    if (!matchedPrefixes.empty()) {
        std::cout << "匹配的.bin和.param文件列表:" << std::endl;
        for (const auto& prefix : matchedPrefixes) {
            std::cout << prefix << std::endl;
            uiMainWindow->comboBox_2->addItem(QString::fromStdString(prefix));
        }
    } else {
        std::cout << "未找到匹配的.bin和.param文件列表." << std::endl;
    }

    // 设置图标
    uiMainWindow->Main_Button->setIcon(QPixmap("Image/icon/首页.png"));
    uiMainWindow->Log_Button->setIcon(QPixmap("Image/icon/日历.png"));
    uiMainWindow->min_Button->setIcon(QPixmap("Image/icon/最小化.png"));
    uiMainWindow->max_Button->setIcon(QPixmap("Image/icon/最大化.png"));
    uiMainWindow->quit_Button->setIcon(QPixmap("Image/icon/关闭.png"));
    uiMainWindow->Regress_Button->setIcon(QPixmap("Image/icon/后退.png"));
    uiMainWindow->VideoState_Button->setIcon(QPixmap("Image/icon/暂停.png"));
    uiMainWindow->Forward_Button->setIcon(QPixmap("Image/icon/快进.png"));
    uiMainWindow->VideoClose_Button->setIcon(QPixmap("Image/icon/终止.png"));

    // 日志输出组件初始化
    logWidget = new LogWidget(uiMainWindow->Log_PlainTextEdit);
}

FolderManager::FolderManager(std::filesystem::path  folderPath) : path(std::move(folderPath)) {
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
        std::cout << "已创建文件夹: " << path << std::endl;
    } else {
        std::cout << "文件夹已存在: " << path << std::endl;
    }
}

bool FolderManager::exists() const {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

Model_List::Model_List(std::filesystem::path folderPath) : FolderManager(std::move(folderPath)) {}

std::vector<std::string> Model_List::getBinAndParamPairs() {
    // 获取所有 .bin 文件的前缀
    std::unordered_set<std::string> binPrefixes = getFilePrefixesWithExtension(".bin");
    // 获取所有 .param 文件的前缀
    std::unordered_set<std::string> paramPrefixes = getFilePrefixesWithExtension(".param");
    std::vector<std::string> matchedPrefixes;
    // 遍历 .bin 文件的前缀，检查是否存在对应的 .param 文件
    for (const auto& prefix : binPrefixes) {
        if (paramPrefixes.find(prefix) != paramPrefixes.end()) {
            // 如果找到匹配的前缀，将其添加到结果中
            matchedPrefixes.push_back(prefix);
        }
    }
    return matchedPrefixes;
}

std::unordered_set<std::string> Model_List::getFilePrefixesWithExtension(const std::string& extension) {
    std::unordered_set<std::string> prefixes;
    // 遍历目录中的所有文件
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        // 检查文件的扩展名是否匹配
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            // 将文件的前缀（不包含扩展名）插入到集合中
            prefixes.insert(entry.path().stem().string());
        }
    }
    return prefixes;
}

TcpUI::TcpUI(const QString &host, quint16 port, GUI *gui, QObject *parent) : TcpClient(host, port, parent), gui(gui){
    // 连接信号和槽
    connect(socket, &QTcpSocket::connected, this, &TcpUI::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpUI::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpUI::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this,
            &TcpUI::onErrorOccurred);
    try {
        // 连接到指定主机和端口
        socket->connectToHost(host, port);
        // 检查连接状态
        if (!socket->waitForConnected(5000)) { // 等待最多 5 秒
            std::cout << "连接异常:" << socket->errorString().toStdString() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cout << "异常：" << e.what() << std::endl;
    }
    std::cout << "连接成功" << std::endl;
}

void TcpUI::onConnected() {
    std::cout << "Connected to: " << host.toStdString() << ", port: " << port << std::endl;
    gui->logWidget->appendLog(QString("已连接到 %1:%2 设备").arg(host).arg(QString::number(port)));
    gui->uiMainWindow->NetworkStatusLabel->setText("已连接");
    gui->uiMainWindow->NetworkStatusLabel->setStyleSheet("QLabel { background-color: green; color: white; border-radius: 10px; font-weight: bold; padding: 10px; }");
}

void TcpUI::onDisconnected() {
    std::cout << "Disconnected from: " << host.toStdString() << std::endl;
    gui->logWidget->appendLog(QString("已断开和 %1:%2 设备的连接").arg(host).arg(QString::number(port)));
    gui->uiMainWindow->NetworkStatusLabel->setText("未连接");
    gui->uiMainWindow->NetworkStatusLabel->setStyleSheet("QLabel { background-color: red; color: white; border-radius: 10px; font-weight: bold; padding: 10px; }");
}

void TcpUI::onReadyRead() {
    QByteArray data = socket->readAll();
    std::cout << "Received: " << data.toStdString() << std::endl;
    gui->logWidget->appendLog(QString("收到 " + data));
}

void TcpUI::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    std::cerr << "Error: " << socket->errorString().toStdString() << std::endl;
    gui->logWidget->appendLog(QString("错误:") + QString::fromStdString(socket->errorString().toStdString()));
}

LogWidget::LogWidget(QPlainTextEdit *PlainTextEdit) : qPlainTextEdit(PlainTextEdit){
    qPlainTextEdit->setReadOnly(true);
}

void LogWidget::appendLog(const QString &message) {
    // 获取当前时间作为日志前缀
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    // 将日志消息添加到 QPlainTextEdit
    qPlainTextEdit->appendPlainText(timestamp + " - " + message);
}

namespace UI {
    MainWindow::MainWindow() {
        // 去掉标题栏 去掉窗口边框
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
        // 设置窗口透明化
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setAttribute(Qt::WA_StyledBackground, true);

        // 创建阴影效果对象
        QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setBlurRadius(20);          // 阴影模糊半径
        shadowEffect->setOffset(10, 10);          // 阴影的偏移量
        shadowEffect->setColor(Qt::black);        // 阴影颜色
        // 应用阴影效果
        this->setGraphicsEffect(shadowEffect);
    }

    void MainWindow::paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);
        QPainter painter(this);
        // 反锯齿
        painter.setRenderHint(QPainter::Antialiasing);

        // 获取坐标
        QRect rect = this->rect();

        // 圆角和阴影参数
        int offset = 18;        // 内部距
        int cornerRadius = 10;  // 圆角半径

        if (this->isMaximized()) {
            // 绘制圆角矩形
            painter.setBrush(QBrush(QColor(255, 255, 255))); // 圆角矩形的填充颜色
            QRect adjustedRect(rect);
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(adjustedRect, 0, 0);
        }
        else {
            // 绘制圆角矩形
            painter.setBrush(QBrush(QColor(255, 255, 255))); // 圆角矩形的填充颜色
            QRect adjustedRect(rect.left() + offset, rect.top() + offset,
                               rect.width() - (offset * 2), rect.height() - (offset * 2));
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(adjustedRect, cornerRadius, cornerRadius);
        }
    }

    void MainWindow::mousePressEvent(QMouseEvent *event) {
        QWidget::mousePressEvent(event);
        this->setFocus();
        if (Qt::LeftButton == event->button() && 0 == (Qt::WindowMaximized & this->windowState())) {
            this->mousePressPosition = event->globalPos();
            event->ignore();
        }
        // 标记鼠标为按下状态
        this->isMousePressed = true;
    }

    void MainWindow::mouseMoveEvent(QMouseEvent *event) {
        QWidget::mouseMoveEvent(event);
        // 如果当前是最大化，则不允许移动
        if (this->isMaximized())
            return;
        // 是否左击
        if ((event->buttons() & Qt::LeftButton) && this->isMousePressed) {
            // 当前鼠标全局位置
            QPoint currentMousePos = event->globalPos();
            // 计算鼠标移动的相对位移
            QPoint delta = currentMousePos - this->mousePressPosition;
            // 移动窗口到新的位置
            move(this->pos() + delta);
            // 更新鼠标按下的位置，以便下次计算移动
            this->mousePressPosition = currentMousePos;
        }
    }

    void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
        QWidget::mouseReleaseEvent(event);
        // 恢复鼠标指针状态
        QApplication::restoreOverrideCursor();
        event->ignore();
        this->isMousePressed = false;
    }


    DrawQView::DrawQView() {
        // 初始化 QGraphicsView
        this->setScene(&scene);
        // 设置 QGraphicsView 的背景透明
        this->setStyleSheet("background: transparent");
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->viewport()->setStyleSheet("background: transparent");
        // 开启抗锯齿
        this->setRenderHint(QPainter::Antialiasing);
        // 关闭平滑像素变换
        this->setRenderHint(QPainter::SmoothPixmapTransform, false);
        // 禁用滚动条
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        // 禁用场景的滚动
        setAlignment(Qt::AlignLeft | Qt::AlignTop);
        // 禁用视图变换
        this->setTransform(QTransform());
    }

    void DrawQView::wheelEvent(QWheelEvent *event) {
        QGraphicsView::wheelEvent(event);
        // 禁用滚轮事件
        event->ignore();
    }

    void DrawQView::resizeEvent(QResizeEvent *event) {
        QGraphicsView::resizeEvent(event);
        this->setDrawQViemRect();
        emit viewChanged();
    }

    void DrawQView::setDrawQViemRect() {
        scene.setSceneRect(0, 0, this->width(), this->height());
    }

    void DrawQView::onUpdateAABB(const std::vector<STrack>& output_stracks) {
        draw_AABB(output_stracks);
    }

    void DrawQView::draw_AABB(const std::vector<STrack>& output_stracks) {
        // 绘制之前清空场景中的所有项
        scene.clear();
        // 遍历 results 列表，绘制每个 AABB 和标签
        for (const auto& strack : output_stracks) {
            // 修正尺寸
            float new_x = strack.byteTrackData.object.rect.x * scaleX;
            float new_y = strack.byteTrackData.object.rect.y * scaleY;
            float new_w = strack.byteTrackData.object.rect.width * scaleX;
            float new_h = strack.byteTrackData.object.rect.height * scaleY;
            // 绘制矩形框
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(new_x, new_y, new_w, new_h);
            // 设置矩形框的颜色，可以根据需要更改
            QPen pen(Qt::red);
            // 设置线条宽度
            pen.setWidth(2);
            rectItem->setPen(pen);
            scene.addItem(rectItem);
            QGraphicsTextItem* textItem = new QGraphicsTextItem(strack.byteTrackData.object.class_name + " ID:" + QString::number(strack.track_id) + " " + strack.byteTrackData.FirstTime);
            textItem->setFont(QFont("微软雅黑", 14));
            textItem->setDefaultTextColor(Qt::yellow);
            textItem->setPos(new_x, new_y-35);
            scene.addItem(textItem);
        }
        // 更新视图以显示新绘制的内容
        this->update();
    }

    void DrawQView::draw_seg() {
        // 绘制一个分割区域，比如绘制一个椭圆，假设中心点(150, 150)，大小为(100, 50)
        scene.addEllipse(150, 150, 100, 50, QPen(Qt::blue), QBrush(Qt::blue));
        this->update();
    }

    void DrawQView::draw_clear() {
        // 清空绘制内容
        scene.clear();
        this->update();
    }

    YOLOThread::YOLOThread(GUI *gui, QVideoSink *videoSink, QObject *parent): QThread(parent), gui(gui), videoSink(videoSink){
        this->drawQView = new DrawQView();
        gui->uiMainWindow->gridLayout_2->addWidget(this->drawQView, 0, 0, 1, 6);
        connect(drawQView, &DrawQView::viewChanged, this, &YOLOThread::onViewChanged);
    }

    void YOLOThread::run() {
        // 连接信号和槽
        connect(this, &YOLOThread::updateAABB, drawQView, &DrawQView::onUpdateAABB);
        auto lastTime = std::chrono::high_resolution_clock::now();
        int frameCount = 0;
        double fps = 0.0;
        this->onViewChanged();
        BYTETracker tracker(60, 3000);
        // 自动加锁
        QMutexLocker locker(&mutex);
        while (true) {
            if (!state) {
                disconnect(this, &YOLOThread::updateAABB, drawQView, &DrawQView::onUpdateAABB);
                std::cout << "已释放YOLOThread线程run函数" << std::endl;
                break;
            }

            // 等待条件变量
            while (paused) {
                waitCondition.wait(&mutex);
            }

            frameCount++;
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
            // 每处理一帧都记录当前时间
            if (elapsedTime > 1000) {
                fps = frameCount * 1000.0 / elapsedTime;
                frameCount = 0;
                lastTime = currentTime;
                std::cout << "当前平均 FPS: " << fps << std::endl;
            }
            std::vector<Object> objects;
            QImage image = videoSink->videoFrame().toImage();

            gui->yolo->detect(image, objects);
            vector<STrack> output_stracks = tracker.update(objects);
            gui->yolo->result(objects);
            this->updateByteTrack(tracker, output_stracks);
            // 发射信号
            emit updateAABB(output_stracks);
        }
    }

    void YOLOThread::updateByteTrack(BYTETracker &tracker, std::vector<STrack> &output_stracks) {
        for (int i = 0; i < output_stracks.size(); i++)
        {
            std::vector<float> tlwh = output_stracks[i].tlwh;
            bool vertical = tlwh[2] / tlwh[3] > 1.6;
            if (tlwh[2] * tlwh[3] > 20 && !vertical)
            {

            }
        }
    }

    void YOLOThread::pause() {
        paused = true;
    }

    void YOLOThread::resume() {
        paused = false;
        waitCondition.wakeOne(); // 唤醒等待的线程
    }

    void YOLOThread::onViewChanged() {
        // 调整缩放因子
        std::cout << drawQView->width() << "x" << drawQView->height() << std::endl;
        float scaleX = static_cast<float>(drawQView->width()) / static_cast<float>(videoSink->videoFrame().toImage().width());
        float scaleY = static_cast<float>(drawQView->height()) / static_cast<float>(videoSink->videoFrame().toImage().height());
        drawQView->scaleX = scaleX;
        drawQView->scaleY = scaleY;
        drawQView->setDrawQViemRect();
    }

    VideoWidget::VideoWidget(QWidget *parent, GUI *gui) : QWidget(parent), m_frame(QImage()), gui(gui) {
        this->player = new QMediaPlayer();
        this->videoSink = new QVideoSink();
        this->yoloThread = new YOLOThread(gui, videoSink, this);
        connect(videoSink, &QVideoSink::videoFrameChanged, this, &UI::VideoWidget::processFrame);

        this->player->setVideoOutput(videoSink);

        gui->uiMainWindow->gridLayout_2->addWidget(this, 0, 0, 1, 6);

        connect(gui->uiMainWindow->detect_Button, &QPushButton::clicked, [this]() {
            this->yoloThread->state = !this->yoloThread->state;
            if (this->gui->Model_flag && this->yoloThread->state) {
                this->gui->uiMainWindow->detect_Button->setText("关闭推理");
                yoloThread->start();
            }
            else {
                this->gui->uiMainWindow->detect_Button->setText("开启推理");
                this->yoloThread->state = false;
            }
        });

        connect(gui->uiMainWindow->Regress_Button, &QPushButton::clicked, [this]() {
            player->setPosition(player->position() - 5000);
        });

        connect(gui->uiMainWindow->VideoState_Button, &QPushButton::clicked, [this]() {
            if (this->player->isPlaying()) {
                this->pause();
            }
            else {
                this->play();
            }
        });

        connect(gui->uiMainWindow->Forward_Button, &QPushButton::clicked, [this]() {
            player->setPosition(player->position() + 5000);
        });

        connect(gui->uiMainWindow->VideoClose_Button, &QPushButton::clicked, [this]() {
            this->clear();
        });

        connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::EndOfMedia) {
                // 执行自定义任务
                qDebug() << "播放结束，执行任务";
                yoloThread->state = false;
                qDebug() << "标志位完成设置";
                yoloThread->requestInterruption();
                qDebug() << "线程强制中断完毕";
            }
        });
    };

    void VideoWidget::setVideoFrame(const QImage &frame) {
        m_frame = frame;
        update();
    }

    void VideoWidget::setVideoUrl(const QUrl qUrl) {
        this->clear();
        player->setSource(qUrl);

        connect(player, &QMediaPlayer::durationChanged, this, [this](qint64 duration) {
            QTime time = QTime(0, 0).addMSecs(duration);
            this->VideoTimer = time.toString("HH:mm:ss");
            gui->uiMainWindow->VideoTimer_Label->setText("00:00:00 / " + this->VideoTimer);
            gui->uiMainWindow->VideoTimer_Slider->setRange(0, duration);
        });

        connect(player, &QMediaPlayer::positionChanged, this, [this](qint64 position) {
            // 将当前播放位置转换为 HH:mm:ss 格式
            QTime time(0, 0, 0);
            time = time.addMSecs(position);
            QString timeString = time.toString("HH:mm:ss");
            // 更新标签，显示当前播放时间和总时长
            gui->uiMainWindow->VideoTimer_Label->setText(timeString + " / " + this->VideoTimer);
            gui->uiMainWindow->VideoTimer_Slider->setValue(position);
        });

        connect(gui->uiMainWindow->VideoTimer_Slider, &QSlider::sliderPressed, this, [this]() {
            player->pause();
            yoloThread->pause();
        });

        connect(gui->uiMainWindow->VideoTimer_Slider, &QSlider::sliderReleased, this, [this]() {
            // 获取当前值
            int newValue = gui->uiMainWindow->VideoTimer_Slider->value();
            // 禁用 QSlider 的所有信号
            gui->uiMainWindow->VideoTimer_Slider->blockSignals(true);
            qDebug() << "滑块释放，新值为：" << newValue;
            // 设置播放位置
            player->setPosition(newValue);
            // 恢复 QSlider 的信号
            gui->uiMainWindow->VideoTimer_Slider->blockSignals(false);
            yoloThread->resume();
            player->play();
        });
    }

    void VideoWidget::processFrame(const QVideoFrame &frame) {
        m_frame = frame.toImage();
        update();
    }

    void VideoWidget::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        if (!m_frame.isNull()) {
            painter.drawImage(rect(), m_frame);
        }
    }

    void VideoWidget::play() {
        player->play();
    }

    void VideoWidget::pause() {
        player->pause();
    }

    void VideoWidget::clear() {
        player->stop();
        this->VideoTimer.clear();
        gui->uiMainWindow->VideoTimer_Label->setText("00:00:00 / 00:00:00");
        // 设置为QUrl() 将导致播放器丢弃与当前媒体源有关的所有信息并停止与该媒体相关的所有 I/O 操作。
        player->setSource(QUrl());
        disconnect(player, &QMediaPlayer::durationChanged, nullptr, nullptr);
        disconnect(player, &QMediaPlayer::positionChanged, nullptr, nullptr);
        disconnect(gui->uiMainWindow->VideoTimer_Slider, &QSlider::sliderPressed, nullptr, nullptr);
        disconnect(gui->uiMainWindow->VideoTimer_Slider, &QSlider::sliderReleased, nullptr, nullptr);
    }
}