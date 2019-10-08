#pragma once
#include <QString>

/*
* This struct represents the data we are going to show in pretty large amount, and edit items one by one.
*/
struct ItemData
{
    ItemData();
    ItemData(quint64 id, const QString& title, const QString& body, const QString& colorCode);

    quint64 m_id;
    QString m_title;
    QString m_body;
    QString m_colorCode;
};
