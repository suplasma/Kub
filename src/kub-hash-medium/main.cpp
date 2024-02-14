#include <QApplication>

#include <hashkub.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HashKub w;
    w.show();

    return app.exec();
}
