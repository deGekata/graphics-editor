#include <stdio.h>
#include <Windows.h>
#include <algorithm>
#include <memory>

// Save the bitmap to a bmp file  
void SaveBitmapToFile( BYTE* pBitmapBits,  
                       LONG lWidth,  
                       LONG lHeight,  
                       WORD wBitsPerPixel, 
                       const unsigned long& padding_size,
                       LPCTSTR lpszFileName );
 
BYTE* LoadBMP ( int* width, int* height, unsigned long* size, LPCTSTR bmpfile );
 
std::unique_ptr<BYTE[]> CreateNewBuffer( unsigned long& padding,
                                         BYTE* pmatrix, 
                                         const int& width,
                                         const int& height );
 
void bmp_dump_tracer(BYTE* data, int width, int height);

void bmp_dump_video();