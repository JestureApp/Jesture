#include "main_window.h"

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QMediaDevices>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QWidget>
#include <QShortcut>
#include <QKeySequence>

#include "jesture/components/frame_view.h"
#include "jesture/components/gesture_editor.h"
#include "jesture/jesturepipe/settings.h"

using namespace jesture;

MainWindow::MainWindow(JesturePipeController* jesturepipe_controller, QWidget* parent) :
    QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint) {
    // Create the parent widget
    auto content = new QWidget(this);
    auto content_layout = new QStackedLayout(content);
    content_layout->setStackingMode(QStackedLayout::StackAll);
    content->setLayout(content_layout);
    setCentralWidget(content);

    // Camera feed
    camera_feed = new FrameView(content);
    content_layout->addWidget(camera_feed);
    connect(
        jesturepipe_controller,
        &JesturePipeController::frameReady,
        camera_feed,
        &FrameView::setFrame
    );

    // Create a parent for all interactive menus
    interactives = new QWidget(content);
    interactives_layout = new QStackedLayout(interactives);
    interactives->setLayout(interactives_layout);
    content_layout->addWidget(interactives);
    content_layout->setCurrentWidget(interactives);

    // Setup menus
    setup_general();
    setup_settings();
    setup_inspector();

    // Check if platform supports the system tray
    if (QSystemTrayIcon::isSystemTrayAvailable()) setup_system_tray();
    
    auto settings_shortcut = new QShortcut(QKeySequence::Preferences, this);
    connect(settings_shortcut, &QShortcut::activated, this, &MainWindow::open_settings);
    auto hide_shortcut = new QShortcut(QKeySequence(Qt::Key_Control | Qt::Key_H), this);
    connect(hide_shortcut, &QShortcut::activated, this, &MainWindow::hide_window);
    auto escape_shortcut = new QShortcut(QKeySequence::Cancel, this);
    connect(escape_shortcut, &QShortcut::activated, this, &MainWindow::close_settings);
    
    setWindowTitle("Jesture");
    setup_stylesheet();
}

void MainWindow::setup_general() {
    // Create menu and add to interactive menus parent
    general = new QWidget(interactives);
    interactives_layout->addWidget(general);
    
    // Create layout
    auto layout = new QHBoxLayout(general);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    general->setLayout(layout);

    // Get icons
    auto cross_icon = new QIcon("icons/cross.svg");
    auto hide_icon = new QIcon("icons/hide.svg");
    auto settings_icon = new QIcon("icons/settings.svg");
    auto inspector_icon = new QIcon("icons/add_element.svg");

    // Create buttons
    auto quit_button = new QPushButton(*cross_icon, "", general);
    auto hide_button = new QPushButton(*hide_icon, "", general);
    auto settings_button = new QPushButton(*settings_icon, "", general);
    auto inspector_button = new QPushButton(*inspector_icon, "", general);
    
    // Styling names
    quit_button->setObjectName("quit_button");
    hide_button->setObjectName("hide_button");
    
    // Connecting button events to actions
    connect(quit_button, &QPushButton::released, this,
            &MainWindow::quit_app);
    connect(hide_button, &QPushButton::released, this,
            &MainWindow::hide_window);
    connect(settings_button, &QPushButton::released, this,
            &MainWindow::open_settings);
    connect(inspector_button, &QPushButton::released, this,
            &MainWindow::open_inspector);
    
    // Add to layout
    layout->addWidget(quit_button);
    layout->addWidget(hide_button);
    layout->addWidget(settings_button);
    layout->addWidget(inspector_button);
}

void MainWindow::setup_settings() {
    // Create menu and add to interactive menus parent
    settings = new QWidget(interactives);
    interactives_layout->addWidget(settings);

    // Create layout
    auto layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    settings->setLayout(layout);
    
    // Create back button
    auto back_icon = new QIcon("icons/left_arrow.svg");
    auto back_button = new QPushButton(*back_icon, "", settings);
    layout->addWidget(back_button, 0, 0);
    connect(back_button, &QPushButton::released, this,
            &MainWindow::close_settings);

    // Create title
    auto title = new QLabel("Settings", settings);
    title->setObjectName("title");
    layout->addWidget(title, 0, 1);

    // Accuracy setting, using a slider
    auto accuracy_slider = new QSlider(Qt::Horizontal, settings);
    auto accuracy_label = new QLabel("Accuracy", settings);
    auto accuracy_description =
        new QLabel("Lower this setting for better peformance.\nRaise this setting for better gesture reading.", settings);
    accuracy_description->setObjectName("description");
    layout->addWidget(accuracy_label, 1, 1);
    layout->addWidget(accuracy_slider, 1, 2);
    layout->addWidget(accuracy_description, 2, 1);

    // Camera setting, using a dropdown box
    auto camera_selector = new QComboBox(settings);
    const auto cameras = QMediaDevices::videoInputs();
    QList<QString> camera_descriptions;
    for (const auto& camera : cameras)
        camera_descriptions.append(camera.description());
    camera_selector->addItems(camera_descriptions);
    auto camera_label = new QLabel("Camera", settings);
    layout->addWidget(camera_label, 3, 1);
    layout->addWidget(camera_selector, 3, 2);
}

void MainWindow::setup_inspector() {
    // Create menu and add to interactive menus parent
    inspector = new QWidget(interactives);
    interactives_layout->addWidget(inspector);

    // Create layout
    auto layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    inspector->setLayout(layout);

    // Create back button
    auto back_icon = new QIcon("icons/left_arrow.svg");
    auto back_button = new QPushButton(*back_icon, "", inspector);
    layout->addWidget(back_button, 0, 0);
    connect(back_button, &QPushButton::released, this,
            &MainWindow::close_inspector);

    // Create title
    auto title = new QLabel("Gestures", inspector);
    title->setObjectName("title");
    layout->addWidget(title, 0, 1);

    auto gesture_list = new QListWidget(inspector);
    layout->addWidget(gesture_list, 1, 1);
}

void MainWindow::setup_system_tray() {
    // Get icons
    auto hide_icon = new QIcon("icons/hide.svg");
    auto quit_icon = new QIcon("icons/quit.svg");
    auto settings_icon = new QIcon("icons/settings.svg");
    auto show_icon = new QIcon("icons/show.svg");

    // Create system tray and menu
    auto tray = new QSystemTrayIcon(*settings_icon, this);
    auto tray_menu = new QMenu(this);

    // Create actions
    hide_action = new QAction(*hide_icon, "Hide", tray_menu);
    show_action = new QAction(*show_icon, "Show", tray_menu);
    quit_action = new QAction(*quit_icon, "Quit", tray_menu);
    connect(hide_action, &QAction::triggered, this,
            &MainWindow::hide_window);
    connect(show_action, &QAction::triggered, this,
            &MainWindow::show_window);
    connect(quit_action, &QAction::triggered, this,
            &MainWindow::quit_app);

    // Show action starts toggled off
    show_action->setVisible(false);

    // Set up tray and menu
    tray_menu->addAction(hide_action);
    tray_menu->addAction(show_action);
    tray_menu->addSeparator();
    tray_menu->addAction(quit_action);
    tray->setContextMenu(tray_menu);
    tray->show();
}

void MainWindow::setup_stylesheet() {
    // Define stylesheet using raw string
    const char* stylesheet = R"(
        QMainWindow {
            border: 1px solid rgba(255, 255, 255, 20);
            border-radius: 20px;
        }
        QLabel {
            font-size: 20pt;
        }
        QLabel#title {
            font-weight: bold;
            font-size: 24pt;
        }
        QLabel#description {
            font-weight: 200;
            font-size: 16pt;
        }
        QPushButton {
            width: 40px;
            height: 40px;
            background-color: rgba(0, 0, 0, 60);
            border: 2px solid rgb(60, 60, 60);
            border-radius: 20px;
            icon-size: 20px;
        }
        QPushButton:focus {
            background-color: rgba(60, 60, 240, 60);
            border-color: rgb(60, 60, 240);
        }
        QPushButton:hover {
            background-color: rgba(120, 120, 120, 60);
            border-color: rgb(120, 120, 120);
        }
        QPushButton#quit_button:hover {
            background-color: rgba(240, 60, 60, 60);
            border-color: rgb(240, 60, 60);
        }
        QPushButton#hide_button:hover {
            background-color: rgba(160, 160, 40, 60);
            border-color: rgb(160, 160, 40);
        }
    )";
    
    // Set window's stylesheet
    setStyleSheet(stylesheet);
}

void MainWindow::open_settings() {
    interactives_layout->setCurrentWidget(settings);
    camera_feed->blur();
}

void MainWindow::close_settings() {
    interactives_layout->setCurrentWidget(general);
    camera_feed->unblur();
}

void MainWindow::open_inspector() {
    interactives_layout->setCurrentWidget(inspector);
    camera_feed->blur();
}

void MainWindow::close_inspector() {
    interactives_layout->setCurrentWidget(general);
    camera_feed->unblur();
}

void MainWindow::inspect_gesture(int index) {}

void MainWindow::mousePressEvent(QMouseEvent* mouse_event) {
    mouse_x = mouse_event->position().x();
    mouse_y = mouse_event->position().y();
}

void MainWindow::mouseMoveEvent(QMouseEvent* mouse_event) {
    move(
        mouse_event->globalPosition().x() - mouse_x,
        mouse_event->globalPosition().y() - mouse_y
    );
}

void MainWindow::hide_window() {
    hide_action->setVisible(false);
    show_action->setVisible(true);
    hide();
}

void MainWindow::show_window() {
    hide_action->setVisible(true);
    show_action->setVisible(false);
    show();
}

void MainWindow::quit_app() { quit(); }