#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

#include "DataManager.h"
#include "ItemView.h"

/*
* First, I would like to explain every argument is for:
* 1) 'container' is for the item views to be kept.
* 2) 'scrollArea' is used in order to detect indices of a models that we are going to bind to the limited amount of views created.
* 3) 'data' is just to show something and demonstrate possible efficiency of this.
*/
DataManager::DataManager(QWidget& container, QScrollArea& scrollArea, const std::vector<ItemData>& data)
    : m_container(container)
    , m_scrollArea(scrollArea)
    , m_data(data)
    , m_dataLayout(nullptr)
    , m_fillerTop(nullptr)
    , m_fillerBottom(nullptr)
    , m_heightResolved(0)
{
    // This method sets up the layout to become like recycler view on Android.
    SetLayout();

    // We set the limited amount of views in the container created through SetLayout.
    SetViews();

    // Finally, we initialize simulation of infinite scrolling.
    ConnectToScrolling();
}

DataManager::~DataManager()
{
}

void DataManager::SetLayout()
{
    /*
     * Top and bottom fillers are being used to simulate scrolling through the infinite amount of items.
     * In other words, amount of items is VERY limited actually (limited to the screen size of a device being used).
     * However, using Qt it is possible to simulate infinite amount of items.
     */
    m_fillerTop = new QWidget();
    m_fillerBottom = new QWidget();

    // Setting zero heights.
    m_fillerTop->setFixedHeight(0);
    m_fillerBottom->setFixedHeight(0);

    /*
    * The layout has the following structure (and it is vertical):
    * 1) TOP FILLER
    * 2) CONTAINER for the views.
    * 3) Bottom FILLER.
    */
    auto mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Container for the views.
    auto container = new QWidget();
    m_dataLayout = new QVBoxLayout();
    m_dataLayout->setContentsMargins(0, 0, 0, 0);
    m_dataLayout->setSpacing(0);
    container->setLayout(m_dataLayout);

    // Finalize the layout introduced.
    mainLayout->addWidget(m_fillerTop);
    mainLayout->addWidget(container);
    mainLayout->addWidget(m_fillerBottom);

    m_container.setLayout(mainLayout);
}

void DataManager::SetViews()
{
    // Under real implementations, this height would calculated based on the screen size of the device.
    // For simplicy, let it be 628. Why? Because rounded PI * 100 * 2 = 628. :)
    auto heightLimit = 628;

    // Adding all the views needed.
    while (heightLimit > 0)
    {
        auto itemView = new ItemView();

        /*
        * One of the most important assumptions for the infinite scrolling to work:
        * DIMENSIONS OF THE VIEW MUST BE FIXED. In this case, it is required for the height to be fixed at least. This is because
        * layout is vertical. However, in flow one both width and height would have to be fixed. The reason for that is that it would be
        * impossible to resolve correct height required e.g. in the middle of the view, and total size of the container would be unresolvable.
        */
        m_heightResolved = itemView->height();

        m_dataLayout->addWidget(itemView);
        heightLimit -= m_heightResolved;
    }
}

void DataManager::CalculateMetrics()
{
    /*
     * Knowing the height of item view, and size of the data,
     * it is pretty easy to know how much height the data should fill in.
    */
    const auto totalHeightNeeded = m_heightResolved * static_cast<int>(m_data.size());

    /*
     * And recycled height is the one which is actually filled in by the created limited
     * amount of items.
     */
    const auto recycledHeight = m_heightResolved * m_dataLayout->count();

    /*
     * This needs more explanation:
     * 1) In order to simulate scrolling happening, we should ensure that top filler would not get height equal to the value of the scrollbar.
     *    If it would, then it would look that no scrolling is happening in the container, i.e. everything (except for the scrollbar) would
     *    look static. This is not the case we want to have.
     * 2) So, by integer division we ensure that at least first item would be actually scrolled down. When the scrollbar value becomes equal
     *    to the height of item view, then we increase top filler height to that size, and we do the same discrete operations again by increasing
     *    the height to 2 heights, 3 heights, and so on.
    */
    auto topFillerHeight = m_scrollArea.verticalScrollBar()->value() / m_heightResolved * m_heightResolved;

    // Bottom filler height is the height that is left subtracted from total, recycled and top filler.
    auto bottomFillerHeight = totalHeightNeeded - recycledHeight - topFillerHeight;

    // It can become zero in case the scrolling is going to the end, but we can not set negative heights, thus zeroing it.
    if (bottomFillerHeight < 0)
        bottomFillerHeight = 0;

    /*
     * And finally, through the same value of scrollbar, we deduce the start index of a model we are going
     * to bind to the first visible item view.
     */
    auto startIndex = m_scrollArea.verticalScrollBar()->value() / m_heightResolved;

    /*
     * This condition means that we are checking if scrolling know is in the recycled area. If this is the case,
     * we need to set maximum amount of top filler height which is possible (otherwise, scroll bar value would increase and increase,
     * and we would never reach the end).
    */
    if (topFillerHeight >= totalHeightNeeded - recycledHeight)
    {
        // If condition is satisfied, we set maximum top filler height, and bottom filler clearly has to have 0 height in this case.
        topFillerHeight = totalHeightNeeded - recycledHeight;
        bottomFillerHeight = 0;

        // Also, start index should be adjusted to the fact that we are reaching the end now.
        startIndex = static_cast<int>(m_data.size()) - recycledHeight / m_heightResolved;
    }

    // This is the easiest part to understand probably.
    m_fillerTop->setFixedHeight(topFillerHeight);
    m_fillerBottom->setFixedHeight(bottomFillerHeight);

    /*
     * This is one of the most important, but also one of the easiest parts.
     * This loop iterates through the widgets in the layout created.
     */
    for (int i = 0; i < m_dataLayout->count(); i++)
    {
        /*
         * First, we take the ItemView from layout. We know the type here, thus we cast to it.
         * However, generic solution would not be that simple.
         */
        auto itemView = static_cast<ItemView*>(m_dataLayout->itemAt(i)->widget());

        // Finally, we call the binding method which binds the current data to our layout.
        itemView->BindTo(m_data[static_cast<size_t>(i + startIndex)]);
    }
}

void DataManager::ConnectToScrolling()
{
    // This is where the magic starts to happen.
    CalculateMetrics();

    // We need to simulate infinite scrolling on vertical scroll bar being moved, thus connecting to this signal.
    QObject::connect(m_scrollArea.verticalScrollBar(), &QScrollBar::valueChanged, [this]
    {
        // And this is where magic happens.
        CalculateMetrics();
    });
}
