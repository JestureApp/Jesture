#include "jesture/components/recording_review.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

namespace jesture {
RecordingReview::RecordingReview(QWidget* parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);

    visualization = new GestureVisualization(this);
    auto prompt = new QLabel("Is this the gesture you wanted?", this);
    auto accept_button = new QPushButton("Accept", this);
    auto reject_button = new QPushButton("Cancel", this);

    prompt->setWordWrap(true);

    layout->addWidget(visualization);
    layout->addWidget(prompt);
    layout->addWidget(accept_button);
    layout->addWidget(reject_button);

    connect(accept_button, &QPushButton::released, this,
            &RecordingReview::save);
    connect(reject_button, &QPushButton::released, this,
            &RecordingReview::cancel);
}

void RecordingReview::set_gesture(jesturepipe::Gesture gesture) {
    std::cout << "Successfully recorded and opened gesture!" << std::endl;
    current_gesture = gesture;
    visualization->set_gesture(gesture);
}

void RecordingReview::save() {
    save_gesture(new Gesture("New Gesture", current_gesture));
}
}  // namespace jesture
