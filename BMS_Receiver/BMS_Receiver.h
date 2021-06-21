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
#define SMA_MAX_LEN         5

typedef struct 
{
    string jsonData;
    float temperature;
    float stateOfCharge;
    float chargeRate;
}BmsParamters;

typedef struct
{
    float           minTemperature;
    float           maxTemperature;
    float           minSoc;
    float           maxSoc;
    float           minChargeRate;
    float           maxChargeRate;
    float           avgTemperature;
    float           avgSoc;
    float           avgChargeRate;
}BmsParamStats;

class CBMSReceiver
{
private:
    vector<BmsParamters> m_bmsDataContainer;
    BmsParamStats        m_paramstat;
    float                m_temperature[SMA_MAX_LEN];
    float                m_stateOfCharge[SMA_MAX_LEN];
    float                m_chargeRate[SMA_MAX_LEN];
    
public:
    
    CBMSReceiver()
    {
        memset(m_temperature, 0.0, sizeof(m_temperature));
        memset(m_stateOfCharge, 0.0, sizeof(m_stateOfCharge));
        memset(m_chargeRate, 0.0, sizeof(m_chargeRate));
    }

    vector<BmsParamters>& GetBmsDataContainer();

    BmsParamStats& GetParameterStats();

    bool ParseDataFromConsole(string , BmsParamters& );
    
    void PerformMinMaxCalculation();

    void PerformSimpleMovingAverage();

    void CalculateBmsParamStatistics();

    void PrintDataToConsole();

    void GetDataFromConsole();
};

#endif
