#include <QStyle>

#include "ItemView.h"
#include "ItemData.h"
#include "ItemViewEditor.h"

/*
* This is nice for simplicity and showing the main point here, but it is bad
* under real circumstances (i.e. instantiating static instances like this in order to avoid passing the dependencies).
*/
namespace Private
{
    static ItemViewEditor* CURRENT_INSTANCE = nullptr;
}

ItemViewEditor::ItemViewEditor(const ItemViewFieldData& fieldData)
    : m_fieldData(fieldData)
    , m_currentItemView(nullptr)
    , m_currentModel(nullptr)
{
    Private::CURRENT_INSTANCE = this;

    SetupConnections();
}

ItemViewEditor::~ItemViewEditor()
{
    Private::CURRENT_INSTANCE = nullptr;
}

ItemViewEditor& ItemViewEditor::GetInstance()
{
    return *Private::CURRENT_INSTANCE;
}

void ItemViewEditor::EditItemView(ItemView* itemView, ItemData* model)
{
    if (m_currentItemView == itemView && m_currentModel == model)
        return; // Already under edit, thus nothing needs to be done.

    SetActive(false);
    m_currentItemView = itemView;
    m_currentModel = model;
    SetActive(true);

    // Setting current values to the editor fields.
    m_fieldData.m_titleField.setText(m_currentModel->m_title);
    m_fieldData.m_colorField.setText(m_currentModel->m_colorCode);
    m_fieldData.m_bodyField.setPlainText(m_currentModel->m_body);
}

void ItemViewEditor::SetupConnections()
{
    /*
     *  Normally, such connections would be made generic as possible, and would go to the implementation of some pattern (e.g. MVVM)
     */
    QObject::connect(&m_fieldData.m_titleField, &QLineEdit::textChanged, [this](const QString& text)
    {
        if (!m_currentItemView || !m_currentModel)
            return;

        m_currentModel->m_title = text;
        m_currentItemView->BindTo(*m_currentModel);
    });

    QObject::connect(&m_fieldData.m_bodyField, &QPlainTextEdit::textChanged, [this]
    {
        if (!m_currentItemView || !m_currentModel)
            return;

        m_currentModel->m_body = m_fieldData.m_bodyField.toPlainText();
        m_currentItemView->BindTo(*m_currentModel);
    });

    QObject::connect(&m_fieldData.m_colorField, &QLineEdit::textChanged, [this](const QString& text)
    {
        if (!m_currentItemView || !m_currentModel)
            return;

        m_currentModel->m_colorCode = text;
        m_currentItemView->BindTo(*m_currentModel);
    });
}

void ItemViewEditor::SetActive(bool active)
{
    if (!m_currentItemView)
        return;

    auto container = m_currentItemView->findChild<QWidget*>("container");
    container->setProperty("active", active);

    /*
     * According to:
     * https://wiki.qt.io/Dynamic_Properties_and_Stylesheets
     */
    container->style()->unpolish(container);
    container->style()->polish(container);
}
