from bmsDataGenerator import DataGenerator
from bmsConstants import default_bms_param
import json
import time

class BmsStreaming():
    def __init__(self, seed_value=None):
        self.DataGenerator = DataGenerator()
        self.seed_value = seed_value
    
    def bms_send_and_logging(self, stop):
        bms_log = []
        for counter in range(stop):
            bms_param_data = self.DataGenerator.generate_bms_data(self.seed_value)
            send_status = self.send_to_console(bms_param_data, counter)
            #time.sleep(0.5) # Sleep for 500 milliseconds
        bms_log.append([bms_param_data,send_status])
        return bms_log
            
    def send_to_console(self, data, index=0):
        if len(data) < len(default_bms_param):
            return 'NOT_SENT'
        
        json_data = json.dumps(data)
        print(json_data)
        return 'OK'

if __name__ == '__main__':
    #stop = int(input('Enter Total Number of Data Sample Required:'))
    bms = BmsStreaming()
    bms.bms_send_and_logging(100)
