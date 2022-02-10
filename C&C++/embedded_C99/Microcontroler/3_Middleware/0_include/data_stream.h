#ifndef _DATA_STREAM_H_
#define _DATA_STREAM_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef enum
{
  DATA_STREAM_STATE_IDLE                = 0,
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_PREPARE             = 1,    //                              Maximum 8 prepare state from 2 to 9 can be over-write
  //...
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_START_WRITTING      = 10,   //                              Maximum 39 start-writting state from 11 to 49 can be over-write
  //...
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_WRITTING            = 50,   //                              Maximum 39 writting state from 51 to 89 can be over-write
  //...
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_END_WRITTING        = 90,   //                              Maximum 39 end-writting state from 91 to 129 can be over-write
  //...
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_START_READDING      = 130,  //                              Maximum 39 start-reading state from 131 to 169 can be over-write
  //....
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_READING             = 170,  //                              Maximum 39 start-reading state from 131 to 169 can be over-write
  //...
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_END_READING         = 210,  //                              Maximum 39 start-reading state from 211 to 249 can be over-write
  //...
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  DATA_STREAM_STATE_ENDING              = 250,  //                              Maximum 5 error state from 251 to 255 can be over-write
  //...
} DATA_STREAM_STATE;
/*
  Example:
if (DATA_STREAM_STATE)
{
  switch (DATA_STREAM_STATE)
  {
    case DATA_STREAM_STATE_PREPARE:             break;
//    case DATA_STREAM_STATE_PREPARE + 1:         break;

    case DATA_STREAM_STATE_START_WRITTING:      break;
    case DATA_STREAM_STATE_WRITTING:            break;
    case DATA_STREAM_STATE_END_WRITTING:        break;

    case DATA_STREAM_STATE_START_READDING:      break;
    case DATA_STREAM_STATE_READING:             break;
    case DATA_STREAM_STATE_END_READING:         break;

    case DATA_STREAM_STATE_ENDING:              break;
  }
}
*/

typedef struct
{
  struct
  {
    unsigned char BitIndex;
    unsigned char Length;
    const unsigned char __gptr* Data;
  } Writer;
  struct
  {
    unsigned char BitIndex;
    unsigned char Length;
    unsigned char* Data;
  } Reader;
} DataStream_TypeDef;

#endif