#include "qratingbar.h"

#include <QDebug>
Ratingbar::Ratingbar(int maxRating, QWidget *parent) : QWidget(parent)
{
    QResource::registerResource("/resources.qrc");
    m_maxRating = maxRating;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);

    // Create a set of tool buttons for each rating level
    for (int i = 1; i <= m_maxRating; i++)
    {
        QToolButton *button = new QToolButton(this);
        button->setIcon(QIcon(":/emptystar.png"));
        button->setIconSize(QSize(16, 16));
        button->setCheckable(true); //chaque boutton verifiable
        button->setAutoExclusive(true);// ne soit pas selectionner l buttons ala fois
        button->setFixedSize(QSize(16, 16));
        button->setToolTip(QString("%1").arg(i)); //definit l'info bulle du boutton
        layout->addWidget(button);

        // Connect the button's toggled signal to a slot that will update the rating value
        connect(button, &QToolButton::toggled, [this, i]()
        {

            m_rating=i;
            updateRating();


        });

        m_ratingButtons.append(button); // ajouter ala fin
    }
}

void Ratingbar::updateRating()
{
    for (int i = 0; i < m_maxRating; i++)
    {
        if (i < m_rating)
        {
            m_ratingButtons[i]->setIcon(QIcon(":/filledstar.png"));
        }
        else
        {

            m_ratingButtons[i]->setIcon(QIcon(":/emptystar.png"));
        }
    }

    emit ratingChanged(m_rating); // heritage
}

int Ratingbar::getrating() const
{
    return m_rating;
}

void Ratingbar::setRating(int rating)
{
    if (m_rating != rating)
    {
        m_rating = rating;
        updateRating();
    }
}
