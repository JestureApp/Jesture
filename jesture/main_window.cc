#include <QtCore/QString>
#include <QtCore/QList>
#include <QtWidgets/QMenu>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QComboBox>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QMediaDevices>

#include "main_window.h"

MainWindow::MainWindow() {
    // Create the parent widget
    auto content = new QWidget(this);
    auto content_layout = new QStackedLayout(content);
    content_layout->setStackingMode(QStackedLayout::StackAll);
    content->setLayout(content_layout);
    setCentralWidget(content);
    
    // Placeholder for camera feed
    auto test_label = new QLabel("This is Jesture!", content);
    content_layout->addWidget(test_label);
    
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
    if (QSystemTrayIcon::isSystemTrayAvailable())
        setup_system_tray();
    
    setWindowTitle("Jesture");
}

void MainWindow::setup_general() {
    // Create menu and add to interactive menus parent
    general = new QWidget(interactives);
    interactives_layout->addWidget(general);
    
    // Create layout
    auto layout = new QHBoxLayout(general);
    general->setLayout(layout);
    
    // Get icons
    auto settings_icon = new QIcon("icons/settings.svg");
    auto inspector_icon = new QIcon("icons/add_element.svg");
    
    // Create buttons
    auto settings_button = new QPushButton(*settings_icon, "Settings", general);
    auto inspector_button = new QPushButton(*inspector_icon, "Gesture Inspector", general);
    
    connect(settings_button, &QPushButton::released, this, &MainWindow::open_settings);
    connect(inspector_button, &QPushButton::released, this, &MainWindow::open_inspector);
    
    // Add to layout
    layout->addWidget(settings_button);
    layout->addWidget(inspector_button);
}

void MainWindow::setup_settings() {
    // Create menu and add to interactive menus parent
    settings = new QWidget(interactives);
    interactives_layout->addWidget(settings);
    
    // Create layout
    auto layout = new QFormLayout();
    settings->setLayout(layout);
    
    // Top level styles
    settings->setStyleSheet("font-size: 20pt");
    
    auto title = new QLabel("Settings", settings);
    title->setStyleSheet("font-weight: bold; font-size: 24pt");
    layout->addRow(title);

    // Accuracy setting, using a slider
    auto accuracy_slider = new QSlider(Qt::Horizontal, settings);
    auto accuracy_description = new QLabel(
        "This is a description of the accuracy setting.", settings);
    accuracy_description->setStyleSheet(
        "font-weight: 200; font-size: 16pt");
    layout->addRow("Accuracy", accuracy_slider);
    layout->addRow(accuracy_description);
    
    // Camera setting, using a dropdown box
    auto camera_selector = new QComboBox(settings);
    const auto cameras = QMediaDevices::videoInputs();
    QList<QString> camera_descriptions;
    for (const auto &camera : cameras)
        camera_descriptions.append(camera.description());
    camera_selector->addItems(camera_descriptions);
    auto camera_description = new QLabel(
        "This is a description of the camera setting.", settings);
    camera_description->setStyleSheet("font-weight: 200; font-size: 16pt");
    layout->addRow("Camera", camera_selector);
    layout->addRow(camera_description);
}

void MainWindow::setup_inspector() {
    
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
    connect(hide_action, &QAction::triggered, this, &MainWindow::hide_from_tray);
    connect(show_action, &QAction::triggered, this, &MainWindow::show_from_tray);
    connect(quit_action, &QAction::triggered, this, &MainWindow::quit_from_tray);
    
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

void MainWindow::open_settings() {
    interactives_layout->setCurrentWidget(settings);
}

void MainWindow::close_settings() {
    interactives_layout->setCurrentWidget(general);
}

void MainWindow::open_inspector() {
    interactives_layout->setCurrentWidget(inspector);
}

void MainWindow::close_inspector() {
    interactives_layout->setCurrentWidget(general);
}

void MainWindow::inspect_gesture(int index) {
    
}

void MainWindow::hide_from_tray() {
    hide_action->setVisible(false);
    show_action->setVisible(true);
    hide();
}

void MainWindow::show_from_tray() {
    hide_action->setVisible(true);
    show_action->setVisible(false);
    show();
}

void MainWindow::quit_from_tray() {
    quit();
}