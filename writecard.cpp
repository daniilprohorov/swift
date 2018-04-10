#include <QDebug>
#include "writecard.h"
#include "mainwindow.h"
writecard::writecard()
{
}

writecard::~writecard()
{

}

int writecard::auth()
{
    if(encoder.encInit() == 0)
    {
        encoder.init = true;
        encoder.encLoadKey(encoder.encoder_h, encoder.key_const );
        encoder.encDcCard(encoder.encoder_h, 0, encoder.cardsnr);
        encoder.encAuthentication(encoder.encoder_h);
        return 0;
    }
    encoder.init = false;
    return 1;

}

int writecard::guest_write(int hotel_code, int room_num, int floor_num, QDate date_out, QTime time_out,  int lux_options, int extra_options)
{

    QTime time_now = QTime::currentTime();
    QDate date_now = QDate::currentDate();

    Now.s = time_now.second();
    Now.m = time_now.minute();
    Now.h = time_now.hour();
    Now.d = date_now.day();
    Now.M = date_now.month();
    Now.y = date_now.year()%100;

    Out.s = time_out.second();
    Out.m = time_out.minute();
    Out.h = time_out.hour();
    Out.d = date_out.day();
    Out.M = date_out.month();
    Out.y = date_out.year()%100;

    unsigned char data_54[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x05};
    unsigned char data_53[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char data_52[16] = {0x00, 0x00, 0x00, 0x0d, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    char card_type[50] = "GUEST CARD";
    char room_num_str[50] = "";
    char time_now_str[50] = "";
    char date_now_str[50] = "";
    char time_out_str[50] = "";
    char date_out_str[50] = "";
    char extra_options_str0[50] = "EXTRA OPTIONS:  1 2 3 4 5 6 7 8"; //
    char extra_options_str1[50] = "                               "; // for extra options

    char hotel_code_str[50] = "";
    char serial_num_str[50] = "";
    char *lux_str = new char[50];

    for(int i = 0; i < 8; i++){
        if((extra_options & (1<<i)) > 0)
            extra_options_str1[16+i*2] = '+';
    }

    sprintf(room_num_str, "ROOM %d", floor_num*100 + room_num);
    sprintf(time_now_str, "TIME OF WRITE:  %02d:%02d:%02d", Now.h, Now.m, Now.s);
    sprintf(date_now_str, "DATE OF WRITE:  %02d/%02d/%02d", Now.d, Now.M, Now.y);
    sprintf(time_out_str, "TIME OF OUT:    %02d:%02d:%02d", Out.h, Out.m, Out.s);
    sprintf(date_out_str, "DATE OF OUT:    %02d/%02d/%02d", Out.d, Out.M, Out.y);

    switch(lux_options){
        case 3:
        lux_str = "LUX OPTIONS:    A";
        break;

        case 5:
        lux_str = "LUX OPTIONS:    B";
        break;

        case 9:
        lux_str = "LUX OPTIONS:    C";
        break;

        case 11:
        lux_str = "LUX OPTIONS:    D";
        break;
    }



    encoder.log(line, 0);
    encoder.log(card_type);
    encoder.log(room_num_str); //write room num to log file
    encoder.log(time_now_str); //write time of write card to log
    encoder.log(date_now_str); //write date of write card to log
    encoder.log(time_out_str); //write time of out from room to log
    encoder.log(date_out_str); //write date of out from room to log
    encoder.log(extra_options_str0); //write extra options const to log
    encoder.log(extra_options_str1); //write extra options to log
    encoder.log(lux_str); // write lux options to log
    encoder.log(line, 0);

    data_54[0] = room_num;

    data_53[0] = DecToHex(Now.s); //передаем секунды
    data_53[1] = DecToHex(Now.m); // передаем минуты
    data_53[2] = DecToHex(Now.h); // передаем часы

    data_53[3]  = DecToHex(Now.d-1); //передаем день записи -1
    data_53[4] = DecToHex(Now.M); // передаем месяц записи
    data_53[5] = DecToHex(Now.y); // передаем год записи

    data_53[7] = DecToHex(time_out.minute()); // передаем минуты выезда
    data_53[8] = DecToHex(time_out.hour()); // передаем часы выезда

    data_53[9]  = DecToHex(date_out.day()); //передаем день выезда
    data_53[10] = DecToHex(date_out.month()); // передаем месяц выезда
    data_53[11] = DecToHex(date_out.year()%100); // передаем год выезда

    data_52[0] = DecToHex(hotel_code/10000);            //
    data_52[1] = DecToHex((hotel_code/100)%100);        // записываем код гостиницы
    data_52[2] = DecToHex(hotel_code%100);              //

    data_52[6] = DecToHex(floor_num); // записываем этаж

    data_52[8] = DecToHex(lux_options); // опции люкс номеров(A, B, C, D)

    data_52[9] = DecToHex(11); //
    data_52[10] = DecToHex(11);// подставляем вместо номера карты
    data_52[11] = DecToHex(11);//

    data_52[15] = extra_options;
if( encoder.encWrite(encoder.encoder_h, 54, data_54) == 0 &&
    encoder.encWrite(encoder.encoder_h, 53, data_53) == 0 &&
    encoder.encWrite(encoder.encoder_h, 52, data_52) == 0 )
    return 0;
else
    return 1; //return 1 when can't write some block of data to encoder
}

int writecard::guest_set_write(int hotel_code, int room_num, int floor_num, int lux_options)
{
    QTime time_now = QTime::currentTime();
    QDate date_now = QDate::currentDate();

    Now.s = time_now.second();
    Now.m = time_now.minute();
    Now.h = time_now.hour();
    Now.d = date_now.day();
    Now.M = date_now.month();
    Now.y = date_now.year()%100;

    unsigned char data_52[16] = {0x00, 0x00, 0x00, 0x0a, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00};

    char card_type[50] = "GUEST SET CARD";
    char room_num_str[50] = "";
    char time_now_str[50] = "";
    char date_now_str[50] = "";

    char hotel_code_str[50] = "";
    char *lux_str = new char[50];

    sprintf(room_num_str, "ROOM %d", floor_num*100 + room_num);
    sprintf(time_now_str, "TIME OF WRITE:  %02d:%02d:%02d", Now.h, Now.m, Now.s);
    sprintf(date_now_str, "DATE OF WRITE:  %02d/%02d/%02d", Now.d, Now.M, Now.y);

    switch(lux_options){
        case 0xD:
        lux_str = "LUX OPTIONS: DOOR";
        break;

        case 0xE:
        lux_str = "LUX OPTIONS:    A";
        break;

        case 0xF:
        lux_str = "LUX OPTIONS:    B";
        break;

        case 0x10:
        lux_str = "LUX OPTIONS:    C";
        break;

        case 0x11:
        lux_str = "LUX OPTIONS:    D";
        break;
    }



    encoder.log(line, 0);
    encoder.log(card_type);
    encoder.log(room_num_str); //write room num to log file
    encoder.log(time_now_str); //write time of write card to log
    encoder.log(date_now_str); //write date of write card to log
    encoder.log(lux_str); // write lux options to log
    encoder.log(line, 0);

    data_52[0] = DecToHex(hotel_code/10000);            //
    data_52[1] = DecToHex((hotel_code/100)%100);        // записываем код гостиницы
    data_52[2] = DecToHex(hotel_code%100);              //

    data_52[6] = DecToHex(floor_num); // записываем этаж
    data_52[7] = DecToHex(room_num); // записываем номер комнаты

    data_52[8] = DecToHex(Now.s); //передаем секунды
    data_52[9] = DecToHex(Now.m); // передаем минуты
    data_52[10] = DecToHex(Now.h); // передаем часы

    data_52[11]  = DecToHex(Now.d); //передаем день записи
    data_52[12] = DecToHex(Now.M); // передаем месяц записи
    data_52[14] = DecToHex(Now.y); // передаем год записи

    data_52[15] = lux_options; // опции люкс номеров(A, B, C, D)

if(encoder.encWrite(encoder.encoder_h, 52, data_52) == 0)
    return 0;
else
    return 1; //return 1 when can't write  block of data to encoder
}

int writecard::read_to_log()
{
    encoder.encRead(encoder.encoder_h, 54, encoder.dat_read);
    encoder.encRead(encoder.encoder_h, 53, encoder.dat_read);
    encoder.encRead(encoder.encoder_h, 52, encoder.dat_read);

}

unsigned char writecard::DecToHex(int dec)
{
    unsigned char buff = dec / 10;
    buff <<= 4;
    buff |= dec % 10;
    return buff;
}
