# DHT Lib 

DEPENDENCY LIBS for build: [WiringPi](https://github.com/WiringPi/WiringPi)

Read data from DHT11 or DHT22 for RaspberryPi.

For connection using pinout GPIO4 *(7 pin for Raspberry PI 3)*

**Install and Test**:

1) sudo apt-get install wiringpi
2) git clone https://github.com/Antowka/DHTLIB.git
2) cd DHTLIB
3) make clean && make && make test
4) sudo cp libdht.a /usr/lib
5) sh rebuild.sh
6) ./test

