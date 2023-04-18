#include "MainWidget.h"

#include "KPYSDK.h"
#include "WordItemData.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("QtPythonDocx by kevinlq(微信公众号:devstone)");
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    QGridLayout *pGridLayout = new QGridLayout;

    m_pExportPathEdit = new QLineEdit("D:/test-20220903.docx", this);
    pGridLayout->addWidget(m_pExportPathEdit, 0, 0, 1, 1);

    m_pTitle = new QLineEdit("这是标题",this);
    pGridLayout->addWidget(m_pTitle, 1, 0, 1, 1);

    pMainLayout->addLayout(pGridLayout);
    QString strText = "这个示例演示了如何通过C++调用python来生成word文档,数据交互采用JSON格式。使用者完全不用关心python 是怎么被调用的，就像正常调用C++函数一样非常简单，这样我们只需要关注具体内容即可";

    m_pText1 = new QTextEdit(strText, this);
    m_pText1->setMinimumHeight(60);
    pGridLayout->addWidget(m_pText1, 2, 0, 1, 1);

    m_pTableView = new QTableView(this);
    m_pTableView->setMinimumHeight(400);
    pGridLayout->addWidget(m_pTableView, 3, 0, 1, 1);

    strText = "人生苦短，我用C++和Python";
    m_pText2 = new QTextEdit(strText, this);
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
        map["savePath"] = savePath;
        map["openFile"] = openFile;
        map["line_spacing"] = 1.5;
        map["header"] = "测试生成页眉";
        map["footer"] = "测试生成页脚";
        map["fontSize"] = 13;
        map["fontName"] = "仿宋";

        QList<DS_ItemData*> contentList;
        DS_ItemData *heading1 = new DS_ItemData(m_pTitle->text(), "0", "", "center", true, false, false, 1);
        contentList << heading1;

        DS_ItemData *heading2 = new DS_ItemData("一.概述", "0", "", "left", true, false, false, 2);
        contentList << heading2;

        DS_ItemData *pText1 = new DS_ItemData(m_pText1->toPlainText(), "1", "", "left", false, false, false, 3);
        pText1->first_line_indent = 2;
        contentList << pText1;

        DS_ItemData *heading3 = new DS_ItemData("二.插入表格", "0", "", "left", true, false, false, 2);
        contentList << heading3;

        int nRows = 4;
        int nColumns = 2;

        QString strText = QString("下面演示创建%1行%2列表格，每个单元格样式都可以自定义，只需要配置具体样式即可").arg(nRows).arg(nColumns);
        {
            DS_ItemData *pTextTable = new DS_ItemData(strText, "1", "", "left", false, false, false, 3);
            pTextTable->first_line_indent = 2;
            pTextTable->space_after = 5;
            contentList << pTextTable;

            DS_TableData *pTableData = new DS_TableData;
            pTableData->type = "3";
            pTableData->text = "";
            pTableData->columns = nColumns;
            pTableData->rows = nRows;

            for(int r = 0; r < nRows; r++)
            {
                for(int c = 0; c < nColumns; c++)
                {
                    DS_ItemData itemData;
                    itemData.bold = false;
                    itemData.italic = false;
                    itemData.level = 5;
                    itemData.alignment = "center";

                    int index = r*nColumns + c;
                    QString text = QString("单元格 %1").arg(index+1);

                    if(index == 0)
                    {
                        text = QString("单元格 %1,加粗、倾斜、红色").arg(index+1);
                        itemData.bold = true;
                        itemData.italic = true;
                        itemData.color = "#ff0000";
                    }

                    itemData.text = text;
                    pTableData->cellItems.push_back(itemData);
                }
            }
            contentList << pTableData;
        }

        {
            nRows = 4;
            nColumns = 4;
            strText = QString("下面演示表格如何合并单元格");
            DS_ItemData *pTextTable = new DS_ItemData(strText, "1", "", "left", false, false, false, 3);
            pTextTable->space_after = 15;
            contentList << pTextTable;

            DS_TableData *pTableData = new DS_TableData;
            pTableData->type = "3";
            pTableData->text = "";
            pTableData->columns = nColumns;
            pTableData->rows = nRows;

            // 合并单元格 ，(0,0)~(0,1)
            DS_TableItem mergeItem;
            mergeItem.beginCell << 0 << 0;;
            mergeItem.endCell << 0 << 1;
            pTableData->mergeCells.push_back(mergeItem);

            for(int r = 0; r < nRows; r++)
            {
                for(int c = 0; c < nColumns; c++)
                {
                    DS_ItemData itemData;
                    itemData.bold = false;
                    itemData.italic = false;
                    itemData.level = 5;

                    int index = r*nColumns + c;
                    QString text = QString("单元格 %1").arg(index+1);

                    if(index == 0)
                    {
                        text = QString("单元格 %1,加粗、倾斜、红色").arg(index+1);
                        itemData.bold = true;
                        itemData.italic = true;
                        itemData.color = "#ff0000";
                    }
                    else if (index == 1)
                    {
                        // 由于00和01合并了，所以01样式、文本会覆盖00，这里进行测试
                        text = QString("(0,0)和(0,1)单元格合并了，因此(0,1)会覆盖(0,2)单元格的文字以及样式，设置覆盖后的单元格样式为:加粗变蓝,左对齐 %1").arg(index+1);
                        itemData.bold = true;
                        itemData.italic = false;
                        itemData.color = "#0000ff";
                        itemData.alignment = "left";
                    }

                    itemData.text = text;
                    pTableData->cellItems.push_back(itemData);
                }
            }
            contentList << pTableData;
        }

        {
            DS_ItemData *heading4 = new DS_ItemData("三.插入图片", "0", "", "left", true, false, false, 2);
            contentList << heading4;
            QString strText = QString("下面演示了如何插入图片，目前图片支持相对路径和绝对路劲，可以根据自己需要在json对应字段传入，如片大小支持手动设置，示例中写了固定值");
            DS_ItemData *pText = new DS_ItemData(strText, "1", "", "left", false, false, false, 3);
            pText->first_line_indent = 2;
            contentList << pText;
            DS_ItemData *pictureItem = new DS_ItemData("", "2", "title.png", "left", false, false, false, 2);
            contentList << pictureItem;
        }

        DS_ItemData *heading5 = new DS_ItemData("四.总结", "0", "", "left", true, false, false, 2);
        contentList << heading5;
        DS_ItemData *pText2 = new DS_ItemData(m_pText2->toPlainText(), "1", "", "left", false, false, false, 3);
        pText2->first_line_indent = 2;
        contentList << pText2;

        QVariantList tmpContentList;
        for(int i = 0; i < contentList.size(); i++)
        {
            tmpContentList.push_back(contentList[i]->toVariantMap());
        }

        map["content"] = tmpContentList;
        QJsonDocument doc = QJsonDocument::fromVariant(map);

        QString strJsonData = QString(doc.toJson());

        //qDebug() << strJsonData;

        args << strJsonData;

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
    }
}

