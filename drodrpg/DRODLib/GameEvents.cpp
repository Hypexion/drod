#include "GameEvents.h"
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
#include "GameEvents.h"

#include "DbRooms.h"
#include "Db.h"

 //*****************************************************************************
CGameEvent::CGameEvent(GameEventType type)
	: eventType(type)
{}

//*****************************************************************************
CEnterRoomEvent::CEnterRoomEvent(CDbRoom* pRoom)
	: CGameEvent(GameEventType::GE_EnterRoom), locationDescription()
{
	pRoom->GetLevelPositionDescription(this->locationDescription);
}

//*****************************************************************************
WSTRING CEnterRoomEvent::toText() const
{
	return this->locationDescription;
}

//*****************************************************************************
CItemCollectedEvent::CItemCollectedEvent(int hp, int atk, int def, int shovels,
	UINT yellowKey, UINT greenKey, UINT blueKey, UINT skeletonKey)
	: CGameEvent(GameEventType::GE_CollectItem)
	, hp(hp), atk(atk), def(def), shovels(shovels)
	, yellowKey(yellowKey), greenKey(greenKey), blueKey(blueKey), skeletonKey(skeletonKey)
{}

//*****************************************************************************
WSTRING CItemCollectedEvent::toText() const
{
	WSTRING wstr = L"Collected ";
	bool needSpace = false;

	if (hp != 0) {
		wstr += to_WSTRING(hp);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_MonsterHP);
		bool needSpace = true;
	}

	if (atk != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(atk);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_ATKStat);
		bool needSpace = true;
	}

	if (def != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(def);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_DEFStat);
		bool needSpace = true;
	}

	if (yellowKey != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(yellowKey);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_YKEYStat);
		bool needSpace = true;
	}

	if (greenKey != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(greenKey);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_GKEYStat);
		bool needSpace = true;
	}

	if (blueKey != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(blueKey);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_BKEYStat);
		bool needSpace = true;
	}

	if (skeletonKey != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(skeletonKey);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_SKEYStat);
		bool needSpace = true;
	}

	if (shovels != 0) {
		if (needSpace) {
			wstr += wszSpace;
		}

		wstr += to_WSTRING(shovels);
		wstr += wszSpace;
		g_pTheDB->GetMessageText(MID_ShovelsStat);
		bool needSpace = true;
	}

	return wstr;
}
