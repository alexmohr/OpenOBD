#include <utility>

#include <utility>

//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_DATAOBJECTUNIT_H
#define OPEN_OBD2_DATAOBJECTUNIT_H

#include <string>

using namespace std;

class SiPrefix {
private:
    string name;
    string symbol;
    int factor;

public:
    SiPrefix(string symbol, string name, int factor) {
        this->name = std::move(name);
        this->symbol = std::move(symbol);
        this->factor = factor;
    }

    string getSymbol() const {
        return symbol;
    }
};


class DataObjectUnit {
private:
    string name;
    string shortName;
    const SiPrefix *prefix;
public:
    DataObjectUnit(string name, string shortName, const SiPrefix *prefix) {
        this->shortName = std::move(shortName);
        this->name = std::move(name);
        this->prefix = prefix;
    }

    string toShortString() const {
        return shortName + prefix->getSymbol();
    }
};

const static SiPrefix si_milli = SiPrefix("k", "kilo", -1000);
const static SiPrefix si_kilo = SiPrefix("k", "kilo", 1000);
const static SiPrefix si_none = SiPrefix("", "", 1);


const static DataObjectUnit unit_bool = DataObjectUnit("Boolean", "", &si_none);
const static DataObjectUnit unit_none = DataObjectUnit("", "", &si_none);

const static DataObjectUnit unit_volt = DataObjectUnit("Volt", "V", &si_none);
const static DataObjectUnit unit_kPa = DataObjectUnit("Pascal", "Pa", &si_kilo);
const static DataObjectUnit unit_celsius = DataObjectUnit("Celsius", "°C", &si_none);
const static DataObjectUnit unit_rpm = DataObjectUnit("Revolutions per Minute", "RPM", &si_none);
const static DataObjectUnit unit_degree = DataObjectUnit("Degree", "°", &si_none);
const static DataObjectUnit unit_gramSec = DataObjectUnit("Grams/Seconds", "g/s", &si_none);
const static DataObjectUnit unit_kph = DataObjectUnit("Kilometer/Hour", "kph", &si_none);
const static DataObjectUnit unit_seconds = DataObjectUnit("Seconds", "s", &si_none);
const static DataObjectUnit unit_percent = DataObjectUnit("Percent", "%", &si_none);
const static DataObjectUnit unit_ratio = DataObjectUnit("Ratio", "", &si_none);
const static DataObjectUnit unit_count = DataObjectUnit("Count", "", &si_none);
const static DataObjectUnit unit_km = DataObjectUnit("Kilometre", "m", &si_kilo);
const static DataObjectUnit unit_mA = DataObjectUnit("Ampere", "A", &si_milli);



#endif //OPEN_OBD2_DATAOBJECTUNIT_H
