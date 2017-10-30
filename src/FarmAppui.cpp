/* ====================================================================
 * File: FarmAppUi.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDES
#include <avkon.hrh>
#include <aknnotewrappers.h> 
#include "Farm.pan"
#include "FarmAppUi.h"
#include "FarmAppView.h"
#include "Farm.hrh"

// CONSTANS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFarmFactory::NewL
// ConstructL is called by the application framework
// ----------------------------------------------------------------------------
//
void CFarmAppUi::ConstructL()
    {
    BaseConstructL();

    Cba()->MakeVisible( EFalse ); 
    StatusPane()->MakeVisible( EFalse );

    SetOrientationL( EAppUiOrientationPortrait );

    iAppView = CFarmAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CFarmAppUi
// ----------------------------------------------------------------------------
//
CFarmAppUi::CFarmAppUi()                              
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::~CFarmAppUi
// ----------------------------------------------------------------------------
//
CFarmAppUi::~CFarmAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CFarmFactory::~CFarmAppUi
// handle any menu commands
// ----------------------------------------------------------------------------
//
void CFarmAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        default:
            Panic(EFarmBasicUi);
            break;
        }
    }

// End of File
