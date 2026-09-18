#include "Controller.h"
#include "MainWindow.h"
#include "InputDialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QDialog>

Controller::Controller(Model* model, MainWindow* view, QObject* parent)
    : QObject(parent), m_model(model), m_view(view),
      m_dialog(new InputDialog(view)) {
    connect(m_view->inputButton(), &QPushButton::clicked,
            this, &Controller::onInputButtonClicked);
    m_view->updateView();
}

void Controller::onInputButtonClicked() {
    // Восстанавливаем последние введённые данные
    if (m_model->hasData())
        m_dialog->setInput(m_model->input());

    while (m_dialog->exec() == QDialog::Accepted) {
        SmokingInput in = m_dialog->input();
        QString error;
        if (!validate(in, error)) {
            QMessageBox::warning(m_view, "Ошибка ввода", error);
            continue; // снова открываем диалог
        }
        in.valid = true;
        m_model->setData(in); // модель сама уведомит View
        break;
    }
}

bool Controller::validate(const SmokingInput& in, QString& error) const {
    if (in.cigarettesPerDay <= 0.0) { error = "Количество сигарет в день должно быть больше 0."; return false; }
    if (in.packPrice <= 0.0)        { error = "Цена пачки должна быть больше 0."; return false; }
    if (in.tarPerCigaretteMg < 0.0) { error = "Содержание смол не может быть отрицательным."; return false; }
    if (in.nicotinePerCigaretteMg < 0.0) { error = "Содержание никотина не может быть отрицательным."; return false; }
    if (in.yearsSmoking <= 0.0)     { error = "Стаж курения должен быть больше 0."; return false; }
    if (in.cakePrice <= 0.0)        { error = "Цена тортика должна быть больше 0."; return false; }
    if (in.orangePrice <= 0.0)      { error = "Цена апельсина должна быть больше 0."; return false; }
    return true;
}