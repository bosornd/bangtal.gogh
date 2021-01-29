#include "bangtal.h"

SceneID room1, room1_left, room1_right;
SceneID room2, room2_table, room2_vase, room2_right, room2_pictures;
SceneID hall1, hall2, gogh1, gogh2, lastdoor;

void createScenes()
{
	room1 = createScene("room1", "image/생레미 앞편.png");
	room1_left = createScene("room1 left", "image/생레미 탁자.png");
	room1_right = createScene("room1 right", "image/생레미 뒷편.png");

	room2 = createScene("room2", "image/고흐의 방 전체.png");
	room2_table = createScene("room2 table", "image/고흐의 방 탁자.png");
	room2_right = createScene("room2 right", "image/고흐의 방 침대.png");
	room2_vase = createScene("room2 vase", "image/고흐의 방 물병.png");
	room2_pictures = createScene("room pictures", "image/그림의 방.png");

	hall1 = createScene("hall1", "image/복도1.png");
	hall2 = createScene("hall2", "image/복도2.png");
	gogh1 = createScene("gogh1", "image/말하는 고흐.png");
	gogh2 = createScene("gogh2", "image/총을 든 고흐.png");
	lastdoor = createScene("lastdoor", "image/탈출의 문.png");
}