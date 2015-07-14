/*
 * ExternalDisplay.hpp
 *
 *  Created on: 09.07.2015
 *      Author: thebigbg
 */

#ifndef EXTERNALDISPLAY_HPP_
#define EXTERNALDISPLAY_HPP_

#include <screen/screen.h>
#include <sys/platform.h>

#include <cstdint>
#include <iostream>
#include <QString>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include <bb/cascades/Image>
#include <bb/ImageData>
#include <bb/utility/ImageConverter>
#include <img/img.h>


// define rendering method, type of display (internal/external) and possible display resolutions
typedef enum RENDERING_API {GL_UNKNOWN = 0, GL_ES_1 = EGL_OPENGL_ES_BIT, GL_ES_2 = EGL_OPENGL_ES2_BIT, VG = EGL_OPENVG_BIT} RENDERING_API;
typedef enum VIEW_DISPLAY  {DISPLAY_UNKNOWN, DISPLAY_DEVICE, DISPLAY_HDMI} VIEW_DISPLAY;
typedef enum RESOLUTIONS_T {RES640x480, RES720x480, RES720x576, RES1024x768, RES1280x720, RES1280x1024, RES1600x1200, RES1920x1080} RESOLUTIONS_T;
typedef enum DISPLAY_STATES_T {UNINITIALIZED, INITIALIZED} DISPLAY_STATES_T;



class ExternalDisplay
{
public:
    ExternalDisplay();
    virtual ~ExternalDisplay();

    // allocation / deallocation of actual resources (for a given display resolution, to be set beforehand)
        int open();
        int close();

        // set or get external display resolution (to be done before open() or close() operation)
        void          setResolution(RESOLUTIONS_T res);
        RESOLUTIONS_T getResolution();

        // show image on external display
        int showImage(bb::ImageData imageData);
private:

    // display and image properties
    DISPLAY_STATES_T _state;        // state of display (only initialized display can be accessed for rendering)
    RESOLUTIONS_T _resolution;      // external display resolution
    int           _transparency;    // transparency of (foreground) image
    int           _numberDisplays;  // number of displays (internal and external)
    int           _numberModes;     // number of display modes
    int           _extDisplayIndex; // index of the external display in the display list
    int           _pixelFormat;     // format of each pixel (e.g. RGBA 32bit)
    int           _width;           // width of display buffer (in pixels)
    int           _height;          // height of display buffer (in pixels)

    // screen and window data structures
    RENDERING_API         _api;
    screen_context_t      _screen_ctx, _screen_ctx2;
    screen_window_t       _screen_win, _screen_win2;
    screen_display_t      _screen_disp;
    screen_display_t      *_screen_dpy;
    screen_display_mode_t *_screen_modes;
    screen_buffer_t       _screen_buf[2];
    int  _nbuffers;
    bool _enabled;
    bool _initialized;
    bool _stale;
    bool _altered;
    bool _visible;
};

#endif /* EXTERNALDISPLAY_HPP_ */
