#ifndef JESTURE_COMPONENTS_SIDEBAR_H
#define JESTURE_COMPONENTS_SIDEBAR_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <list>

namespace jesture {

class SidebarItem : public QWidget {
    Q_OBJECT
   public:
    SidebarItem(const QIcon& icon, QString name,
                QSize button_size = QSize(32, 32), QWidget* parent = nullptr);

   public slots:
    void setLabelVisible(bool visible);

   protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

   private:
    QLabel* icon_label;
    QLabel* label;
};

class Sidebar : public QWidget {
    Q_OBJECT
   public:
    explicit Sidebar(QWidget* parent = nullptr);

    QObject* createItem(const QIcon& icon, QString name);

   public slots:
    void reveal();
    void hide();
    void setExpanded(bool expanded);

   protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

   private:
    static constexpr int button_size = 32;

    bool expanded;
    QVBoxLayout* layout;
    std::list<SidebarItem*> items;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_SIDEBAR_H