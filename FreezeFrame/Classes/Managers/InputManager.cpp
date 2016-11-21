#include "InputManager.h"
#include "ScreenManager.h"

#include <pugixml.hpp>
using namespace pugi;

InputManager* InputManager::instance = NULL;

#define AXIS_VALUE_HIGH 100
#define AXIS_VALUE_LOW -100
#define AXIS_DEADZONE 10
#define AXIS_PRESSED_THRESHOLD 80

InputManager::InputManager()
{
	if (instance)
	{
		cout << "ERROR (InputManager) : Attempting to instantiate InputManager directly. This is not allowed!" << endl;
		return;
	}

	LoadInputConfig();
	debugText = Text("", ScreenManager::GetInstance()->GetFont(), 20);
	debugText.setFillColor(Color(255,0,0,255));
}

InputManager::~InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	if (!instance)
	{
		instance = new InputManager();
	}
	return instance;
}

void InputManager::PollEvent(Event e)
{
	if (e.type == Event::KeyPressed)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
			{
				if (it->keyboardMapping == e.key.code && !it->pressed && !it->down)
				{
					it->pressed = true;
				}
			}
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->keyboardHighMapping == e.key.code && !it->highPressed && !it->highDown)
				{
					it->highPressed = true;
					it->value = AXIS_VALUE_HIGH;
				}
				else if (it->keyboardLowMapping == e.key.code && !it->lowPressed && !it->lowDown)
				{
					it->lowPressed = true;
					it->value = AXIS_VALUE_LOW;
				}
			}
		}
	}
	else if (e.type == Event::KeyReleased)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
			{
				if (it->keyboardMapping == e.key.code && !it->released)
				{
					it->released = true;
				}
			}
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->keyboardHighMapping == e.key.code && !it->highReleased)
				{
					it->highReleased = true;
					it->value = 0;
				}
				else if (it->keyboardLowMapping == e.key.code && !it->lowReleased)
				{
					it->lowReleased = true;
					it->value = 0;
				}
			}
		}
	}
	else if (e.type == Event::JoystickButtonPressed)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
			{
				if (it->joystickMapping == e.joystickButton.button && !it->pressed && !it->down)
				{
					it->pressed = true;
				}
			}
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->joystickHighMapping == e.joystickButton.button && !it->highPressed && !it->highDown)
				{
					it->highPressed = true;
					it->value = AXIS_VALUE_HIGH;
				}
				else if (it->joystickLowMapping == e.joystickButton.button && !it->lowPressed && !it->lowDown)
				{
					it->lowPressed = true;
					it->value = AXIS_VALUE_LOW;
				}
			}
		}
	}
	else if (e.type == Event::JoystickButtonReleased)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
			{
				if (it->joystickMapping == e.joystickButton.button && !it->released)
				{
					it->released = true;
				}
			}
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->joystickHighMapping == e.joystickButton.button && !it->highReleased)
				{
					it->highReleased = true;
					it->value = AXIS_VALUE_HIGH;
				}
				else if (it->joystickLowMapping == e.joystickButton.button && !it->lowReleased)
				{
					it->lowReleased = true;
					it->value = AXIS_VALUE_LOW;
				}
			}
		}
	}
	else if (e.type == Event::JoystickMoved)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->joystickHighMapping == e.joystickMove.axis)
				{
					it->value = e.joystickMove.position;
					if (!it->highPressed && !it->highDown && e.joystickMove.position > AXIS_PRESSED_THRESHOLD)
						it->highPressed = true;
					else if (it->highDown && e.joystickMove.position < AXIS_PRESSED_THRESHOLD)
						it->highReleased = true;
				}
				if (it->joystickLowMapping == e.joystickMove.axis)
				{
					it->value = e.joystickMove.position;
					if (!it->lowPressed && !it->lowDown && e.joystickMove.position < AXIS_PRESSED_THRESHOLD * -1)
						it->lowPressed = true;
					else if (it->lowDown && e.joystickMove.position > AXIS_PRESSED_THRESHOLD * -1)
						it->lowReleased = true;
				}
			}
		}
	}
	if (e.type == Event::MouseButtonPressed)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
			{
				if (it->mouseMapping == e.mouseButton.button && !it->pressed && !it->down)
				{
					it->pressed = true;
				}
			}
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->mouseHighMapping == e.mouseButton.button && !it->highPressed && !it->highDown)
				{
					it->highPressed = true;
					it->value = AXIS_VALUE_HIGH;
				}
				else if (it->mouseLowMapping == e.mouseButton.button && !it->lowPressed && !it->lowDown)
				{
					it->lowPressed = true;
					it->value = AXIS_VALUE_LOW;
				}
			}
		}
	}
	else if (e.type == Event::MouseButtonReleased)
	{
		for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
		{
			for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
			{
				if (it->mouseMapping == e.mouseButton.button && !it->released)
				{
					it->released = true;
				}
			}
			for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
			{
				if (it->mouseHighMapping == e.mouseButton.button && !it->highReleased)
				{
					it->highReleased = true;
					it->value = 0;
				}
				else if (it->mouseLowMapping == e.mouseButton.button && !it->lowReleased)
				{
					it->lowReleased = true;
					it->value = 0;
				}
			}
		}
	}
}

void InputManager::Update(float dt)
{
	UpdateInput();
}

void InputManager::Draw(RenderWindow* window)
{
	window->draw(debugText);
}

bool InputManager::IsButtonPressed(int playerId, InputID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].buttonInputs[inputId].pressed;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsButtonDown(int playerId, InputID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].buttonInputs[inputId].down;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsButtonReleased(int playerId, InputID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].buttonInputs[inputId].released;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsHighAxisButtonPressed(int playerId, AxisID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[inputId].highPressed;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsHighAxisButtonDown(int playerId, AxisID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[inputId].highDown;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsHighAxisButtonReleased(int playerId, AxisID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[inputId].highReleased;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsLowAxisButtonPressed(int playerId, AxisID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[inputId].lowPressed;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsLowAxisButtonDown(int playerId, AxisID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[inputId].lowDown;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

bool InputManager::IsLowAxisButtonReleased(int playerId, AxisID inputId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[inputId].lowReleased;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return false;
}

float InputManager::GetAxisValue(int playerId, AxisID axisId)
{
	if (playerId >= 0 && playerId < playerInputs.size())
		return playerInputs[playerId].axisInputs[axisId].value;
	cout << "ERROR (InputManager) : Invalid playerId" << endl;
	return 0;
}

void InputManager::UpdateInput()
{
	for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
	{
		for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
		{
			if (it->pressed)
			{
				it->pressed = false;
				it->down = true;
			}
			if (it->released)
			{
				it->down = false;
				it->released = false;
			}
		}
		for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
		{
			if (it->highPressed)
			{
				it->highPressed = false;
				it->highDown = true;
			}
			if (it->highReleased)
			{
				it->highDown = false;
				it->highReleased = false;
			}
			if (it->lowPressed)
			{
				it->lowPressed = false;
				it->lowDown = true;
			}
			if (it->lowReleased)
			{
				it->lowDown = false;
				it->lowReleased = false;
			}
		}
	}
}

void InputManager::LoadInputConfig()
{
	xml_document doc;
	xml_parse_result result = doc.load_file(CONFIG_IO_PATH "InputMapping.xml");
	if (!result)
	{
		cout << "ERROR (InputManager) : Could not load XML file: " << CONFIG_IO_PATH << "InputMapping.xml" << endl;
		return;
	}
	xml_node root = doc.document_element();
	
	for (pugi::xml_node_iterator mappingIt = root.begin(); mappingIt != root.end(); mappingIt++)
	{
		PlayerInput pi;
		xml_node buttons = mappingIt->child("Buttons");
		xml_node axes = mappingIt->child("Axes");
		for (pugi::xml_node_iterator it = buttons.begin(); it != buttons.end(); it++)
		{
			ButtonInput input;
			input.id = (InputID)it->attribute("ID").as_int();
			if (it->child("Keyboard"))
				input.keyboardMapping = it->child("Keyboard").attribute("Value").as_int();
			if (it->child("Joystick"))
				input.joystickMapping = it->child("Joystick").attribute("Value").as_int();
			if (it->child("Mouse"))
				input.mouseMapping = it->child("Mouse").attribute("Value").as_int();

			pi.buttonInputs.push_back(input);
		}
		for (pugi::xml_node_iterator it = axes.begin(); it != axes.end(); it++)
		{
			AxisInput input;
			input.id = (AxisID)it->attribute("ID").as_int();
			// Axis inputs are split up into two inputs - high and low - in that order
			// HIGH Input
			if (it->child("Keyboard"))
				input.keyboardHighMapping = it->child("Keyboard").attribute("Value").as_int();
			if (it->child("Joystick"))
				input.joystickHighMapping = it->child("Joystick").attribute("Value").as_int();
			if (it->child("Mouse"))
				input.mouseHighMapping = it->child("Mouse").attribute("Value").as_int();
			// LOW Input
			it++;
			if (it->child("Keyboard"))
				input.keyboardLowMapping = it->child("Keyboard").attribute("Value").as_int();
			if (it->child("Joystick"))
				input.joystickLowMapping = it->child("Joystick").attribute("Value").as_int();
			if (it->child("Mouse"))
				input.mouseLowMapping = it->child("Mouse").attribute("Value").as_int();

			pi.axisInputs.push_back(input);
		}
		playerInputs.push_back(pi);
	}
}

void InputManager::SaveInputConfig()
{
	xml_document doc;
	xml_node root = doc.append_child("InputMapping");

	for (vector<PlayerInput>::iterator mappingIt = playerInputs.begin(); mappingIt != playerInputs.end(); mappingIt++)
	{
		xml_node mapping = root.append_child("InputMapping");
		xml_node buttons = mapping.append_child("Buttons");
		xml_node axes = mapping.append_child("Axes");

		for (vector<ButtonInput>::iterator it = mappingIt->buttonInputs.begin(); it != mappingIt->buttonInputs.end(); it++)
		{
			xml_node node = buttons.append_child("Input");
			node.append_attribute("ID").set_value(it->id);
			if (it->keyboardMapping >= 0)
				node.append_child("Keyboard").append_attribute("Value").set_value(it->keyboardMapping);
			if (it->joystickMapping >= 0)
				node.append_child("Joystick").append_attribute("Value").set_value(it->joystickMapping);
			if (it->mouseMapping >= 0)
				node.append_child("Mouse").append_attribute("Value").set_value(it->mouseMapping);
		}

		for (vector<AxisInput>::iterator it = mappingIt->axisInputs.begin(); it != mappingIt->axisInputs.end(); it++)
		{
			{
				xml_node node = axes.append_child("Input");
				node.append_attribute("ID").set_value(it->id);
				node.append_attribute("Value").set_value(AXIS_VALUE_HIGH);
				if (it->keyboardHighMapping >= 0)
					node.append_child("Keyboard").append_attribute("Value").set_value(it->keyboardHighMapping);
				if (it->joystickHighMapping >= 0)
					node.append_child("Joystick").append_attribute("Value").set_value(it->joystickHighMapping);
				if (it->mouseHighMapping >= 0)
					node.append_child("Mouse").append_attribute("Value").set_value(it->mouseHighMapping);
			}
			{
				xml_node node = axes.append_child("Input");
				node.append_attribute("ID").set_value(it->id);
				node.append_attribute("Value").set_value(AXIS_VALUE_LOW);
				if (it->keyboardLowMapping >= 0)
					node.append_child("Keyboard").append_attribute("Value").set_value(it->keyboardLowMapping);
				if (it->joystickLowMapping >= 0)
					node.append_child("Joystick").append_attribute("Value").set_value(it->joystickLowMapping);
				if (it->mouseLowMapping >= 0)
					node.append_child("Mouse").append_attribute("Value").set_value(it->mouseLowMapping);
			}
		}
	}

	if (!doc.save_file(CONFIG_IO_PATH "InputMapping.xml"))
	{
		cout << "ERROR (InputManager) : Could not save XML file: " << CONFIG_IO_PATH << "InputMapping.xml" << endl;
		return;
	}
}

InputManager::ButtonInput::ButtonInput()
{
	id = InputID::InputIDMax;
	keyboardMapping = -1;
	joystickMapping = -1;
	mouseMapping = -1;

	pressed = false;
	down = false;
	released = false;
}

string InputManager::ButtonInput::ToString()
{
	stringstream ret;
	ret << "Button Input: " << id << endl;
	ret << " - Keyboard: " << keyboardMapping << endl;
	ret << " - Joystick: " << joystickMapping << endl;
	ret << " - Mouse: " << mouseMapping;
	return ret.str();
}

string InputManager::ButtonInput::GetStatus()
{
	stringstream ret;
	ret << "Button Input " << id << ": " << pressed << "::" << down << "::" << released;
	return ret.str();
}

InputManager::AxisInput::AxisInput()
{
	id = AxisID::AxisIDMax;
	keyboardHighMapping = -1;
	keyboardLowMapping = -1;
	joystickHighMapping = -1;
	joystickLowMapping = -1;
	mouseHighMapping = -1;
	mouseLowMapping = -1;

	highPressed = false;
	lowPressed = false;
	highDown = false;
	lowDown = false;
	highReleased = false;
	lowReleased = false;
	value = 0;
}

string InputManager::AxisInput::ToString()
{
	stringstream ret;
	ret << "Axis Input: " << id << endl;
	ret << " - Keyboard High: " << keyboardHighMapping << endl;
	ret << " - Keyboard Low: " << keyboardLowMapping << endl;
	ret << " - Joystick High: " << joystickHighMapping << endl;
	ret << " - Joystick Low: " << joystickLowMapping << endl;
	ret << " - Mouse High: " << mouseHighMapping << endl;
	ret << " - Mouse Low: " << mouseLowMapping;
	return ret.str();
}

string InputManager::AxisInput::GetStatus()
{
	stringstream ret;
	ret << "Axis Input " << id << ": " << value << endl << "\tHIGH: " << highPressed << "::" << highDown << "::" << highReleased << "\tLOW:  " << lowPressed << "::" << lowDown << "::" << lowReleased;
	return ret.str();
}
