#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>

MainWindow::MainWindow(Model* model, QWidget *parent)
    : QMainWindow(parent), m_model(model) {
    setWindowTitle("Калькулятор Тортиков — вариант 18");

    auto* central = new QWidget(this);
    auto* layout = new QVBoxLayout(central);

    m_lastInputLabel = new QLabel("Последние введённые данные: нет", central);
    m_resultLabel = new QLabel("Результат: нет", central);
    m_lastInputLabel->setWordWrap(true);
    m_resultLabel->setWordWrap(true);

    QFont font = m_resultLabel->font();
    font.setPointSize(font.pointSize() + 1);
    m_lastInputLabel->setFont(font);
    m_resultLabel->setFont(font);

    m_inputButton = new QPushButton("Ввести данные", central);

    layout->addWidget(m_lastInputLabel);
    layout->addWidget(m_resultLabel);
    layout->addWidget(m_inputButton);
    layout->addStretch();

    setCentralWidget(central);
    resize(750, 450);

    // View подписывается на сигнал модели (активная модель)
    connect(m_model, &Model::dataChanged, this, &MainWindow::updateView);
}

void MainWindow::updateView() {
    if (!m_model->hasData()) {
        m_lastInputLabel->setText("Последние введённые данные: нет");
        m_resultLabel->setText("Результат: нет");
        return;
    }

    const auto& in = m_model->input();
    const auto& r = m_model->result();

    m_lastInputLabel->setText(QString(
        "Последние введённые данные:\n"
        "Сигарет в день: %1\n"
        "Цена пачки: %2\n"
        "Смолы в 1 сигарете: %3 мг\n"
        "Никотина в 1 сигарете: %4 мг\n"
        "Стаж курения: %5 лет\n"
        "Цена тортика: %6\n"
        "Цена апельсина: %7"
    ).arg(in.cigarettesPerDay).arg(in.packPrice)
     .arg(in.tarPerCigaretteMg).arg(in.nicotinePerCigaretteMg)
     .arg(in.yearsSmoking).arg(in.cakePrice).arg(in.orangePrice));

    m_resultLabel->setText(QString(
        "Результат:\n"
        "Всего сигарет: %1\n"
        "Пачек: %2\n"
        "Потрачено денег: %3\n"
        "Смолы прошло через лёгкие: %4 мг (%5 г)\n"
        "Никотина прошло через тело: %6 мг (%7 г)\n"
        "Можно было купить тортиков: %8\n"
        "Можно было купить апельсинов: %9"
    ).arg(r.totalCigarettes, 0, 'f', 2)
     .arg(r.totalPacks, 0, 'f', 2)
     .arg(r.moneySpent, 0, 'f', 2)
     .arg(r.totalTarMg, 0, 'f', 2)
     .arg(r.totalTarG, 0, 'f', 3)
     .arg(r.totalNicotineMg, 0, 'f', 2)
     .arg(r.totalNicotineG, 0, 'f', 3)
     .arg(r.cakes, 0, 'f', 2)
     .arg(r.oranges, 0, 'f', 2));
}