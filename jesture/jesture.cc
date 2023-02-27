#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>
#include "main_window.h"
#include "config_manager.h"

/*
        Notes
        QScrollArea* scroll_area = new QScrollArea;
        scroll_area->setFrameShape(QFrame::NoFrame);
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->verticalScrollBar()->setStyleSheet("QScrollBar:vertical
        {width: 20px;}"); scroll_area->setWidget(content);

        QVBoxLayout* scroll_area_layout = new QVBoxLayout;
        scroll_area_layout->setContentsMargins(0, 0, 0, 0);
        scroll_area_layout->addWidget(scroll_area);

        setLayout(scroll_area_layout);
*/

int main(int argc, char **argv) {
    //Q_INIT_RESOURCE(systray);
    
    QApplication app(argc, argv);
    app.setApplicationName("Jesture");
    
    auto app_icon = new QIcon("icons/settings.svg");
    app.setWindowIcon(*app_icon);
    
    auto config_manager = new ConfigManager();
    config_manager->connect(&app, &QApplication::aboutToQuit, config_manager, &ConfigManager::save);
    
    auto window = new MainWindow();
    window->connect(window, &MainWindow::quit, &app, &QApplication::quit);
    window->resize(1280, 720);
    window->show();
    
    return app.exec();
}