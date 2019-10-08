#pragma once
#include <QLineEdit>
#include <QPlainTextEdit>

struct ItemViewFieldData
{
    ItemViewFieldData(QLineEdit& titleField, QLineEdit& colorField, QPlainTextEdit& bodyField);

    QLineEdit& m_titleField;
    QLineEdit& m_colorField;
    QPlainTextEdit& m_bodyField;
};
