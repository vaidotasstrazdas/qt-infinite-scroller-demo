#pragma once
#include <memory>

#include <QWidget>

#include "ItemData.h"
#include "ItemViewFieldData.h"

namespace Ui
{
    class ItemView;
}

/*
* This is the class representing Item Data View we are going to show in large amounts.
*/
class ItemView
        : public QWidget
{
        Q_OBJECT
    public:
        ItemView(QWidget* parent = nullptr);
        virtual ~ItemView();

        /*
         * This method is one of the most important ones.
         * Efficient data representation must rely on limited amount of views whose construction is pricy.
         * However, creation of the data is not that pricy, thus we should try to reuse as much views as possible.
         * In order to do so, we must support a way to bind models to the same instance of a view.
         * This is the reason why the BindTo(...) is introduced, and the signature for it is such.
        */
        void BindTo(ItemData& data);

    protected:
        /*
         * I am enabling editing of the item in case user double clicks on the item. Different approaches also can be used.
         *
         */
        virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

    private:
        std::unique_ptr<Ui::ItemView> m_ui;
        ItemData* m_currentData;
};
