#include "TGAReader.h"

#include "AssetController.h"

TGAReader::TGAReader() {
	m_header = {};
	m_data = nullptr;
}

void TGAReader::ProcessAsset(Asset* _rawTGA, ImageInfo* _imageInfo) {
	memcpy(&m_header, _rawTGA->GetData(), sizeof(TGAHeader));

	
	M_ASSERT((m_header.DataTypeCode == 2), "Can only handle image type 2");
	M_ASSERT((m_header.BitsPerPixel == 0 || m_header.BitsPerPixel == 32), "Can only handle 32 or 24 pixels");
	M_ASSERT((m_header.ColourMapType == 0), "Can only handle colour map type 0");

	int dataOffset = sizeof(TGAHeader);
	dataOffset += m_header.IDLength;
	dataOffset += m_header.ColourMapType * m_header.ColourMapLength;

	_imageInfo->Width = 512;
	_imageInfo->Height = 512;
	_imageInfo->BitsPerPixel = 32;


	/*_imageInfo->Width = m_header.Width;
	_imageInfo->Height = m_header.Height;
	_imageInfo->BitsPerPixel = m_header.BitsPerPixel;*/
	_imageInfo->DataOffset = dataOffset;
}


Asset* TGAReader::LoadTGAFromFile(string _file, ImageInfo* _imageInfo) {
	m_data = AssetController::Instance().GetAsset(_file);
	ProcessAsset(m_data, _imageInfo);
	return m_data;
}