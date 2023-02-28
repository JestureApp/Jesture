#include "jesture/components/gesture_editor.h"

#include <QBoxLayout>
#include <QFrame>
#include <QKeySequence>
#include <QPushButton>
#include <QSizePolicy>

namespace jesture {

class RecordButton : public QPushButton {
   public:
    RecordButton(QWidget* parent = nullptr) : QPushButton(parent) {
        setStyleSheet("background-color:red");
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    QSize sizeHint() const override { return QSize{50, 50}; }
};

GestureEditor::GestureEditor(JesturePipeController* controller,
                             QWidget* parent) noexcept
    : QWidget(parent), controller(controller) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    frame_view = new FrameView();
    mainLayout->insertWidget(0, frame_view);

    auto bottom_bar = new QWidget();
    mainLayout->insertWidget(1, bottom_bar);
    bottom_bar->setStyleSheet("background-color:grey");
    bottom_bar->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::Fixed);

    auto bottom_bar_layout = new QHBoxLayout();
    bottom_bar->setLayout(bottom_bar_layout);

    auto record_button = new RecordButton();
    bottom_bar_layout->addWidget(record_button, 0, Qt::AlignLeft);
    record_button->setShortcut(QKeySequence(Qt::Key_Space));

    setLayout(mainLayout);

    QObject::connect(controller, &JesturePipeController::frameReady, frame_view,
                     &FrameView::setFrame);
    QObject::connect(record_button, &QPushButton::clicked, controller,
                     &JesturePipeController::toggleRecording);
};

}  // namespace jesture