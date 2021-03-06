import serial
import csv
import datetime

dylos_comport = '/dev/cu.usbserial'
baud = 9600
tm = 100


def sync_timing(dylos_comport, baud, tm):
	with serial.Serial(dylos_comport, baud, timeout=tm, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE) as ser:
		line = ser.readline()

def read_data(dylos_comport, baud, tm, csvname, sample_id):
	with serial.Serial(dylos_comport, baud, timeout=tm, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE) as ser:
		line = ser.readline()
		dylos_data = extract_dylos_counts(line)
		write_to_csv(sample_id, dylos_data[0], dylos_data[1], csvname)

def extract_dylos_counts(line):
	if not line:
		print "Failed Dylos Read"
		return [0,0]
	else:
		comma = line.index(',')
		small_count = line[0:comma]
		carriage_return = line.index('\r')
		large_count = line[comma+1:carriage_return]
		return [small_count, large_count]

# small, large, date/time
def write_to_csv(sample_id, small, large, csvname):
	with open(csvname, 'a') as csvfile:
		print "Dylos: ", small, large
		w = csv.writer(csvfile)
		w.writerow([sample_id, datetime.datetime.now(), small, large])
