#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "singlesudokufield.h"
#include "sudokufield.h"
#include <QQmlContext> // this is required for setContextProperty
#include <QQmlEngine> // for qmlRegisterType

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    SudokuField sudokuField(":/files/");
    engine.rootContext()->setContextProperty("SudokuField", &sudokuField);
    // template <typename T> int qmlRegisterType(const char *uri, int versionMajor, int versionMinor, const char *qmlName)
    qmlRegisterType<SingleSudokuField>("com.sudoku.app", 1, 0, "SingleSudokuField");
    engine.load(url);

    return app.exec();
}
