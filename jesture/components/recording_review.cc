#include "jesture/components/recording_review.h"

#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>

namespace jesture {
RecordingReview::RecordingReview(QWidget* parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);

    visualization = new GestureVisualization(this);
    auto prompt = new QLabel("Is this the gesture you wanted?", this);
    auto name_input = new QLineEdit(this);
    auto accept_button = new QPushButton("Accept", this);
    auto reject_button = new QPushButton("Cancel", this);

    prompt->setWordWrap(true);
    name_input->setPlaceholderText("Enter a name for the gesture");

    layout->addWidget(visualization);
    layout->addWidget(prompt);
    layout->addWidget(name_input);
    layout->addWidget(accept_button);
    layout->addWidget(reject_button);

    auto accept_shortcut =
        new QShortcut(QKeySequence::InsertParagraphSeparator, this);
    auto reject_shortcut = new QShortcut(QKeySequence::Cancel, this);
    connect(accept_button, &QPushButton::released, this,
            &RecordingReview::save);
    connect(accept_shortcut, &QShortcut::activated, this,
            &RecordingReview::save);
    connect(reject_button, &QPushButton::released, this,
            &RecordingReview::cancel);
    connect(reject_shortcut, &QShortcut::activatedAmbiguously, this,
            &RecordingReview::cancel);
    connect(name_input, &QLineEdit::textChanged, this,
            &RecordingReview::name_change);
}

void RecordingReview::set_gesture(jesturepipe::Gesture gesture) {
    name = "";
    current_gesture = gesture;
    visualization->set_gesture(gesture);
}

void RecordingReview::save() {
    if (name == "") name = "New Gesture";
    save_gesture(Gesture(name, current_gesture));
}

void RecordingReview::name_change(const QString& text) {
    name = text.toStdString();
}
}  // namespace jesture
