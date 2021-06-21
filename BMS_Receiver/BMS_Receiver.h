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

typedef struct
{
    
}BmsSmaArrays;

class CBMSReceiver
{
private:
    vector<BmsParamters> m_bmsDataContainer;
    BmsParamStats        m_paramstat;
    int                  pos;
    float                m_temprature[SMA_MAX_LEN];
    float                m_stateOfCharge[SMA_MAX_LEN];
    float                m_chargeRate[SMA_MAX_LEN];

    bool ParseDataFromConsole(string& , BmsParamters& );
    
    void PerformMinMaxCalculation();

    void PerformSimpleMovingAverage();

    void CalculateBmsParamStatistics();

    void PrintDataToConsole();

public:
    
    CBMSReceiver()
    {
        pos = 0;
        memset(m_temprature, 0.0, SMA_MAX_LEN);
        memset(m_stateOfCharge, 0.0, SMA_MAX_LEN);
        memset(m_chargeRate, 0.0, SMA_MAX_LEN);
    }

    void GetDataFromConsole();
};

#endif
