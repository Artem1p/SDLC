#include <QApplication>
#include "Model.h"
#include "MainWindow.h"
#include "Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Model model;
    MainWindow view(&model);
    Controller controller(&model, &view);

    view.show();
    return app.exec();
}