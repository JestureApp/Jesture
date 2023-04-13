#ifndef JESTURE_COMPONENTS_SIDEBAR_H
#define JESTURE_COMPONENTS_SIDEBAR_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <list>

namespace jesture {

class SidebarItem : public QPushButton {
    Q_OBJECT
   public:
    SidebarItem(const QIcon& icon, QString name, QWidget* parent = nullptr);
    QString get_name();

   public slots:
    void setLabelVisible(bool visible);

   protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

   private:
    QString name;
};

class Sidebar : public QWidget {
    Q_OBJECT
   public:
    explicit Sidebar(QWidget* parent = nullptr);

    SidebarItem* create_item(const QIcon& icon, QString name);

   public slots:
    void reveal();
    void hide();
    void setExpanded(bool expanded);
    void handle_radio_buttons();

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