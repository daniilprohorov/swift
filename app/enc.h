#ifndef ENC_H
#define ENC_H
#include <QFile>
#include <QTextStream>
#include <windows.h>
#include "dcrf32.h"
#include <string>

using namespace std;

class enc{
public:


    boolean init = false;
    HANDLE encoder_h; //handle for device

	unsigned char key_const[7] = {0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char dat_read[16]; // var for read
	unsigned char dat_write[16]; // var for write
    unsigned long cardsnr;

    const int beep_time = 10; //long of time to beep
	enc();
	~enc();
	int encInit(int port = 100, long baud = 125200);
    int encBeep(HANDLE encoder);
    int encLoadKey(HANDLE encoder, unsigned char* key, unsigned char mode = 0, unsigned char sector = 1);
    int encDcCard(HANDLE encoder, unsigned char mode, unsigned long card_num);
    int encAuthentication(HANDLE encoder, unsigned char mode = 0, unsigned char sector = 13);
    int encRead(HANDLE encoder, int block, unsigned char data[16] );
    int encWrite(HANDLE encoder, int block, unsigned char data[16]);
    int log(char *text, boolean time = true);
	char* encTime();
};

#endif // ENC_H
