//#include "stdafx.h"
#include "enc.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <ctime>

using namespace std;

ofstream logfile("log.txt", ios_base::app);

enc::enc()
{
	encInit();
}


enc::~enc()
{
	dc_exit(encoder_h);
	logfile.close();
}


//������� �������������
int enc::encInit(int port, long baud)
{
	encoder_h = dc_init(port, baud);
	if (encBeep(encoder_h) == 0) {
		
		init = true;

		logfile << "\n" << encTime() <<"|    - " << " INIT COMPLETE" << endl;
		

		return 0; 
	}
	else {
		init = false;
		
		logfile << "\n" << encTime() << "|    - " << " INIT ERROR" << endl;
		return 1; 
	}
	
}


//������� ������������ ��������� ������
int enc::encBeep(HANDLE encoder)
{
    if (dc_beep(encoder, beep_time) == 0) {
		
		return 0;  // BEEP COMPLETE
	}
	else {
		
		return 1; // BEEP ERROR 
	}
	
}


//������� �������� ����� � �������
int enc::encLoadKey(HANDLE encoder, unsigned char* key, unsigned char mode, unsigned char sector)
{
	

	if (dc_load_key(encoder, mode, sector, key) == 0) {

		
		logfile << encTime() << "|    - " << " LOAD KEY COMPLETE" << endl;
		return 0;  
	}
	else {

		logfile << encTime() << "|    - " << " LOAD KEY ERROR" << endl;
		return 1; 
	}
	
}


//������� ������ ����� 
int enc::encDcCard(HANDLE encoder, unsigned char mode, unsigned long card_num)
{
	if (dc_card(encoder, mode, &card_num) == 0) {

		logfile << encTime() << "|    - " << " DETECT CARD COMPLETE " << card_num << endl;
		return 0;
	}
	else {

		logfile << encTime() << "|    - " << " DETECT CARD ERROR" << endl;
		return 1;
	}

}


//������� ��������������� �����
int enc::encAuthentication(HANDLE encoder, unsigned char mode, unsigned char sector)
{
	if (dc_authentication(encoder, mode, sector) == 0) {
		
		//encBeep(encoder_h);
		logfile << encTime() << "|    - " << " AUTHENTICATION COMPLETE" << endl;
		return 0;  
	}
	else {

		logfile << encTime() << "|    - " << " AUTHENTICATION ERROR!" << endl;
		return 1;  
	}
}


//������� ���������� ����� 16 ���� �� ����� ������������������ �����
int enc::encRead(HANDLE encoder, int block, unsigned char data[16])
{
	if (dc_read(encoder, block, data) == 0) {

		encBeep(encoder_h);

		logfile << encTime() << "|    - " << " READ CARD COMPLETE. DATA : ";
		for (int i = 0; i < 16; i++) {
			logfile << hex << setw(8) <<(int)data[i];
		}
		logfile << " from block : "<< dec << block << endl;
		
		return 0;  
	}
	else {
		logfile << encTime() << "|    - " << " READ CARD ERROR!" << endl;
		return 1; 
	}
}


//������� ������ ����� 16 ���� � ���� �����
int enc::encWrite(HANDLE encoder, int block, unsigned char data[16])
{
	if (dc_write(encoder, block, data) == 0) {

		encBeep(encoder_h);

		logfile << encTime() << "|    - " << " WRITE DATA : ";
		for (int i = 0; i < 16; i++) {
			logfile << hex << setw(3) << (int)data[i];
		}
		logfile << " to block : " << dec<< block << " COMPLETE"  << endl;
		
		return 0;
	}
	else {
		logfile << encTime() << "|    - " << " WRITE CARD DATA ";
		for (int i = 0; i < 16; i++) {
			logfile << hex << setw(3) << (int)data[i];
		}
		logfile << " to block : "<< dec << block << " ERROR!" << endl;
		return 1;
	}
}

char * enc::encTime()
{
    time_t rawtime;
    struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char *str_out = new char[30];
    strftime(str_out, 30, "%d/%m/%y  %X", timeinfo);
    return str_out;

}
//write to log file
int enc::log(char *text, boolean time){
    if(time == true)
        logfile << encTime() << "|    -  " << text << endl;
    else
        logfile << text << endl;

}


