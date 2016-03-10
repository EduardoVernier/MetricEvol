#include "metricextractor.h"

MetricExtractor::MetricExtractor()
{

}

QString MetricExtractor::run_metrics()
{
    QString project_folder_path = "/home/eduardo/Desktop/MetricEvol/build-MetricEvol-Desktop-Debug/source_files/";
    QString metrics_output_file = "/home/eduardo/Desktop/MetricEvol/build-MetricEvol-Desktop-Debug/metrics/m" + QString::number(counter) + ".csv";

    QString cmd = "cd /home/eduardo/Documents/scitools/bin/linux64/; "
                  "/usr/bin/time -f \"%e\" sh -c './und create -db newDatabase.udb -languages java add " + project_folder_path +
                  " settings -metrics all settings -metricsOutputFile " + metrics_output_file +
                  " analyze metrics > log.txt; ' 2>&1 ";
    QString time = exec(cmd);
    time.remove(QChar('\n'), Qt::CaseInsensitive);
    time.remove(QChar('"'), Qt::CaseInsensitive);

    QFile file("./metrics/times.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return "error opening times file"; // fix later

    QTextStream out(&file);
    out << counter << ": " << time << "\n";
    counter++;

    return time;
}

QString MetricExtractor::exec(QString cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd.toUtf8(), "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    QString result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}
