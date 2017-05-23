
#include "Tablet.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptor[] PROGMEM = {

    0x05, 0x0c,                    //        Usage Page (Consumer Devices)
    0x09, 0x01,                    //        Usage (Consumer Control)
    0xa1, 0x01,                    //        Collection (Application)
    0x85, 0x04,                    //        REPORT_ID (4)
    0x15, 0x00,                    //        Logical Minimum (0)
    0x25, 0x01,                    //        Logical Maximum (1)
    0x09, 0xe9,                    //        Usage (Volume Up)
    0x09, 0xea,                    //        Usage (Volume Down)
    0x75, 0x01,                    //        Report Size (1)
    0x95, 0x02,                    //        Report Count (2)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xe2,                    //        Usage (Mute)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xb0,                    //        Usage (Play)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xb1,                    //        Usage (Pause)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xcd,                    //        Usage (Play/Pause)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

	0x09, 0xb7,                    //        Usage (Stop)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)
	
    0x09, 0xb5,                    //        Usage (Next)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xb6,                    //        Usage (Previous)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xb3,                    //        Usage (Fast Forward)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0xb4,                    //        Usage (Rewind)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x09, 0x30,                    //        Usage (Power)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)
	
	0x0A, 0x23, 0x02,              //        Usage (WWW_Home)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

	0x0A, 0x21, 0x02,              //        Usage (WWW Search)
    0x95, 0x01,                    //        Report Count (1)
    0x81, 0x06,                    //        Input (Data, Variable, Relative)

    0x95, 0x02,                    //        Report Count (6) Number of bits remaining in byte
    0x81, 0x07,                    //        Input (Constant, Variable, Relative) 
    0xc0                           // END_COLLECTION
};



Tablet_::Tablet_(void)
{
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void Tablet_::begin(void) 
{
}

void Tablet_::end(void) 
{
}

void Tablet_::vol_up(void)
{
        uint8_t m[2];
        m[0] = VOLUME_UP;
        m[1] = 0;
        HID().SendReport(4,m,2);
}
 
void Tablet_::vol_down(void)
{
        uint8_t m[2];
        m[0] = VOLUME_DOWN;
        m[1] = 0;
        HID().SendReport(4,m,2);
}
 
void Tablet_::mute(void)
{
        uint8_t m[2];
        m[0] = VOLUME_MUTE;
        m[1] = 0;
        HID().SendReport(4,m,2);
}
 
void Tablet_::play(void)
{
        uint8_t m[2];
        m[0] = TABLET_PLAY;
        m[1] = 0;
        HID().SendReport(4,m,2);
}
 
void Tablet_::pause(void)
{
        uint8_t m[2];
        m[0] = TABLET_PAUSE;
        m[1] = 0;
        HID().SendReport(4,m,2);
}
 
void Tablet_::play_pause(void)
{
        uint8_t m[2];
        m[0] = TABLET_PLAY_PAUSE;
        m[1] = 0;
        HID().SendReport(4,m,2);
}

void Tablet_::stop(void)
{
	    uint8_t m[2];
	    m[0] = TABLET_STOP;
	    m[1] = 0;
	    HID().SendReport(4,m,2);
}
 
void Tablet_::next(void)
{
        uint8_t m[2];
        m[0] = TABLET_NEXT;
        m[1] = 0;
        HID().SendReport(4,m,2);
}
 
void Tablet_::previous(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = TABLET_PREVIOUS >> 8;
        HID().SendReport(4,m,2);
}
 
void Tablet_::forward(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = TABLET_FAST_FORWARD >> 8;
        HID().SendReport(4,m,2);
}
 
void Tablet_::rewind(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = TABLET_REWIND >> 8;
        HID().SendReport(4,m,2);
}

void Tablet_::power(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = TABLET_POWER >> 8;
        HID().SendReport(4,m,2);
}

void Tablet_::home(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = TABLET_HOME >> 8;
        HID().SendReport(4,m,2);
}

void Tablet_::search(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = TABLET_SEARCH >> 8;
        HID().SendReport(4,m,2);
}
 
void Tablet_::clear(void)
{
        uint8_t m[2];
        m[0] = 0;
        m[1] = 0;
        HID().SendReport(4,m,2);
}

Tablet_ Tablet;

#endif
