#include "metricextractor.h"
#include <stdlib.h>

MetricExtractor::MetricExtractor()
{
    // Remove timing file from last metric extraction
    QFile::remove("./metrics/times.txt");
}

string MetricExtractor::run_metrics(char * cmt)
{
    // Folder being analysed - where only source files from a given version live
    QString project_folder_path = "/home/eduardo/Desktop/MetricEvol/build-MetricEvol-Desktop-Debug/source_files/";
    // CSV file where the metrics are generated
    QString metrics_output_file = "/home/eduardo/Desktop/MetricEvol/build-MetricEvol-Desktop-Debug/metrics/m" + QString::number(counter) + ".csv";

    // Breaking down: First go to the directory where Understand is installed
    // /usr/bin/time -f \"%e\" sh -c '...' -> times in seconds the time taken to run the commands in the apostrophes
    // The database is generated for Java source code - change to C++ if necessary by "-languages c++ "
    // The warnings and errors of the metric extraction is directed to log.txt
    // The output of time goes to stderr, 2>&1 redirects it to stdout so we can use it in the program
//    QString cmd = "cd /home/eduardo/Documents/scitools/bin/linux64/; "
//                  "/usr/bin/time -f \"%e\" sh -c './und create -db newDatabase.udb -languages java add " + project_folder_path +
//                  " settings -metrics all settings -metricsOutputFile " + metrics_output_file +
//                  " analyze metrics > log.txt; ' 2>&1 ";
		QString time = exec("pwd");

    // Cleaning "time that took to process the extraction" string

    // Save time in a file specifying each extraction it belongs
    QFile file("./metrics/meta.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
        return "error opening times file";
    QTextStream out(&file);
		out << "m" << counter << ": " << cmt << " - "<<   time << "\n";
    counter++;

		return time.toStdString();
}

// exec works like a terminal - how? magic.
QString MetricExtractor::exec(QString cmd) {

	system(cmd.toUtf8());
	//		std::shared_ptr<FILE> pipe(popen(cmd.toUtf8(), "r"), pclose);
//		if (!pipe) return "ERROR";
//		char buffer[128];
//		QString result = "";
//		while (!feof(pipe.get())) {
//				if (fgets(buffer, 128, pipe.get()) != NULL)
//						result += buffer;
//		}
//		return result;
}
