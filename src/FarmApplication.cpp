/* ====================================================================
 * File: FarmApplication.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDS
#include "FarmDocument.h"
#include "FarmApplication.h"

// CONSTANS
// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidFarmApp = {0xAFF05676};

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFarmApplication::CreateDocumentL
// Create an Farm document, and return a pointer to it
// ----------------------------------------------------------------------------
//
CApaDocument* CFarmApplication::CreateDocumentL()
    {  
    CApaDocument* document = CFarmDocument::NewL(*this);
    return document;
    }

// ----------------------------------------------------------------------------
// CFarmApplication::AppDllUid
// ----------------------------------------------------------------------------
//
TUid CFarmApplication::AppDllUid() const
    {
    // Return the UID for the Farm application
    return KUidFarmApp;
    }

