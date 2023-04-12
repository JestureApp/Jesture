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