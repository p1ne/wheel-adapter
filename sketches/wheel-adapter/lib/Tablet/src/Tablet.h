
#ifndef TABLET_h
#define TABLET_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else


#define TABLET_CLEAR 0
#define VOLUME_UP 1
#define VOLUME_DOWN 2
#define VOLUME_MUTE 4
#define TABLET_PLAY 8
#define TABLET_PAUSE 16
#define TABLET_PLAY_PAUSE 32
#define TABLET_STOP 64
#define TABLET_NEXT 128
#define TABLET_PREVIOUS 256
#define TABLET_FAST_FORWARD 512
#define TABLET_REWIND 1024
#define TABLET_POWER 2048
#define TABLET_HOME 4096
#define TABLET_SEARCH 8192


class Tablet_
{
private:
public:
        Tablet_(void);
        void begin(void);
        void end(void);
 
        // Volume
        void vol_up(void);
        void vol_down(void);
        void mute(void);
 
        // Playback
        void play(void);
        void pause(void);
        void play_pause(void);
		void stop(void);
 
        // Track Controls
        void next(void);
        void previous(void);
        void forward(void);
        void rewind(void);
		
		void power(void);
		void home(void);
		void search(void);
 
        // Send an empty report to prevent repeated actions
        void clear(void);
};
extern Tablet_ Tablet;

#endif
#endif