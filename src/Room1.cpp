#include "bangtal.h"

#include "Objects.h"

extern SceneID room1, room1_left, room1_right;
extern SceneID room2, room2_table, room2_vase, room2_right, room2_pictures;
extern SceneID hall1, hall2, gogh1, gogh2, lastdoor;

Door room1_right_door;
Keypad room1_right_keypad;
ImageObject room1_window, room1_picture2, room1_right_picture1;
ToggleImageObject room1_picture1, room1_right_picture2;
ToggleObject room1_curtain;
Connector room1_toRight, room1_toLeft, room1_left_toRight, room1_right_toLeft;
Item room1_letter, room1_key, room1_leather, room1_glass, room1_knife, room1_post;
Box room1_left_box1, room1_left_box2;
ObjectID room1_curtain_closed;

bool room1_right_picture2_cut = false;

void room1_curtain_on(ToggleObject& toggleObject)
{
    hideObject(room1_curtain_closed);
    offToggleImageObject(room1_picture1);

    setSceneLight(room1, 1.f);
    setSceneLight(room1_right, 1.f);
    setSceneLight(room1_left, 1.f);
}

void room1_curtain_off(ToggleObject& toggleObject)
{
    showObject(room1_curtain_closed);
    onToggleImageObject(room1_picture1);

    setSceneLight(room1, 0.25f);
    setSceneLight(room1_right, 0.25f);
    setSceneLight(room1_left, 0.25f);

    showMessage("커튼을 쳤더니 깜깜해졌어.");
}

void setupRoom1() {
    room1_right_door = createDoor(
        "문", "image/문.png", "image/문.png",     // name, closedImage, openedImage
        room1_right, 1020, 0,                          // scene, x, y
        room2,                                         // connectTo
        0,                                             // key
        true, true,                                    // opened, locked
        "문이 잠겨있다.",                             // lockedMessage
        "문이 열렸어.",                               // unlockedMessage
        "",                             // keyMessage
        "",                                           // openedMessage
        true                                           // shown
        );

    room1_right_keypad = createKeypad(
        "keypad", "image/keypad-se.png",             // name, image
        room1_right, 1230, 340,                         // scene, x, y
        room1_right_door.id,                            // target
        "3748",                                        // password
        "다이얼 잠금장치네. 비밀번호가 뭘까?",         // message
        true                                            // shown
    );

    room1_window = createImageObject(
        "window", "image/창문.png",                  // name, image
        room1, 155, 250,                                // scene, x, y
        "image/생레미 창문.png",                      // target
        "2층 높이지만 쇠창살로 막혀있군.",             // message
        true                                            // shown
    );
    scaleObject(room1_window.id, 0.6f);

    room1_picture1 = createToggleImageObject(
        "picture1",                                                      // name
        "image/별이 빛나는 밤-2.png", "image/별이 빛나는 밤-1.png",   // onImage, offImage
        room1, 450, 200,                                                  // scene, x, y
        "image/별이 빛나는 밤 글씨.png", "image/별이 빛나는 밤.png",  // onTargetImage, offTargetImage
        "",                                                              // onMessage
        "재작년 MOMA 미술관에서 본 진품과\n아주 유사한걸?",              // offMessage
        false,                                                            // on
        true                                                              // shown
    );
    scaleObject(room1_picture1.id, 0.5f);

    room1_curtain = createToggleObject(
        "curtain", "image/커튼1.png", "image/커튼1.png",       // name, onImage, offImage
        room1, 80, 80,                                              // scene, x, y
        room1_curtain_on,                                           // onCallback
        room1_curtain_off,                                          // onCallback
        true,                                                       // on
        true                                                        // shown
    );
    scaleObject(room1_curtain.id, 2.f);

    room1_curtain_closed = createObject("curtain", "image/커튼3.png", room1, 130, 60, false);

    room1_letter = createItem(
        "letter", "", "image/편지.png",                 // name, pickImage, dropImage
        room1, 750, 130,                                    // scene, x, y
        "편지를 발견했다.",                                // pickMessage
        "",                                                // dropMessage
        true                                                // shown
    );
    scaleObject(room1_letter.id, 0.05f);

    room1_key = createItem(
        "key", "", "image/key.png",                 // name, pickImage, dropImage
        room1_right, 620, 50,                                    // scene, x, y
        "열쇠를 얻었다!",                                // pickMessage
        "",                                                // dropMessage
        false                                                // shown
    );
    scaleObject(room1_key.id, 0.02f);

    room1_leather = createItem(
        "leather", "", "image/찢어진 가죽.png",                 // name, pickImage, dropImage
        0, 0, 0,                                    // scene, x, y
        "두꺼운 가죽조각이네. 옷을 수선하는 용도인가?",                                // pickMessage
        "",                                                // dropMessage
        false                                                // shown
    );
    scaleObject(room1_leather.id, 0.1f);

    room1_glass = createItem(
        "glass", "", "image/유리조각.png",                 // name, pickImage, dropImage
        room1_right, 770, 100,                                    // scene, x, y
        "이런 곳에 유리조각이 떨어져있다니, 위험한걸?",                                // pickMessage
        "",                                                // dropMessage
        true                                                // shown
    );
    scaleObject(room1_glass.id, 0.1f);

    room1_knife = createItem(
        "knife", "", "image/칼.png",                 // name, pickImage, dropImage
        0, 0, 0,                                    // scene, x, y
        "",                                // pickMessage
        "",                                                // dropMessage
        false                                                // shown
    );
    scaleObject(room1_knife.id, 0.1f);

    defineCombination(room1_leather.id, room1_glass.id, room1_knife.id);

    room1_left_box1 = createBox(
        "box1", "image/Box(Closed)-sw.png", "image/Box(Opened)-sw.png",     // name, closedImage, openedImage
        room1_left, 320, 480,                          // scene, x, y
        room1_leather.id,                              // hiddenObject
        0,                                             // key
        false, false,                                  // opened, locked
        "",                             // lockedMessage
        "",                               // unlockedMessage
        "",                             // keyMessage
        "",                                           // openedMessage
        true                                           // shown
    );
    scaleObject(room1_left_box1.id, 0.1f);
    locateObject(room1_leather.id, room1_left, 350, 505);

    room1_post = createItem(
        "쪽지", "image/paper.png", "image/roll paper.png",                 // name, pickImage, dropImage
        0, 0, 0,                                    // scene, x, y
        "쪽지를 발견했다.",                                // pickMessage
        "",                                                // dropMessage
        false                                                // shown
    );
    scaleObject(room1_post.id, 0.1f);

    room1_left_box2 = createBox(
        "box1", "image/비밀상자.png", "image/비밀상자-1.png",     // name, closedImage, openedImage
        room1_left, 0, 0,                          // scene, x, y
        room1_post.id,                              // hiddenObject
        room1_key.id,                                             // key
        false, false,                                  // opened, locked
        "",                             // lockedMessage
        "",                               // unlockedMessage
        "열쇠가 필요해.",                             // keyMessage
        "",                                           // openedMessage
        true                                           // shown
    );
    scaleObject(room1_left_box2.id, 1.4f);
    locateObject(room1_post.id, room1_left, 100, 110);

    room1_picture2 = createImageObject(
        "picture2", "image/파이프를 물고 귀에 붕대를 한 자화상-1.png",                  // name, image
        room1, 900, 300,                                // scene, x, y
        "image/파이프를 물고 귀에 붕대를 한 자화상.png",                      // target
        "눈빛이 쓸쓸해 보이네.",             // message
        true                                            // shown
    );
    scaleObject(room1_picture2.id, 0.3f);

    room1_right_picture1 = createImageObject(
        "picture1", "image/파이프를 물고 귀에 붕대를 한 자화상-2.png",                  // name, image
        room1_right, 150, 400,                                // scene, x, y
        "image/파이프를 물고 귀에 붕대를 한 자화상.png",                      // target
        "눈빛이 쓸쓸해 보이네.",             // message
        true                                            // shown
    );
    scaleObject(room1_right_picture1.id, 0.3f);

    room1_right_picture2 = createToggleImageObject(
        "picture2",                                                      // name
        "image/귀에 붕대를 감은 자화상-3.png", "image/귀에 붕대를 감은 자화상-1.png",   // onImage, offImage
        room1_right, 600, 400,                                                  // scene, x, y
        "image/귀에 붕대를 감은 자화상-2.png", "image/귀에 붕대를 감은 자화상.png",  // onTargetImage, offTargetImage
        "그림 속에 물건을 숨겨놓다니,\n괴짜가 따로없네.",                                                              // onMessage
        "내 귀를 잘라줘.....\n섬뜩한 목소리가 들리는 것만 같다.",              // offMessage
        false,                                                            // on
        true
    );
    scaleObject(room1_right_picture2.id, 0.3f);

    room1_toRight = createConnector("toRight", "image/오른쪽 화살표.png", room1, 1145, 375, room1_right);
    room1_toLeft = createConnector("toLeft", "image/왼쪽 화살표.png", room1, 50, 375, room1_left);
    room1_left_toRight = createConnector("toRight", "image/오른쪽 화살표.png", room1_left, 635, 375, room1);
    room1_right_toLeft = createConnector("toLeft", "image/왼쪽 화살표.png", room1_right, 50, 375, room1);
}
