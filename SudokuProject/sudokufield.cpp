#include "sudokufield.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>
#include <QDir>
#include <QUrl>

QString SudokuField::convertUrlToNativeFilePath(const QUrl& urlStylePath) const
{
    return urlStylePath.toLocalFile();
}

SudokuField::SudokuField(QString source, QObject* parent):
    QObject(parent)
{
    // load from source
    if (source.isEmpty()) {
        // emit error("source is empty");
        qCritical() << "Source is empty";
        return;
    }

    // QString localFilePath = convertUrlToNativeFilePath(source);

    // assuming there are 1000 games and solutions available
    int randomNumber = QRandomGenerator::global()->bounded(0, 1000);
    QString gamePath = source;
    QString solutionPath = source;

    m_isFinished = false;

    m_source = source;

    // get full game path from source
    gamePath.append(QString("games/game"));
    gamePath.append(QString::number(randomNumber));
    gamePath.append(QString(".txt"));
    // get full solution path
    solutionPath.append(QString("solutions/solution"));
    solutionPath.append(QString::number(randomNumber));
    solutionPath.append(QString(".txt"));

    // load data
    QFile gameFile(gamePath);
    QFile solutionFile(solutionPath);
    QString gameContent;
    QString solutionContent;

    if (gameFile.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &gameFile );
        do {
            line = t.readLine();
            gameContent += line;
         } while (!line.isNull());

        gameFile.close();
    }
    else {
        // emit error("Unable to open the game file");
        qCritical() << "Unable to open the game file: " << gamePath;
        return;
    }

    if (solutionFile.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &solutionFile );
        do {
            line = t.readLine();
            solutionContent += line;
         } while (!line.isNull());

        solutionFile.close();
    }
    else {
        // emit error("Unable to open the solution file");
        qCritical() << "Unable to open the solution file: " << solutionPath;
        return;
    }

    // use contents to construct list

    // 0 value means variable, else the number is fixed
    for (int i = 0; i < 81; ++i) {

        int solutionNum = QString(solutionContent[i]).toInt();
        SingleSudokuField* sfield;
        sfield = new SingleSudokuField(solutionNum, true, true, solutionNum);

        m_SudokuFieldSolution.push_back(sfield);

        // QStrings can be accessed like arrays
        int gameNum = QString(gameContent[i]).toInt();
        SingleSudokuField* field;
        if (gameNum == 0) {
            field = new SingleSudokuField(gameNum, false, false, solutionNum);
        }
        else {
            field = new SingleSudokuField(gameNum, true, true, gameNum);
        }
        m_SudokuFieldList.push_back(field);
    }
}

int SudokuField::correctCounter() {
    int counter = 0;
    for (int i = 0; i < 81; ++i) {
        if (m_SudokuFieldList[i]->isCorrect()) {
            counter++;
        }
    }

    return counter;
}

QQmlListProperty<SingleSudokuField> SudokuField::field() {
    isFinished();
    return QQmlListProperty<SingleSudokuField>(this, &m_SudokuFieldList);
}

void SudokuField::writeField() {
    int randomNumber = QRandomGenerator::global()->bounded(0, 1000);
    QString gamePath = m_source;
    QString solutionPath = m_source;

    // get full game path from source
    gamePath.append(QString("games/game"));
    gamePath.append(QString::number(randomNumber));
    gamePath.append(QString(".txt"));
    // get full solution path
    solutionPath.append(QString("solutions/solution"));
    solutionPath.append(QString::number(randomNumber));
    solutionPath.append(QString(".txt"));

    // load data
    QFile gameFile(gamePath);
    QFile solutionFile(solutionPath);
    QString gameContent;
    QString solutionContent;

    if (gameFile.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &gameFile );
        do {
            line = t.readLine();
            gameContent += line;
         } while (!line.isNull());

        gameFile.close();
    }
    else {
        // emit error("Unable to open the game file");
        qCritical() << "Unable to open the game file: " << gamePath;
        return;
    }

    if (solutionFile.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &solutionFile );
        do {
            line = t.readLine();
            solutionContent += line;
         } while (!line.isNull());

        solutionFile.close();
    }
    else {
        // emit error("Unable to open the solution file");
        qCritical() << "Unable to open the solution file: " << solutionPath;
        return;
    }

    // use contents to construct list
    // 0 value means variable, else the number is fixed
    for (int i = 0; i < 81; ++i) {

        int solutionNum = QString(solutionContent[i]).toInt();
        // update solution field )
        m_SudokuFieldSolution[i]->changeIsFixed(true);
        m_SudokuFieldSolution[i]->changeIsCorrect(true);
        m_SudokuFieldSolution[i]->changeCurrentNumber(solutionNum);
        m_SudokuFieldSolution[i]->changeExpectedNumber(solutionNum);

        // QStrings can be accessed like arrays
        int gameNum = QString(gameContent[i]).toInt();
        if (gameNum == 0) {
            m_SudokuFieldList[i]->changeIsFixed(false);
            m_SudokuFieldList[i]->changeIsCorrect(false);
            m_SudokuFieldList[i]->changeCurrentNumber(gameNum);
            m_SudokuFieldList[i]->changeExpectedNumber(solutionNum);
        }
        else {
            m_SudokuFieldList[i]->changeIsFixed(true);
            m_SudokuFieldList[i]->changeIsCorrect(true);
            m_SudokuFieldList[i]->changeCurrentNumber(gameNum);
            m_SudokuFieldList[i]->changeExpectedNumber(solutionNum);
        }
    }

    m_isFinished = false;

    emit fieldChanged(QQmlListProperty<SingleSudokuField>(this, &m_SudokuFieldList));
}

bool SudokuField::isFinished() {
    bool _isFinished = false;
    int correctFields = correctCounter();
    if (correctFields == 81) {
        _isFinished = true;

    }

    if (m_isFinished != _isFinished) {
        m_isFinished = _isFinished;
        emit isFinishedChanged(_isFinished);
    }

    return _isFinished;

}
