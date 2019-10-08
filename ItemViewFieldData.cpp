#include "ItemViewFieldData.h"

ItemViewFieldData::ItemViewFieldData(QLineEdit& titleField, QLineEdit& colorField, QPlainTextEdit& bodyField)
    : m_titleField(titleField)
    , m_colorField(colorField)
    , m_bodyField(bodyField)
{
}
