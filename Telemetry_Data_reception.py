import serial

ser = serial.Serial('COM3', baudrate=57600, timeout=1)


try:
    while True:
        rowData = ser.readline()
        data = rowData.decode('utf-8', errors='ignore')
        print(data)  # 'ignore' ignores the error
except KeyboardInterrupt:
    ser.close()
