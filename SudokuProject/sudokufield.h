#ifndef SUDOKUFIELD_H
#define SUDOKUFIELD_H
#include "singlesudokufield.h"
#include <QList>
#include <QQmlListProperty>
#include <QObject>
#include <QUrl>

class SudokuField: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<SingleSudokuField> field READ field NOTIFY fieldChanged)
    Q_PROPERTY(bool isFinished READ isFinished NOTIFY isFinishedChanged)

    bool m_isFinished = false;
    QList<SingleSudokuField*> m_SudokuFieldList;
    QList<SingleSudokuField*> m_SudokuFieldSolution;
    QString m_source;
    int correctCounter();
public:
    SudokuField(QString source = ":/files/", QObject* parent = nullptr);
    QQmlListProperty<SingleSudokuField> field();
    QString convertUrlToNativeFilePath(const QUrl& urlStylePath) const;
    bool isFinished();
public slots:
    void writeField(); // used to generate a new field
signals:
    void fieldChanged(QQmlListProperty<SingleSudokuField> field);
    void error(const QString& msg);
    void isFinishedChanged(bool _isFinished);
};

#endif // SUDOKUFIELD_H
