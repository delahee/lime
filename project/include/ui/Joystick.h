#ifndef LIME_UI_JOYSTICK_H
#define LIME_UI_JOYSTICK_H


namespace lime {


	class Joystick {

		public:

			static const char* GetDeviceGUID (int id);
			static const char* GetDeviceName (int id);
			
			#ifdef __NINTENDO_SWITCH__
			static const int GetDeviceNpadID (int id);
			#endif
			
			static int GetNumAxes (int id);
			static int GetNumButtons (int id);
			static int GetNumHats (int id);
			static int GetNumTrackballs (int id);

	};


}


#endif