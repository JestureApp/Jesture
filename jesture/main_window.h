#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <vector>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedLayout>
#include <QtGui/QAction>
#include <QListWidget>
#include "jesturepipe/controller.h"
#include "jesture/components/frame_view.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(
        jesture::JesturePipeSettings initial_settings,
        std::vector<jesturepipe::Gesture> initial_gestures,
        QWidget* parent = 0
    );
signals:
    void quit();
    void new_camera_frame(cv::Mat frame);
    void update_camera_setting(int index);
    void toggle_recording();
public slots:
    void add_gesture(jesturepipe::Gesture gesture);
private slots:
    void open_settings();
    void close_settings();
    void open_inspector();
    void close_inspector();
    void inspect_gesture(int index);
    void hide_window();
    void show_window();
    void toggle_recording_display();
private:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    
    void setup_general();
    void setup_settings(jesture::JesturePipeSettings initial_settings);
    void setup_inspector(std::vector<jesturepipe::Gesture> initial_gestures);
    void setup_system_tray();
    void setup_stylesheet();
    
    QWidget* recording_overlay;
    QWidget* interactives;
    QStackedLayout* interactives_layout;
    jesture::FrameView* camera_feed;
    QWidget* general;
    QWidget* settings;
    QWidget* inspector;
    QListWidget* gesture_list;
    
    QAction* hide_action;
    QAction* show_action;
    QAction* quit_action;
    
    int mouse_x;
    int mouse_y;
};

#endif