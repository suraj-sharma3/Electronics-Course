import time
import serial
data_from_arduino = serial.Serial('com4', 9600)

time.sleep(1)

while True:
    while data_from_arduino.inWaiting() == 0:
        pass
    data_packet = data_from_arduino.readline()
    data_packet_str = str(data_packet, 'utf-8')
    print(data_packet_str)
    # data_packet_str = data_packet_str.strip('\r\n')
    # # print(data_packet_str)

    # split_packet = data_packet_str.split(",")
    # # print(split_packet)

    # # flex1 = split_packet[0]
    # # flex2 = split_packet[1] 
    # flex3 = split_packet[2]

    # # print(flex1)
    # # print(flex2)
    # print(flex3)

