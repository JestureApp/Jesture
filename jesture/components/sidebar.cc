#include "jesture/components/sidebar.h"

#include <QHBoxLayout>
#include <iostream>

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

SidebarItem* Sidebar::create_item(const QIcon& icon, QString name) {
    auto item = new SidebarItem(icon, name);
    layout->addWidget(item);

    if (items.size() == 0) {
        item->setEnabled(false);
    }

    item->connect(item, &SidebarItem::clicked, this,
                  &Sidebar::handle_radio_buttons);

    items.push_back(item);

    return item;
}

void Sidebar::handle_radio_buttons() {
    for (auto item : this->items) {
        item->setEnabled(true);
    }

    SidebarItem* item = qobject_cast<SidebarItem*>(sender());
    item->setEnabled(false);
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

QString SidebarItem::get_name() { return QString(this->name); }

}  // namespace jesture