//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
#include <iostream>
#include <string>
#include <exception>
#include <drawer.hpp>
#include <ui.hpp>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Win win(0);
    win.resize(150, 150);
    win.show();
    return app.exec();
}
