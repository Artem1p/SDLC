#pragma once
#include <QDialog>
#include "Model.h"

class QLineEdit;
class QDialogButtonBox;

class InputDialog : public QDialog {
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = nullptr);

    void setInput(const SmokingInput& input);
    SmokingInput input() const;

private:
    QLineEdit* m_cigarettesPerDay;
    QLineEdit* m_packPrice;
    QLineEdit* m_tar;
    QLineEdit* m_nicotine;
    QLineEdit* m_years;
    QLineEdit* m_cakePrice;
    QLineEdit* m_orangePrice;
    QDialogButtonBox* m_buttons;
};