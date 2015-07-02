//
//  BmpReader.cpp
//  bmp
//
//  Created by Alexey Zabrodin on 30.06.15.
//  Copyright (c) 2015 Alexey Zabodin. All rights reserved.
//

#include "BmpReader.h"


BmpReader::BmpReader(FileReader* fileReader){
    _fileReader = fileReader;
    
//    BitMapFileHeader bitMapFileHeader;
    uint8_t* ptrBitMapFileHeader = (uint8_t*)&_bitMapFileHeader;
    int bitMapHeaderSize = sizeof(BitMapFileHeader);
    _fileReader->seek(0);
    for (int currentByte = 0; currentByte < bitMapHeaderSize; currentByte++) {
        ptrBitMapFileHeader[currentByte] = _fileReader->read();
    }
    
//    BitMapInfoHeader bitMapInfoFileHeader;
    uint8_t* ptrBitMapInfoFileHeader = (uint8_t*)&_bitMapInfoHeader;
    int bitMapInfoFileHeaderSize = sizeof(BitMapInfoHeader);
    _fileReader->seek(bitMapHeaderSize);
    for (int currentByte = 0; currentByte < bitMapInfoFileHeaderSize; currentByte++) {
        ptrBitMapInfoFileHeader[currentByte] = _fileReader->read();
    }

    
}


uint64_t BmpReader::height (void){
    return _bitMapInfoHeader.biHeight;
}

uint64_t BmpReader::width  (void){
    return _bitMapInfoHeader.biWidth;
}

uint8_t BmpReader::pixel565 (int xPosition, int yPosition){
    _fileReader->seek(_bitMapFileHeader.bfOffBits + _bitMapInfoHeader.biWidth * yPosition + xPosition);
    return _fileReader->read();
}