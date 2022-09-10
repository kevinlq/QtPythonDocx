#pragma once

#include <QWidget>

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableView>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private Q_SLOTS:
    void onExportButtonClicked();

private:
    QLineEdit *m_pExportPathEdit = nullptr;     // 导出路径
    QLineEdit *m_pTitle = nullptr;
    QTextEdit *m_pText1 = nullptr;
    QTableView *m_pTableView = nullptr;
    QTextEdit *m_pText2 = nullptr;

    QCheckBox   *m_pOpenFileCheck = nullptr;
    QPushButton *m_pExportButton = nullptr;
};

