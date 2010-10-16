#pragma once

#include "EStatusCode.h"
#include "ObjectsBasicTypes.h"
#include "WrittenFontRepresentation.h"

#include <utility>
#include <vector>
#include <string>
#include <list>

class FreeTypeFaceWrapper;
class ObjectsContext;
class DictionaryContext;
class IANSIFontWriterHelper;

using namespace std;

typedef pair<unsigned short,string>  UShortAndString;
typedef list<UShortAndString> UShortAndStringList;

typedef pair<unsigned int, GlyphEncodingInfo> UIntAndGlyphEncodingInfo;
typedef vector<UIntAndGlyphEncodingInfo> UIntAndGlyphEncodingInfoVector;

class ANSIFontWriter 
{
public:
	ANSIFontWriter(void);
	~ANSIFontWriter(void);


	EStatusCode WriteFont(	FreeTypeFaceWrapper& inFontInfo,
							WrittenFontRepresentation* inFontOccurrence,
							ObjectsContext* inObjectsContext,
							IANSIFontWriterHelper* inANSIFontWriterHelper);

private:

	void CalculateCharacterEncodingArray();
	void WriteWidths(DictionaryContext* inFontContext);
	void CalculateDifferences();
	void WriteEncoding(DictionaryContext* inFontContext);
	void WriteEncodingDictionary();
	void WriteToUnicodeMap(ObjectIDType inToUnicodeMap);

	FreeTypeFaceWrapper* mFontInfo;
	WrittenFontRepresentation* mFontOccurrence;
	ObjectsContext* mObjectsContext;

	UIntAndGlyphEncodingInfoVector mCharactersVector;
	UShortAndStringList mDifferences;
	ObjectIDType mEncodingDictionaryID;
};