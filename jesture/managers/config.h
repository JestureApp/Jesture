#ifndef JESTURE_MANAGERS_CONFIG_H
#define JESTURE_MANAGERS_CONFIG_H

#include <QObject>

namespace jesture {

class Config : public QObject {
    Q_OBJECT

   public:
    Config(QObject *parent = nullptr);

   public slots:
    void load();
    void save();
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CONFIG_H