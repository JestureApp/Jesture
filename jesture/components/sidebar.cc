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

SidebarItem::SidebarItem(const QIcon& icon, QString name, QSize button_size,
                         QWidget* parent)
    : QWidget(parent) {
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    icon_label = new QLabel(this);
    icon_label->setPixmap(icon.pixmap(button_size));
    layout->addWidget(icon_label);

    label = new QLabel(name, this);
    label->setVisible(false);
    layout->addWidget(label);
}

void SidebarItem::setLabelVisible(bool visible) { label->setVisible(visible); }

void SidebarItem::enterEvent(QEnterEvent* event) {
    // TODO
    QWidget::enterEvent(event);
}

void SidebarItem::leaveEvent(QEvent* event) {
    // TODO
    QWidget::leaveEvent(event);
}

}  // namespace jesture