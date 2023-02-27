#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedLayout>
#include <QtGui/QAction>
#include "jesturepipe/controller.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(jesture::JesturePipeController* jesturepipe_controller);
signals:
    void quit();
private slots:
    void open_settings();
    void close_settings();
    void open_inspector();
    void close_inspector();
    void inspect_gesture(int index);
    
    void hide_from_tray();
    void show_from_tray();
    void quit_from_tray();
private:
    void setup_general();
    void setup_settings();
    void setup_inspector();
    void setup_system_tray();
    
    QWidget* interactives;
    QStackedLayout* interactives_layout;
    QWidget* general;
    QWidget* settings;
    QWidget* inspector;
    
    QAction* hide_action;
    QAction* show_action;
    QAction* quit_action;
/*protected:
    void closeEvent(QCloseEvent *event) override;
*/
};

#endif