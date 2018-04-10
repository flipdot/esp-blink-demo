all:
	platformio run -e d1_mini -t upload --upload-port=/dev/ttyUSB0
