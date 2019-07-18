#include "SDLGamepad.h"


namespace lime {


	std::map<int, SDL_GameController*> gameControllers = std::map<int, SDL_GameController*> ();
	std::map<int, int> gameControllerIDs = std::map<int, int> ();


	bool SDLGamepad::Connect (int deviceID) {

		if (SDL_IsGameController (deviceID)) {

			SDL_GameController *gameController = SDL_GameControllerOpen (deviceID);

			if (gameController) {

				SDL_Joystick *joystick = SDL_GameControllerGetJoystick (gameController);
				int id = SDL_JoystickInstanceID (joystick);

				gameControllers[id] = gameController;
				gameControllerIDs[deviceID] = id;

				return true;

			}

		}

		return false;

	}


	bool SDLGamepad::Disconnect (int id) {

		if (gameControllers.find (id) != gameControllers.end ()) {

			SDL_GameController *gameController = gameControllers[id];
			SDL_GameControllerClose (gameController);
			gameControllers.erase (id);

			return true;

		}

		return false;

	}


	int SDLGamepad::GetInstanceID (int deviceID) {

		return gameControllerIDs[deviceID];

	}


	void Gamepad::AddMapping (const char* content) {

		SDL_GameControllerAddMapping (content);

	}


	const char* Gamepad::GetDeviceGUID (int id) {

		SDL_Joystick* joystick = SDL_GameControllerGetJoystick (gameControllers[id]);

		if (joystick) {

			char* guid = new char[64];
			SDL_JoystickGetGUIDString (SDL_JoystickGetGUID (joystick), guid, 64);
			return guid;

		}

		return 0;

	}


	const char* Gamepad::GetDeviceName (int id) {

		return SDL_GameControllerName (gameControllers[id]);

	}

	#ifdef __NINTENDO_SWITCH__
	const int Gamepad::GetDeviceNpadID (int id) {
		
		SDL_Joystick* joystick = SDL_GameControllerGetJoystick (gameControllers[id]);
		
		if (joystick) {
			
			int npadid = -1;
			
			if (SDL_NintendoSwitch_JoystickNpadId(joystick, &npadid) == 0) {
			
				return npadid;
				
			}
			
		}
		
		return -1;
	}
	#endif

}