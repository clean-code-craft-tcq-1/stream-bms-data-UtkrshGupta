#include "BMS_Receiver.h"

void CBMSReceiver::ParseDataFromConsole(string& data, BmsData& params)
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

void CBMSReceiver::GetDataFromConsole()
{
    std::string data;
    bool init = true;
    for (int i = 0; i < 5; ++i)
    {
        BmsData param;
        std::getline(std::cin, data);
        ParseDataFromConsole(data, param); 
        m_bmsDataContainer.push_back(param);
        if (init)
        {
            m_maxTemperature = m_minTemperature = m_bmsDataContainer.at(i).temperature;
            m_maxSoc = m_minSoc = m_bmsDataContainer.at(i).stateOfCharge;
            m_maxChargeRate = m_minChargeRate = m_bmsDataContainer.at(i).chargeRate;
        }
        

    }
}
