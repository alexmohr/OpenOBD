//
// Created by me on 01/01/19.
//

#ifndef OPEN_OBD2_CALCULATEDDATAOBJECTFACTORY_H
#define OPEN_OBD2_CALCULATEDDATAOBJECTFACTORY_H

#include "CalculatedDataObject.h"

class CalculatedDataObjectFactory {
public:
    static unique_ptr<CalculatedDataObject<byte, float>> volt_ADivided200(string description);

    static unique_ptr<CalculatedDataObject<byte, float>>
    percent_Percent128Minus100(ByteIndex startbyte, string description);

    static unique_ptr<CalculatedDataObject<byte, float>> percent(string description);

    static unique_ptr<CalculatedDataObject<byte, short>> celsius_AMinus40(string description);

    static unique_ptr<CalculatedDataObject<byte, unsigned short>> kPa_3A(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> rpm_divided4(string description);

    static unique_ptr<CalculatedDataObject<byte, float>> degree_Divided2Minus64(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> gramSec_Divided100(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> kPa_0_079Value(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, unsigned int>> kPa_UShortTimes10(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> percent_Divided4TwoComplement(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> volt_Divided1000(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, unsigned short>>
    percent_100Divided255TimesTimes256APlusB(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> ratio_2Divided2Pow16TimesValue(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> ratio_8Divided2Pow16TimesValue(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> celsius_Divided10Minus40(string description);

    static unique_ptr<CalculatedDataObject<unsigned short, float>> mA_ValueMinus128(string description);
};


#endif //OPEN_OBD2_CALCULATEDDATAOBJECTFACTORY_H
