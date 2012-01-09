//
// SampleSource.h - MrsWatson
// Created by Nik Reiman on 1/2/12.
// Copyright (c) 2012 Teragon Audio. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include "Types.h"
#include "SampleBuffer.h"
#include "CharString.h"

#ifndef MrsWatson_SampleSource_h
#define MrsWatson_SampleSource_h

typedef enum {
  SAMPLE_SOURCE_TYPE_INVALID,
  SAMPLE_SOURCE_TYPE_PCM_FILE,
  SAMPLE_SOURCE_TYPE_PCM_STREAM,
  SAMPLE_SOURCE_TYPE_SILENCE,
  NUM_SAMPLE_SOURCES
} SampleSourceType;

typedef enum {
  SAMPLE_SOURCE_OPEN_NOT_OPENED,
  SAMPLE_SOURCE_OPEN_READ,
  SAMPLE_SOURCE_OPEN_WRITE,
  NUM_SAMPLE_SOURCE_OPEN_AS
} SampleSourceOpenAs;

typedef boolean (*OpenSampleSourceFunc)(void*, const SampleSourceOpenAs);
typedef boolean (*ReadSampleBlockFunc)(void*, SampleBuffer);
typedef boolean (*WriteSampleBlockFunc)(void*, const SampleBuffer);
typedef void (*FreeSampleSourceDataFunc)(void*);

typedef struct {
  SampleSourceType sampleSourceType;
  SampleSourceOpenAs openedAs;
  CharString sourceName;
  int numChannels;
  float sampleRate;

  OpenSampleSourceFunc openSampleSource;
  ReadSampleBlockFunc readSampleBlock;
  WriteSampleBlockFunc writeSampleBlock;
  FreeSampleSourceDataFunc freeSampleSourceData;

  void* extraData;
} SampleSourceMembers;

typedef SampleSourceMembers* SampleSource;

void printSupportedSourceTypes(void);
SampleSourceType guessSampleSourceType(const CharString sampleSourceTypeString);
SampleSource newSampleSource(SampleSourceType sampleSourceType, const CharString sampleSourceName);
void freeSampleSource(SampleSource sampleSource);

#endif
