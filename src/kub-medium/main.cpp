#include <QApplication>

#include <kublonwindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KubLonWindow w;
    w.show();

    return app.exec();
}
