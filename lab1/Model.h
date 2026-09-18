#pragma once
#include <QObject>

struct SmokingInput {
    double cigarettesPerDay = 0.0;
    double packPrice = 0.0;
    double tarPerCigaretteMg = 0.0;
    double nicotinePerCigaretteMg = 0.0;
    double yearsSmoking = 0.0;
    double cakePrice = 0.0;
    double orangePrice = 0.0;
    bool valid = false;
};

struct SmokingResult {
    double totalCigarettes = 0.0;
    double totalPacks = 0.0;
    double moneySpent = 0.0;
    double totalTarMg = 0.0;
    double totalTarG = 0.0;
    double totalNicotineMg = 0.0;
    double totalNicotineG = 0.0;
    double cakes = 0.0;
    double oranges = 0.0;
};

// Активная модель: сама уведомляет View через сигнал dataChanged()
class Model : public QObject {
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    const SmokingInput& input() const { return m_input; }
    const SmokingResult& result() const { return m_result; }
    bool hasData() const { return m_hasData; }

    void setData(const SmokingInput& input);

signals:
    void dataChanged();

private:
    void recalculate();

    SmokingInput m_input;
    SmokingResult m_result;
    bool m_hasData = false;
};