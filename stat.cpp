#include "stat.h"
#include <QDebug>
#include <algorithm>
using namespace  std;
Stat::Stat()
{



}
QChartView * Stat::Preparechart()
{
    QSqlQuery query;
    QMap<QString, int> countMap;

    if (query.exec("SELECT type FROM service")) {
        while (query.next()) {
            QString type = query.value(0).toString();
            countMap[type]++;
        }
    }

    QPieSeries* series = new QPieSeries();
    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelOutside);

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        QPieSlice* slice = series->append(label, it.value());
        slice->setLabelVisible();
    }


    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Les types de service");
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart::ChartTheme theme = QChart::ChartThemeBlueIcy;
    chartView->chart()->setTheme(theme);

    return chartView;
    }



