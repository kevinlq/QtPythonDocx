#include "MainWidget.h"
#include "KPythonRunScript.h"

#include <QDebug>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDesktopServices>

// 基本数据结构
struct DS_ItemData
{
    DS_ItemData(){;}
    DS_ItemData(const QString &strText, const QString &strType, const QString &strPicture,
                const QString &strAlignment, bool bBold, bool bItalic, bool bStrike, int nLevel);

    QString text = "";
    QString type = "0";
    QString picture = "";
    QString alignment = "left";
    bool bold = false;
    bool italic = false;
    bool strike = false;
    int level = 5;

    virtual QVariantMap toVariantMap();
};

DS_ItemData::DS_ItemData(const QString &strText, const QString &strType, const QString &strPicture,
                         const QString &strAlignment, bool bBold, bool bItalic, bool bStrike, int nLevel)
    : text(strText), type(strType), picture(strPicture), alignment(strAlignment), bold(bBold)
    , italic(bItalic), strike(bStrike), level(nLevel)
{
}

QVariantMap DS_ItemData::toVariantMap()
{
    QVariantMap map;
    map["type"] = type;
    map["text"] = text;
    map["level"] = level;
    map["bold"] = bold;
    map["italic"] = italic;
    map["strike"] = strike;
    map["alignment"] = alignment;
    map["picture"] = picture;

    return map;
}

struct DS_TableData : public DS_ItemData
{
    int columns = 0;
    int rows = 0;
    QList<DS_ItemData> cellItems;

    QVariantMap toVariantMap() override;
};

QVariantMap DS_TableData::toVariantMap()
{
    QVariantMap map = DS_ItemData::toVariantMap();

    QVariantList tableCellList;
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            int index = r*columns + c;

            if(index >= cellItems.size())
            {
                qWarning() << "index outof range.." << index << cellItems.size();
                continue;
            }

            QVariantMap itemMap = cellItems[index].toVariantMap();
            tableCellList << itemMap;
        }
    }

    map["columns"]      = columns;
    map["rows"]         = rows;
    map["tableCell"]    = tableCellList;

    return map;
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    QGridLayout *pGridLayout = new QGridLayout;

    m_pExportPathEdit = new QLineEdit("D:/test-20220903.docx", this);
    pGridLayout->addWidget(m_pExportPathEdit, 0, 0, 1, 1);

    m_pTitle = new QLineEdit("这是标题",this);
    pGridLayout->addWidget(m_pTitle, 1, 0, 1, 1);

    pMainLayout->addLayout(pGridLayout);

    m_pText1 = new QTextEdit("这个示例演示了如何通过C++调用python来生成word文档,数据交互采用JSON格式", this);
    m_pText1->setMinimumHeight(60);
    pGridLayout->addWidget(m_pText1, 2, 0, 1, 1);

    m_pTableView = new QTableView(this);
    m_pTableView->setMinimumHeight(400);
    pGridLayout->addWidget(m_pTableView, 3, 0, 1, 1);

    m_pText2 = new QTextEdit("这是测试段落", this);
    m_pText2->setMinimumHeight(60);
    pGridLayout->addWidget(m_pText2, 4, 0, 1, 1);

    m_pOpenFileCheck = new QCheckBox("导出后打开文件",this);
    m_pOpenFileCheck->setChecked(true);
    m_pExportButton = new QPushButton("导出",this);
    connect(m_pExportButton, &QPushButton::clicked,
            this, &MainWidget::onExportButtonClicked);
    auto pHLayout = new QHBoxLayout;
    pHLayout->addStretch();
    pHLayout->addWidget(m_pOpenFileCheck);
    pHLayout->addSpacing(6);
    pHLayout->addWidget(m_pExportButton);
    pMainLayout->addLayout(pHLayout);

    pMainLayout->addStretch();

    setLayout(pMainLayout);
}

void MainWidget::onExportButtonClicked()
{
    bool bResult = false;

    QVariant returnValue = 0;
    QVariantList args = {1,2};

    // 测试生成word文件
    {
        returnValue = true;
        args.clear();

        bool openFile = m_pOpenFileCheck->isChecked();
        QString savePath = m_pExportPathEdit->text();

        QVariantMap map;
        map["title"] = m_pTitle->text();
        map["savePath"] = savePath;
        map["openFile"] = openFile;
        map["line_spacing"] = 1.5;
        map["header"] = "测试生成页眉";
        map["footer"] = "测试生成页脚";

        QList<DS_ItemData*> contentList;
        DS_ItemData *heading1 = new DS_ItemData("这个是 word 标题", "0", "", "center", true, false, false, 1);
        contentList << heading1;

        DS_ItemData *heading2 = new DS_ItemData("一.概述", "0", "", "left", true, false, false, 2);
        contentList << heading2;

        DS_ItemData *pText1 = new DS_ItemData(m_pText1->toPlainText(), "1", "", "left", false, false, false, 3);
        contentList << pText1;

        DS_ItemData *heading3 = new DS_ItemData("二.插入表格", "0", "", "left", true, false, false, 2);
        contentList << heading3;

        int nRows = 4;
        int nColumns = 2;

        DS_TableData *pTableData = new DS_TableData;
        pTableData->type = "3";
        pTableData->text = "";
        pTableData->columns = nColumns;
        pTableData->rows = nRows;

        for(int r = 0; r < nRows; r++)
        {
            for(int c = 0; c < nColumns; c++)
            {
                int index = r*nColumns + c;
                bool bold = false;
                bool italic = false;
                QString text = QString("单元格 %1").arg(index+1);

                if(index == 0)
                {
                    text = QString("单元格 %1,加粗、倾斜").arg(index+1);
                    bold = true;
                    italic = true;
                }

                DS_ItemData itemData;
                itemData.text = text;
                itemData.bold = bold;
                itemData.italic = italic;
                itemData.level = 5;
                pTableData->cellItems.push_back(itemData);
            }
        }

        contentList << pTableData;

        DS_ItemData *heading4 = new DS_ItemData("三.插入图片", "0", "", "left", true, false, false, 2);
        contentList << heading4;
        DS_ItemData *pictureItem = new DS_ItemData("", "2", "title.png", "left", false, false, false, 2);
        contentList << pictureItem;

        DS_ItemData *heading5 = new DS_ItemData("四.总结", "0", "", "left", true, false, false, 2);
        contentList << heading5;
        DS_ItemData *pText2 = new DS_ItemData(m_pText2->toPlainText(), "1", "", "left", false, false, false, 3);
        contentList << pText2;

        QVariantList tmpContentList;
        for(int i = 0; i < contentList.size(); i++)
        {
            tmpContentList.push_back(contentList[i]->toVariantMap());
        }

        map["content"] = tmpContentList;
        QJsonDocument doc = QJsonDocument::fromVariant(map);

        args << QString(doc.toJson());

        KPythonRunScript *pRunScript = KPythonRunScript::instance("wordOperate");

        if(false)
        {
            returnValue = QString("");
            args.clear();
            args.push_back(QString::fromLocal8Bit("this is test"));
            pRunScript->callFun("callTest", args, returnValue);
            qDebug() << "run callTest result:" << bResult << returnValue;

            return;
        }

        bResult = pRunScript->callFun("generateWord", args, returnValue);
        qDebug() << "run generateWord result:" << bResult << returnValue;

        if(!bResult)
        {
            qWarning() << "write word fail.....";
            return;
        }

        if(openFile)
        {
            //QDesktopServices::openUrl(QString("file:///%1").arg(savePath));
        }
    }
}

