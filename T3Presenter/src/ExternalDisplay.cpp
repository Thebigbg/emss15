/*
 * ExternalDisplay.cpp
 *
 *  Created on: 06.05.2013
 *      Author: wtheimer
 */

#include "ExternalDisplay.hpp"


ExternalDisplay::ExternalDisplay() {
	// initialize members shared by derived classes
	_nbuffers    = 2;
	_enabled     = false;
	_initialized = false;
	_stale       = false;
	_altered     = false;
	_visible     = false;

	_screen_win = NULL;
	_screen_dpy = NULL;

	_resolution      = RES1280x720;
	_transparency    = 0;
	_extDisplayIndex = 0;
	_state           = UNINITIALIZED;
	_api             = GL_ES_1;
	_pixelFormat     = SCREEN_FORMAT_RGBA8888; // byte order: ARGB
	_width			 = 0;
	_height			 = 0;
}

ExternalDisplay::~ExternalDisplay() {

}

// allocation / deallocation of actual resources (for a given display resolution, to be set beforehand)
int ExternalDisplay::open() {
    int        returnCode;
    int        type;

	// create a screen context
    returnCode = screen_create_context(&_screen_ctx, 0);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_create_context");
		return EXIT_FAILURE;
	}

	returnCode = screen_get_context_property_iv(_screen_ctx, SCREEN_PROPERTY_DISPLAY_COUNT, &_numberDisplays);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_get_context_property_iv: SCREEN_PROPERTY_DISPLAY_COUNT");
		return EXIT_FAILURE;
	}

	_screen_dpy = (screen_display_t *)std::calloc(_numberDisplays, sizeof(screen_display_t));
	if (_screen_dpy == NULL) {
		perror("calloc");
		return EXIT_FAILURE;
	}

	returnCode = screen_get_context_property_pv(_screen_ctx, SCREEN_PROPERTY_DISPLAYS, (void **)_screen_dpy);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_get_context_property_pv: SCREEN_PROPERTY_DISPLAYS");
		return EXIT_FAILURE;
	}

	for (int index = 0; index < _numberDisplays; index++) {
		int displayID;
		int rect[4] = { 0, 0, 0, 0 };

        returnCode = screen_get_display_property_iv(_screen_dpy[index], SCREEN_PROPERTY_ID,  (int *)&displayID);
    	if (returnCode != EXIT_SUCCESS) {
    		perror("screen_get_display_property_iv: SCREEN_PROPERTY_ID");
    		return EXIT_FAILURE;
    	} else {
    		// check if the display is an external (HDMI) display
    		returnCode = screen_get_display_property_iv(_screen_dpy[index], SCREEN_PROPERTY_TYPE,  &type);
			if (returnCode != EXIT_SUCCESS) {
				perror("screen_get_display_property_iv: SCREEN_PROPERTY_TYPE");
				return EXIT_FAILURE;
			}

			if (type == SCREEN_DISPLAY_TYPE_HDMI) {
    			_extDisplayIndex = index;

    			// create new graphics context for external display
    			returnCode = screen_create_context(&_screen_ctx2, SCREEN_APPLICATION_CONTEXT);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_create_context");
    				return EXIT_FAILURE;
    			}

    			// create window associated with the new graphics context
    			returnCode = screen_create_window(&_screen_win2, _screen_ctx2);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_create_window");
    				return EXIT_FAILURE;
    			}

    			// set the new window properties to the ones valid for the external display
    			returnCode = screen_set_window_property_pv(_screen_win2, SCREEN_PROPERTY_DISPLAY, (void **) &_screen_dpy[_extDisplayIndex]);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_set_window_property_pv: SCREEN_PROPERTY_DISPLAY");
    				return EXIT_FAILURE;
    			}

    			// set the window for native usage
    			int usage = SCREEN_USAGE_NATIVE;
    			returnCode = screen_set_window_property_iv(_screen_win2, SCREEN_PROPERTY_USAGE, &usage);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_set_window_property_iv: SCREEN_PROPERTY_USAGE");
    				return EXIT_FAILURE;
    			}

    			// set display resolution
    			returnCode = screen_get_display_property_iv(_screen_dpy[_extDisplayIndex], SCREEN_PROPERTY_SIZE, rect + 2);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_get_display_property_iv: SCREEN_PROPERTY_SIZE");
    				return EXIT_FAILURE;
    			}

    			switch (_resolution) {
    			case RES640x480:
    				rect[2] = 640;
    				rect[3] = 480;
    				break;
    			case RES720x480:
    				rect[2] = 720;
    				rect[3] = 480;
    				break;
    			case RES720x576:
    				rect[2] = 720;
    				rect[3] = 576;
    				break;
    			case RES1024x768:
    				rect[2] = 1024;
    				rect[3] = 768;
    				break;
    			case RES1280x720:
    				rect[2] = 1280;
    				rect[3] = 720;
    				break;
    			case RES1280x1024:
    				rect[2] = 1280;
    				rect[3] = 1024;
    				break;
    			case RES1600x1200:
    				rect[2] = 1600;
    				rect[3] = 120;
    				break;
    			case RES1920x1080:
    				rect[2] = 1920;
    				rect[3] = 1080;
    				break;
    			default:
    				rect[2] = 1280;
    				rect[3] = 720;
    				break;
    			}

    			returnCode = screen_set_window_property_iv(_screen_win2, SCREEN_PROPERTY_BUFFER_SIZE, rect + 2);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_set_window_property_iv: SCREEN_PROPERTY_BUFFER_SIZE");
    				return EXIT_FAILURE;
    			}
    			_width  = rect[2];
    			_height = rect[3];

    			// create two window buffers (double buffering) so that one buffer can be displayed while the second is modified
    			returnCode = screen_create_window_buffers(_screen_win2, 2);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_create_window_buffers");
    				return EXIT_FAILURE;
    			}

    			returnCode = screen_get_window_property_pv(_screen_win2, SCREEN_PROPERTY_RENDER_BUFFERS, (void **) _screen_buf);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_get_window_property_pv: SCREEN_PROPERTY_RENDER_BUFFERS");
    				return EXIT_FAILURE;
    			}

    			returnCode = screen_get_display_property_iv(_screen_dpy[_extDisplayIndex], SCREEN_PROPERTY_SIZE, rect + 2);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_get_window_property_iv: SCREEN_PROPERTY_SIZE");
    				return EXIT_FAILURE;
    			}

    			// set pixel format to RGBA 32bit
    			returnCode = screen_set_window_property_iv(_screen_win2, SCREEN_PROPERTY_FORMAT, &_pixelFormat);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_set_window_property_iv: SCREEN_PROPERTY_FORMAT");
    				return EXIT_FAILURE;
    			}

    			// set transparency
    			returnCode = screen_set_window_property_iv(_screen_win2, SCREEN_PROPERTY_TRANSPARENCY, &_transparency);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_set_window_property_iv: SCREEN_PROPERTY_TRANSPARENCY");
    				return EXIT_FAILURE;
    			}

    			// create a black background
    			int bg[] = { SCREEN_BLIT_COLOR, 0x00000000, SCREEN_BLIT_END };
    			returnCode = screen_fill(_screen_ctx2, _screen_buf[0], bg);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_fill");
    				return EXIT_FAILURE;
    			}

    			// display current buffer
    			returnCode = screen_post_window(_screen_win2, _screen_buf[0], 1, rect, 0);
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_post_window");
    				return EXIT_FAILURE;
    			}
    		}
    		if (type == SCREEN_DISPLAY_TYPE_HDMI) {
    			returnCode = screen_set_window_property_pv(_screen_win2, SCREEN_PROPERTY_DISPLAY, (void **)&(_screen_dpy[index]));
    			if (returnCode != EXIT_SUCCESS) {
    				perror("screen_set_window_property_pv: SCREEN_PROPERTY_DISPLAY");
    				return EXIT_FAILURE;
    			}
    		}
        }
	}

	_state = INITIALIZED;

	return EXIT_SUCCESS;

}

int ExternalDisplay::close() {
	// revert state back to uninitialized
	_state = UNINITIALIZED;

	// delete window resources to allow another app to take over external display
	screen_destroy_window(_screen_win2);

	return EXIT_SUCCESS;
}

// set or get external display resolution (changes only possible before open() is called!)
void ExternalDisplay::setResolution(RESOLUTIONS_T resolution) {
	// only if display is not yet initialized (opened), the display resolution can be changed
	if (_state == UNINITIALIZED) {
		_resolution = resolution;
	}
}

RESOLUTIONS_T ExternalDisplay::getResolution() {
	return _resolution;
}

// show image on external display
int ExternalDisplay::showImage(bb::ImageData imageData) {
	int returnCode;
	int i, j;
	int dx, dy, dw, dh;
	const unsigned char *imagePixels;
	unsigned char *ptr = NULL;
	int usage, stride;
	int rect[4]        = { 0, 0, 0, 0 };
	int source_rect[4] = { 0, 0, 0, 0 };
	screen_pixmap_t screen_pix;
	screen_buffer_t screen_pbuf;

	// check if imageData is an existing object
	if (!imageData.isValid()) {
		perror("showImage");
		return EXIT_FAILURE;
	}

	// copy image data to screen buffer
	imagePixels = imageData.constPixels();

	// center image on screen, i.e. upper left corner at (dx,dy) with original width dw and height dh
	dx = (_width - imageData.width()) / 2;
	dw = imageData.width();
	if (dx < 0) {
		dx = 0;
		dw = _width;
	}

	dy = (_height - imageData.height()) / 2;
	dh = imageData.height();
	if (dy < 0) {
		dy = 0;
		dh = _height;
	}

	// define BLIT command to copy image data (source) to display (destination)
	int hg[] = {
	    SCREEN_BLIT_SOURCE_WIDTH,  imageData.width(),
	    SCREEN_BLIT_SOURCE_HEIGHT, imageData.height(),
	    SCREEN_BLIT_DESTINATION_X, dx,
	    SCREEN_BLIT_DESTINATION_Y, dy,
	    SCREEN_BLIT_DESTINATION_WIDTH,  dw,
	    SCREEN_BLIT_DESTINATION_HEIGHT, dh,
	    SCREEN_BLIT_TRANSPARENCY, SCREEN_TRANSPARENCY_NONE,
	    SCREEN_BLIT_END
	};

	rect[2] = _width;
	rect[3] = _height;
	source_rect[2] = imageData.width();
	source_rect[3] = imageData.height();

	// create pixmap without actual buffer
	returnCode = screen_create_pixmap(&screen_pix, _screen_ctx2);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_create_pixmap");
		return EXIT_FAILURE;
	}

	// set pixel format (here: RGBA = RGB pixels with alpha blending for transparency)
	returnCode = screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_FORMAT, &_pixelFormat);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_set_pixmap_property_iv: SCREEN_PROPERTY_FORMAT");
		return EXIT_FAILURE;
	}

	// set pixel buffer access method
	usage = SCREEN_USAGE_WRITE | SCREEN_USAGE_NATIVE;
	returnCode = screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_USAGE, &usage);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_set_pixmap_property_iv: SCREEN_PROPERTY_USAGE");
		return EXIT_FAILURE;
	}

	// set size of pixel map according to image size
	returnCode = screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_BUFFER_SIZE, source_rect+2);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_set_pixmap_property_iv: SCREEN_PROPERTY_BUFFER_SIZE");
		return EXIT_FAILURE;
	}

	// create actual pixel buffer according to image size
	returnCode = screen_create_pixmap_buffer(screen_pix);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_create_pixmap_buffer");
		return EXIT_FAILURE;
	}

	// retrieve pointer to the beginning of the screen buffer in the pixel map
	returnCode = screen_get_pixmap_property_pv(screen_pix, SCREEN_PROPERTY_RENDER_BUFFERS, (void **)&screen_pbuf);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_get_pixmap_property_iv: SCREEN_PROPERTY_RENDER_BUFFERS");
		return EXIT_FAILURE;
	}

	// get actual pointer to the beginning of the screen buffer
	returnCode = screen_get_buffer_property_pv(screen_pbuf, SCREEN_PROPERTY_POINTER, (void **)&ptr);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_get_buffer_property_iv: SCREEN_PROPERTY_POINTER");
		return EXIT_FAILURE;
	}

	// retrieve the number of bytes between two subsequent lines in the image (stride)
	returnCode = screen_get_buffer_property_iv(screen_pbuf, SCREEN_PROPERTY_STRIDE, &stride);
	if (returnCode != EXIT_SUCCESS) {
		perror("screen_get_buffer_property_iv: SCREEN_PROPERTY_STRIDE");
		return EXIT_FAILURE;
	}

	// copy ImageData content to screen pixel buffer, reversing byte order RGBA -> BGRA
	for (i = 0; i < source_rect[3]; i++, ptr += stride) {
			for (j = 0; j < source_rect[2]; j++) {
				ptr[j*4]   = imagePixels[4*i*source_rect[2]+4*j+2];
				ptr[j*4+1] = imagePixels[4*i*source_rect[2]+4*j+1];
				ptr[j*4+2] = imagePixels[4*i*source_rect[2]+4*j+0];
				ptr[j*4+3] = imagePixels[4*i*source_rect[2]+4*j+3];
			}
	}

	// copy buffer to screen window and make it visible
	screen_blit(_screen_ctx2, _screen_buf[0], screen_pbuf, hg);
	screen_post_window(_screen_win2, _screen_buf[0], 1, rect, 0);

	// free allocated resources of pixmap
	screen_destroy_pixmap(screen_pix);

	return EXIT_SUCCESS;
}



