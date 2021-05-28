import unittest
from bmsStreaming import BmsStreaming
from bmsDataGenerator import DataGenerator

class BmsStreamingTest(unittest.TestCase):
    def test_bms_data_generation(self):
        bms = BmsStreaming(1234)
        generator = DataGenerator()
        bms_param = generator.generate_bms_data(seed_value=1234)
        log = bms.bms_send_and_logging(1)
        self.assertEqual(log[0][0],bms_param)
    
    def test_ok_send_status(self):
        bms = BmsStreaming()
        self.assertEqual(bms.send_to_console({'temperature': 43, 'soc':40, 'charging rate': 0.5}),'OK')
        
    def test_not_send_status(self):
        bms = BmsStreaming()
        self.assertEqual(bms.send_to_console({'temperature': 43, 'soc':40}),'NOT_SENT')
        
    def test_format_of_return_bms_param_and_log(self):
        bms = BmsStreaming(1234)
        generator = DataGenerator()
        bms_param = generator.generate_bms_data(seed_value=1234)
        log = bms.bms_send_and_logging(1)
        self.assertEqual(type(bms_param), dict)
        self.assertEqual(type(log), list) 
        
if __name__ == '__main__':
  unittest.main()