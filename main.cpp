#include "GUI.hpp"
extern "C"{
    #include <libavformat/avformat.h>
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    std::cout << msg.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    av_log_set_level(AV_LOG_INFO);
    av_log(NULL, AV_LOG_INFO, "avformat_configurations: \n %s", avformat_configuration());
    qInstallMessageHandler(customMessageHandler);
    QApplication app(argc, argv);
    GUI *gui = new GUI();
    gui->ui->show();
    return app.exec();
}