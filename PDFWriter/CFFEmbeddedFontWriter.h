/*
   Source File : CFFEmbeddedFontWriter.h


   Copyright 2011 Gal Kahana PDFWriter

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   
*/
#pragma once

#include "EPDFStatusCode.h"
#include "ObjectsBasicTypes.h"
#include "OpenTypeFileInput.h"
#include "MyStringBuf.h"
#include "InputFile.h"
#include "CFFPrimitiveWriter.h"
#include "OutputStringBufferStream.h"
#include "IOBasicTypes.h"

#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using namespace IOBasicTypes;

typedef vector<unsigned int> UIntVector;
typedef set<unsigned int> UIntSet;
typedef vector<unsigned short> UShortVector;
typedef map<FontDictInfo*,Byte> FontDictInfoToByteMap;


class FreeTypeFaceWrapper;
class ObjectsContext;

class CFFEmbeddedFontWriter
{
public:
	CFFEmbeddedFontWriter(void);
	~CFFEmbeddedFontWriter(void);

	EPDFStatusCode WriteEmbeddedFont(	FreeTypeFaceWrapper& inFontInfo,
									const UIntVector& inSubsetGlyphIDs,
									const string& inFontFile3SubType,
									const string& inSubsetFontName,
									ObjectsContext* inObjectsContext,
									ObjectIDType& outEmbeddedFontObjectID);

	// the optional inCIDMapping parameter provides a vector ordered in the same
	// way as the glyph IDs. for each position in the CID mapping vector there's the matching CID
	// for the GID in the same position in the subset glyph IDs.
	// use it when the CFF origin is from a subset font, and the GID->CID mapping is not simply
	// identity
	EPDFStatusCode WriteEmbeddedFont(	FreeTypeFaceWrapper& inFontInfo,
									const UIntVector& inSubsetGlyphIDs,
									const string& inFontFile3SubType,
									const string& inSubsetFontName,
									ObjectsContext* inObjectsContext,
									UShortVector* inCIDMapping,
									ObjectIDType& outEmbeddedFontObjectID);


private:
	OpenTypeFileInput mOpenTypeInput;
	InputFile mOpenTypeFile;
	CFFPrimitiveWriter mPrimitivesWriter;
	OutputStringBufferStream mFontFileStream;
	bool mIsCID;
	string mOptionalEmbeddedPostscript;

	// placeholders positions
	LongFilePositionType mCharsetPlaceHolderPosition;
	LongFilePositionType mEncodingPlaceHolderPosition;
	LongFilePositionType mCharstringsPlaceHolderPosition;
	LongFilePositionType mPrivatePlaceHolderPosition;
	LongFilePositionType mFDArrayPlaceHolderPosition;
	LongFilePositionType mFDSelectPlaceHolderPosition;
	
	LongFilePositionType mEncodingPosition;
	LongFilePositionType mCharsetPosition;
	LongFilePositionType mCharStringPosition;
	LongFilePositionType mPrivatePosition;
	LongFilePositionType mPrivateSize;
	LongFilePositionType mFDArrayPosition;
	LongFilePositionType mFDSelectPosition;

	EPDFStatusCode CreateCFFSubset(	
					FreeTypeFaceWrapper& inFontInfo,
					const UIntVector& inSubsetGlyphIDs,
					UShortVector* inCIDMapping,
					const string& inSubsetFontName,
					bool& outNotEmbedded,
					MyStringBuf& outFontProgram);
	EPDFStatusCode AddDependentGlyphs(UIntVector& ioSubsetGlyphIDs);
	EPDFStatusCode AddComponentGlyphs(unsigned int inGlyphID,UIntSet& ioComponents,bool &outFoundComponents);
	EPDFStatusCode WriteCFFHeader();
	EPDFStatusCode WriteName(const string& inSubsetFontName);
	EPDFStatusCode WriteTopIndex();
	Byte GetMostCompressedOffsetSize(unsigned long inOffset);
	EPDFStatusCode WriteTopDictSegment(MyStringBuf& ioTopDictSegment);
	EPDFStatusCode WriteStringIndex();
	EPDFStatusCode WriteGlobalSubrsIndex();
	EPDFStatusCode WriteEncodings(const UIntVector& inSubsetGlyphIDs);
	EPDFStatusCode WriteCharsets(const UIntVector& inSubsetGlyphIDs,UShortVector* inCIDMapping);
	EPDFStatusCode WriteCharStrings(const UIntVector& inSubsetGlyphIDs);
	EPDFStatusCode WritePrivateDictionary();

	EPDFStatusCode WriteFDArray(const UIntVector& inSubsetGlyphIDs,const FontDictInfoToByteMap& inNewFontDictsIndexes);
	EPDFStatusCode WriteFDSelect(const UIntVector& inSubsetGlyphIDs,const FontDictInfoToByteMap& inNewFontDictsIndexes);
	EPDFStatusCode WritePrivateDictionaryBody(	const PrivateDictInfo& inPrivateDictionary,
											LongFilePositionType& outWriteSize,
											LongFilePositionType& outWritePosition);
	EPDFStatusCode UpdateIndexesAtTopDict();

	void DetermineFDArrayIndexes(const UIntVector& inSubsetGlyphIDs,FontDictInfoToByteMap& outNewFontDictsIndexes);
	
};
