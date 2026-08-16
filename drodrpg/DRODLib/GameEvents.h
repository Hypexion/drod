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

//GameEvents.h

#ifndef DB_GAMEEVENTS
#define DB_GAMEEVENTS

#include <BackEndLib/Wchar.h>
#include <string>

#include "RoomData.h"

enum GameEventType {
	GE_EnterRoom,
	GE_CollectItem,
	GE_UseKeyOnDoor,
	GE_UseMoneyOnDoor,
	GE_DigDirt,
	GE_Combat,
	GE_MonsterAttack,
	GE_HurtByTile,
	GE_SwapEquipment,
	GE_UseEquipment,
	GE_UsePortableOrbOnDoor,
	GE_UsePickaxeOnWall,
	GE_UseHandbomb,
	GE_UseWarpToken,
	GE_ScoreCheckpoint,
	GE_ScriptStatChange
};

//*****************************************************************************
class CDbRoom;
class CGameEvent {
public:
	CGameEvent(GameEventType type);
	~CGameEvent() = default;

	GameEventType type() const { return eventType; }
	virtual WSTRING toText() const = 0;

private:
	GameEventType eventType;
};

//*****************************************************************************
class CEnterRoomEvent : public CGameEvent {
public:
	CEnterRoomEvent(CDbRoom* pRoom);
	~CEnterRoomEvent() = default;

	virtual WSTRING toText() const override;

private:
	WSTRING locationDescription;
};

//*****************************************************************************
class CCollectedItemEvent : public CGameEvent {
public:
	CCollectedItemEvent();
	~CCollectedItemEvent() = default;

	void addHP(int amount);
	void addATK(int amount);
	void addDEF(int amount);
	void addShovels(int amount);
	void addYellowKey(UINT amount);
	void addGreenKey(UINT amount);
	void addBlueKey(UINT amount);
	void addSkeletonKey(UINT amount);

	virtual WSTRING toText() const override;

private:
	int hp, atk, def, shovels; //amount of stats gained (can be negative with multiplier)
	UINT yellowKey, greenKey, blueKey, skeletonKey; //amount of keys gained
};

//*****************************************************************************
class CUseKeyOnDoorEvent : public CGameEvent {
public:
	CUseKeyOnDoorEvent(KeyType type, UINT x, UINT y, bool opened);
	~CUseKeyOnDoorEvent() = default;

	virtual WSTRING toText() const override;

private:
	KeyType type;
	CCoord position;
	bool opened;
};

//*****************************************************************************
class CUseMoneyOnDoorEvent : public CGameEvent {
public:
	CUseMoneyOnDoorEvent(int cost, UINT x, UINT y, bool opened);
	~CUseMoneyOnDoorEvent() = default;

	virtual WSTRING toText() const override;

private:
	int cost;
	CCoord position;
	bool opened;
};

//*****************************************************************************
class CDigDirtEvent : public CGameEvent {
public:
	CDigDirtEvent(UINT cost, UINT x, UINT y);
	~CDigDirtEvent() = default;

	virtual WSTRING toText() const override;

private:
	UINT cost;
	CCoord position;
};

//*****************************************************************************
class CCombatEvent : public CGameEvent {
public:
	CCombatEvent(
		const WSTRING& monsterName, UINT wX, UINT wY);
	~CCombatEvent() = default;

	void setResults(const int hpDelta, const int grDelta, const int repDelta);

	virtual WSTRING toText() const override;

private:
	CCoord position;
	WSTRING monsterName;
	int hpDelta;
	int grDelta;
	int repDelta;
};

//*****************************************************************************
class CMonsterAttackEvent : public CGameEvent {
public:
	CMonsterAttackEvent(const WSTRING& monsterName, UINT wX, UINT wY, UINT damage);
	~CMonsterAttackEvent() = default;

	virtual WSTRING toText() const override;

private:
	CCoord position;
	WSTRING monsterName;
	UINT damage;
};

//*****************************************************************************
class CScoreCheckpointEvent : public CGameEvent {
public:
	CScoreCheckpointEvent(const WSTRING& name, int score);
	~CScoreCheckpointEvent() = default;

	virtual WSTRING toText() const override;

private:
	WSTRING scoreCheckpointName;
	int score;
};

#endif //#ifndef DB_GAMEEVENTS
