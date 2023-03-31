#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <QtWidgets>

namespace jesture {

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);

   signals:
    void quit();
};

}  // namespace jesture

#endif  // JESTURE_MAIN_WINDOW_H