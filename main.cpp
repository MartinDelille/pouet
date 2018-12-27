#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCommandLineParser parser;

	parser.setApplicationDescription("pouet");

	parser.addHelpOption();
	parser.addVersionOption();

	parser.addPositionalArgument("files", "Files to process.");

	QCommandLineOption verboseOption({ "v", "verbose" },  "Perform a verbose log.");
	QCommandLineOption outputOption({ "o", "output" }, "File to output the result.", "filename");
	parser.addOptions({ verboseOption, outputOption });

	if (!parser.parse(a.arguments())) {
		qDebug() << parser.errorText();
		return -1;
	}

	parser.process(a);

	QStringList args = parser.positionalArguments();

	if (args.empty()) {
		qDebug() << "Please provide some arguments!";
		parser.showHelp(-1);
	}

	bool verbose = parser.isSet(verboseOption);
	QString outputFile;

	if (parser.isSet(outputOption)) {
		outputFile = parser.value("output");
	}

	foreach(QString arg, args) {
		if (verbose) {
			qDebug() << "A verbose log";
		}
		qDebug() << arg;
	}

	return 0;
}
