#include "Model.h"

Model::Model(QObject *parent) : QObject(parent) {}

void Model::setData(const SmokingInput& input) {
    m_input = input;
    m_hasData = true;
    recalculate();
    emit dataChanged(); // активная модель уведомляет View
}

void Model::recalculate() {
    const double daysPerYear = 365.0;
    const double cigarettesInPack = 20.0;

    m_result.totalCigarettes = m_input.cigarettesPerDay * daysPerYear * m_input.yearsSmoking;
    m_result.totalPacks = m_result.totalCigarettes / cigarettesInPack;
    m_result.moneySpent = m_result.totalPacks * m_input.packPrice;

    m_result.totalTarMg = m_result.totalCigarettes * m_input.tarPerCigaretteMg;
    m_result.totalTarG = m_result.totalTarMg / 1000.0;

    m_result.totalNicotineMg = m_result.totalCigarettes * m_input.nicotinePerCigaretteMg;
    m_result.totalNicotineG = m_result.totalNicotineMg / 1000.0;

    m_result.cakes = m_input.cakePrice > 0.0 ? m_result.moneySpent / m_input.cakePrice : 0.0;
    m_result.oranges = m_input.orangePrice > 0.0 ? m_result.moneySpent / m_input.orangePrice : 0.0;
}