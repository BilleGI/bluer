#include <QtGui/QtGui>
#include <QApplication>

#include "my_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MY_WINDOW window;
    window.bluer_effect();
    window.choice_picture();
    window.save_picture();
    QScreen* screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    window.resize(size.width(), size.height());
    window.show();
    return app.exec();
}
