//
// Created by 绮名桑 on 2024/9/14.
//
#include <QRandomGenerator>
#include "uiBeautify.hpp"

namespace AM {
    clickEffect::clickEffect(QWidget *parent) : QLabel(parent) {
        // 设置窗口标志，使窗口无边框、总是位于最上层，并作为工具提示窗口显示
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
        // 设置对齐方式为居中 注意：此方法通常用于对齐布局中小部件，直接对 QWidget 使用可能不会有实际效果
        this->setAlignment(Qt::AlignCenter);
        // 使窗口背景完全透明，以便只显示窗口内容而不显示背景色
        this->setAttribute(Qt::WA_TranslucentBackground);
        // 设置窗口关闭时自动删除 窗口关闭时会自动释放内存，不需要手动删除
        this->setAttribute(Qt::WA_DeleteOnClose);
        this->setStyleSheet("font-size: 40px;");
        // 创建透明度效果对象
        opacityEffect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(opacityEffect);
        // 创建几何动画对象
        positionAnimation = new QPropertyAnimation(this, "geometry");
        positionAnimation->setDuration(1500);
        // 创建透明度动画对象
        opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnimation->setDuration(1500);
        // 创建动画组对象
        animationGroup = new QParallelAnimationGroup(this);
        // 将位置动画添加到动画组
        animationGroup->addAnimation(positionAnimation);
        // 将透明度动画添加到动画组
        animationGroup->addAnimation(opacityAnimation);
        // 配置信号槽 动画结束后自动删除
        connect(animationGroup, &QPropertyAnimation::finished, this, &clickEffect::onAnimationFinished);
    }

    void clickEffect::showEffect(const QString &text, const QPoint &position) {
        // 设置显示的文本，比如心形或其他符号
        this->setText(text);
        // 自动调整自身  适配样式表
        this->adjustSize();
        // 随机坐标确定
        int startX = QRandomGenerator::global()->bounded(-150, 151);
        int startY = QRandomGenerator::global()->bounded(-150, 151);
        // 设置特效的起始和终止位置
        QRect startRect = QRect(position.x() - (this->width() / 2), position.y() - (this->height() / 2), this->width(), this->height()); // 初始位置
        QRect endRect = QRect(position.x() + startX, position.y() + startY, this->width(), this->height());  // 最终位置
        // 设置几何动画的起点和终点
        positionAnimation->setStartValue(startRect);
        positionAnimation->setEndValue(endRect);
        // 设置透明度动画的起点和终点
        opacityAnimation->setStartValue(1.0);
        opacityAnimation->setEndValue(0.0);
        // 设置初始几何
        this->setGeometry(startRect);
        // 显示效果
        this->show();
        // 启动动画
        animationGroup->start();
    }

    void clickEffect::onAnimationFinished() {
        // 动画结束后删除自己
        this->deleteLater();
    }

    clickEffect::~clickEffect() {

    }

}

namespace UI {
    QButtonGroup::QButtonGroup(const std::vector<QPushButton*>& buttonsList, int index) : buttons(buttonsList) {
        buttons[Page_index]->setStyleSheet(
                "QPushButton { border: none; background: none; } QPushButton:hover { border-radius: 5px; background: white; }"
        );
        buttons[index]->setStyleSheet(
                "border-radius: 5px;"
                "background: white;"
        );
        Page_index = index;
    }
}
