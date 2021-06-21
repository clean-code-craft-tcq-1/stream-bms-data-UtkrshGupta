from bmsConstants import default_bms_param
from bmsConstants import bms_param_data_generator_thresholds
import random

class DataGenerator():
    def __init__(self):
        self.__data = None
        self.__bms_param_data = {}
        self.__seed = None
        
    def __define_random_seed(self, value):
        self.__seed = random.seed(value)
        
    def __generator(self, start, stop, seed_value=None):
        if seed_value != None:
            self.__define_random_seed(seed_value)
        self.__data = round(random.uniform(start, stop),2)
        return self.__data
    
    def generate_bms_data(self,seed_value=None):
        for param in default_bms_param.keys():
            self.__bms_param_data[param] = self.__generator(bms_param_data_generator_thresholds[param]['lower_limit'],
                                            bms_param_data_generator_thresholds[param]['upper_limit'], seed_value)
        return self.__bms_param_data
    