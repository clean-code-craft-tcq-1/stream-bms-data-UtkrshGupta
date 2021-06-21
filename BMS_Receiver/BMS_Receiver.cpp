#include "BMS_Receiver.h"
#include <algorithm>

void CBMSReceiver::ParseDataFromConsole(string& data, BmsParamters& params)
{
    string dataCopy = data;
    dataCopy.resize(dataCopy.size() - 1);
    stringstream str(dataCopy);
    string subString[7];

    for (int i = 0; i < 7; ++i)
    {
        str >> subString[i];
    }

    params.jsonData = data;
    params.temperature = std::stof(subString[TEMP_JSON_INDEX]);
    params.stateOfCharge = std::stof(subString[SOC_JSON_INDEX]);
    params.chargeRate = std::stof(subString[CR_JSON_INDEX]);
}

void CBMSReceiver::PerformMinMaxCalculation()
{

    auto data = std::minmax_element(begin(m_bmsDataContainer), end(m_bmsDataContainer), 
                                    [](BmsParamters& p1, BmsParamters& p2)
                                    {
                                        return p1.temperature < p2.temperature; 
                                    });

    m_paramstat.minTemperature = data.first->temperature;
    m_paramstat.maxTemperature = data.second->temperature;

    data = std::minmax_element(begin(m_bmsDataContainer), end(m_bmsDataContainer), 
                                    [](BmsParamters& p1, BmsParamters& p2)
                                    {
                                        return p1.stateOfCharge < p2.stateOfCharge; 
                                    });

    m_paramstat.minSoc = data.first->stateOfCharge;
    m_paramstat.maxSoc = data.second->stateOfCharge;

    data = std::minmax_element(begin(m_bmsDataContainer), end(m_bmsDataContainer), 
                                    [](BmsParamters& p1, BmsParamters& p2)
                                    {
                                        return p1.chargeRate < p2.chargeRate; 
                                    });

    m_paramstat.minChargeRate = data.first->chargeRate;
    m_paramstat.maxChargeRate = data.second->chargeRate;
}

void CBMSReceiver::PerformSimpleMovingAverage()
{
                 
}

void CBMSReceiver::CalculateBmsParamStatistics()
{
    PerformMinMaxCalculation();
    PerformSimpleMovingAverage();        
}

void CBMSReceiver::GetDataFromConsole()
{
    std::string data;
    bool init = true;
    for (int i = 0; i < 5; ++i)
    {
        BmsParamters param;
        std::getline(std::cin, data);
        ParseDataFromConsole(data, param); 
        m_bmsDataContainer.push_back(param);
        CalculateBmsParamStatistics();
    }
}
