#ifndef _BMS_RECEIVER_H
#define _BMS_RECEIVER_H

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#define TEMP_JSON_INDEX     1
#define SOC_JSON_INDEX      3
#define CR_JSON_INDEX       5

typedef struct BmsData
{
    string jsonData;
    float temperature;
    float stateOfCharge;
    float chargeRate;
}BmsData;

class CBMSReceiver
{
private:
    vector<BmsData> m_bmsDataContainer;
    float           m_minTemperature;
    float           m_maxTemperature;
    float           m_minSoc;
    float           m_maxSoc;
    float           m_minChargeRate;
    float           m_maxChargeRate;
    float           m_avgTemperature;
    float           m_avgSoc;
    float           m_avgChargeRate;

    void ParseDataFromConsole(string& , BmsData& );
    void CalcSimpleMovingAverage();

    inline void SetMinTemperature(float temperature)
    { 
        m_minTemperature = temperature;
    }

    inline void SetMaxtemperature(float temperature)
    {
        m_maxTemperature = temperature;
    }

    inline void SetMinStateOfCharge(float soc)
    {
        m_minSoc = soc;
    }

    inline void SetMaxStateOfCharge(float soc)
    {
        m_maxSoc = soc;
    }

    inline void SetMinChargeRate(float cr)
    {
        m_minChargeRate = cr;
    }

    inline void SetMaxChargeRate(float cr)
    {
        m_maxChargeRate = cr;
    }

public:
    void GetDataFromConsole();
};

#endif