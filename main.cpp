#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>

#include "sndfile.hh"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCommandLineParser parser;
	QDebug out = qDebug();

	out.noquote();

	parser.setApplicationDescription("pouet");

	parser.addHelpOption();
	parser.addVersionOption();

	parser.addPositionalArgument("files", "Files to process.");

	QCommandLineOption verboseOption({ "v", "verbose" },  "Perform a verbose log.");
	QCommandLineOption outputOption({ "o", "output" }, "File to output the result.", "filename");
	parser.addOptions({ verboseOption, outputOption });

	if (!parser.parse(a.arguments())) {
		out << parser.errorText() << endl;
		return -1;
	}

	parser.process(a);

	QStringList args = parser.positionalArguments();

	if (args.empty()) {
		out << "Please provide some arguments!" << endl;
		parser.showHelp(-1);
	}

	bool verbose = parser.isSet(verboseOption);
	QString outputFile;

	if (parser.isSet(outputOption)) {
		outputFile = parser.value("output");
	}

	foreach(QString arg, args) {
		if (verbose) {
			out << "A verbose log" << endl;
		}
		out << arg << endl;
		QFileInfo info(arg);

		if (info.suffix().toLower() == "wav") {
			SndfileHandle handle(arg.toStdString().c_str());
			out << "Sample rate:" << handle.samplerate() << endl;
		}
	}

	return 0;
}
