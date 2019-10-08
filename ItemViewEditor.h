#pragma once
#include <memory>

#include "ItemViewFieldData.h"

struct ItemData;
class ItemView;

/*
* This represents item editor.
*/
class ItemViewEditor
{
    public:
        ItemViewEditor(const ItemViewFieldData& fieldData);
        ~ItemViewEditor();

        static ItemViewEditor& GetInstance();

        void EditItemView(ItemView* itemView, ItemData* model);

    private:
        void SetupConnections();
        void SetActive(bool active);

    private:
        ItemViewFieldData m_fieldData;
        ItemView* m_currentItemView;
        ItemData* m_currentModel;
};
