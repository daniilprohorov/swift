#ifndef WRITECARD_H
#define WRITECARD_H
#include <QDateTime>
#include "enc.h"


class writecard
{

public:
    enc encoder;
    const int hotel_code_test = 651838; //315368; // test number of hotel

    char line[60] = "-------------------------------------------------";

    struct DateTime{
        int s, m, h, d, M, y;
    };

    DateTime Now;
    DateTime Out;


    writecard();
    ~writecard();

    //function to write guests cards
    int guest_write(int hotel_code, int room_num, int floor_num, QDate date_out, QTime time_out, int lux_options, int extra_options);

    //function to write guests set cards
    int guest_set_write(int hotel_code, int room_num, int floor_num, int lux_options);

    //function to read card, only to log
    int read_to_log();

    //function to authorization card(init/loadkey/DcCard/authorization)
    int auth();

    //return var in HEX, stylish like DEC
    unsigned char DecToHex(int Dec);
};

#endif // WRITECARD_H
