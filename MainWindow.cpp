#include "DataManager.h"
#include "ItemViewEditor.h"
#include "Util.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow())
{
    m_ui->setupUi(this);

    /*
     * First, we are going to create some items.
     * 1000 of them is pretty much to demonstrate a need for efficient solutions.
    */
    const quint32 numberOfItems = 1000;

    // Then, we generate all of the data.
    std::vector<ItemData> data;
    for (quint32 id = 1; id <= numberOfItems; id++) {
        // Set title, description, and random color code.
        const QString title = "Title of an item identified by ID=" + QString::number(id);
        const QString description = "Description of an item identified by ID=" + QString::number(id);
        const QString colorCode = "#" + Util::GetRandomHex(6);

        data.push_back(ItemData(id, title, description, colorCode));
    }

    // Instantiating the creator that is responsible to create all of the data needed.
    m_editor.reset(new ItemViewEditor(
        ItemViewFieldData(
            *m_ui->titleEdit, // Reference to title field of an item being currently edited.
            *m_ui->colorEdit, // Reference to color code field of an item being currently edited.
            *m_ui->descriptionEdit // Reference to description field of an item being currently edited.
        )
    ));

    m_manager.reset(
        new DataManager(
            *m_ui->items, // Container where the item views representing the data are going to be shown.
            *m_ui->scrollArea, // Reference to the scroll area which is being used to calculate properties required for CRUD API.
            data // Data representing all the items we are going to show.
        )
    );
}

MainWindow::~MainWindow()
{
}
