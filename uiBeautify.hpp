//
// Created by 绮名桑 on 2024/9/14.
//

#ifndef WIFI_QT_UIBEAUTIFY_HPP
#define WIFI_QT_UIBEAUTIFY_HPP

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QPushButton>

#include "Mark.hpp"

namespace AM {
    class clickEffect : public QLabel {
    public:
        explicit clickEffect(QWidget *parent = nullptr);
        void showEffect(const QString &text, const QPoint &position);
        ~clickEffect() override;
    private slots:
        void onAnimationFinished();
    private:
        QGraphicsOpacityEffect *opacityEffect;      // 透明度效果
        QPropertyAnimation *positionAnimation;      // 位置动画
        QPropertyAnimation *opacityAnimation;       // 透明度动画
        QParallelAnimationGroup *animationGroup;    // 动画组
    };
}

namespace UI {
    class QButtonGroup {
    public:
        explicit QButtonGroup(const std::vector<QPushButton*>& buttons, int index);
    private:
        std::vector<QPushButton*> buttons;  // 直接存储按钮指针的 vector
    };
}

#endif //WIFI_QT_UIBEAUTIFY_HPP
