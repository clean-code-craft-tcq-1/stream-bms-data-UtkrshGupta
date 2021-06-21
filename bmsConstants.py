default_bms_param = { 'temperature': 'Temperature ( in celsius )',
                      'soc': 'State of charge ( in % )',
                      'chargingrate': 'Charging Rate ( in coulombs )'  
                    }

bms_param_data_generator_thresholds = { 'temperature': {'lower_limit':-100, 'upper_limit':100},
                                        'soc': {'lower_limit':0, 'upper_limit':100},
                                        'chargingrate': {'lower_limit':0, 'upper_limit':1 }  
                                      }