#pragma once

#include <iostream>
#include <functional>

ObjectID createObject(const std::string& name, const std::string& image, SceneID scene = 0, int x = 0, int y = 0, bool shown = true);


struct ImageObject {
    ObjectID id;

    std::string targetImage;
    std::string message;
};

ImageObject createImageObject(const std::string& name, const std::string& image,
    SceneID scene, int x, int y,
    const std::string& targetImage,
    const std::string& message = "",
    bool shown = true);

void mouseActionCallback_ImageObject(ImageObject& imageObject, int x, int y, MouseAction action);

struct ToggleImageObject {
    ObjectID id;

    bool on;
    std::string onImage, onTargetImage;
    std::string offImage, offTargetImage;
    std::string onMessage;
    std::string offMessage;
};

ToggleImageObject createToggleImageObject(const std::string& name,
    const std::string& onImage, const std::string& offImage,
    SceneID scene, int x, int y,
    const std::string& onTargetImage, const std::string& offTargetImage,
    const std::string& onMessage = "",
    const std::string& offMessage = "",
    bool on = false,
    bool shown = true);

void mouseActionCallback_ToggleImageObject(ToggleImageObject& toggleImageObject, int x, int y, MouseAction action);
void onToggleImageObject(ToggleImageObject& toggleImageObject);
void offToggleImageObject(ToggleImageObject& toggleImageObject);

struct ToggleObject {
    ObjectID id;

    bool on;
    std::string onImage;
    std::string offImage;

    void (*onCallback)(ToggleObject&);
    void (*offCallback)(ToggleObject&);
};

ToggleObject createToggleObject(const std::string& name, const std::string& onImage, const std::string& offImage,
    SceneID scene, int x, int y,
    void (*onCallback)(ToggleObject&),
    void (*offCallback)(ToggleObject&) = NULL,
    bool on = false,
    bool shown = true);

void mouseActionCallback_ToggleObject(ToggleObject& toggleObject, int x, int y, MouseAction action);


struct Item {
	ObjectID id;

	std::string pickImage;
	std::string pickMessage;

	std::string dropImage;
	std::string dropMessage;
};

Item createItem(const std::string& name,
    const std::string& pickImage, const std::string& dropImage,
    SceneID scene = 0, int x = 0, int y = 0,
    const std::string& pickMessage = "", const std::string& dropMessage = "",
    bool shown = true);

void mouseActionCallback_Item(Item& item, int x, int y, MouseAction action);
void objectCallback_Item(Item& item, EventID event);

struct Connector {
    ObjectID id;
    SceneID connectTo;
};

Connector createConnector(const std::string& name, const std::string& image,
    SceneID scene, int x, int y,
    SceneID connectTo = 0,
    bool shown = true);

void mouseActionCallback_Connector(Connector& connector, int x, int y, MouseAction action);


struct Door {
	ObjectID id;

    std::string closedImage;
    std::string openedImage;

    bool opened, locked;

    SceneID connectTo;
    ObjectID key;

    std::string lockedMessage;     // when locked, "문이 잠겨 있습니다."
    std::string unlockedMessage;   // when unlocked, "잠김이 해제되었습니다."
    std::string keyMessage;        // key required, "열쇠가 필요합니다."
    std::string openedMessage;     // when opened, "문이 열렸습니다.
};

Door createDoor(const std::string& name, const std::string& closedImage, const std::string& openedImage,
    SceneID scene, int x, int y,
    SceneID connectTo = 0,
    ObjectID key = 0,
    bool opened = false, bool locked = false,
    const std::string& lockedMessage = "",
    const std::string& unlockedMessage = "",
    const std::string& keyMessage = "",
    const std::string& openedMessage = "",
    bool shown = true);

void mouseActionCallback_Door(Door& door, int x, int y, MouseAction action);
void keypadCallback_Door(Door& door);


struct Box {
    ObjectID id;

    std::string closedImage;
    std::string openedImage;

    bool opened, locked;

    ObjectID hiddenObject;
    ObjectID key;

    std::string lockedMessage;     // when locked, "문이 잠겨 있습니다."
    std::string unlockedMessage;   // when unlocked, "잠김이 해제되었습니다."
    std::string keyMessage;        // key required, "열쇠가 필요합니다."
    std::string openedMessage;     // when opened, "문이 열렸습니다.
};

Box createBox(const std::string& name, const std::string& closedImage, const std::string& openedImage,
    SceneID scene, int x, int y,
    ObjectID hiddenObject = 0,
    ObjectID key = 0,
    bool opened = false, bool locked = false,
    const std::string& lockedMessage = "",
    const std::string& unlockedMessage = "",
    const std::string& keyMessage = "",
    const std::string& openedMessage = "",
    bool shown = true);

void mouseActionCallback_Box(Box& box, int x, int y, MouseAction action);
void keypadCallback_Box(Box& box);

struct Keypad {
    ObjectID id;

    ObjectID target;
    std::string password;
    std::string message;
};

Keypad createKeypad(const std::string& name, const std::string& image,
    SceneID scene, int x, int y,
    ObjectID target = 0,
    const std::string& password = "",
    const std::string& message = "",
    bool shown = true);

void mouseActionCallback_Keypad(Keypad& keypad, int x, int y, MouseAction action);

