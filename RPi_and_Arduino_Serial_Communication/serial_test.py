from serial import Serial

ser = Serial('/dev/ttyUSB0',115200)

while True:
	read_serial = ser.readline()
	read_serial = read_serial.decode("utf-8") 
	# print (read_serial)
	read_serial = read_serial.split(",")
	if len(read_serial) > 1 :
		read_serial[-1] = read_serial[-1].replace("\r\n","")
		print (read_serial)
		if read_serial == ['3686744587', '219', '191', '66', '11'] :
			print("True")
			ser.write("DerpHashTurnOn".encode())
		else:
			print("False")
			ser.write("off".encode())
