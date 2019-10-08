#pragma once
#include <memory>

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class DataManager;
class ItemViewEditor;

class MainWindow
        : public QMainWindow
{
        Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        virtual ~MainWindow();

    private:
        std::unique_ptr<Ui::MainWindow> m_ui;
        std::unique_ptr<DataManager> m_manager;
        std::unique_ptr<ItemViewEditor> m_editor;
};
