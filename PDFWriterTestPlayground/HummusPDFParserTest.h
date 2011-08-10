/*
   Source File : HummusPDFParserTest.h


   Copyright 2011 Gal Kahana HummusPDFWriter

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

#include "TestsRunner.h"
#include "ObjectsBasicTypes.h"


#include <set>

class PDFObject;
class HummusPDFParser;
class IByteWriter;

typedef set<ObjectIDType> ObjectIDTypeSet;

class HummusPDFParserTest : public ITestUnit
{
public:
	HummusPDFParserTest(void);
	virtual ~HummusPDFParserTest(void);

	virtual EPDFStatusCode Run();

private:

	EPDFStatusCode IterateObjectTypes(PDFObject* inObject,HummusPDFParser& inParser,IByteWriter* inOutput);

	int mTabLevel;
	ObjectIDTypeSet mIteratedObjectIDs;
};
