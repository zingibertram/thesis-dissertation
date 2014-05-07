#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>

class TrRu // строковые константы
           // для удобства в отдельном классе
{
public:
    static const QString function;
    static const QString sourceFrag;
    static const QString minFrag;
    static const QString maxFrag;
    static const QString xCort;
    static const QString yCort;
    static const QString dff1;
    static const QString dff2;
    static const QString dff3;
    static const QString dffSqr;
    static const QString stripLength;
    static const QString stripSquareNum;
    static const QString dffMaximum;
    static const QString y;
    static const QString x;
    static const QString dataFiles;
    static const QString openDlgHead;
    static const QString saveResDir;
    static const QString saveGenDir;
    static const QString calcCancel;
    static const QString cancel;
    static const QString defaultSource;
    static const QString resultImgFile;
    static const QString resultDatFile;
    static const QString sourceImgFile;
    static const QString sourceMaxImgFile;
    static const QString sourceMinImgFile;
    static const QString damagedFile;
    static const QString error;
    static const QString damagedInput;
    static const QString damagedCalc;
    static const QString damagedRes;
};

#endif // TRANSLATION_H
