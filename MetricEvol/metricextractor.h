#ifndef METRICEXTRACTOR_H
#define METRICEXTRACTOR_H

#include <iostream>
#include <cstdio>
#include <memory>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <string.h>

using namespace std;

class MetricExtractor
{
public:
    MetricExtractor();
		string run_metrics(char *cmt);

private:
    QString exec(QString cmd);
    int counter = 0; // Counts number extractions
};

#endif // METRICEXTRACTOR_H
