#pragma once
#include <QObject>
#include <QString>
#include "Model.h"

class MainWindow;
class InputDialog;

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(Model* model, MainWindow* view, QObject* parent = nullptr);

private slots:
    void onInputButtonClicked();

private:
    bool validate(const SmokingInput& in, QString& error) const;

    Model* m_model;
    MainWindow* m_view;
    InputDialog* m_dialog;
};