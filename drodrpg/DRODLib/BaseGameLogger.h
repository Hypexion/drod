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

//CBaseGameLogger.h
//Base class for logging of game actions. As well as being the base class, it
//acts a "null" implementation that doesn't log anything.

#ifndef BASEGAMELOGGER
#define BASEGAMELOGGER

#include "RoomData.h"

//*****************************************************************************
class CDbRoom;
class CBaseGameLogger {
public:
	CBaseGameLogger() = default;
	~CBaseGameLogger() = default;

	virtual void enterRoom(CDbRoom* room) {}

	virtual void collectHP(const int amount) {}
	virtual void collectATK(const int amount) {}
	virtual void collectDEF(const int amount) {}
	virtual void collectShovels(const int amount) {}
	virtual void collectKey(const KeyType type) {}

	virtual void openDoorWithKey(const KeyType type, UINT wX, UINT wY) {}
	virtual void closeDoorWithKey(const KeyType type, UINT wX, UINT wY) {}
	virtual void openDoorWithMoney(const int cost, UINT wX, UINT wY) {}
	virtual void closeDoorWithMoney(const int cost, UINT wX, UINT wY) {}

	virtual void digDirt(const UINT cost, UINT wX, UINT wY) {}

	virtual void beginCombat(const WSTRING& monsterName, UINT wX, UINT wY) {}
	virtual void endCombat(const int hpDelta, const int grDelta, const int repDelta) {}

	virtual void scoreCheckpoint(const WSTRING& scoreName, const int score) {}

	virtual void output() {}

	virtual void clear() {}
};

#endif // #ifndef BASEGAMELOGGER
