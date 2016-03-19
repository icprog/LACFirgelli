#include <iostream>
#include <libusb-1.0/libusb.h>
#define SET_POSITION    0x20

using namespace std;
libusb_device **devs; 
libusb_device_handle *dev_handle; 
libusb_context *ctx = NULL; 
int r; 
ssize_t cnt;
unsigned char *data = new unsigned char[3]; 

int open(){ 
	r = libusb_init(&ctx); 
	if(r<0){	cout<<"Init Error "<<r<<endl;	return 1;}
	libusb_set_debug(ctx, 3); 
	cnt = libusb_get_device_list(ctx, &devs); 
	if(cnt<0){	cout<<"Get Device Error"<<endl;	return 1;}
		cout<<cnt<<" Devices in list."<<endl;
	dev_handle = libusb_open_device_with_vid_pid(ctx, 1240, 64607); 
	if(dev_handle == NULL)	cout<<"Cannot open device"	<<endl;
	else			cout<<"Device Opened"		<<endl;
	libusb_free_device_list(devs, 1);
}
int send(){
	int actual; 
	if(libusb_kernel_driver_active(dev_handle, 0) == 1) { 
		cout<<"Kernel Driver Active"<<endl;
		if(libusb_detach_kernel_driver(dev_handle, 0) == 0) 
			cout<<"Kernel Driver Detached!"<<endl;
	}
	r = libusb_claim_interface(dev_handle, 0); 
	if(r < 0) {
		cout<<"Cannot Claim Interface"<<endl;
		return 1;
	}
	cout<<"Claimed Interface"<<endl;	
	cout<<"Data->"<<data<<"<-"<<endl; 
	cout<<"Writing Data..."<<endl;
	r = libusb_bulk_transfer(dev_handle, 0x01, data, 3, &actual, 100); 
	if(r == 0 && actual == 3) 
		cout<<"Writing Successful!"<<endl;
	else
		cout<<"Write Error"<<endl;
	
	r = libusb_release_interface(dev_handle, 0); 
	if(r!=0) {
		cout<<"Cannot Release Interface"<<endl;
		return 1;
	}
	cout<<"Released Interface"<<endl;

	libusb_close(dev_handle); 
	libusb_exit(ctx); 

	delete[] data;
}
int main() {
int val;
	open(); 
	cout << "Enter value : "; cin >> val;
	if(val>1023) 	val = 1023;
	if(val<0)	val = 0;

	data[0]=0x20;
	data[1]=(unsigned char) val;
	data[2]=(unsigned char) (val>>8); 
	send(); 
	return 0;
}

