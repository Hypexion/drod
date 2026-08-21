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
#include "TileConstants.h"

//*****************************************************************************
WSTRING coordinateToWSTRING(CCoord cordinate)
{
	WSTRING positionStr = wszLeftParen;
	positionStr += to_WSTRING(cordinate.wX);
	positionStr += wszComma;
	positionStr += to_WSTRING(cordinate.wY);
	positionStr += wszRightParen;
	return positionStr;
}

//*****************************************************************************
CGameEvent::CGameEvent(GameEventType type)
	: eventType(type)
{}

//*****************************************************************************
CEnterRoomEvent::CEnterRoomEvent(CDbRoom* pRoom)
	: CGameEvent(GameEventType::GE_EnterRoom), locationDescription()
{
	CDbLevel* pLevel = pRoom->GetCurrentGame()->pLevel;
	this->locationDescription = (const WCHAR*)pLevel->NameText;
	WSTRING position;
	pRoom->GetLevelPositionDescription(position);
	this->locationDescription += wszColon;
	this->locationDescription += wszSpace;
	this->locationDescription += position;
}

//*****************************************************************************
WSTRING CEnterRoomEvent::toText() const
{
	return this->locationDescription;
}

//*****************************************************************************
CCollectedItemEvent::CCollectedItemEvent()
	: CGameEvent(GameEventType::GE_CollectItem)
	, hp(0), atk(0), def(0), shovels(0)
	, yellowKey(0), greenKey(0), blueKey(0), skeletonKey(0)
{}

//*****************************************************************************
void CCollectedItemEvent::addHP(int amount)
{
	this->hp += amount;
}

//*****************************************************************************
void CCollectedItemEvent::addATK(int amount)
{
	this->atk += amount;
}

//*****************************************************************************
void CCollectedItemEvent::addDEF(int amount)
{
	this->def += amount;
}

//*****************************************************************************
void CCollectedItemEvent::addShovels(int amount)
{
	this->shovels += amount;
}

//*****************************************************************************
void CCollectedItemEvent::addYellowKey(UINT amount)
{
	this->yellowKey += amount;
}

//*****************************************************************************
void CCollectedItemEvent::addGreenKey(UINT amount)
{
	this->greenKey += amount;
}

//*****************************************************************************
void CCollectedItemEvent::addBlueKey(UINT amount)
{
	this->blueKey += amount;
}
//*****************************************************************************
void CCollectedItemEvent::addSkeletonKey(UINT amount)
{
	this->skeletonKey += amount;
}

//*****************************************************************************
WSTRING CCollectedItemEvent::toText() const
{
	WSTRING wstr = L"Collected ";
	bool needSpace = false;

	if (hp != 0) {
		wstr += to_WSTRING(hp);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_MonsterHP);
		needSpace = true;
	}

	if (atk != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(atk);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_ATKStat);
		needSpace = true;
	}

	if (def != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(def);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_DEFStat);
		needSpace = true;
	}

	if (yellowKey != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(yellowKey);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_YKEYStat);
		needSpace = true;
	}

	if (greenKey != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(greenKey);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_GKEYStat);
		needSpace = true;
	}

	if (blueKey != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(blueKey);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_BKEYStat);
		needSpace = true;
	}

	if (skeletonKey != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(skeletonKey);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_SKEYStat);
		needSpace = true;
	}

	if (shovels != 0) {
		if (needSpace) {
			wstr += wszCommaSpace;
		}

		wstr += to_WSTRING(shovels);
		wstr += wszSpace;
		wstr += g_pTheDB->GetMessageText(MID_ShovelsStat);
		needSpace = true;
	}

	return wstr;
}

//*****************************************************************************
CUseKeyOnDoorEvent::CUseKeyOnDoorEvent(KeyType type, UINT x, UINT y, bool opened)
	: CGameEvent(GE_UseKeyOnDoor), type(type), position(x, y), opened(opened)
{}

//*****************************************************************************
WSTRING CUseKeyOnDoorEvent::toText() const
{
	WSTRING wstr = this->opened ? L"Opened door at %position%" :
		L"Closed door at %position%";

	WSTRING positionStr = wszLeftParen;
	positionStr += to_WSTRING(position.wX);
	positionStr += wszComma;
	positionStr += to_WSTRING(position.wY);
	positionStr += wszRightParen;
	wstr = WCSReplace(wstr, WS("%position%"), positionStr);

	wstr += wszSpace;
	wstr += wszLeftParen;
	wstr += wszHyphen;
	wstr += wszOne;
	wstr += wszSpace;
	wstr += g_pTheDB->GetMessageText(getKeyStatMID(type));
	wstr += wszRightParen;

	return wstr;
}

//*****************************************************************************
CUseMoneyOnDoorEvent::CUseMoneyOnDoorEvent(int cost, UINT x, UINT y, bool opened)
	: CGameEvent(GE_UseMoneyOnDoor), cost(cost), position(x,y), opened(opened)
{}

//*****************************************************************************
WSTRING CUseMoneyOnDoorEvent::toText() const
{
	WSTRING wstr = this->opened ? L"Opened door at %position%" :
		L"Closed door at %position%";
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));

	wstr += wszSpace;
	wstr += wszLeftParen;
	if (cost < 0) {
		wstr += wszPlus;
	}
	wstr += to_WSTRING(-cost);
	wstr += wszSpace;
	wstr += g_pTheDB->GetMessageText(MID_GRStat);
	wstr += wszRightParen;

	return wstr;
}

//*****************************************************************************
CDigDirtEvent::CDigDirtEvent(UINT cost, UINT x, UINT y)
	: CGameEvent(GE_DigDirt), cost(cost), position(x, y)
{}

//*****************************************************************************
WSTRING CDigDirtEvent::toText() const
{
	WSTRING wstr = L"Dug up dirt at %position%";
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));

	wstr += wszSpace;
	wstr += wszLeftParen;
	wstr += to_WSTRING(-cost);
	wstr += wszSpace;
	wstr += g_pTheDB->GetMessageText(MID_ShovelsStat);
	wstr += wszRightParen;

	return wstr;
}

//*****************************************************************************
CCombatEvent::CCombatEvent(const WSTRING& monsterName, UINT wX, UINT wY)
	: CGameEvent(GE_Combat), monsterName(monsterName), position(wX, wY)
	, hpDelta(0), grDelta(0), repDelta(0)
{}

//*****************************************************************************
void CCombatEvent::setResults(const int hpDelta, const int grDelta, const int repDelta)
{
	this->hpDelta = hpDelta;
	this->grDelta = grDelta;
	this->repDelta = repDelta;
}

//*****************************************************************************
WSTRING CCombatEvent::toText() const
{
	WSTRING wstr = L"Fought %monster% at %position%";
	wstr = WCSReplace(wstr, WS("%monster%"), monsterName);
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));

	if (hpDelta != 0 || grDelta != 0 || repDelta != 0) {
		bool needSpace = false;
		wstr += wszSpace;
		wstr += wszLeftParen;
		if (hpDelta != 0) {
				if (hpDelta > 0) {
					wstr += wszPlus;
				}
			wstr += to_WSTRING(hpDelta);
			wstr += wszSpace;
			wstr += g_pTheDB->GetMessageText(MID_MonsterHP);
			needSpace = true;
		}

		if (grDelta != 0) {
			if (needSpace) {
				wstr += wszCommaSpace;
			}
			if (grDelta > 0) {
				wstr += wszPlus;
			}
			wstr += to_WSTRING(grDelta);
			wstr += wszSpace;
			wstr += g_pTheDB->GetMessageText(MID_GRStat);
			needSpace = true;
		}

		if (repDelta != 0) {
			if (needSpace) {
				wstr += wszCommaSpace;
			}
			if (repDelta > 0) {
				wstr += wszPlus;
			}
			wstr += to_WSTRING(repDelta);
			wstr += wszSpace;
			wstr += g_pTheDB->GetMessageText(MID_XPStat);
		}

		wstr += wszRightParen;
	}

	return wstr;
}

//*****************************************************************************
CMonsterAttackEvent::CMonsterAttackEvent(
	const WSTRING& monsterName, UINT wX, UINT wY, UINT damage)
	: CGameEvent(GE_MonsterAttack)
	, monsterName(monsterName), position(wX, wY), damage(damage)
{}

//*****************************************************************************
WSTRING CMonsterAttackEvent::toText() const
{
	WSTRING wstr = L"Hit by %monster% at %position%";
	wstr = WCSReplace(wstr, WS("%monster%"), monsterName);
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));

	wstr += wszSpace;
	wstr += wszLeftParen;
	wstr += to_WSTRING(-damage);
	wstr += wszSpace;
	wstr += g_pTheDB->GetMessageText(MID_MonsterHP);
	wstr += wszRightParen;

	return wstr;
}

//*****************************************************************************
CBeamDamageEvent::CBeamDamageEvent(
	const UINT wX, const UINT wY, const UINT damage)
	: CGameEvent(CE_BeamDamage), position(wX, wY), damage(damage)
{}

//*****************************************************************************
WSTRING CBeamDamageEvent::toText() const
{
	WSTRING wstr = L"Hit by beam at %position%";
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));

	wstr += wszSpace;
	wstr += wszLeftParen;
	wstr += to_WSTRING(-damage);
	wstr += wszSpace;
	wstr += g_pTheDB->GetMessageText(MID_MonsterHP);
	wstr += wszRightParen;

	return wstr;
}

//*****************************************************************************
CTileDamageEvent::CTileDamageEvent(
	const UINT tileType, const UINT wX, const UINT wY, const UINT damage)
	: CGameEvent(GE_TileDamage), tileType(tileType)
	, position(wX, wY), damage(damage)
{}

//*****************************************************************************
WSTRING CTileDamageEvent::toText() const
{
	WSTRING wstr = L"Stepped on %tile% at %position%";
	wstr = WCSReplace(wstr, WS("%tile%"), g_pTheDB->GetMessageText(TILE_MID[tileType]));
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));

	wstr += wszSpace;
	wstr += wszLeftParen;
	wstr += to_WSTRING(-damage);
	wstr += wszSpace;
	wstr += g_pTheDB->GetMessageText(MID_MonsterHP);
	wstr += wszRightParen;

	return wstr;
}

//*****************************************************************************
CUsePickaxeOnWallEvent::CUsePickaxeOnWallEvent(const UINT wX, const UINT wY)
	: CGameEvent(GE_UsePickaxeOnWall), position(wX, wY)
{}

//*****************************************************************************
WSTRING CUsePickaxeOnWallEvent::toText() const
{
	WSTRING wstr = L"Destroyed wall at %position% using pickaxe";
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));
	return wstr;
}

//*****************************************************************************
CUsePortableOrbOnDoorEvent::CUsePortableOrbOnDoorEvent(const UINT wX, const UINT wY)
	: CGameEvent(GE_UsePortableOrbOnDoor), position(wX, wY)
{}

//*****************************************************************************
WSTRING CUsePortableOrbOnDoorEvent::toText() const
{
	WSTRING wstr = L"Opened door at %position% using portable orb";
	wstr = WCSReplace(wstr, WS("%position%"), coordinateToWSTRING(position));
	return wstr;
}

//*****************************************************************************
CScoreCheckpointEvent::CScoreCheckpointEvent(const WSTRING& name, int score)
	: CGameEvent(GE_ScoreCheckpoint), scoreCheckpointName(name), score(score)
{}

//*****************************************************************************
WSTRING CScoreCheckpointEvent::toText() const
{
	WSTRING wstr = L"Achievied score checkpoint:";
	wstr += wszSpace;
	wstr += scoreCheckpointName;
	wstr += wszSpace;
	wstr += wszHyphen;
	wstr += wszSpace;
	wstr += to_WSTRING(score);
	return wstr;
}
