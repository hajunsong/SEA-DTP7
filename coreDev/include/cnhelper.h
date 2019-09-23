#ifndef NRHELPER_H
#define NRHELPER_H


#include <QString>
#include "cntype.h"

class CNHelper
{
public:

    static char* toMultiByteCode(const QString& qstr);
    static void translateArrVarName(QString name, int& index, QString& vName);

    static void tmatToFArr(cn_trans2* tMatIn, float* fArrOut, bool trackOption = false);
    static void fArrToTMat(float* fArrIn, cn_trans2* tMatOut, bool trackOption = false);

    static void transToFArr(cn_trans* trIn, float* fArrOut, bool trackOption = false);
    static void fArrToTrans(float* fArrIn, cn_trans* trOut, bool trackOption = false);

};

#endif // NRHELPER_H
