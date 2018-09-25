/// =====================================================================================
///
///        @file:      be_xlink.h
///        @brief:     
///        @created:   11/13/2017 04:22:44 PM
///        @author:    csoka, attila.csok@movidius.com
///        @copyright: All code copyright Movidius Ltd 2013, all rights reserved.
///                  For License Warranty see: common/license.txt
/// =====================================================================================
///

/// System Includes
/// -------------------------------------------------------------------------------------

#include "XLink.h"
#include <pthread.h>
#include <string.h>
#include <assert.h>
/// Application Includes
/// -------------------------------------------------------------------------------------
#define MAX_DIR_NAME_SIZE 32
/// Source Specific #defines and types (typedef,enum,struct)
/// -------------------------------------------------------------------------------------

/// Global Data (Only if absolutely necessary)
/// -------------------------------------------------------------------------------------

/// Static Local Data
/// -------------------------------------------------------------------------------------

/// Static Function Prototypes
/// -------------------------------------------------------------------------------------

/// Functions Implementation
/// -------------------------------------------------------------------------------------

class Rec2File{
public:
    Rec2File(int streamId, const char *dirname)
    {
        uint32_t strLenght = strlen(dirname) + 1;
        assert(strLenght <= MAX_DIR_NAME_SIZE);

        this->streamId   = streamId;
        memcpy(this->dirname, dirname, strLenght);
    }

    void Start();
    void Stop();

    static void *xLinkRead(void *This);
    void *xlinkReadThread();

private:
    pthread_t thread;
    char dirname[MAX_DIR_NAME_SIZE];
    int streamId;


};
