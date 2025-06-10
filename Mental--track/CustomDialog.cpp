#include "CustomDialog.h"

CustomDialog::CustomDialog(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    setModal(false);

    m_layout = new QVBoxLayout(this);
    m_messageLabel = new QLabel(this);
    m_infoLabel = new QLabel(this);
    m_buttonLayout = new QHBoxLayout();

    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_infoLabel->setAlignment(Qt::AlignCenter);

    m_layout->addWidget(m_messageLabel);
    m_layout->addWidget(m_infoLabel);
    m_layout->addLayout(m_buttonLayout);
}

void CustomDialog::setMessage(const QString &message) {
    m_messageLabel->setText(message);
}

void CustomDialog::setInformativeText(const QString &text) {
    m_infoLabel->setText(text);
}

void CustomDialog::addButton(const QString &text, QMessageBox::ButtonRole role)
{
    QPushButton *button = new QPushButton(text, this);
    connect(button, &QPushButton::clicked, this, [this, role]()
    {
        done(role == QMessageBox::AcceptRole ? QDialog::Accepted : QDialog::Rejected);
    });

    m_buttonLayout->addWidget(button);
}
