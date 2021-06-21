#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "BMS_Receiver.h"
#include <algorithm>

bool CBMSReceiver::ParseDataFromConsole(string& data, BmsParamters& params)
{
    std::stringstream ss;
    ss.str(data);

    try
    {
        boost::property_tree::ptree pt;
	boost::property_tree::read_json(ss, pt);
    	params.jsonData = data;
    	params.temperature = pt.get<float>("temperature");
    	params.stateOfCharge = pt.get<float>("soc");
    	params.chargeRate = pt.get<float>("chargingrate");
    }
    catch(std::exception const& e)
    {
	std::cerr << e.what() << std::endl;
	return false;
    }

    return true;
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

static float MovingAvg(float* ptrArrNum, float* ptrSum, int pos, int len, float nextNum)
{
    //Subtract the oldest number from the prev sum, add the new number
    *ptrSum = *ptrSum - ptrArrNum[pos] + nextNum;
    //Assign the nextNum to the position in the array
    ptrArrNum[pos] = nextNum;
    //return the average
    return *ptrSum / len;
}

void CBMSReceiver::PerformSimpleMovingAverage()
{
    int pos = 0;
    float sum, tTemp, tSoc, tCr;

    tTemp = tSoc = tCr = 0;
    // Moving average of temperature, SoC, CR
    for (size_t i = 0; i < m_bmsDataContainer.size(); ++i)
    {
        sum = tTemp;
        m_paramstat.avgTemperature = MovingAvg(m_temperature, &sum, pos, SMA_MAX_LEN, m_bmsDataContainer.at(i).temperature);
        tTemp = sum;

        sum = tSoc;
        m_paramstat.avgSoc = MovingAvg(m_stateOfCharge, &sum, pos, SMA_MAX_LEN, m_bmsDataContainer.at(i).stateOfCharge);
        tSoc = sum;

        sum = tCr;
        m_paramstat.avgChargeRate = MovingAvg(m_chargeRate, &sum, pos, SMA_MAX_LEN, m_bmsDataContainer.at(i).chargeRate);
        tCr = sum;

        pos++;
        if (pos >= SMA_MAX_LEN)
        {
            pos = 0;    
        }
    }
}

void CBMSReceiver::CalculateBmsParamStatistics()
{
    PerformMinMaxCalculation();
    PerformSimpleMovingAverage();
}

void CBMSReceiver::PrintDataToConsole()
{
    cout << "________________BMS Statistrics________________" << endl;

    cout << "Minimum temperature        : " << m_paramstat.minTemperature << endl;
    cout << "Maximum temperature        : " << m_paramstat.maxTemperature << endl;
    cout << "Minimum state of charge    : " << m_paramstat.minSoc << endl;
    cout << "Maximum State of charge    : " << m_paramstat.maxSoc << endl;
    cout << "Minimum charge rate        : " << m_paramstat.minChargeRate << endl;
    cout << "Maximum charge rate        : " << m_paramstat.maxChargeRate << endl;
    cout << "Moving average temperature : " << m_paramstat.avgTemperature << endl;
    cout << "Moving average SOC         : " << m_paramstat.avgSoc << endl;
    cout << "Moving average charge rate : " << m_paramstat.avgChargeRate << endl;
 }

void CBMSReceiver::GetDataFromConsole()
{
    std::string data;
    for (int i = 0; i < 100; ++i)
    {
        BmsParamters param;
        std::getline(std::cin, data);
        if (ParseDataFromConsole(data, param))
	{
            m_bmsDataContainer.push_back(param);
	}	
    }
    CalculateBmsParamStatistics();
    PrintDataToConsole();
}

