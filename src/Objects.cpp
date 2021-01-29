#include "bangtal.h"

#include "Objects.h"

#define SHOW_MESSAGE(wstr)	if (!wstr.empty()) showMessage(wstr.c_str())

ObjectID createObject(const std::string& name, const std::string& image, SceneID scene, int x, int y, bool shown)
{
	ObjectID obj = createObject(image.c_str());
	if (scene > 0) {
		locateObject(obj, scene, x, y);
		if (shown) showObject(obj);
	}
	return obj;
}

ImageObject createImageObject(const std::string& name, const std::string& image,
	SceneID scene, int x, int y,
	const std::string& targetImage,
	const std::string& message,
	bool shown)
{
	ImageObject imageObject;
	imageObject.id = createObject(name.c_str(), image.c_str(), scene, x, y, shown);

	imageObject.targetImage = targetImage;
	imageObject.message = message;

	return imageObject;
}

void mouseActionCallback_ImageObject(ImageObject& imageObject, int x, int y, MouseAction action)
{
	showImageViewer(imageObject.targetImage.c_str());
	SHOW_MESSAGE(imageObject.message);
}

ToggleImageObject createToggleImageObject(const std::string& name,
	const std::string& onImage, const std::string& offImage,
	SceneID scene, int x, int y,
	const std::string& onTargetImage, const std::string& offTargetImage,
	const std::string& onMessage,
	const std::string& offMessage,
	bool on,
	bool shown)
{
	ToggleImageObject toggleImageObject;
	toggleImageObject.id = createObject(name.c_str(), on ? onImage.c_str() : offImage.c_str(), scene, x, y, shown);

	toggleImageObject.on = on;
	toggleImageObject.onImage = onImage;
	toggleImageObject.onTargetImage = onTargetImage;
	toggleImageObject.offImage = offImage;
	toggleImageObject.offTargetImage = offTargetImage;
	toggleImageObject.onMessage = onMessage;
	toggleImageObject.offMessage = offMessage;

	return toggleImageObject;
}

void onToggleImageObject(ToggleImageObject& toggleImageObject)
{
	toggleImageObject.on = true;
	setObjectImage(toggleImageObject.id, toggleImageObject.onImage.c_str());
}

void offToggleImageObject(ToggleImageObject& toggleImageObject)
{
	toggleImageObject.on = false;
	setObjectImage(toggleImageObject.id, toggleImageObject.offImage.c_str());
}


void mouseActionCallback_ToggleImageObject(ToggleImageObject& toggleImageObject, int x, int y, MouseAction action)
{
	const std::string& image = toggleImageObject.on ? toggleImageObject.onTargetImage : toggleImageObject.offTargetImage;
	const std::string& message = toggleImageObject.on ? toggleImageObject.onMessage : toggleImageObject.offMessage;

	showImageViewer(image.c_str());
	SHOW_MESSAGE(message);
}



ToggleObject createToggleObject(const std::string& name, const std::string& onImage, const std::string& offImage,
	SceneID scene, int x, int y,
	void (*onCallback)(ToggleObject&),
	void (*offCallback)(ToggleObject&),
	bool on,
	bool shown)
{
	ToggleObject toggleObject;
	toggleObject.id = createObject(name.c_str(), on ? onImage.c_str() : offImage.c_str(), scene, x, y, shown);

	toggleObject.on = on;
	toggleObject.onCallback = onCallback;
	toggleObject.offCallback = offCallback;

	return toggleObject;
}

void mouseActionCallback_ToggleObject(ToggleObject& toggleObject, int x, int y, MouseAction action)
{
	toggleObject.on = !toggleObject.on;

	if (toggleObject.on) {
		if (toggleObject.onCallback) toggleObject.onCallback(toggleObject);
	}
	else {
		if (toggleObject.offCallback) toggleObject.offCallback(toggleObject);
	}
}

Item createItem(const std::string& name,
	const std::string& pickImage, const std::string& dropImage,
	SceneID scene, int x, int y,
	const std::string& pickMessage, const std::string& dropMessage,
	bool shown)
{
	Item item;
	item.id = createObject(name.c_str(), dropImage.c_str(), scene, x, y, shown);

	item.pickImage = pickImage;
	item.dropImage = dropImage;
	item.pickMessage = pickMessage;
	item.dropMessage = dropMessage;

	return item;
}

void mouseActionCallback_Item(Item& item, int x, int y, MouseAction action)
{
	pickObject(item.id);
}

void objectCallback_Item(Item& item, EventID event)
{
	if (event == EventID::EVENT_PICK_OBJECT) {
		if (!item.pickImage.empty())
			setObjectImage(item.id, item.pickImage.c_str());
		SHOW_MESSAGE(item.pickMessage);
	}
	else if (event == EventID::EVENT_DROP_OBJECT) {
		if (!item.dropImage.empty())
			setObjectImage(item.id, item.dropImage.c_str());
		SHOW_MESSAGE(item.dropMessage);
	}
}

Connector createConnector(const std::string& name, const std::string& image,
	SceneID scene, int x, int y,
	SceneID connectTo,
	bool shown)
{
	Connector connector;
	connector.id = createObject(name.c_str(), image.c_str(), scene, x, y, shown);
	connector.connectTo = connectTo;
	return connector;
}

void mouseActionCallback_Connector(Connector& connector, int x, int y, MouseAction action)
{
	enterScene(connector.connectTo);
}


Door createDoor(const std::string& name, const std::string& closedImage, const std::string& openedImage,
	SceneID scene, int x, int y,
	SceneID connectTo,
	ObjectID key,
	bool opened, bool locked,
	const std::string& lockedMessage,
	const std::string& unlockedMessage,
	const std::string& keyMessage,
	const std::string& openedMessage,
	bool shown)
{
	Door door;
	door.closedImage = closedImage;
	door.openedImage = openedImage;

	door.opened = opened;
	door.locked = locked;

	door.connectTo = connectTo;
	door.key = key;

	door.lockedMessage = lockedMessage;
	door.unlockedMessage = unlockedMessage;
	door.keyMessage = keyMessage;
	door.openedMessage = openedMessage;

	if (opened) {
		door.id = createObject(name.c_str(), door.openedImage, scene, x, y, shown);
	}
	else {
		door.id = createObject(name.c_str(), door.closedImage, scene, x, y, shown);
	}
	return door;
}

void enterDoor(const Door& door)
{
	if (door.connectTo > 0) {
		enterScene(door.connectTo);
	}
	else {
		endGame();
	}
}

void mouseActionCallback_Door(Door& door, int x, int y, MouseAction action)
{
	if (door.locked) {
		SHOW_MESSAGE(door.lockedMessage);
	}
	else {
		if (door.opened) {
			enterDoor(door);
		}
		else {
			if (door.key > 0 && door.key != getHandObject()) {
				SHOW_MESSAGE(door.keyMessage);
			}
			else {
				door.opened = true;

				if (door.openedImage.compare(door.closedImage) != 0) {
					setObjectImage(door.id, door.openedImage.c_str());
					SHOW_MESSAGE(door.openedMessage);
				}
				else enterDoor(door);
			}
		}
	}
}

void keypadCallback_Door(Door& door)
{
	door.locked = false;
	SHOW_MESSAGE(door.unlockedMessage);
}

Box createBox(const std::string& name, const std::string& closedImage, const std::string& openedImage,
	SceneID scene, int x, int y,
	ObjectID hiddenObject,
	ObjectID key,
	bool opened, bool locked,
	const std::string& lockedMessage,
	const std::string& unlockedMessage,
	const std::string& keyMessage,
	const std::string& openedMessage,
	bool shown)
{
	Box box;
	box.closedImage = closedImage;
	box.openedImage = openedImage;

	box.opened = opened;
	box.locked = locked;

	box.hiddenObject = hiddenObject;
	box.key = key;

	box.lockedMessage = lockedMessage;
	box.unlockedMessage = unlockedMessage;
	box.keyMessage = keyMessage;
	box.openedMessage = openedMessage;

	if (opened) {
		box.id = createObject(name.c_str(), box.openedImage, scene, x, y, shown);
	}
	else {
		box.id = createObject(name.c_str(), box.closedImage, scene, x, y, shown);
	}
	return box;
}

void mouseActionCallback_Box(Box& box, int x, int y, MouseAction action)
{
	if (box.locked) {
		SHOW_MESSAGE(box.lockedMessage);
	}
	else if (!box.opened) {
		if (box.key > 0 && box.key != getHandObject()) {
			SHOW_MESSAGE(box.keyMessage);
		}
		else {
			box.opened = true;

			if (box.openedImage.compare(box.closedImage) != 0) {
				setObjectImage(box.id, box.openedImage.c_str());
				SHOW_MESSAGE(box.openedMessage);

				if (box.hiddenObject > 0) {
					showObject(box.hiddenObject);
				}
			}
		}
	}
}

void keypadCallback_Box(Box& box)
{
	box.locked = false;
	SHOW_MESSAGE(box.unlockedMessage);
}


Keypad createKeypad(const std::string& name, const std::string& image,
	SceneID scene, int x, int y,
	ObjectID target,
	const std::string& password,
	const std::string& message,
	bool shown)
{
	Keypad keypad;
	keypad.id = createObject(name.c_str(), image.c_str(), scene, x, y, shown);

	keypad.target = target;
	keypad.password = password;
	keypad.message = message;

	return keypad;
}

void mouseActionCallback_Keypad(Keypad& keypad, int x, int y, MouseAction action)
{
	showKeypad(keypad.password.c_str(), keypad.target);
	SHOW_MESSAGE(keypad.message);
}

