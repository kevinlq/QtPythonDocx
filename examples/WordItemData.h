#pragma once

#include <QDebug>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonArray>

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
    QString vertical_alignment = "center";  // 垂直居中
    QString color = "#000000";
    bool bold = false;
    bool italic = false;
    bool strike = false;
    int level = 5;
    double space_after = 15;
    double space_before = 15;
    int first_line_indent = 0;  // 首行缩进字符，2个字符给2
    double height = 1.1;         // 行高,主要针对每个表格单元格属性，单位cm

    virtual QVariantMap toVariantMap();
};

struct DS_TableItem
{
    QVariantList beginCell;
    QVariantList endCell;
    QVariantMap toVariantMap();
};

struct DS_TableData : public DS_ItemData
{
    int columns = 0;
    int rows = 0;
    double height = 1.1;         // 整体行高，单位cm
    QList<DS_TableItem> mergeCells;     // 合并的单元格信息
    QList<DS_ItemData> cellItems;

    QVariantMap toVariantMap() override;
};
