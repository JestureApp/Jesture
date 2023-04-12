#ifndef JESTURE_JESTUREPIPE_ACTION_H
#define JESTURE_JESTUREPIPE_ACTION_H

#include <QKeySequence>
#include <list>

#include "jesturepipe/actions/action.h"

namespace jesture {

typedef struct Action {
    jesturepipe::Action pipeline_action;
    QKeySequence sequence;
} Action;

typedef struct ActionsList {
    std::list<Action> action_list;
    jesturepipe::CursorControl cursor_control;
} ActionsList;

}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_ACTION_H