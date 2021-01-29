#include "bangtal.h"
#include "Objects.h"

extern SceneID room1, room1_left, room1_right;
extern SceneID room2, room2_table, room2_vase, room2_right, room2_pictures;
extern SceneID hall1, hall2, gogh1, gogh2, lastdoor;

/* room1 */
extern Door room1_right_door;
extern Keypad room1_right_keypad;
extern ImageObject room1_window, room1_picture2, room1_right_picture1;
extern ToggleImageObject room1_picture1, room1_right_picture2;
extern ToggleObject room1_curtain;
extern Item room1_letter, room1_key, room1_leather, room1_glass, room1_knife, room1_post;
extern Box room1_left_box1, room1_left_box2;
extern Connector room2_door2, room1_toRight, room1_toLeft, room1_left_toRight, room1_right_toLeft;
extern bool room1_right_picture2_cut;

/* room2 */
extern Door room2_door1;
extern Keypad room2_keypad;
extern Item room2_letter1, room2_letter2, room2_bullet, room2_gun, room2_guncom;
extern ImageObject room2_window, room2_mirror, room2_pictures_year;
extern Connector room2_toRight, room2_toBack, room2_right_toLeft, room2_onTable, room2_vase_toBack, room2_inTable, room2_table_toBack, room2_pictures_toBack;
extern ObjectID room2_table_drawer1, room2_table_drawer2;
extern ObjectID room2_pictures_picture1, room2_pictures_picture2, room2_pictures_picture3;
extern int room2_pictures_count;

extern SoundID room2_sound1, room2_sound2;

/* room3*/
extern Door lastdoor_bigbox;
extern Keypad lastdoor_keypad;
extern ImageObject hall2_why;
extern ObjectID hall1_gogh1, hall1_gogh2, gogh1_box, gogh2_box;
extern Connector hall1_toBack, hall1_toRight, hall2_toBack, hall2_toFront, lastdoor_toBack, gogh1_toBack;

void GHsceneCallback(SceneID scene, EventID event)
{
	if (scene == room2) {
		if (event == EventID::EVENT_ENTER_SCENE)
			showMessage("우와, 여기는 진짜 고흐의 방 같잖아?");
	}
	else if (scene == room2_pictures) {
		if (event == EventID::EVENT_ENTER_SCENE)
			showMessage("이런 곳이 있었네.");
	}
}

#define DEFINE_OBJECT_CALLBACK(o, type) if (object == o.id) objectCallback_ ## type(o, event)
#define DEFINE_KEYPAD_CALLBACK(o, type) if (object == o.id) keypadCallback_ ## type(o)
void GHobjectCallback(ObjectID object, EventID event)
{
	/* room1 */
	DEFINE_OBJECT_CALLBACK(room1_letter, Item);
	else DEFINE_OBJECT_CALLBACK(room1_key, Item);
	else DEFINE_OBJECT_CALLBACK(room1_leather, Item);
	else DEFINE_OBJECT_CALLBACK(room1_glass, Item);
	else DEFINE_OBJECT_CALLBACK(room1_knife, Item);
	else DEFINE_OBJECT_CALLBACK(room1_post, Item);

	/* room2 */
	else DEFINE_OBJECT_CALLBACK(room2_letter1, Item);
	else DEFINE_OBJECT_CALLBACK(room2_letter2, Item);
	else DEFINE_OBJECT_CALLBACK(room2_bullet, Item);
	else DEFINE_OBJECT_CALLBACK(room2_gun, Item);
	else DEFINE_OBJECT_CALLBACK(room2_guncom, Item);

	/* keypad */
	else DEFINE_KEYPAD_CALLBACK(room1_right_door, Door);
	else DEFINE_KEYPAD_CALLBACK(room2_door1, Door);
	else DEFINE_KEYPAD_CALLBACK(lastdoor_bigbox, Door);
}

#define DEFINE_MOUSE_ACTION_CALLBACK(o, type) if (object == o.id) mouseActionCallback_ ## type(o, x, y, action)
void GHmouseActionCallback(ObjectID object, int x, int y, MouseAction action)
{
	/* room1 */
	DEFINE_MOUSE_ACTION_CALLBACK(room1_right_door, Door);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_right_keypad, Keypad);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_window, ImageObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_picture2, ImageObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_right_picture1, ImageObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_picture1, ToggleImageObject);
	/*
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_right_picture2, ToggleImageObject);
	*/
	else if (object == room1_right_picture2.id) {
		if (!room1_right_picture2_cut && getHandObject() == room1_knife.id) {
			room1_right_picture2_cut = true;

			onToggleImageObject(room1_right_picture2);
			showObject(room1_key.id);

			showMessage("으악, 뭐야? 고흐의 귀를 자르자 무언가 떨어졌다.");
		}
		else mouseActionCallback_ToggleImageObject(room1_right_picture2, x, y, action);
	}
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_curtain, ToggleObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_letter, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_key, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_leather, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_glass, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_knife, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_post, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_left_box1, Box);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_left_box2, Box);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_toRight, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_toLeft, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_left_toRight, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room1_right_toLeft, Connector);

	/* room2 */
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_door1, Door);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_keypad, Keypad);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_letter1, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_letter2, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_bullet, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_gun, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_guncom, Item);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_window, ImageObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_mirror, ImageObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_pictures_year, ImageObject);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_door2, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_toRight, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_toBack, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_right_toLeft, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_onTable, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_vase_toBack, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_inTable, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_table_toBack, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(room2_pictures_toBack, Connector);
	else if (object == room2_table_drawer1) {
		hideObject(room2_table_drawer1);
		showObject(room2_table_drawer2);
		showObject(room2_gun.id);
	}
	else if (object == room2_pictures_picture1) {
		playSound(room2_sound2);

	}
	else if (object == room2_pictures_picture2) {
		room2_pictures_count = 0;
	}
	else if (object == room2_pictures_picture3) {
		playSound(room2_sound1);
	}

	/* room3 */
	else DEFINE_MOUSE_ACTION_CALLBACK(lastdoor_bigbox, Door);
	else DEFINE_MOUSE_ACTION_CALLBACK(lastdoor_keypad, Keypad);
	else DEFINE_MOUSE_ACTION_CALLBACK(hall2_why, ImageObject);
	else if (object == hall1_gogh1) {
		enterScene(gogh1);
	}
	else if (object == hall1_gogh2) {
		showMessage("The agony will last forever.\n고통이 영원하다는 말이 귓가에 맴돈다.");
	}
	else if (object == gogh1_box) {
		if (getHandObject() == room2_guncom.id) {
			enterScene(gogh2);
		}
		else {
			showMessage("장전된 권총이 필요해.");
		}
	}
	else if (object == gogh2_box) {
		hideObject(hall1_gogh1);
		showObject(hall1_gogh2);

		showMessage("안돼...!! 그가 의미심장한 말을 남기고 스스로를 쏴버렸다!");
		enterScene(hall1);
	}
	else DEFINE_MOUSE_ACTION_CALLBACK(hall1_toBack, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(hall1_toRight, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(hall2_toBack, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(hall2_toFront, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(lastdoor_toBack, Connector);
	else DEFINE_MOUSE_ACTION_CALLBACK(gogh1_toBack, Connector);
}

void GHtimerCallback(TimerID timer)
{

}

void GHsoundCallback(SoundID sound)
{
	if (sound == room2_sound1) {
		if (room2_pictures_count == 1) {
			room2_pictures_count++;
		}
		else if (room2_pictures_count == 2) {
			room2_pictures_count++;
		}
		else {
			room2_pictures_count = 0;
		}
	}
	else if (sound == room2_sound2) {
		if (room2_pictures_count == 0) {
			room2_pictures_count++;
		}
		else if (room2_pictures_count == 3) {
			room2_pictures_count++;
			locateObject(room2_pictures_picture2, room2_pictures, 450, 20);
		}
		else {
			room2_pictures_count = 0;
		}
	}
}

void registerCallbacks()
{
	setSceneCallback(GHsceneCallback);
	setObjectCallback(GHobjectCallback);
	setMouseCallback(GHmouseActionCallback);
	setTimerCallback(GHtimerCallback);
	setSoundCallback(GHsoundCallback);
}