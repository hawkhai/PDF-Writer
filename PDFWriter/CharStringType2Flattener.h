/*
   Source File : CharStringType2Flattener.h


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
#include "IType2InterpreterImplementation.h"

class CFFFileInput;
class IByteWriter;

class CharStringType2Flattener : public IType2InterpreterImplementation
{
public:
	CharStringType2Flattener(void);
	~CharStringType2Flattener(void);

	// will write a font program to another stream, flattening the references to subrs and gsubrs, so that
	// the charstring becomes independent (with possible references to other charachters through seac-like endchar)
	EPDFStatusCode WriteFlattenedGlyphProgram(unsigned short inFontIndex, unsigned short inGlyphIndex, CFFFileInput* inCFFFileInput, IByteWriter* inWriter);

	// IType2InterpreterImplementation implementation
	virtual EPDFStatusCode ReadCharString(LongFilePositionType inCharStringStart,
							   LongFilePositionType inCharStringEnd,
							   Byte** outCharString);	
	virtual EPDFStatusCode Type2InterpretNumber(const CharStringOperand& inOperand);
	virtual EPDFStatusCode Type2Hstem(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Vstem(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Vmoveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Rlineto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hlineto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Vlineto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2RRCurveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Return(const CharStringOperandList& inOperandList) ;
	virtual EPDFStatusCode Type2Endchar(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hstemhm(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hintmask(const CharStringOperandList& inOperandList,Byte* inProgramCounter);
	virtual EPDFStatusCode Type2Cntrmask(const CharStringOperandList& inOperandList,Byte* inProgramCounter);
	virtual EPDFStatusCode Type2Rmoveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hmoveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Vstemhm(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Rcurveline(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Rlinecurve(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Vvcurveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hvcurveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hhcurveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Vhcurveto(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hflex(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Hflex1(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Flex(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Flex1(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2And(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Or(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Not(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Abs(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Add(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Sub(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Div(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Neg(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Eq(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Drop(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Put(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Get(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Ifelse(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Random(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Mul(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Sqrt(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Dup(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Exch(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Index(const CharStringOperandList& inOperandList);
	virtual EPDFStatusCode Type2Roll(const CharStringOperandList& inOperandList);
	virtual CharString* GetLocalSubr(long inSubrIndex);
	virtual CharString* GetGlobalSubr(long inSubrIndex);

private:
	IByteWriter* mWriter;
	CFFFileInput* mHelper;
	unsigned short mStemsCount;
	CharStringOperandList mOperandsToWrite;

	EPDFStatusCode WriteRegularOperator(unsigned short inOperatorCode);
	EPDFStatusCode WriteStemMask(Byte* inProgramCounter);
	EPDFStatusCode WriteCharStringOperand(const CharStringOperand& inOperand);
	EPDFStatusCode WriteCharStringOperator(unsigned short inOperatorCode);
	EPDFStatusCode WriteByte(Byte inValue);
	EPDFStatusCode WriteSubrOperator(unsigned short inOperatorCode);

};
