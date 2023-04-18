#include "KPYSDK.h"

#undef slots
#include <Python.h>
#define slots Q_SLOTS
#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>

class KPythonRunScriptImpl
{
public:
    KPythonRunScriptImpl(const char *modelName);
    ~KPythonRunScriptImpl();

    bool initPyData(const char *modelName);

    bool bPyValid();

    PyObject *m_pModule = nullptr;
    bool m_bInitialized = false;
};

KPythonRunScriptImpl::KPythonRunScriptImpl(const char *modelName)
{
    initPyData(modelName);
}

KPythonRunScriptImpl::~KPythonRunScriptImpl()
{
    qDebug() << "~KPythonRunScriptImpl";
    Py_Finalize();
    m_pModule = nullptr;
}

bool KPythonRunScriptImpl::initPyData(const char *modelName)
{
    QString pyHomePath = QCoreApplication::applicationDirPath() + "/python310";
    Py_SetPythonHome(reinterpret_cast<const wchar_t *>(pyHomePath.utf16()));

    // 初始化python环境
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./script')");

    m_bInitialized = Py_IsInitialized();
    if(!m_bInitialized)
    {
        qDebug() << __FUNCTION__ << " init python fail..";
        return false;
    }

    m_pModule= PyImport_ImportModule(modelName);
    if(nullptr == m_pModule)
    {
        qDebug() << __FUNCTION__ << " pModule is NULL,please check init model name." << QString(modelName);
        return false;
    }

    qDebug() << "init python model ok";

    return true;
}

bool KPythonRunScriptImpl::bPyValid()
{
    if(nullptr == m_pModule)
    {
        return false;
    }

    return true;
}

KPythonRunScript::KPythonRunScript(const char *modelName)
    : m_pImple(new KPythonRunScriptImpl(modelName))
{
}

KPythonRunScript *KPythonRunScript::instance(const char *modelName)
{
    static KPythonRunScript _instance(modelName);

    return &_instance;
}

KPythonRunScript::~KPythonRunScript()
{
    delete m_pImple;
    m_pImple = nullptr;
}

bool KPythonRunScript::callFun(const char *funcName, const QVariantList &args, QVariant &returnValue)
{
    //qDebug() << __FUNCTION__  << args;
    if(!m_pImple->bPyValid())
    {
        qDebug() << __FUNCTION__ << " python init fail, model is NULL.";
        return false;
    }

    PyObject *pFunObj = PyObject_GetAttrString(m_pImple->m_pModule, funcName);
    if(nullptr == pFunObj)
    {
        qDebug() << __FUNCTION__ << " get python fun obj fail." << QString(funcName);
        return false;
    }

    PyObject *pArgsObj = PyTuple_New(args.size());

    for(int index = 0; index < args.size(); index++)
    {
        QVariant arg = args[index];
        switch (arg.type())
        {
        case QVariant::String:
        {
            // 这里要进行编码转换，python 使用的是 UTF-8 编码
            QByteArray baContent = arg.toString().toLocal8Bit();
            PyTuple_SetItem(pArgsObj, index, Py_BuildValue("s", baContent.constData()));
        }
            break;
        case QVariant::Int:         PyTuple_SetItem(pArgsObj, index, Py_BuildValue("i", arg.toInt()));                                      break;
        case QVariant::Double:      PyTuple_SetItem(pArgsObj, index, Py_BuildValue("d", arg.toDouble()));                                   break;
        case QVariant::LongLong:    PyTuple_SetItem(pArgsObj, index, Py_BuildValue("l", arg.toLongLong()));                                 break;
        case QVariant::Char:        PyTuple_SetItem(pArgsObj, index, Py_BuildValue("b", arg.toChar().toLatin1()));                          break;
        case QVariant::Invalid:     PyTuple_SetItem(pArgsObj, index, Py_BuildValue("()"));                                                  break;
        default: break;
        }
    }

    // run function
    PyObject *pReturnObj = PyObject_CallObject(pFunObj, pArgsObj);

    if (nullptr == pReturnObj)
    {
        qDebug() << __FUNCTION__ << " pReturnObj is NULL.";
        return false;
    }

    if(!returnValue.isValid())
    {
        return true;
    }

    switch (returnValue.type())
    {
    case QVariant::String:
    {
        char *sValue = nullptr;
        PyArg_Parse(pReturnObj, "s", sValue);
        returnValue = QVariant::fromValue(QString(sValue));
    }
        break;
    case QVariant::Int:
    {
        int nValue = -1;
        PyArg_Parse(pReturnObj, "i", &nValue);
        returnValue = QVariant::fromValue(nValue);
    }
        break;
    case QVariant::Bool:
    {
        bool bValue = false;
        PyArg_Parse(pReturnObj, "b", &bValue);
        returnValue = QVariant::fromValue(bValue);
    }
        break;
    case QVariant::Double:
    {
        double dValue = -1;
        PyArg_Parse(pReturnObj, "d", dValue);
        returnValue = QVariant::fromValue(dValue);
    }
        break;
    case QVariant::LongLong:
    {
        long long lValue = 0;
        PyArg_Parse(pReturnObj, "l", lValue);
        returnValue = QVariant::fromValue(lValue);
    }
        break;
    default:
        break;
    }

    Py_CLEAR(pFunObj);
    Py_CLEAR(pArgsObj);
    Py_CLEAR(pReturnObj);
    PyGC_Collect();

    return true;
}
