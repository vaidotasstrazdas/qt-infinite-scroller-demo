#include "ItemView.h"
#include "ItemViewEditor.h"
#include "ui_ItemView.h"

ItemView::ItemView(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ItemView())
    , m_currentData(nullptr)
{
    m_ui->setupUi(this);
}

ItemView::~ItemView()
{
}

void ItemView::BindTo(ItemData& data)
{
    // For some manipulations, having pointer to the current data might be required.
    m_currentData = &data;

    /*
     * Binding is pretty simple here actually.
     * We just set the data, and that is it.
     * In more advanced implementations, this binding would be implemented probably through usage of some pattern (e.g. MVVM).
     * However, I am not goint to implement even a subset of MVVM in order to keep things as simple as possible, and be able to get to the main point.
    */
    m_ui->titleLabel->setText(data.m_title);
    m_ui->bodyLabel->setText(data.m_body);
    m_ui->container->setStyleSheet("#container{background-color:" + data.m_colorCode + "}");
}

void ItemView::mouseDoubleClickEvent(QMouseEvent* event)
{
    // We have no reason to avoid default behavior here, thus calling a base method.
    QWidget::mouseDoubleClickEvent(event);

    // Just move the item and its' current view model to the editor.
    ItemViewEditor::GetInstance().EditItemView(this, m_currentData);
}

