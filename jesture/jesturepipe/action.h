#ifndef JESTURE_JESTUREPIPE_ACTION_H
#define JESTURE_JESTUREPIPE_ACTION_H

#include <QKeySequence>

#include "jesturepipe/actions/action.h"

namespace jesture {

actions::action::KeySequence keySequenceFromQt(QKeySequence keys);

typedef struct Action {
    jesturepipe::Action pipeline_action;
    QKeySequence sequence;
} Action;

Action NoOp();

Action MouseClick(int mouse_button);

Action MousePress(int mouse_button);

Action MouseRelease(int mouse_button);

Action Keystroke(const QKeySequence &keys);

Action KeysPress(const QKeySequence &keys);

Action KeysRelease(const QKeySequence &keys);

typedef struct ActionsList {
    std::vector<Action> action_list;
    jesturepipe::CursorControl cursor_control;
} ActionsList;

}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_ACTION_H