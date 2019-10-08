#pragma once
#include <vector>

#include <QScrollArea>
#include <QWidget>

#include "ItemData.h"

/*
* This class is the most important one regarding the management of bigger amounts of data.
*/
class DataManager
{
    public:
        DataManager(QWidget& container, QScrollArea& scrollArea, const std::vector<ItemData>& data);
        ~DataManager();

    private:
        void SetLayout();
        void SetViews();
        void CalculateMetrics();
        void ConnectToScrolling();

    private:
        QWidget& m_container;
        QScrollArea& m_scrollArea;
        std::vector<ItemData> m_data;
        QLayout* m_dataLayout;
        QWidget* m_fillerTop;
        QWidget* m_fillerBottom;
        int m_heightResolved;
};
