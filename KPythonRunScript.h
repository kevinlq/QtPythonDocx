#pragma once


#include <QVariantList>

#pragma execution_character_set("UTF-8")

class KPythonRunScriptImpl;
class KPythonRunScript
{
    KPythonRunScript(const char *modelName);
public:
    static KPythonRunScript* instance(const char *modelName);
    ~KPythonRunScript();

    bool callFun(const char *funcName,
                 const QVariantList &args = QVariantList(),
                 QVariant &returnValue = QVariant(QVariant::Invalid));

private:
    KPythonRunScriptImpl *m_pImple;
};

