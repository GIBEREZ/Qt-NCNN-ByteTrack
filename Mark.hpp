//
// Created by 绮名桑 on 2024/9/12.
//

#ifndef WIFI_QT_MARK_HPP
#define WIFI_QT_MARK_HPP

//***** UI 界面 静态全局标志位 *****//

static bool Model_Flag = false;             // 模型加载标志位
static bool YOLOThread_Paused = false;      // YOLOThread暂停自锁标志位
static bool YOLOThread_Flag = false;        // YOLOThread终止标志位
static int Page_index = 1;                  // YOLOThread计页器

//***** UI 界面 表情符号 *****//
static const QString emojis[] = {
        "😃", "😁", "😂", "😃", "😄", "😅","😆", "😇", "😈", "😉", "😊", "😋","😌", "😍", "😎", "😏", "😐", "😑",
        "😒", "😓", "😔", "😕", "😖", "😗","😘", "😙", "😚", "😛", "😜", "😝","😞", "😟", "😠", "😡", "😢", "😣",
        "😤", "😥", "😦", "😧", "😨", "😩","😪", "😫", "😬", "😭", "😮", "😯","😰", "😱", "😲", "😳", "😴", "😵",
        "😶"
};
static const int emojiCount = sizeof(emojis) / sizeof(emojis[0]);

#endif //WIFI_QT_MARK_HPP
