// $Id: DbXML.h 9286 2008-10-29 02:11:16Z mrimer $

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
 * Portions created by the Initial Developer are Copyright (C) 1995, 1996, 
 * 1997, 2000, 2001, 2002, 2005 Caravel Software. All Rights Reserved.
 *
 * Contributor(s):
 * Mike Rimer (mrimer)
 *
 * ***** END LICENSE BLOCK ***** */

//DbXML.h
//Declarations for CDbXML.
//Interface for exporting/importing database data to/from disk.

#ifndef DBXML_H
#define DBXML_H

#include "Db.h"
#include "../Texts/MIDs.h"

#include <expat.h>

#include <vector>
using std::vector;

extern const char szDRODVersion[];

/*
struct DEMO_UPLOAD
{
	DEMO_UPLOAD(const string& buffer, const UINT wTurn, const UINT dwTimeElapsed,
			const UINT dwDemoID)
		: buffer(buffer), wTurn(wTurn), dwTimeElapsed(dwTimeElapsed), dwDemoID(dwDemoID)
	{ }
	string buffer;
	UINT wTurn;
	UINT dwTimeElapsed;
	UINT dwDemoID;
};
*/
struct SCORE_UPLOAD
{
	SCORE_UPLOAD(const string& buffer, const UINT wScore, const WSTRING& scorename, const UINT dwSavedGameID)
		: buffer(buffer), scorename(scorename), wScore(wScore), dwSavedGameID(dwSavedGameID)
	{ }
	string buffer;
	WSTRING scorename;
	UINT wScore;
	UINT dwSavedGameID;
};

//*****************************************************************************
class CDbXML : public CDb
{
public:
	//Importing and exporting methods.
	static void CleanUp();
	static MESSAGE_ID ImportXML(const WCHAR *pszFilename, const CImportInfo::ImportType type);
	static MESSAGE_ID ImportXML(CStretchyBuffer &buffer, const CImportInfo::ImportType type);
	static MESSAGE_ID ImportXML();	//continue import already in progress
	static bool ExportXML(const VIEWTYPE vType,
			const UINT dwPrimaryKey, const WCHAR *pszFilename);
	static bool ExportXML(const VIEWTYPE vType,
			const CIDSet& primaryKeys, const WCHAR *pszFilename);
	static bool ExportXML(const VIEWTYPE vType, const CIDSet& primaryKeys,
			string &text, const UINT eSaveType=0);

	static UINT GetActiveSpeechID();

	static string getXMLheader(const string *pString=NULL);
	static string getXMLfooter();

	//For XML parsing.
	static void TallyElement(void *userData, const char *name, const char **atts);
	static void StartElement(void *userData, const char *name, const char **atts);
	static void EndElement(void *userData, const char *name);

	static bool WasImportSuccessful();

	static bool ExportSavedGames(const UINT dwHoldID);

	static void SetCallback(CAttachableObject *pObject);
	static void PerformCallback(long val);
	static void PerformCallbackf(float fVal);
	static void PerformCallbackText(const WCHAR* wpText);

	//For (un)compression
	static bool z_compress(const BYTE* src, const ULONG srcSize,
			BYTE*& dest, ULONG& destLen);
	static MESSAGE_ID z_uncompress(ULONG& decodedSize, BYTE*& decodedBuf,
			const BYTE* inBuffer, const UINT inBufferSize);

	static CImportInfo info;
//	static vector<DEMO_UPLOAD> upgradedHoldVictoryDemos;
	static RecordMap exportInfo;

private:
	static void AddRowsForPendingRecords();

	static bool ContinueImport(const MESSAGE_ID status = MID_ImportSuccessful);

	static CDbBase * GetNewRecord(const VIEWTYPE vType);

	static MESSAGE_ID ImportXML(const char *buf, const UINT size);

	static VIEWTYPE ParseViewType(const char *str);
	static VIEWPROPTYPE ParseViewpropType(const char *str);
	static PROPTYPE ParsePropType(const char *str);

	static bool UpdateLocalIDs();

	static void ImportSavedGames();
//	static void VerifySavedGames();

	static vector <CDbBase*> dbRecordStack;   //stack of records being parsed
	static vector <UINT> dbImportedRecordIDs;  //imported record IDs (primary keys)
	static vector <VIEWTYPE> dbRecordTypes;   //record types
	static vector <VIEWPROPTYPE> vpCurrentType;  //stack of viewprops being parsed
	static vector <bool>  SaveRecord;   //whether record should be saved to the DB
};

#endif //...#ifndef DBMXL_H

