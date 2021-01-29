#include "bangtal.h"

void registerCallbacks();

void createScenes();
void setupRoom1();
void setupRoom2();
void setupRoom3();

extern SceneID room1;

int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	registerCallbacks();

	createScenes();
	setupRoom1();
	setupRoom2();
	setupRoom3();

	showMessage("으...어지러워...\n여긴 대체 어디야?");
	startGame(room1);
}
