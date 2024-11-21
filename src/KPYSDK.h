#pragma once


#include <QVariantList>
#include "KPYSDK_global.h"

#pragma execution_character_set("UTF-8")

class KPythonRunScriptImpl;
class KPYSDK_EXPORT KPythonRunScript
{
    KPythonRunScript(const char *modelName);
public:
    static KPythonRunScript* instance(const char *modelName);
    ~KPythonRunScript();

    bool callFun(const char *funcName,
                 const QVariantList &args,
                 QVariant &returnValue);

private:
    KPythonRunScriptImpl *m_pImple;
};

