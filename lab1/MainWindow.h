#pragma once
#include <QMainWindow>
#include "Model.h"

class QLabel;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Model* model, QWidget *parent = nullptr);

    void updateView();
    QPushButton* inputButton() const { return m_inputButton; }

private:
    Model* m_model;
    QLabel* m_lastInputLabel;
    QLabel* m_resultLabel;
    QPushButton* m_inputButton;
};