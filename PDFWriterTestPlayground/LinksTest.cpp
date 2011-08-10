/*
   Source File : LinksTest.cpp


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
#include "LinksTest.h"
#include "HummusPDFWriter.h"
#include "PDFPage.h"
#include "PDFRectangle.h"
#include "PageContentContext.h"
#include "PDFFormXObject.h"
#include "TestsRunner.h"

#include <iostream>

LinksTest::LinksTest(void)
{
}

LinksTest::~LinksTest(void)
{
}

EPDFStatusCode LinksTest::Run()
{
	EPDFStatusCode status;
	HummusPDFWriter pdfWriter;

	do
	{
		status = pdfWriter.StartPDF(L"C:\\PDFLibTests\\LinksTest.PDF",ePDFVersion13,LogConfiguration(true,L"C:\\PDFLibTests\\LinksTest.log"));
		if(status != ePDFSuccess)
		{
			wcout<<"failed to start PDF\n";
			break;
		}	

		PDFPage* page = new PDFPage();
		page->SetMediaBox(PDFRectangle(0,0,595,842));

		PDFFormXObject* soundCloudLogo = pdfWriter.CreateFormXObjectFromJPGFile(L"c:\\PDFLibTests\\TestMaterials\\Images\\soundcloud_logo.jpg");


		PageContentContext* contentContext = pdfWriter.StartPageContentContext(page);
		if(NULL == contentContext)
		{
			status = ePDFFailure;
			wcout<<"failed to create content context for page\n";
			break;
		}

		PDFUsedFont* font = pdfWriter.GetFontForFile(L"C:\\PDFLibTests\\TestMaterials\\fonts\\arial.ttf");
		if(!font)
		{
			status = ePDFFailure;
			wcout<<"Failed to create font object for arial.ttf\n";
			break;
		}

		// Draw some text
		contentContext->BT();
		contentContext->k(0,0,0,1);
		contentContext->Tf(font,1);
		contentContext->Tm(11,0,0,11,90.024,709.54);
		EPDFStatusCode encodingStatus = contentContext->Tj(L"http://pdfhummus.com");
		if(encodingStatus != ePDFSuccess)
			wcout<<"Could not find some of the glyphs for this font (arial)";
		// continue even if failed...want to see how it looks like
		contentContext->ET();

		// Draw soundcloud loog
		contentContext->q();
		contentContext->cm(0.5,0,0,0.5,90.024,200);
		contentContext->Do(page->GetResourcesDictionary().AddFormXObjectMapping(soundCloudLogo->GetObjectID()));
		contentContext->Q();
		
		status = pdfWriter.EndPageContentContext(contentContext);
		if(status != ePDFSuccess)
		{
			wcout<<"failed to end page content context\n";
			break;
		}

		delete soundCloudLogo;


		// now let's attach some links.

		// first, the link for the test:
		pdfWriter.AttachURLLinktoCurrentPage(L"http://www.pdfhummus.com",PDFRectangle(87.75,694.56,198.76,720));

		// second, link for the logo.
		pdfWriter.AttachURLLinktoCurrentPage(L"http://www.soundcloud.com",PDFRectangle(90.024,200,367.524,375));

		status = pdfWriter.WritePageAndRelease(page);
		if(status != ePDFSuccess)
		{
			wcout<<"failed to write page\n";
			break;
		}

		status = pdfWriter.EndPDF();
		if(status != ePDFSuccess)
		{
			wcout<<"failed in end PDF\n";
			break;
		}	
	}while(false);

	return status;
}


ADD_CATEGORIZED_TEST(LinksTest,"PDF")