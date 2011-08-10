/*
   Source File : CharStringType2Flattener.cpp


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
#include "CharStringType2Flattener.h"
#include "CFFFileInput.h"
#include "IByteWriter.h"
#include "CharStringType2Interpreter.h"
#include "Trace.h"

#include <math.h>

CharStringType2Flattener::CharStringType2Flattener(void)
{
}

CharStringType2Flattener::~CharStringType2Flattener(void)
{
}

EPDFStatusCode CharStringType2Flattener::WriteFlattenedGlyphProgram(unsigned short inFontIndex, 
																 unsigned short inGlyphIndex, 
																 CFFFileInput* inCFFFileInput, 
																 IByteWriter* inWriter)
{
	CharStringType2Interpreter interpreter;
	EPDFStatusCode status = inCFFFileInput->PrepareForGlyphIntepretation(inFontIndex,inGlyphIndex);

	mWriter = inWriter;
	mHelper = inCFFFileInput;
	mOperandsToWrite.clear();
	mStemsCount = 0;

	do
	{
		if(status != ePDFSuccess)
		{
			TRACE_LOG("CharStringType2Flattener::Trace, Exception, cannot prepare for glyph interpretation");
			break;
		}
		
		CharString* charString = inCFFFileInput->GetGlyphCharString(inFontIndex,inGlyphIndex);
		if(!charString)
		{
			TRACE_LOG("CharStringType2Flattener::Trace, Exception, cannot find glyph index");
			break;
		}

		status = interpreter.Intepret(*charString,this);

		/*
			The alrogithm for writing a flattened charstring is as follows:
			1. enumerator, through interpretation, the charstring
			2. hit an operand? accumulate.
			3. hit an operator? if it's not callgsubr or callsubr just write the operand stack, and continue. 
								if it is callgsubr/callsubr pop the last element on the operand stack and write it, then continue.
			4. an exception would be when callgsubr/callsubr follow an operator, in which case their index operand is already written. just call drop.

		*/

	}while(false);
	return status;
}


EPDFStatusCode CharStringType2Flattener::ReadCharString(LongFilePositionType inCharStringStart,
						   LongFilePositionType inCharStringEnd,
						   Byte** outCharString)
{
	return mHelper->ReadCharString(inCharStringStart,inCharStringEnd,outCharString);
}

EPDFStatusCode CharStringType2Flattener::Type2InterpretNumber(const CharStringOperand& inOperand)
{
	mOperandsToWrite.push_back(inOperand);
	return ePDFSuccess;
}

EPDFStatusCode CharStringType2Flattener::Type2Hstem(const CharStringOperandList& inOperandList)
{
	mStemsCount+= (unsigned short)(inOperandList.size() / 2);

	return WriteRegularOperator(1);
}

EPDFStatusCode CharStringType2Flattener::WriteRegularOperator(unsigned short inOperatorCode)
{
	CharStringOperandList::iterator it = mOperandsToWrite.begin();
	EPDFStatusCode status = ePDFSuccess;

	for(; it != mOperandsToWrite.end() && ePDFSuccess == status;++it)
		status = WriteCharStringOperand(*it);
	if(status != ePDFFailure)
		status = WriteCharStringOperator(inOperatorCode);

	mOperandsToWrite.clear();

	return status;
}

EPDFStatusCode CharStringType2Flattener::WriteCharStringOperand(const CharStringOperand& inOperand)
{
	if(inOperand.IsInteger)
	{
		long value = inOperand.IntegerValue;

		if(-107 <= value && value <= 107)
		{
			return WriteByte((Byte)(value + 139));
		}
		else if(108 <= value && value <= 1131)
		{
			Byte byte0,byte1;

			value-=108;
			byte0 = ((value >> 8) & 0xff) + 247;
			byte1 = value & 0xff;

			if(WriteByte(byte0) != ePDFSuccess)
				return ePDFFailure;

			if(WriteByte(byte1) != ePDFSuccess)
				return ePDFFailure;
		}
		else if(-1131 <= value && value <= -108)
		{
			Byte byte0,byte1;

			value = -(value + 108);

			byte0 = ((value >> 8) & 0xff) + 251;
			byte1 = value & 0xff;

			if(WriteByte(byte0) != ePDFSuccess)
				return ePDFFailure;

			if(WriteByte(byte1) != ePDFSuccess)
				return ePDFFailure;
		}
		else if(-32768 <= value && value<= 32767)
		{
			Byte byte1,byte2;

			byte1 = (value >> 8) & 0xff;
			byte2 = value & 0xff;

			if(WriteByte(28) != ePDFSuccess)
				return ePDFFailure;

			if(WriteByte(byte1) != ePDFSuccess)
				return ePDFFailure;

			if(WriteByte(byte2) != ePDFSuccess)
				return ePDFFailure;
		}
		else
			return ePDFFailure;
	}
	else
	{
		double value = inOperand.RealValue;
		bool sign = inOperand.RealValue < 0;
		if(sign)
				value = -value;
		long integerPart = (long)floor(value);
		long realPart = (long)((value - floor(value))* 65536);
		if(sign)
			integerPart = -integerPart;

		if(WriteByte(Byte((integerPart>>8) & 0xff)) != ePDFSuccess)
			return ePDFFailure;
		if(WriteByte(Byte(integerPart & 0xff)) != ePDFSuccess)
			return ePDFFailure;

		if(WriteByte(Byte((realPart>>8) & 0xff)) != ePDFSuccess)
			return ePDFFailure;
		if(WriteByte(Byte(realPart & 0xff)) != ePDFSuccess)
			return ePDFFailure;

	}
	return ePDFSuccess;
}

EPDFStatusCode CharStringType2Flattener::WriteCharStringOperator(unsigned short inOperatorCode)
{
	if((inOperatorCode & 0xff00) == 0x0c00)
	{
		if(WriteByte(0xc0) != ePDFSuccess)
			return ePDFFailure;
	}
	return WriteByte(Byte(inOperatorCode & 0xff));
}

EPDFStatusCode CharStringType2Flattener::WriteByte(Byte inValue)
{
	return (mWriter->Write(&inValue,1) == 1 ? ePDFSuccess : ePDFFailure);
}

EPDFStatusCode CharStringType2Flattener::Type2Vstem(const CharStringOperandList& inOperandList)
{
	mStemsCount+= (unsigned short)(inOperandList.size() / 2);

	return WriteRegularOperator(3);
}

EPDFStatusCode CharStringType2Flattener::Type2Vmoveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(4);
}

EPDFStatusCode CharStringType2Flattener::Type2Rlineto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(5);
}

EPDFStatusCode CharStringType2Flattener::Type2Hlineto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(6);
}

EPDFStatusCode CharStringType2Flattener::Type2Vlineto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(7);
}

EPDFStatusCode CharStringType2Flattener::Type2RRCurveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(8);
}

EPDFStatusCode CharStringType2Flattener::Type2Return(const CharStringOperandList& inOperandList)
{
	// ignore returns
	return ePDFSuccess;
}

EPDFStatusCode CharStringType2Flattener::Type2Endchar(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(14);
}

EPDFStatusCode CharStringType2Flattener::Type2Hstemhm(const CharStringOperandList& inOperandList)
{
	mStemsCount+= (unsigned short)(inOperandList.size() / 2);

	return WriteRegularOperator(18);
}

EPDFStatusCode CharStringType2Flattener::Type2Hintmask(const CharStringOperandList& inOperandList,Byte* inProgramCounter)
{
	mStemsCount+= (unsigned short)(inOperandList.size() / 2);

	if(WriteRegularOperator(19) != ePDFSuccess)
		return ePDFFailure;

	return WriteStemMask(inProgramCounter);
}

EPDFStatusCode CharStringType2Flattener::WriteStemMask(Byte* inProgramCounter)
{
	unsigned short maskSize = mStemsCount/8 + (mStemsCount % 8 != 0 ? 1:0);

	return mWriter->Write(inProgramCounter,maskSize) != maskSize ? ePDFFailure : ePDFSuccess;
}

EPDFStatusCode CharStringType2Flattener::Type2Cntrmask(const CharStringOperandList& inOperandList,Byte* inProgramCounter)
{
	if(WriteRegularOperator(20) != ePDFSuccess)
		return ePDFFailure;

	return WriteStemMask(inProgramCounter);
}

EPDFStatusCode CharStringType2Flattener::Type2Rmoveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(21);
}

EPDFStatusCode CharStringType2Flattener::Type2Hmoveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(22);
}

EPDFStatusCode CharStringType2Flattener::Type2Vstemhm(const CharStringOperandList& inOperandList)
{
	mStemsCount+= (unsigned short)(inOperandList.size() / 2);

	return WriteRegularOperator(23);
}

EPDFStatusCode CharStringType2Flattener::Type2Rcurveline(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(24);
}

EPDFStatusCode CharStringType2Flattener::Type2Rlinecurve(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(25);
}

EPDFStatusCode CharStringType2Flattener::Type2Vvcurveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(26);
}

EPDFStatusCode CharStringType2Flattener::Type2Hvcurveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(31);
}

EPDFStatusCode CharStringType2Flattener::Type2Hhcurveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(27);
}

EPDFStatusCode CharStringType2Flattener::Type2Vhcurveto(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(30);
}

EPDFStatusCode CharStringType2Flattener::Type2Hflex(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c22);
}

EPDFStatusCode CharStringType2Flattener::Type2Hflex1(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c24);
}

EPDFStatusCode CharStringType2Flattener::Type2Flex(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c23);
}

EPDFStatusCode CharStringType2Flattener::Type2Flex1(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c25);
}

EPDFStatusCode CharStringType2Flattener::Type2And(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c03);
}

EPDFStatusCode CharStringType2Flattener::Type2Or(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c04);
}

EPDFStatusCode CharStringType2Flattener::Type2Not(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c05);
}

EPDFStatusCode CharStringType2Flattener::Type2Abs(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c09);
}

EPDFStatusCode CharStringType2Flattener::Type2Add(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c0a);
}

EPDFStatusCode CharStringType2Flattener::Type2Sub(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c0b);
}

EPDFStatusCode CharStringType2Flattener::Type2Div(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c0c);
}

EPDFStatusCode CharStringType2Flattener::Type2Neg(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c0e);
}

EPDFStatusCode CharStringType2Flattener::Type2Eq(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c0f);
}

EPDFStatusCode CharStringType2Flattener::Type2Drop(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c12);
}

EPDFStatusCode CharStringType2Flattener::Type2Put(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c14);
}

EPDFStatusCode CharStringType2Flattener::Type2Get(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c15);
}

EPDFStatusCode CharStringType2Flattener::Type2Ifelse(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c16);
}

EPDFStatusCode CharStringType2Flattener::Type2Random(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c17);
}

EPDFStatusCode CharStringType2Flattener::Type2Mul(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c18);
}

EPDFStatusCode CharStringType2Flattener::Type2Sqrt(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c1a);
}

EPDFStatusCode CharStringType2Flattener::Type2Dup(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c1b);
}

EPDFStatusCode CharStringType2Flattener::Type2Exch(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c1c);
}

EPDFStatusCode CharStringType2Flattener::Type2Index(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c1d);
}

EPDFStatusCode CharStringType2Flattener::Type2Roll(const CharStringOperandList& inOperandList)
{
	return WriteRegularOperator(0x0c1e);
}

CharString* CharStringType2Flattener::GetLocalSubr(long inSubrIndex)
{
	if(WriteSubrOperator(10) != ePDFSuccess)
		return NULL;

	return mHelper->GetLocalSubr(inSubrIndex);
}

EPDFStatusCode CharStringType2Flattener::WriteSubrOperator(unsigned short inOperatorCode)
{
	if(mOperandsToWrite.size() > 0)
	{
		EPDFStatusCode status = ePDFSuccess;
		mOperandsToWrite.pop_back(); // pop back parameter, which is the subr index

		// now continue writing all operands
		CharStringOperandList::iterator it = mOperandsToWrite.begin();

		for(; it != mOperandsToWrite.end() && ePDFSuccess == status;++it)
			status = WriteCharStringOperand(*it);

		mOperandsToWrite.clear();
		return status;
	}
	else // no current operands. either result of calculation or just multiple operators one of the other
		return WriteCharStringOperator(0x0c12); // write a "drop" command for the subr index
}


CharString* CharStringType2Flattener::GetGlobalSubr(long inSubrIndex)
{
	if(WriteSubrOperator(29) != ePDFSuccess)
		return NULL;

	return mHelper->GetGlobalSubr(inSubrIndex);
}

