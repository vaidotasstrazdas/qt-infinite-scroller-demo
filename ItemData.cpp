#include "ItemData.h"

ItemData::ItemData()
    : ItemData(0, "", "", "")
{
}

ItemData::ItemData(quint64 id, const QString& title, const QString& body, const QString& colorCode)
    : m_id(id)
    , m_title(title)
    , m_body(body)
    , m_colorCode(colorCode)
{
}
