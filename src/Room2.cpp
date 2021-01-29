#include "bangtal.h"

#include "Objects.h"

extern SceneID room1, room1_left, room1_right;
extern SceneID room2, room2_table, room2_vase, room2_right, room2_pictures;
extern SceneID hall1, hall2, gogh1, gogh2, lastdoor;

Door room2_door1;
Keypad room2_keypad;
Item room2_letter1, room2_letter2, room2_bullet, room2_gun, room2_guncom;
ImageObject room2_window, room2_mirror, room2_pictures_year;
Connector room2_door2, room2_toRight, room2_toBack, room2_right_toLeft, room2_onTable, room2_vase_toBack, room2_inTable, room2_table_toBack, room2_pictures_toBack;
ObjectID room2_table_drawer1, room2_table_drawer2;
ObjectID room2_pictures_picture1, room2_pictures_picture2, room2_pictures_picture3;
int room2_pictures_count = 0;

SoundID room2_sound1, room2_sound2;

void setupRoom2() {
    room2_door1 = createDoor(
        "문", "image/문2.png", "image/문2.png",     // name, closedImage, openedImage
        room2, 0, 120,                          // scene, x, y
        hall1,                                         // connectTo
        0,                                             // key
        true, true,                                    // opened, locked
        "문이 잠겨있다.",                             // lockedMessage
        "문이 열렸어.",                               // unlockedMessage
        "",                             // keyMessage
        "",                                           // openedMessage
        true                                           // shown
    );

    room2_keypad = createKeypad(
        "keypad", "image/keypad2-sw.png",             // name, image
        room2, 145, 500,                         // scene, x, y
        room2_door1.id,                            // target
        "1888",                                        // password
        "다이얼 잠금장치네. 비밀번호가 뭘까?",         // message
        true                                            // shown
    );
    scaleObject(room2_keypad.id, 0.15f);

    room2_letter1 = createItem(
        "letter1", "", "image/편지2.png",                 // name, pickImage, dropImage
        room2_right, 650, 280,                                    // scene, x, y
        "편지를 발견했다.",                                // pickMessage
        "",                                                // dropMessage
        true                                                // shown
    );
    scaleObject(room2_letter1.id, 0.05f);

    room2_letter2 = createItem(
        "letter2", "image/모스 부호.png", "image/roll paper2.png",                 // name, pickImage, dropImage
        room2_vase, 285, 535,                                    // scene, x, y
        "종이를 발견했다.",                                // pickMessage
        "",                                                // dropMessage
        true                                                // shown
    );
    scaleObject(room2_letter2.id, 0.1f);

    room2_table_drawer1 = createObject("drawer", "image/서랍장 선택.png", room2_table, 270, 350, true);
    room2_table_drawer2 = createObject("drawer", "image/서랍.png", room2_table, 230, 300, false);

    room2_bullet = createItem(
        "bullet", "", "image/총알.png",                 // name, pickImage, dropImage
        room2_right, 900, 100,                                    // scene, x, y
        "꽤나 묵직한 총알이 떨어져있다.",                                // pickMessage
        "",                                                // dropMessage
        true                                                // shown
    );
    scaleObject(room2_bullet.id, 0.05f);

    room2_gun = createItem(
        "총", "", "image/총.png",                 // name, pickImage, dropImage
        room2_table, 280, 360,                                    // scene, x, y
        "서랍에서 탄알 없는 총을 찾았다.",                                // pickMessage
        "",                                                // dropMessage
        false                                                // shown
    );
    scaleObject(room2_gun.id, 0.2f);

    room2_guncom = createItem(
        "장전된 총", "", "image/장전된 총.png",                 // name, pickImage, dropImage
        0, 0, 0,                                    // scene, x, y
        "",                                // pickMessage
        "",                                                // dropMessage
        false                                                // shown
    );

    defineCombination(room2_bullet.id, room2_gun.id, room2_guncom.id);

    room2_window = createImageObject(
        "window", "image/아를의 창문.png",                  // name, image
        room2, 405, 472,                                // scene, x, y
        "image/아를의 풍경.png",                      // target
        "2층이지만 뛰어내리는데 거부감을 느낀다. \n내 의지가 사라지는 기분이다.",             // message
        true                                            // shown
    );

    room2_mirror = createImageObject(
        "mirror", "image/거울.png",                  // name, image
        room2, 305, 510,                                // scene, x, y
        "image/말하는 고흐.png",                      // target
        "이럴수가! 거울에 비친 내 모습이 고흐로 바뀌어있다!!",             // message
        true                                            // shown
    );

    room2_pictures_year = createImageObject(
        "year", "image/연도.png",                  // name, image
        room2_pictures, 600, 450,                                // scene, x, y
        "image/연도 확대.png",                      // target
        "분필로 쓴 글씨네. 이건.... 연도인가?",             // message
        true                                            // shown
    );
    scaleObject(room2_pictures_year.id, 0.05f);

    room2_pictures_picture1 = createObject("picture1", "image/해바라기.png", room2_pictures, 100, 300);
    scaleObject(room2_pictures_picture1, 0.5f);
    room2_pictures_picture2 = createObject("picture2", "image/고흐의 방 액자.png", room2_pictures, 450, 300);
    scaleObject(room2_pictures_picture2, 0.5f);
    room2_pictures_picture3 = createObject("picture3", "image/붓꽃.png", room2_pictures, 900, 300);
    scaleObject(room2_pictures_picture3, 0.5f);

    room2_door2 = createConnector("toRight", "image/문4.png", room2, 1150, 50, room2_pictures);
    room2_pictures_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", room2_pictures, 620, 10, room2);

    room2_toRight = createConnector("toRight", "image/오른쪽 화살표.png", room2, 1145, 375, room2_right);
    room2_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", room2, 620, 10, room1_right);
    room2_right_toLeft = createConnector("toLeft", "image/왼쪽 화살표.png", room2_right, 50, 375, room2);

    room2_onTable = createConnector("onTable", "image/탁자 위.png", room2, 300, 420, room2_vase);
    room2_vase_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", room2_vase, 290, 10, room2);

    room2_inTable = createConnector("inTable", "image/탁자 선택.png", room2, 300, 370, room2_table);
    room2_table_toBack = createConnector("toBack", "image/뒤로가기 화살표.png", room2_table, 283, 10, room2);

    room2_sound1 = createSound("audio/모스1.wav");
    room2_sound2 = createSound("audio/모스2.wav");
}
