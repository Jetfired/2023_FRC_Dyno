import time
import serial
import pandas as pd
import re

serialPort = serial.Serial(port="COM3", baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

if not serialPort.isOpen():
    serialPort.open()

serialString = ""  # Used to hold data coming over UART
encoderOutput = {
    "Encoder Number": [],
    "Time": [],
    "Encoder Value": [],
    "Direction": [],
}
    
print("start")
start_time = time.time()
while (float(time.time()) - start_time) < 5.0:
    #print("start")
    # Wait until there is data waiting in the serial buffer
    if serialPort.in_waiting > 0:
        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.readline()
        serialString = serialString.decode("Ascii")
        # Print the contents of the serial data
        try:
            print(serialString)
            serialString = re.sub(r'[a-zA-Z:]', '', serialString)
            for value, key in enumerate(encoderOutput):
                if serialString.find("|") == -1:
                    encoderOutput[key].append(serialString.strip())
                    break
                encoderOutput[key].append(serialString[:serialString.find("|")].strip())
                serialString = serialString[serialString.find("|")+1:]
        except:
            pass
    #print("end")
print(encoderOutput)           
data = pd.DataFrame(encoderOutput)
print(data)
data.to_excel("data.xlsx", index=False, freeze_panes=[1, 0])
