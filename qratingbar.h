#ifndef QRATINGBAR_H
#define QRATINGBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QToolButton>
#include <QResource>
class Ratingbar: public QWidget
{
    Q_OBJECT
    private:
        int m_maxRating;
        int m_rating = 0;
        QList<QToolButton*> m_ratingButtons;
        void updateRating();

public:
        Ratingbar(int maxRating, QWidget *parent = nullptr);
           int getrating()const;
           void setRating(int rating);

       signals:
           // Emitted when the rating value changes
           void ratingChanged(int rating);
       };


#endif // QRATINGBAR_H
