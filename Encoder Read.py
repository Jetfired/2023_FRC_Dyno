import serial
import time
import pandas as pd

serialPort = serial.Serial(
    port="COM3", baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)

serialString = ""  # Used to hold data coming over UART
encoderOutput = {
    "Time": [],
    "Encoder Number": [],
    "Encoder Value": [],
}
    
while 1:
    # Wait until there is data waiting in the serial buffer
    if serialPort.in_waiting > 0:

        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.readline()
        serialString = serialString.decode("Ascii")
        
        time = serialString[:serialString.find("|")]
        encoderNumber = serialString[serialString.find("|")+1:serialString.rfind("|")]
        encoderValue = serialString[serialString.rfind("|")+1:]

        # Print the contents of the serial data
        try:
            print(serialString)
            encoderOutput["Time"].append(time)
            encoderOutput["Encoder Number"].append(encoderNumber)
            encoderOutput["Encoder Value"].append(encoderValue)
        except:
            pass
            
data = pd.DataFrame(encoderOutput)
print(data)