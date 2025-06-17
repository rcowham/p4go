
/*******************************************************************************

Copyright (c) 2024, Perforce Software, Inc.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

2.  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL PERFORCE SOFTWARE, INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

enum P4GoResultType
{
    STRING,
    BINARY,
    TRACK,
    DICT,
    ERROR,
    SPEC
};

struct P4GoResult
{
    P4GoResultType type;
    int taken;
    StrBuf* str;
    StrDict* dict;
    Error* err;
    P4GoSpecData* spec;
};

class P4GoResults : public VVarArray
{
  public:
    P4GoResults();
    ~P4GoResults();

    virtual int Compare( const void*, const void* ) const;
    virtual void Destroy( void* ) const;

    // Setting
    void AddOutput( Error* e );
    void AddOutput( StrPtr o , bool binary=false );
    void AddOutput( StrDict* d );
    void AddOutput( P4GoSpecData* d );
    void AddTrack( const char* t );
    void AddTrack( StrPtr t );
    void DeleteTrack();

    // Get errors/warnings as a formatted string
    void FmtErrors( StrBuf& buf );
    void FmtWarnings( StrBuf& buf );

    // Set API level for backwards compatibility
    void SetApiLevel( int l ) { apiLevel = l; }

    // Testing
    int ErrorCount();
    int WarningCount();

    // Clear previous results
    void Reset();

  private:
    void Fmt( const char* label, void* ary, StrBuf& buf );
    char* FmtMessage( Error* e );
    char* WrapMessage( Error* e );

    int infoCount;
    int warnCount;
    int errorCount;
    int trackCount;
    int dictCount;
    int specCount;
    int stringCount;

    int apiLevel;
};
