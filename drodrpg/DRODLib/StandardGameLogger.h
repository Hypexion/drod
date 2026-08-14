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

//StandardGameLogger.h

#ifndef STANDARDGAMELOGGER
#define STANDARDGAMELOGGER

#include "BaseGameLogger.h"
#include "GameEvents.h"

#include <BackEndLib/StretchyBuffer.h>

#include <memory>
#include <vector>

//*****************************************************************************
class CStandardGameLogger : public CBaseGameLogger {
public:
	CStandardGameLogger() = default;
	~CStandardGameLogger();

	virtual void enterRoom(CDbRoom* room) override;

	virtual void collectHP(const int amount) override;
	virtual void collectATK(const int amount) override;
	virtual void collectDEF(const int amount) override;
	virtual void collectShovels(const int amount) override;
	virtual void collectKey(const KeyType type) override;

	virtual void openDoorWithKey(const KeyType type, UINT wX, UINT wY) override;
	virtual void closeDoorWithKey(const KeyType type, UINT wX, UINT wY) override;
	virtual void openDoorWithMoney(const int cost, UINT wX, UINT wY) override;
	virtual void closeDoorWithMoney(const int cost, UINT wX, UINT wY) override;

	virtual void digDirt(const UINT cost, UINT wX, UINT wY) override;

	virtual void beginCombat(const WSTRING& monsterName, UINT wX, UINT wY) override;
	virtual void endCombat(const int hpDelta, const int grDelta, const int repDelta) override;

	virtual void scoreCheckpoint(const WSTRING& scoreName, const int score) override;

	virtual void output() override;

	virtual void clear() override;

	void writeToFile() const;

protected:
	CCollectedItemEvent* getCollectedItemEvent();

	std::vector<std::unique_ptr<CGameEvent>> gameEvents;
	CStretchyBuffer outputBuffer;
};

#endif // #ifndef STANDARDGAMELOGGER
