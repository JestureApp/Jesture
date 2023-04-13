#include "jesture/jesturepipe/action.h"

namespace jesture {

actions::action::KeySequence keySequenceFromQt(QKeySequence keys) {
    std::string to_string = keys.toString().toStdString();

    auto sequence = actions::action::ParseKeystroke(to_string);

    if (!sequence.ok()) {
        qFatal("Failed to parse key sequence %s: %s",
               keys.toString(QKeySequence::PortableText).toStdString().c_str(),
               sequence.status().ToString().c_str());
    }

    return sequence.value();
}

Action NoOp() {
    return Action{.pipeline_action = actions::action::NoOp(),
                  .sequence = QKeySequence()};
}

Action MouseClick(int mouse_button) {
    actions::action::MouseClick pipeline_action;
    if (mouse_button == 0) {
        pipeline_action = actions::action::MouseClick::LeftClick;
    } else if (mouse_button == 1) {
        pipeline_action = actions::action::MouseClick::MiddleClick;
    } else {
        pipeline_action = actions::action::MouseClick::RightClick;
    }
    return Action{pipeline_action, .sequence = QKeySequence()};
}

Action MousePress(int mouse_button) {
    actions::action::MousePress pipeline_action;
    if (mouse_button == 0) {
        pipeline_action = actions::action::MousePress::LeftPress;
    } else if (mouse_button == 1) {
        pipeline_action = actions::action::MousePress::MiddlePress;
    } else {
        pipeline_action = actions::action::MousePress::RightPress;
    }
    return Action{pipeline_action, .sequence = QKeySequence()};
}

Action MouseRelease(int mouse_button) {
    actions::action::MouseRelease pipeline_action;
    if (mouse_button == 0) {
        pipeline_action = actions::action::MouseRelease::LeftRelease;
    } else if (mouse_button == 1) {
        pipeline_action = actions::action::MouseRelease::MiddleRelease;
    } else {
        pipeline_action = actions::action::MouseRelease::RightRelease;
    }
    return Action{pipeline_action, .sequence = QKeySequence()};
}

Action Keystroke(const QKeySequence &keys) {
    return Action{
        .pipeline_action = actions::action::Keystroke{keySequenceFromQt(keys)},
        .sequence = keys};
}

Action KeysPress(const QKeySequence &keys) {
    return Action{
        .pipeline_action = actions::action::KeysPress{keySequenceFromQt(keys)},
        .sequence = keys};
}

Action KeysRelease(const QKeySequence &keys) {
    return Action{.pipeline_action =
                      actions::action::KeysRelease{keySequenceFromQt(keys)},
                  .sequence = keys};
}

}  // namespace jesture