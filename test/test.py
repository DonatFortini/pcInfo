from unittest import TestCase
from pcInfo.Serialcon import *


class test(TestCase):

    def testBoard():
        assert get_serial_port() == "/dev/ttyACM0"

    def testCpu():
        assert type(get_cpu_values()[0]) == int



if __name__ == '__main__':
    test.testBoard()
    test.testCpu()