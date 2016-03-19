#include <iostream>
#include <libusb-1.0/libusb.h>
#define SET_POSITION    0x20

using namespace std;
libusb_device **devs; 
libusb_device_handle *dev_handle; 
libusb_context *ctx = NULL; 
int r,val,act;
uint8_t i; 
ssize_t cnt;
unsigned char *data = new unsigned char[3]; 
int open(){ 
	r = libusb_init(&ctx); 	
	if(r<0)  {	cout<<"Init Error "<<r<<endl;	return 1;}
	libusb_set_debug(ctx, 3); 
	cnt = libusb_get_device_list(ctx, &devs); 
	if(cnt<0){	cout<<"Get Device Error"<<endl;	return 1;}
			cout<<cnt<<" Devices in list."<<endl;
	dev_handle = libusb_open_device_with_vid_pid(ctx, 1240, 64607); 
	if(dev_handle == NULL)	cout<<"Cannot open device"	<<endl;
	else			cout<<"Device Opened"		<<endl;
	libusb_free_device_list(devs, 1);
}

int send(int val){
	data[0]=0x20;
	data[1]=(unsigned char) val;
	data[2]=(unsigned char) (val>>8);
	r = libusb_bulk_transfer(dev_handle, 0x01, data, 3, &act, 100); 
	libusb_close(dev_handle); 
	libusb_exit(ctx); 
	delete[] data;
}
int main() {
	open(); 
	cout << "Enter value : "; cin >> val;
	if(val>1023) 	val = 1023;
	if(val<0)	val = 0;
	send(val); 
	return 0;
}

