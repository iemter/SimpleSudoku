#include "singlesudokufield.h"

// QObject needs to be initialized first!
SingleSudokuField::SingleSudokuField(int _currentNumber, bool _isFixed, bool _isCorrect, int _expectedNumber, QObject* parent)
    :QObject(parent), m_currentNumber(_currentNumber), m_isFixed(_isFixed), m_isCorrect(_isCorrect), m_expectedNumber(_expectedNumber)
{}

int SingleSudokuField::currentNumber() const{
    return m_currentNumber;
}

bool SingleSudokuField::isFixed() const {
    return m_isFixed;
}

void SingleSudokuField::setCurrentNumber(int _currentNumber) {
    if (m_currentNumber == _currentNumber) {
        return;
    }

    if (_currentNumber < 1 || _currentNumber > 9) {
        return;
    }

    if (m_isFixed) {
        return;
    }

    m_currentNumber = _currentNumber;

    bool correct;
    // check if currentNumber equals expected number
    if (m_currentNumber == m_expectedNumber) {
        correct = true;
    }
    else {
        correct = false;
    }

    if (correct != m_isCorrect) {
        m_isCorrect = correct;
        emit isCorrectChanged(correct);
    }


    emit currentNumberChanged(_currentNumber);
}

bool SingleSudokuField::isCorrect() const {
    return m_isCorrect;
}
