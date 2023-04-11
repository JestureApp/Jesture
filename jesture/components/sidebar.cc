#include "jesture/components/sidebar.h"

#include <QHBoxLayout>

namespace jesture {
Sidebar::Sidebar(QWidget* parent) : QWidget(parent), expanded(false) {
    setObjectName("sidebar");

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    // layout->setContentsMargins(0, 0, 0, 0);
}

void Sidebar::reveal() { setExpanded(true); }

void Sidebar::hide() { setExpanded(false); }

void Sidebar::setExpanded(bool expanded) {
    if (this->expanded == expanded) return;

    for (auto item : items) {
        item->setLabelVisible(expanded);
    }

    this->expanded = expanded;
}

QObject* Sidebar::createItem(const QIcon& icon, QString name) {
    auto item = new SidebarItem(icon, name);
    layout->addWidget(item);

    items.push_back(item);

    return item;
}

void Sidebar::enterEvent(QEnterEvent* event) {
    setExpanded(true);

    QWidget::enterEvent(event);
}

void Sidebar::leaveEvent(QEvent* event) {
    setExpanded(false);

    QWidget::leaveEvent(event);
}

SidebarItem::SidebarItem(const QIcon& icon, QString name, QWidget* parent)
    : QPushButton(icon, "", parent), name(name) {}

void SidebarItem::setLabelVisible(bool visible) {
    if (visible)
        setText(name);
    else
        setText("");
}

void SidebarItem::enterEvent(QEnterEvent* event) {
    // TODO
    QPushButton::enterEvent(event);
}

void SidebarItem::leaveEvent(QEvent* event) {
    // TODO
    QPushButton::leaveEvent(event);
}

}  // namespace jesture