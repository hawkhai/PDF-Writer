/*
   Source File : TIFFImageTest.cpp


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
#include "TIFFImageTest.h"
#include "TestsRunner.h"
#include "HummusPDFWriter.h"
#include "PDFFormXObject.h"
#include "PDFPage.h"
#include "PageContentContext.h"
#include "BoxingBase.h"

#include <iostream>

using namespace std;

TIFFImageTest::TIFFImageTest(void)
{
}

TIFFImageTest::~TIFFImageTest(void)
{
}

EPDFStatusCode TIFFImageTest::Run()
{
	HummusPDFWriter pdfWriter;
	EPDFStatusCode status; 

	do
	{
		status = pdfWriter.StartPDF(L"C:\\PDFLibTests\\BasicTIFFImagesTest.PDF",ePDFVersion13,LogConfiguration(true,L"C:\\PDFLibTests\\TiffImageTestLog.txt"));
		if(status != ePDFSuccess)
		{
			wcout<<"failed to start PDF\n";
			break;
		}	

		for(int i=1;i<9 && status != ePDFFailure;++i)
			status = AddPageForTIFF(pdfWriter,(wstring(L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\CCITT_") + Int(i).ToWString() + L".TIF").c_str());
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\FLAG_T24.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\G4.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\G4S.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\G31D.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\G31DS.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\G32D.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\GMARBLES.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\MARBIBM.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\MARBLES.TIF");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\XING_T24.TIF");
		if(status != ePDFSuccess)
			break;

		// tiled image
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\cramps-tile.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\cramps.tif");
		if(status != ePDFSuccess)
			break;

		// Looks corrupted by the tool. on mine looks good
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\dscf0013.tif");
		if(status != ePDFSuccess)
			break;

		// Creates bad PDF by tool. on mine looks good
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\fax2d.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\g3test.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\jello.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\jim___ah.tif");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\jim___cg.tif");
		if(status != ePDFSuccess)
			break;
		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\jim___dg.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\jim___gg.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\oxford.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\quad-lzw.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\quad-tile.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\strike.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\ycbcr-cat.tif");
		if(status != ePDFSuccess)
			break;

		for(int i=2;i<9 && status != ePDFFailure;i=i*2)
			status = AddPageForTIFF(pdfWriter,(wstring(L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\flower-minisblack-") + Int(i).ToWString() + L".tif").c_str());
		if(status !=ePDFSuccess)
			break;

		for(int i=2;i<9 && status != ePDFFailure;i=i*2)
			status = AddPageForTIFF(pdfWriter,(wstring(L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\flower-palette-") + Int(i).ToWString() + L".tif").c_str());
		if(status !=ePDFSuccess)
			break;

		for(int i=2;i<9 && status != ePDFFailure;i=i*2)
			status = AddPageForTIFF(pdfWriter,(wstring(L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\flower-rgb-contig-") + Int(i).ToWString() + L".tif").c_str());
		if(status !=ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\flower-rgb-planar-8.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\flower-separated-contig-8.tif");
		if(status != ePDFSuccess)
			break;

		status = AddPageForTIFF(pdfWriter,L"C:\\PDFLibTests\\TestMaterials\\images\\tiff\\flower-separated-planar-8.tif");
		if(status != ePDFSuccess)
			break;

		status = pdfWriter.EndPDF();
		if(status != ePDFSuccess)
		{
			wcout<<"failed in end PDF\n";
			break;
		}
	}while(false);

	return status;	
}

EPDFStatusCode TIFFImageTest::AddPageForTIFF(HummusPDFWriter& inpdfWriter, const wchar_t* inTiffFilePath)
{
	EPDFStatusCode status = ePDFSuccess;

	do {
		PDFPage* page = new PDFPage();
		page->SetMediaBox(PDFRectangle(0,0,595,842));

		PageContentContext* pageContentContext = inpdfWriter.StartPageContentContext(page);
		if(NULL == pageContentContext)
		{
			status = ePDFFailure;
			wcout<<"failed to create content context for page, for file"<<inTiffFilePath<<"\n";
		}

		PDFFormXObject* imageFormXObject = inpdfWriter.CreateFormXObjectFromTIFFFile(inTiffFilePath);
		if(!imageFormXObject)
		{
			wcout<<"failed to create image form XObject from file, for file"<<inTiffFilePath<<"\n";
			status = ePDFFailure;
			break;
		}

		string imageXObjectName = page->GetResourcesDictionary().AddFormXObjectMapping(imageFormXObject->GetObjectID());

		// continue page drawing, place the image in 0,0 (playing...could avoid CM at all)
		pageContentContext->q();
		pageContentContext->cm(1,0,0,1,0,0);
		pageContentContext->Do(imageXObjectName);
		pageContentContext->Q();

		delete imageFormXObject;

		status = inpdfWriter.EndPageContentContext(pageContentContext);
		if(status != ePDFSuccess)
		{
			wcout<<"failed to end page content context, for file"<<inTiffFilePath<<"\n";
			break;
		}

		status = inpdfWriter.WritePageAndRelease(page);
		if(status != ePDFSuccess)
		{
			wcout<<"failed to write page, for file"<<inTiffFilePath<<"\n";
			break;
		}
	}while(false);

	return status;
}

ADD_CATEGORIZED_TEST(TIFFImageTest,"PDF Images")
