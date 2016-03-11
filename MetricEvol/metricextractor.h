#ifndef METRICEXTRACTOR_H
#define METRICEXTRACTOR_H

#include <iostream>
#include <cstdio>
#include <memory>
#include <QString>
#include <QFile>
#include <QTextStream>

class MetricExtractor
{
public:
    MetricExtractor();
    QString run_metrics();

private:
    QString exec(QString cmd);
    int counter = 0; // Counts number extractions
};

#endif // METRICEXTRACTOR_H
