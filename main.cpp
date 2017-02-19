#include <QApplication>
//#include "settingswindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow m;
  //  SettingsWindow window;

    return app.exec();
}
