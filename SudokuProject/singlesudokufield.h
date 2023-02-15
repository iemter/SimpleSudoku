#ifndef SINGLESUDOKUFIELD_H
#define SINGLESUDOKUFIELD_H

#include <QObject>

class SingleSudokuField: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentNumber READ currentNumber WRITE setCurrentNumber NOTIFY currentNumberChanged)
    Q_PROPERTY(bool isFixed READ isFixed CONSTANT)
    Q_PROPERTY(bool isCorrect READ isCorrect NOTIFY isCorrectChanged)

    int m_currentNumber = 0;
    bool m_isFixed = false;
    bool m_isCorrect = false;
    int m_expectedNumber = 0;
public:
    SingleSudokuField(int _currentNumber = 0, bool _isFixed = false, bool _isCorrect = false, int _expectedNumber = 0, QObject* parent = nullptr);
    int currentNumber() const;
    bool isFixed() const;
    bool isCorrect() const;
    void changeIsFixed(bool _isFixed) {
        m_isFixed = _isFixed;
    }
    void changeIsCorrect(bool _isCorrect) {
        m_isCorrect = _isCorrect;
    }
    void changeCurrentNumber(int _currentNumber) {
        m_currentNumber = _currentNumber;
    }
    void changeExpectedNumber(int _expectedNumber) {
        m_expectedNumber = _expectedNumber;
    }

public slots:
    void setCurrentNumber(int _currentNumber);
signals:
    void currentNumberChanged(int _currentNumber);
    void isCorrectChanged(int _isCorrect);

};

#endif // SINGLESUDOKUFIELD_H
