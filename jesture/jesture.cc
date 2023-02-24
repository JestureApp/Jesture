#include <QtCore/QList>
#include <QtCore/QString>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

#include <QtGui/QAction>

#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraDevice>
#include <QtMultimedia/QMediaDevices>
#include <QtMultimediaWidgets/QGraphicsVideoItem>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        /*QScrollArea* scroll_area = new QScrollArea;
        scroll_area->setFrameShape(QFrame::NoFrame);
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 20px;}");
        scroll_area->setWidget(content);
        
        QVBoxLayout* scroll_area_layout = new QVBoxLayout;
        scroll_area_layout->setContentsMargins(0, 0, 0, 0);
        scroll_area_layout->addWidget(scroll_area);
        
        setLayout(scroll_area_layout);*/
        
        // Create a top-level stack layout--only one child widget will be shown at a time
        auto stack = new QWidget(this);
        auto stack_layout = new QStackedLayout(stack);
        
        // Create main camera view
        auto main = new QWidget(stack);
        auto main_layout = new QVBoxLayout(main);
        main->setLayout(main_layout);
        
        // Add a test label to the main camera view
        auto test_label = new QLabel("test", main);
        
        // Create settings menu in a form layout
        auto settings = new QWidget(stack);
        settings->setStyleSheet("font-size: 20pt");
        auto form = new QFormLayout(settings);
        settings->setLayout(form);
        
        // Back button
        auto back_from_settings = new QPushButton("Back", settings);
        form->addRow(back_from_settings);
        
        // Form title
        auto title = new QLabel("Settings", settings);
        title->setStyleSheet("font-weight: bold; font-size: 24pt");
        form->addRow(title);
        
        // Accuracy setting, using a slider
        auto accuracy_slider = new QSlider(Qt::Horizontal, settings);
        auto accuracy_description = new QLabel("This is a description of the accuracy setting.", settings);
        accuracy_description->setStyleSheet("font-weight: 200; font-size: 16pt");
        form->addRow("Accuracy", accuracy_slider);
        form->addRow(accuracy_description);
        
        // Camera setting, using a dropdown box
        auto camera_selector = new QComboBox(settings);
        const auto cameras = QMediaDevices::videoInputs();
        QList<QString> camera_descriptions;
        for (const auto &camera : cameras) {
            camera_descriptions.append(camera.description());
        }
        camera_selector->addItems(camera_descriptions);
        auto camera_description = new QLabel("This is a description of the camera setting.", settings);
        camera_description->setStyleSheet("font-weight: 200; font-size: 16pt");
        form->addRow("Camera", camera_selector);
        form->addRow(camera_description);
        
        // Add screens to stack
        stack_layout->addWidget(settings);
        stack_layout->addWidget(main);
        stack->setLayout(stack_layout);
        
        auto system_tray = new QSystemTrayIcon(this);
        auto system_tray_menu = new QMenu(this);
        system_tray_menu->addAction("Hide");
        system_tray->setContextMenu(system_tray_menu);
        
        // Display window
        setCentralWidget(stack);
        setWindowTitle("Jesture");
    }
private:
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("Jesture");
    app.setOrganizationName("jesture");
    
    /* Notes for later:
    QApplication::setWindowIcon(QIcon(":/some_path.ui.ico"));
    QApplication::setOrganizationDomain("jesture");
    QFile stylesheet(":/some_path.ui.qss");
    
    if(!stylesheet.open(QIDevice::ReadOnly)) {
        qWarning("Unable to open stylesheet!");
    } else {
        app.setStyleSheet(stylesheet.readAll());
    }
    */
    
    MainWindow* window = new MainWindow();
    window->resize(1280, 720);
    window->show();
    
    return app.exec();
}