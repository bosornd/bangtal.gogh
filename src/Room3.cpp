#include "bangtal.h"

#include "Objects.h"

extern SceneID room1, room1_left, room1_right;
extern SceneID room2, room2_table, room2_vase, room2_right, room2_pictures;
extern SceneID hall1, hall2, gogh1, gogh2, lastdoor;

Door lastdoor_bigbox;
Keypad lastdoor_keypad;
ImageObject hall2_why;
ObjectID hall1_gogh1, hall1_gogh2, gogh1_box, gogh2_box;

Connector hall1_toBack, hall1_toRight, hall2_toBack, hall2_toFront, lastdoor_toBack, gogh1_toBack;


void setupRoom3() {
    lastdoor_bigbox = createDoor(
        "문", "image/선택창.png", "image/선택창.png",     // name, closedImage, openedImage
        lastdoor, 0, 0,                          // scene, x, y
        0,                                         // connectTo --> endGame
        0,                                             // key
        true, true,                                    // opened, locked
        "문이 잠겨있다.",                             // lockedMessage
        "잠금장치가 열리는 소리가 들렸다.",                               // unlockedMessage
        "",                             // keyMessage
        "",                                           // openedMessage
        true                                           // shown
    );
    scaleObject(lastdoor_bigbox.id, 0.9f);

    lastdoor_keypad = createKeypad(
        "keypad", "image/keypad.png",             // name, image
        lastdoor, 70, 250,                         // scene, x, y
        lastdoor_bigbox.id,                            // target
        "AGONY",                                        // password
        "고통스럽다...\n이 문을 열면 행복해질 수 있을까?",         // message
        true                                            // shown
    );
    scaleObject(lastdoor_keypad.id, 0.05f);

    hall2_why = createImageObject(
        "why", "image/액자 선택.png",                  // name, image
        hall2, 210, 560,                                // scene, x, y
        "image/슬퍼하는 고흐.png",                      // target
        "어쩌면 영원히 존재하는 그의\n고통 속으로 들어온 것일지도 몰라.",             // message
        true                                            // shown
    );

    hall1_gogh1 = createObject("gogh1", "image/앉아있는 고흐.png", hall1, 160, 55);
    scaleObject(hall1_gogh1, 0.5f);
    hall1_gogh2 = createObject("gogh2", "image/쓰러진 고흐.png", hall1, 200, 55, false);
    scaleObject(hall1_gogh2, 0.2f);
    gogh1_box = createObject("box", "image/선택창.png", gogh1, 10, 0);
    gogh2_box = createObject("box", "image/선택창.png", gogh2, 20, 0);

    hall1_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", hall1, 620, 30, room2);
    hall1_toRight = createConnector("toRight", "image/오른쪽 화살표.png", hall1, 1145, 375, hall2);

    hall2_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", hall2, 250, 30, hall1);
    hall2_toFront = createConnector("toFront", "image/앞으로 화살표.png", hall2, 250, 300, lastdoor);
    lastdoor_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", lastdoor, 116, -100, hall2);

    gogh1_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", gogh1, 150, 10, hall1);
}
