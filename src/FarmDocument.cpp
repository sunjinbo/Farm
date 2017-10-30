/* ====================================================================
 * File: FarmDocument.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDS
#include "FarmAppUi.h"
#include "FarmDocument.h"

// CONSTANS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFarmFactory::NewL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CFarmDocument* CFarmDocument::NewL(CEikApplication& aApp)
    {
    CFarmDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::NewLC
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CFarmDocument* CFarmDocument::NewLC(CEikApplication& aApp)
    {
    CFarmDocument* self = new (ELeave) CFarmDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ConstructL
// ----------------------------------------------------------------------------
//
void CFarmDocument::ConstructL()
    {
    // no implementation required
    }    

// ----------------------------------------------------------------------------
// CFarmFactory::CFarmDocument
// ----------------------------------------------------------------------------
//
CFarmDocument::CFarmDocument(CEikApplication& aApp) 
    : CAknDocument(aApp) 
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::~CFarmDocument
// ----------------------------------------------------------------------------
//
CFarmDocument::~CFarmDocument()
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CreateAppUiL
// ----------------------------------------------------------------------------
//
CEikAppUi* CFarmDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CFarmAppUi;
    return appUi;
    }

// End of File
