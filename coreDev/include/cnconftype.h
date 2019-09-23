#ifndef CNCONFTYPE_H
#define CNCONFTYPE_H

#include <QString>
#include <QMap>

enum CN_PARAM_VAL_TYPE
{
    PVT_BOOL,           /* bool */

    PVT_I32,
    PVT_F32,

    PVT_ARR_I32,
    PVT_ARR_F32,

    PVT_UI32,

    PVT_ARR_UI32,

    PVT_STRING,
    PVT_STRINGLIST,

    PVT_ETC1,           /* QString, int */
    PVT_ETC2,
    PVT_ETC3,
    PVT_ETC4,
    PVT_ETC5,
    PVT_ETC6,
};


/**
 * @brief The CORE_LANG enum
 *   language
 */
enum CN_LANG
{
    CN_LANG_EN_US,  // default
    CN_LANG_KO,  // korean
    CN_LANG_ZH_CN,  // chinese simplified
    CN_LANG_ZH_TW,  // chinese taiwan
    CN_LANG_DE_DE,    // german
    CN_LANG_JP_JP,
};

#define CN_MAX_AXIS_SIZE 32


#endif // CNCONFTYPE_H
