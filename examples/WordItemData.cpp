#include "WordItemData.h"

DS_ItemData::DS_ItemData(const QString &strText, const QString &strType, const QString &strPicture, const QString &strAlignment, bool bBold, bool bItalic, bool bStrike, int nLevel)
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
    map["vertical_alignment"] = vertical_alignment;
    map["color"]    = color;
    map["picture"] = picture;
    map["space_after"] = space_after;
    map["space_after"] = space_after;
    map["first_line_indent"] = first_line_indent;
    map["height"] = height;

    return map;
}

QVariantMap DS_TableItem::toVariantMap()
{
    QVariantMap map;
    map["begin"] = beginCell;
    map["end"] = endCell;
    return map;
}

QVariantMap DS_TableData::toVariantMap()
{
    QVariantMap map = DS_ItemData::toVariantMap();

    QVariantList mergeCellList;
    for(int i = 0; i < mergeCells.size(); i++)
    {
        mergeCellList.push_back(mergeCells[i].toVariantMap());
    }
    map["mergeCells"] = mergeCellList;
    map["height"] = height;

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
