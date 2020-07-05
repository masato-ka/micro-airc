import sys 
import argparse
import time
import csv
try:
    import serial
except ImportError:
    print("Please install PySerial 'pip install pyserial' .")


def main(args):
    print("Start recording.")
    counter = 0
    with serial.Serial(args.port,9600) as ser:
        with open(args.file, 'w') as f:
            writer = csv.writer(f)
            while True:
                counter += 1
                a = ser.readline().decode().strip().split(",")
                writer.writerow(a)
                if (counter % 100) == 0:
                    print("count: {}".format(counter))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='airc-micro tools. Save trainig data from airc-car.')
    parser.add_argument('-p', '--port', type=str, help='Specify serial port.')
    parser.add_argument('-f', '--file', type=str, help='Specify save file name.')
    args = parser.parse_args()
    print("Waiting 10seconds.")
    time.sleep(10)
    main(args)
