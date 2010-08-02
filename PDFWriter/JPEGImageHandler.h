#pragma once

#include "JPEGImageInformation.h"

#include <map>
#include <string>
#include <utility>

using namespace std;

class ObjectsContext;
class PDFImageXObject;
class IDocumentContextExtender;
class PDFFormXObject;
class DocumentContext;

typedef map<wstring,JPEGImageInformation> WStringToJPEGImageInformationMap;
typedef std::pair<bool,JPEGImageInformation> BoolAndJPEGImageInformation;
typedef std::pair<double,double> DoubleAndDoublePair;

class JPEGImageHandler
{
public:
	JPEGImageHandler();
	~JPEGImageHandler(void);

	// use this for retrieving image information for JPEG (useful for deciphering JPG dimensions tags)
	BoolAndJPEGImageInformation RetrieveImageInformation(const wstring& inJPGFilePath);

	// DocumentContext::CreateImageXObjectFromJPGFile are equivelent
	PDFImageXObject* CreateImageXObjectFromJPGFile(const wstring& inJPGFilePath);
	
	// will return form XObject, which will include the xobject at it's size
	PDFFormXObject* CreateFormXObjectFromJPGFile(const wstring& inJPGFilePath);

	void SetOperationsContexts(DocumentContext* inDocumentContext,ObjectsContext* inObjectsContext);
	void SetDocumentContextExtender(IDocumentContextExtender* inExtender);

private:
	JPEGImageInformation mNullInformation;
	WStringToJPEGImageInformationMap mImagesInformationMap;
	ObjectsContext* mObjectsContext;
	DocumentContext* mDocumentContext;
	IDocumentContextExtender* mExtender;

	PDFImageXObject* CreateAndWriteImageXObjectFromJPGInformation(const wstring& inJPGFilePath, const JPEGImageInformation& inJPGImageInformation);
	PDFFormXObject* CreateImageFormXObjectFromImageXObject(PDFImageXObject* inImageXObject, const JPEGImageInformation& inJPGImageInformation);
	DoubleAndDoublePair GetImageDimensions(const JPEGImageInformation& inJPGImageInformation);

};