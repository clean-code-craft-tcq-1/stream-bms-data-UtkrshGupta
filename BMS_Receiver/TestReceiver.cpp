#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "BMS_Receiver.h"
#include <cmath>

string dummy_data[6] = {"{\"temperature\" : 92.11,\"soc\" : 62.55,\"chargingrate\" : 0.4 }",
			"{\"temperature\" : -36.23,\"soc\" : 8.38,\"chargingrate\" : 0.1}", 
			"{\"temperature\" : 28.43,\"soc\" : 5.82,\"chargingrate\" : 0.5}", 
			"{\"temperature\" : 46.25,\"soc\" : 21.13,\"chargingrate\" : 0.8}", 
			"{\"temperature\" : 52.10,\"soc\" : 34.08,\"chargingrate\" : 1.0}", 
			"{\"temperature\" : -24.01,\"soc\" : 84.86,\"chargingrate\" : 0.08}"
                       };

bool compare_float(float x, float y, float epsilon = 0.01f) {
	if (fabs(x - y) < epsilon)
		return true; 
	return false; 
}

TEST_CASE("validate sender data")
{
    CBMSReceiver receiver;
    BmsParamters params;
	
    for (int i = 0; i < 6; i++)
    {
        REQUIRE(receiver.ParseDataFromConsole(dummy_data[i], params));
        auto& list = receiver.GetBmsDataContainer();
	list.push_back(params);		
    }

	//validate list size
	REQUIRE(receiver.GetBmsDataContainer().size() == 6);

	receiver.CalculateBmsParamStatistics();
	auto& stat = receiver.GetParameterStats();

	//positive test cases - validate paramters with expected output after calculation
	REQUIRE(compare_float(stat.minTemperature , -36.23));
	REQUIRE(compare_float(stat.maxTemperature , 92.11));
	REQUIRE(compare_float(stat.minSoc , 5.82));
	REQUIRE(compare_float(stat.maxSoc , 84.86));
	REQUIRE(compare_float(stat.minChargeRate , 0.08));
	REQUIRE(compare_float(stat.maxChargeRate, 1.0));
    	REQUIRE(compare_float(stat.avgTemperature, 13.308));
    	REQUIRE(compare_float(stat.avgSoc, 30.854));
    	REQUIRE(compare_float(stat.avgChargeRate, 0.496));

	//Negative test by injecting inappropriate json format
    	string data = "aa bb cc";
	REQUIRE(!receiver.ParseDataFromConsole(data, params));
    	data = "{\"Temperature:-32,\"SOC\" : 36}";
	REQUIRE(!receiver.ParseDataFromConsole(data, params));
    	data = "{\"Temperature:one,\"SOC\" : two}";
	REQUIRE(!receiver.ParseDataFromConsole(data, params));
}
