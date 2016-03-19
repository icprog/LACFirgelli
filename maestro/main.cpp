#include <iostream>
#include <libusb.h>
#define SET_POSITION 0x20
#define BYTE uint8_t

using namespace std;
unsigned char bytes[3];

libusb_device_handle *dev;

int main(){
	unsigned char *outdata; 
	dev = libusb_open_device_with_vid_pid( NULL, 0x04d8, 0xfc5f );
        int value;
        int servo=0;
	outdata = "a";
        cout << "Enter position: ";
        cin >> value;
	if (value > 1023) value = 1023;
	if (value < 0) value = 0;
	bytes[0] = SET_POSITION;
	bytes[1] = (unsigned char) value;			
        bytes[2] = (unsigned char) (value >> 8); 		
        libusb_bulk_write(dev, 0x20, outdata, 3, &bytes, 0);
    	libusb_close(dev);
	return 0;
}
