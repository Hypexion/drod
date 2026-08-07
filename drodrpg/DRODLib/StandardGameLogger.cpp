/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Deadly Rooms of Death.
 *
 * The Initial Developer of the Original Code is
 * Caravel Software.
 * Portions created by the Initial Developer are Copyright (C) 2026
 * Caravel Software. All Rights Reserved.
 *
 * Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

#include "StandardGameLogger.h"

#include <BackEndLib/Files.h>

#include <cstdio>

//Help trim down long lines
using std::unique_ptr;
using std::make_unique;

//*****************************************************************************
CStandardGameLogger::~CStandardGameLogger()
{
	output();
	writeToFile();
}

//*****************************************************************************
void CStandardGameLogger::enterRoom(CDbRoom* room)
{
	this->gameEvents.push_back(std::make_unique<CEnterRoomEvent>(room));
}

//*****************************************************************************
void CStandardGameLogger::collectHP(const int amount)
{
	unique_ptr<CCollectedItemEvent> event = make_unique<CCollectedItemEvent>();
	event->addHP(amount);
	this->gameEvents.push_back(std::move(event));
}

//*****************************************************************************
void CStandardGameLogger::collectATK(const int amount)
{
	unique_ptr<CCollectedItemEvent> event = make_unique<CCollectedItemEvent>();
	event->addATK(amount);
	this->gameEvents.push_back(std::move(event));
}

//*****************************************************************************
void CStandardGameLogger::collectDEF(const int amount)
{
	unique_ptr<CCollectedItemEvent> event = make_unique<CCollectedItemEvent>();
	event->addDEF(amount);
	this->gameEvents.push_back(std::move(event));
}

//*****************************************************************************
void CStandardGameLogger::collectShovels(const int amount)
{
	unique_ptr<CCollectedItemEvent> event = make_unique<CCollectedItemEvent>();
	event->addShovels(amount);
	this->gameEvents.push_back(std::move(event));
}

//*****************************************************************************
void CStandardGameLogger::collectKey(const KeyType type)
{
	unique_ptr<CCollectedItemEvent> event = make_unique<CCollectedItemEvent>();

	switch (type) {
		case YellowKey: event->addYellowKey(1); break;
		case GreenKey: event->addGreenKey(1); break;
		case BlueKey: event->addBlueKey(1); break;
		case SkeletonKey: event->addSkeletonKey(1); break;
		default: ASSERT("Invalid key type");
	}

	this->gameEvents.push_back(std::move(event));
}

//*****************************************************************************
void CStandardGameLogger::output()
//Write out the logged game actions to somewhere else (console while in dev)
{
	for (auto& event : this->gameEvents) {
		std::string str = UnicodeToUTF8(event->toText());
		str += NEWLINE;
		this->outputBuffer += str.c_str();
	}
}

//*****************************************************************************
void CStandardGameLogger::clear()
{
	this->gameEvents.clear();
}

//*****************************************************************************
void CStandardGameLogger::writeToFile() const
{
	CFiles::WriteBufferToFile("D:/thing/testlog.txt", this->outputBuffer);
}
