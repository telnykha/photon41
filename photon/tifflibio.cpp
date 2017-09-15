//---------------------------------------------------------------------------

#pragma hdrstop
#include "tifflibio.h"
#include "ExportRaster.h"

//---------------------------------------------------------------------------

void __fastcall TTiffDecoder::Init()
{
    tif = TIFFOpen(FFileName.c_str(), "r");
    if ( tif == NULL )
        throw Exception("Cannot open file");
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &FNumScanLines);
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &FWidth);
    TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &planar);
    TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &nsamples);
    FBufferSize = TIFFScanlineSize(tif);
    FScanBuffer = new char[FBufferSize];

}

void __fastcall TTiffDecoder::ReadScanLine( int ScanLine )
{
    if( planar != PLANARCONFIG_CONTIG || nsamples != 3 )
        throw Exception( "This tiff type is not supported" );

    if ( TIFFReadScanline(tif, FScanBuffer, ScanLine)== -1 )
        throw Exception( "Reading file error" );

      rgb_to_bgr( FScanBuffer, FWidth );
//    for ( int i = 0, j = 0; j < FBufferSize; i += 4, j += 3 )
//    {
//            *( FScanBuffer + j ) = *( buf + i + 3 );
//            *( FScanBuffer + j + 1 ) = *( buf + i + 2 );
//            *( FScanBuffer + j + 2 ) = *( buf + i + 1 );
//        }
//     }
//     else if ( planar == PLANARCONFIG_SEPARATE && nsamples == 4 );
}

void __fastcall TTiffDecoder::Close()
{
	TIFFClose(tif);
}
