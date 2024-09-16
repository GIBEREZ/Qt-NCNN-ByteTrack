/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H
#define UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *min_Button;
    QPushButton *max_Button;
    QPushButton *quit_Button;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QGridLayout *gridLayout_6;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *NetworkStatusLabel;
    QPushButton *GetVideo_Button;
    QComboBox *comboBox_2;
    QPushButton *detect_Button;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *SelectModel_Button;
    QLabel *label_3;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_9;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QPushButton *pushButton_25;
    QPushButton *pushButton_21;
    QPushButton *pushButton_27;
    QPushButton *pushButton_20;
    QPushButton *pushButton_9;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QLabel *label_4;
    QLabel *IPv4Label;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_8;
    QLineEdit *Port_Edit;
    QLabel *WifiName_Label;
    QPushButton *connect_Button;
    QLineEdit *Host_Edit;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_13;
    QPushButton *pushButton_12;
    QLabel *label_9;
    QPushButton *pushButton_11;
    QLineEdit *ZigBee_Edit;
    QPushButton *SendChar_Button;
    QPushButton *SendBin_Edit;
    QPushButton *pushButton_15;
    QPushButton *SendHex_Button;
    QPushButton *pushButton_14;
    QPushButton *pushButton_10;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *Url_Edit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *Forward_Button;
    QPushButton *Regress_Button;
    QPushButton *VideoState_Button;
    QPushButton *VideoClose_Button;
    QSlider *VideoTimer_Slider;
    QLabel *VideoTimer_Label;
    QWidget *Video_Widget;
    QGridLayout *gridLayout_10;
    QWidget *page_6;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_8;
    QPlainTextEdit *Log_PlainTextEdit;
    QWidget *Sidebar_QWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *Head_QLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *Main_Button;
    QPushButton *Log_Button;
    QPushButton *Tool_Button;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Folder_Button;
    QPushButton *Setting_Button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        MainWindow->setMinimumSize(QSize(1920, 1080));
        MainWindow->setMaximumSize(QSize(2560, 1440));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(18, 18, 18, 18);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(9, -1, 9, -1);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        min_Button = new QPushButton(widget_3);
        min_Button->setObjectName("min_Button");
        min_Button->setMinimumSize(QSize(25, 25));
        min_Button->setMaximumSize(QSize(25, 25));
        min_Button->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(min_Button);

        max_Button = new QPushButton(widget_3);
        max_Button->setObjectName("max_Button");
        max_Button->setMinimumSize(QSize(25, 25));
        max_Button->setMaximumSize(QSize(25, 25));
        max_Button->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(max_Button);

        quit_Button = new QPushButton(widget_3);
        quit_Button->setObjectName("quit_Button");
        quit_Button->setMinimumSize(QSize(25, 25));
        quit_Button->setMaximumSize(QSize(25, 25));
        quit_Button->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(quit_Button);


        gridLayout->addWidget(widget_3, 0, 1, 1, 3);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        gridLayout_6 = new QGridLayout(page_5);
        gridLayout_6->setSpacing(10);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(9, 0, 9, 9);
        widget = new QWidget(page_5);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(380, 0));
        widget->setMaximumSize(QSize(380, 16777215));
        widget->setSizeIncrement(QSize(200, 0));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName("groupBox_3");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName("gridLayout_3");
        NetworkStatusLabel = new QLabel(groupBox_3);
        NetworkStatusLabel->setObjectName("NetworkStatusLabel");
        sizePolicy.setHeightForWidth(NetworkStatusLabel->sizePolicy().hasHeightForWidth());
        NetworkStatusLabel->setSizePolicy(sizePolicy);
        NetworkStatusLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(NetworkStatusLabel, 0, 2, 1, 1);

        GetVideo_Button = new QPushButton(groupBox_3);
        GetVideo_Button->setObjectName("GetVideo_Button");

        gridLayout_3->addWidget(GetVideo_Button, 0, 3, 1, 1);

        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName("comboBox_2");
        sizePolicy.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(comboBox_2, 2, 0, 1, 2);

        detect_Button = new QPushButton(groupBox_3);
        detect_Button->setObjectName("detect_Button");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(detect_Button->sizePolicy().hasHeightForWidth());
        detect_Button->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(detect_Button, 2, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        SelectModel_Button = new QPushButton(groupBox_3);
        SelectModel_Button->setObjectName("SelectModel_Button");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(SelectModel_Button->sizePolicy().hasHeightForWidth());
        SelectModel_Button->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(SelectModel_Button, 2, 2, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_7 = new QGroupBox(widget);
        groupBox_7->setObjectName("groupBox_7");
        gridLayout_9 = new QGridLayout(groupBox_7);
        gridLayout_9->setObjectName("gridLayout_9");
        pushButton_23 = new QPushButton(groupBox_7);
        pushButton_23->setObjectName("pushButton_23");

        gridLayout_9->addWidget(pushButton_23, 1, 2, 1, 1);

        pushButton_24 = new QPushButton(groupBox_7);
        pushButton_24->setObjectName("pushButton_24");

        gridLayout_9->addWidget(pushButton_24, 2, 0, 1, 1);

        pushButton_25 = new QPushButton(groupBox_7);
        pushButton_25->setObjectName("pushButton_25");

        gridLayout_9->addWidget(pushButton_25, 2, 1, 1, 1);

        pushButton_21 = new QPushButton(groupBox_7);
        pushButton_21->setObjectName("pushButton_21");

        gridLayout_9->addWidget(pushButton_21, 1, 1, 1, 1);

        pushButton_27 = new QPushButton(groupBox_7);
        pushButton_27->setObjectName("pushButton_27");

        gridLayout_9->addWidget(pushButton_27, 2, 2, 1, 1);

        pushButton_20 = new QPushButton(groupBox_7);
        pushButton_20->setObjectName("pushButton_20");

        gridLayout_9->addWidget(pushButton_20, 1, 0, 1, 1);

        pushButton_9 = new QPushButton(groupBox_7);
        pushButton_9->setObjectName("pushButton_9");

        gridLayout_9->addWidget(pushButton_9, 0, 2, 1, 1);

        pushButton_6 = new QPushButton(groupBox_7);
        pushButton_6->setObjectName("pushButton_6");

        gridLayout_9->addWidget(pushButton_6, 0, 1, 1, 1);

        pushButton_4 = new QPushButton(groupBox_7);
        pushButton_4->setObjectName("pushButton_4");

        gridLayout_9->addWidget(pushButton_4, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_7);

        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName("groupBox_4");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy4);
        groupBox_4->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName("gridLayout_4");
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 2, 0, 1, 1);

        IPv4Label = new QLabel(groupBox_4);
        IPv4Label->setObjectName("IPv4Label");

        gridLayout_4->addWidget(IPv4Label, 5, 0, 1, 2);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 6, 0, 1, 2);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName("label_8");

        gridLayout_4->addWidget(label_8, 7, 0, 1, 2);

        Port_Edit = new QLineEdit(groupBox_4);
        Port_Edit->setObjectName("Port_Edit");

        gridLayout_4->addWidget(Port_Edit, 2, 1, 1, 1);

        WifiName_Label = new QLabel(groupBox_4);
        WifiName_Label->setObjectName("WifiName_Label");

        gridLayout_4->addWidget(WifiName_Label, 4, 0, 1, 2);

        connect_Button = new QPushButton(groupBox_4);
        connect_Button->setObjectName("connect_Button");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(connect_Button->sizePolicy().hasHeightForWidth());
        connect_Button->setSizePolicy(sizePolicy5);
        connect_Button->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(connect_Button, 3, 1, 1, 1);

        Host_Edit = new QLineEdit(groupBox_4);
        Host_Edit->setObjectName("Host_Edit");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(Host_Edit->sizePolicy().hasHeightForWidth());
        Host_Edit->setSizePolicy(sizePolicy6);

        gridLayout_4->addWidget(Host_Edit, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName("groupBox_5");
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName("gridLayout_5");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 2, 0, 1, 3);

        pushButton_13 = new QPushButton(groupBox_5);
        pushButton_13->setObjectName("pushButton_13");

        gridLayout_5->addWidget(pushButton_13, 3, 2, 1, 1);

        pushButton_12 = new QPushButton(groupBox_5);
        pushButton_12->setObjectName("pushButton_12");

        gridLayout_5->addWidget(pushButton_12, 4, 2, 1, 1);

        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName("label_9");
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_9, 0, 0, 1, 4);

        pushButton_11 = new QPushButton(groupBox_5);
        pushButton_11->setObjectName("pushButton_11");

        gridLayout_5->addWidget(pushButton_11, 4, 1, 1, 1);

        ZigBee_Edit = new QLineEdit(groupBox_5);
        ZigBee_Edit->setObjectName("ZigBee_Edit");

        gridLayout_5->addWidget(ZigBee_Edit, 1, 0, 1, 4);

        SendChar_Button = new QPushButton(groupBox_5);
        SendChar_Button->setObjectName("SendChar_Button");

        gridLayout_5->addWidget(SendChar_Button, 2, 3, 1, 1);

        SendBin_Edit = new QPushButton(groupBox_5);
        SendBin_Edit->setObjectName("SendBin_Edit");

        gridLayout_5->addWidget(SendBin_Edit, 3, 1, 1, 1);

        pushButton_15 = new QPushButton(groupBox_5);
        pushButton_15->setObjectName("pushButton_15");

        gridLayout_5->addWidget(pushButton_15, 4, 3, 1, 1);

        SendHex_Button = new QPushButton(groupBox_5);
        SendHex_Button->setObjectName("SendHex_Button");

        gridLayout_5->addWidget(SendHex_Button, 3, 0, 1, 1);

        pushButton_14 = new QPushButton(groupBox_5);
        pushButton_14->setObjectName("pushButton_14");

        gridLayout_5->addWidget(pushButton_14, 3, 3, 1, 1);

        pushButton_10 = new QPushButton(groupBox_5);
        pushButton_10->setObjectName("pushButton_10");

        gridLayout_5->addWidget(pushButton_10, 4, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);


        gridLayout_6->addWidget(widget, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(page_5);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        Url_Edit = new QLineEdit(groupBox_2);
        Url_Edit->setObjectName("Url_Edit");

        verticalLayout_2->addWidget(Url_Edit);


        gridLayout_6->addWidget(groupBox_2, 0, 0, 1, 2);

        groupBox = new QGroupBox(page_5);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy7);
        groupBox->setMinimumSize(QSize(640, 480));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        Forward_Button = new QPushButton(groupBox);
        Forward_Button->setObjectName("Forward_Button");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(Forward_Button->sizePolicy().hasHeightForWidth());
        Forward_Button->setSizePolicy(sizePolicy8);
        Forward_Button->setMinimumSize(QSize(35, 35));
        Forward_Button->setMaximumSize(QSize(35, 35));
        Forward_Button->setIconSize(QSize(30, 30));

        gridLayout_2->addWidget(Forward_Button, 1, 4, 1, 1);

        Regress_Button = new QPushButton(groupBox);
        Regress_Button->setObjectName("Regress_Button");
        sizePolicy8.setHeightForWidth(Regress_Button->sizePolicy().hasHeightForWidth());
        Regress_Button->setSizePolicy(sizePolicy8);
        Regress_Button->setMinimumSize(QSize(35, 35));
        Regress_Button->setMaximumSize(QSize(35, 35));
        Regress_Button->setIconSize(QSize(30, 30));

        gridLayout_2->addWidget(Regress_Button, 1, 2, 1, 1);

        VideoState_Button = new QPushButton(groupBox);
        VideoState_Button->setObjectName("VideoState_Button");
        sizePolicy8.setHeightForWidth(VideoState_Button->sizePolicy().hasHeightForWidth());
        VideoState_Button->setSizePolicy(sizePolicy8);
        VideoState_Button->setMinimumSize(QSize(35, 35));
        VideoState_Button->setMaximumSize(QSize(35, 35));
        VideoState_Button->setIconSize(QSize(35, 35));

        gridLayout_2->addWidget(VideoState_Button, 1, 3, 1, 1);

        VideoClose_Button = new QPushButton(groupBox);
        VideoClose_Button->setObjectName("VideoClose_Button");
        sizePolicy8.setHeightForWidth(VideoClose_Button->sizePolicy().hasHeightForWidth());
        VideoClose_Button->setSizePolicy(sizePolicy8);
        VideoClose_Button->setMinimumSize(QSize(35, 35));
        VideoClose_Button->setMaximumSize(QSize(35, 35));
        VideoClose_Button->setIconSize(QSize(35, 35));

        gridLayout_2->addWidget(VideoClose_Button, 1, 5, 1, 1);

        VideoTimer_Slider = new QSlider(groupBox);
        VideoTimer_Slider->setObjectName("VideoTimer_Slider");
        VideoTimer_Slider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(VideoTimer_Slider, 1, 0, 1, 1);

        VideoTimer_Label = new QLabel(groupBox);
        VideoTimer_Label->setObjectName("VideoTimer_Label");
        VideoTimer_Label->setMinimumSize(QSize(150, 30));
        VideoTimer_Label->setMaximumSize(QSize(150, 30));
        VideoTimer_Label->setLayoutDirection(Qt::LeftToRight);
        VideoTimer_Label->setTextFormat(Qt::AutoText);
        VideoTimer_Label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(VideoTimer_Label, 1, 1, 1, 1);

        Video_Widget = new QWidget(groupBox);
        Video_Widget->setObjectName("Video_Widget");
        gridLayout_10 = new QGridLayout(Video_Widget);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setContentsMargins(0, 0, 0, 0);

        gridLayout_2->addWidget(Video_Widget, 0, 0, 1, 6);


        gridLayout_6->addWidget(groupBox, 1, 1, 1, 1);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        gridLayout_7 = new QGridLayout(page_6);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(9, 0, 9, 9);
        groupBox_6 = new QGroupBox(page_6);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_8 = new QGridLayout(groupBox_6);
        gridLayout_8->setObjectName("gridLayout_8");
        Log_PlainTextEdit = new QPlainTextEdit(groupBox_6);
        Log_PlainTextEdit->setObjectName("Log_PlainTextEdit");

        gridLayout_8->addWidget(Log_PlainTextEdit, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_6, 0, 0, 1, 1);

        stackedWidget->addWidget(page_6);

        gridLayout->addWidget(stackedWidget, 1, 2, 1, 1);

        Sidebar_QWidget = new QWidget(centralwidget);
        Sidebar_QWidget->setObjectName("Sidebar_QWidget");
        sizePolicy.setHeightForWidth(Sidebar_QWidget->sizePolicy().hasHeightForWidth());
        Sidebar_QWidget->setSizePolicy(sizePolicy);
        Sidebar_QWidget->setMinimumSize(QSize(0, 0));
        Sidebar_QWidget->setCursor(QCursor(Qt::ArrowCursor));
        Sidebar_QWidget->setMouseTracking(false);
        Sidebar_QWidget->setTabletTracking(false);
        Sidebar_QWidget->setAcceptDrops(false);
#if QT_CONFIG(accessibility)
        Sidebar_QWidget->setAccessibleName(QString::fromUtf8(""));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        Sidebar_QWidget->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_CONFIG(accessibility)
        Sidebar_QWidget->setLayoutDirection(Qt::LeftToRight);
        Sidebar_QWidget->setAutoFillBackground(false);
        verticalLayout_3 = new QVBoxLayout(Sidebar_QWidget);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 40, 10, 10);
        Head_QLabel = new QLabel(Sidebar_QWidget);
        Head_QLabel->setObjectName("Head_QLabel");
        Head_QLabel->setMinimumSize(QSize(40, 40));
        Head_QLabel->setMaximumSize(QSize(40, 40));
        Head_QLabel->setStyleSheet(QString::fromUtf8(""));
        Head_QLabel->setScaledContents(true);
        Head_QLabel->setAlignment(Qt::AlignCenter);
        Head_QLabel->setWordWrap(false);
        Head_QLabel->setOpenExternalLinks(false);

        verticalLayout_3->addWidget(Head_QLabel);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        Main_Button = new QPushButton(Sidebar_QWidget);
        Main_Button->setObjectName("Main_Button");
        Main_Button->setMinimumSize(QSize(40, 40));
        Main_Button->setMaximumSize(QSize(40, 40));
        Main_Button->setCursor(QCursor(Qt::PointingHandCursor));
        Main_Button->setLayoutDirection(Qt::LeftToRight);
        Main_Button->setIconSize(QSize(35, 35));
        Main_Button->setAutoDefault(false);
        Main_Button->setFlat(false);

        verticalLayout_3->addWidget(Main_Button);

        Log_Button = new QPushButton(Sidebar_QWidget);
        Log_Button->setObjectName("Log_Button");
        Log_Button->setMinimumSize(QSize(40, 40));
        Log_Button->setMaximumSize(QSize(40, 40));
        Log_Button->setCursor(QCursor(Qt::PointingHandCursor));
        Log_Button->setIconSize(QSize(35, 35));

        verticalLayout_3->addWidget(Log_Button);

        Tool_Button = new QPushButton(Sidebar_QWidget);
        Tool_Button->setObjectName("Tool_Button");
        Tool_Button->setMinimumSize(QSize(40, 40));
        Tool_Button->setMaximumSize(QSize(40, 40));
        Tool_Button->setCursor(QCursor(Qt::PointingHandCursor));
        Tool_Button->setIconSize(QSize(35, 35));

        verticalLayout_3->addWidget(Tool_Button);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        Folder_Button = new QPushButton(Sidebar_QWidget);
        Folder_Button->setObjectName("Folder_Button");
        Folder_Button->setMinimumSize(QSize(40, 40));
        Folder_Button->setMaximumSize(QSize(40, 40));
        Folder_Button->setCursor(QCursor(Qt::PointingHandCursor));
        Folder_Button->setIconSize(QSize(35, 35));

        verticalLayout_3->addWidget(Folder_Button);

        Setting_Button = new QPushButton(Sidebar_QWidget);
        Setting_Button->setObjectName("Setting_Button");
        Setting_Button->setMinimumSize(QSize(40, 40));
        Setting_Button->setMaximumSize(QSize(40, 40));
        Setting_Button->setCursor(QCursor(Qt::PointingHandCursor));
        Setting_Button->setIconSize(QSize(35, 35));

        verticalLayout_3->addWidget(Setting_Button);


        gridLayout->addWidget(Sidebar_QWidget, 0, 0, 2, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        Main_Button->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\265\214\345\205\245\345\274\217\344\270\273\350\275\246Windows\344\270\212\344\275\215\346\234\272", nullptr));
        min_Button->setText(QString());
        max_Button->setText(QString());
        quit_Button->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        NetworkStatusLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\252\350\277\236\346\216\245", nullptr));
        GetVideo_Button->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\350\247\206\351\242\221\346\216\250\346\265\201", nullptr));
        detect_Button->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\346\216\250\347\220\206", nullptr));
        SelectModel_Button->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\250\241\345\236\213", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\345\212\237\350\203\275", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_24->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_25->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_27->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\347\211\251\345\223\201\351\253\230\345\272\246", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\347\275\221\347\273\234\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        IPv4Label->setText(QCoreApplication::translate("MainWindow", "IPv4\345\234\260\345\235\200\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\255\220\347\275\221\346\216\251\347\240\201\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\351\273\230\350\256\244\347\275\221\345\205\263\357\274\232", nullptr));
        WifiName_Label->setText(QCoreApplication::translate("MainWindow", "WIFI\345\220\215\347\247\260\357\274\232", nullptr));
        connect_Button->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\347\233\256\346\240\207\350\256\276\345\244\207", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\351\200\232\350\256\257\345\212\237\350\203\275", nullptr));
        pushButton_13->setText(QString());
        pushButton_12->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\217\221\351\200\201\347\232\204\344\277\241\346\201\257\357\274\232", nullptr));
        pushButton_11->setText(QString());
        SendChar_Button->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\344\277\241\346\201\257", nullptr));
        SendBin_Edit->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201Bin\344\277\241\346\201\257", nullptr));
        pushButton_15->setText(QString());
        SendHex_Button->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201Hex\344\277\241\346\201\257", nullptr));
        pushButton_14->setText(QString());
        pushButton_10->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "URL\347\233\256\346\240\207", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\351\242\221\346\216\250\346\265\201", nullptr));
        Forward_Button->setText(QString());
        Regress_Button->setText(QString());
        VideoState_Button->setText(QString());
        VideoClose_Button->setText(QString());
        VideoTimer_Label->setText(QCoreApplication::translate("MainWindow", "00:00:00 / 00:00:00", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227\350\276\223\345\207\272", nullptr));
        Head_QLabel->setText(QString());
        Main_Button->setText(QString());
        Log_Button->setText(QString());
        Tool_Button->setText(QString());
        Folder_Button->setText(QString());
        Setting_Button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H
