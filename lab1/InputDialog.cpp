#include "InputDialog.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDoubleValidator>
#include <QLocale>

InputDialog::InputDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Ввод данных");

    m_cigarettesPerDay = new QLineEdit(this);
    m_packPrice = new QLineEdit(this);
    m_tar = new QLineEdit(this);
    m_nicotine = new QLineEdit(this);
    m_years = new QLineEdit(this);
    m_cakePrice = new QLineEdit(this);
    m_orangePrice = new QLineEdit(this);

    auto* validator = new QDoubleValidator(0.0, 1e9, 3, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setLocale(QLocale::c()); // принимать точку, а не запятую

    const QList<QLineEdit*> edits = {
        m_cigarettesPerDay, m_packPrice, m_tar, m_nicotine,
        m_years, m_cakePrice, m_orangePrice
    };
    for (QLineEdit* edit : edits)
        edit->setValidator(validator);

    auto* form = new QFormLayout;
    form->addRow("Сигарет в день:", m_cigarettesPerDay);
    form->addRow("Цена пачки:", m_packPrice);
    form->addRow("Смолы в 1 сигарете (мг):", m_tar);
    form->addRow("Никотина в 1 сигарете (мг):", m_nicotine);
    form->addRow("Стаж курения (лет):", m_years);
    form->addRow("Цена тортика:", m_cakePrice);
    form->addRow("Цена апельсина:", m_orangePrice);

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(m_buttons);
}

void InputDialog::setInput(const SmokingInput& input) {
    m_cigarettesPerDay->setText(QString::number(input.cigarettesPerDay));
    m_packPrice->setText(QString::number(input.packPrice));
    m_tar->setText(QString::number(input.tarPerCigaretteMg));
    m_nicotine->setText(QString::number(input.nicotinePerCigaretteMg));
    m_years->setText(QString::number(input.yearsSmoking));
    m_cakePrice->setText(QString::number(input.cakePrice));
    m_orangePrice->setText(QString::number(input.orangePrice));
}

SmokingInput InputDialog::input() const {
    SmokingInput in;
    in.cigarettesPerDay = m_cigarettesPerDay->text().toDouble();
    in.packPrice = m_packPrice->text().toDouble();
    in.tarPerCigaretteMg = m_tar->text().toDouble();
    in.nicotinePerCigaretteMg = m_nicotine->text().toDouble();
    in.yearsSmoking = m_years->text().toDouble();
    in.cakePrice = m_cakePrice->text().toDouble();
    in.orangePrice = m_orangePrice->text().toDouble();
    return in;
}