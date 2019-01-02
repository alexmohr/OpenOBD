//
// Created by me on 01/01/19.
//

#include "CalculatedDataObjectFactory.h"

unique_ptr<CalculatedDataObject<byte, float>> CalculatedDataObjectFactory::volt_ADivided200() {
    return make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0,
            CalculatedValues::toADivided200, CalculatedValues::fromADivided200,
            unit_volt, 0.0f, 1.275f);
}

unique_ptr<CalculatedDataObject<byte, float>>
CalculatedDataObjectFactory::percent_Percent128Minus100(ByteIndex startbyte) {
    return make_unique<CalculatedDataObject<byte, float>>(
            startbyte, 7, startbyte, 0,
            CalculatedValues::toPercent128Minus100, CalculatedValues::fromPercent128Minus100,
            unit_percent, -100.0f, 99.2f);
}

unique_ptr<CalculatedDataObject<byte, float>> CalculatedDataObjectFactory::percent() {
    return make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0, 100);

}

unique_ptr<CalculatedDataObject<byte, short>> CalculatedDataObjectFactory::celsius_AMinus40() {
    return make_unique<CalculatedDataObject<byte, short>>(
            A, 7, A, 0, CalculatedValues::toAMinus40, CalculatedValues::fromAMinus40,
            unit_celsius, -40, 215);
}

unique_ptr<CalculatedDataObject<byte, unsigned short>> CalculatedDataObjectFactory::kPa_3A() {
    return make_unique<CalculatedDataObject<byte, unsigned short>>(
            A, 7, A, 0, CalculatedValues::to3A, CalculatedValues::from3A,
            unit_kPa, 0, 765);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::rpm_divided4() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0, CalculatedValues::to256APlusBDivided4, CalculatedValues::from256APlusBDivided4,
            unit_rpm, 0, 16383.75);
}

unique_ptr<CalculatedDataObject<byte, float>> CalculatedDataObjectFactory::degree_Divided2Minus64() {
    return make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toADivided2Minus64, CalculatedValues::fromADivided2Minus64,
            unit_degree, -64, 63.5);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::gramSec_Divided100() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0, CalculatedValues::to256APlusBDivided100, CalculatedValues::from256APlusBDivided100,
            unit_gramSec, 0, 655.35);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::kPa_0_079Value() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0, CalculatedValues::to0_079_Times256APlusB, CalculatedValues::from0_079_Times256APlusB,
            unit_kPa, 0.0f, 5177.265f);
}

unique_ptr<CalculatedDataObject<unsigned short, unsigned int>> CalculatedDataObjectFactory::kPa_UShortTimes10() {
    return make_unique<CalculatedDataObject<unsigned short, unsigned int>>(
            A, 7, B, 0, CalculatedValues::toUShortTimes10, CalculatedValues::fromUShortTimes10,
            unit_kPa, 0, 655350);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::percent_Divided4TwoComplement() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided4TwoComplement, CalculatedValues::from256APlusBDivided4TwoComplement,
            unit_percent, -8192, 8191.75);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::volt_Divided1000() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided1000, CalculatedValues::from256APlusBDivided1000,
            unit_volt, 0, 65.535f);
}

unique_ptr<CalculatedDataObject<unsigned short, unsigned short>>
CalculatedDataObjectFactory::percent_100Divided255TimesTimes256APlusB() {
    return make_unique<CalculatedDataObject<unsigned short, unsigned short>>(
            A, 7, B, 0,
            CalculatedValues::to100Divided255Times256APlusB, CalculatedValues::from100Divided255Times256APlusB,
            unit_percent, 0, 25700);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::ratio_2Divided2Pow16TimesValue() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to2Divided65536Times256PlusB, CalculatedValues::from2Divided65536Times256PlusB,
            unit_ratio, 0, 1.9999f);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::ratio_8Divided2Pow16TimesValue() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            C, 7, D, 0, CalculatedValues::to8Divided65536Times256PlusB,
            CalculatedValues::from8Divided65536Times256PlusB,
            unit_ratio, 0.0f, 7.9999f);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::celsius_Divided10Minus40() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided10Minus40, CalculatedValues::from256APlusBDivided10Minus40,
            unit_celsius, -40, 6513.5);
}

unique_ptr<CalculatedDataObject<unsigned short, float>> CalculatedDataObjectFactory::mA_ValueMinus128() {
    return make_unique<CalculatedDataObject<unsigned short, float>>(
            C, 7, D, 0,
            CalculatedValues::toAPlusBDivided256Minus128, CalculatedValues::fromAPlusBDivided256Minus128,
            unit_mA, -128.0f, 127.9999f);
}

