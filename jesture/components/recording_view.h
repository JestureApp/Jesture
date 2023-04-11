#ifndef JESTURE_COMPONENTS_RECORDING_VIEW_H
#define JESTURE_COMPONENTS_RECORDING_VIEW_H

#include <QWidget>

namespace jesture {

class RecordingView : public QWidget {
    Q_OBJECT
   public:
    explicit RecordingView(QWidget* parent = nullptr);

   private:
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_RECORDING_VIEW_H