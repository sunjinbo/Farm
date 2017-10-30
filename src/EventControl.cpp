/* ====================================================================
 * File: EventControl.cpp
 * Created: 01/18/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <eikenv.h>
#include <coeaui.h>
#include "EventControlObserver.h"
#include "EventControl.h"

// CONSTANTS

// ============================ MEMBER FUNCTIONS ==============================

// ----------------------------------------------------------------------------
// CEventControl::NewL
// 2-phased constructor
// (static, may leave)
// ----------------------------------------------------------------------------
//
CEventControl* CEventControl::NewL(  MEventControlObserver& aObserver )
    {
    CEventControl* self = new ( ELeave ) CEventControl( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CEventControl::ConstructL
// 2nd phase constructor
// (may leave)
// ----------------------------------------------------------------------------
//
void CEventControl::ConstructL()
    {
    CreateWindowL();

    iAppUi->AddToStackL( this, 
                         ECoeStackPriorityFep, 
                         ECoeStackFlagRefusesFocus | ECoeStackFlagSharable 
                       );
    }

// ----------------------------------------------------------------------------
// CEventControl::CEventControl
// C++ constructor
// ----------------------------------------------------------------------------
//
CEventControl::CEventControl( MEventControlObserver& aObserver  )
    : iObserver( aObserver ), iAppUi( CEikonEnv::Static()->AppUi() )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CEventControl::~CEventControl
// C++ destructor
// ----------------------------------------------------------------------------
//
CEventControl::~CEventControl()
    {    
    if ( iAppUi )
        {
        iAppUi->RemoveFromStack( this );
        } // iAppUi
    }

// ----------------------------------------------------------------------------
// CEventControl::HandlePointerEventL
// Handles pointer events
// ----------------------------------------------------------------------------
//
void CEventControl::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            iStart = aPointerEvent.iPosition;
            break;
        case TPointerEvent::EDrag:
            break;
        case TPointerEvent::EButton1Up:
            iObserver.EventControlEvent( iStart, aPointerEvent.iPosition );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CEventControl::OfferKeyEventL
// Key event handling
// (may leave)
// ----------------------------------------------------------------------------
//
TKeyResponse CEventControl::OfferKeyEventL( const TKeyEvent& /*aKeyEvent*/, 
                                            TEventCode /*aType*/ 
                                          ) 
    {
    TKeyResponse r( EKeyWasNotConsumed );
    return r;
    }

// ----------------------------------------------------------------------------
// CEventControl::ComponentControl 
// From CCoeControl
// ----------------------------------------------------------------------------
//
CCoeControl* CEventControl::ComponentControl(TInt /* aIndex */) const
    {
    return NULL;
    }

// ----------------------------------------------------------------------------
// CEventControl::CountComponentControls
// From CCoeControl
// ----------------------------------------------------------------------------
//
TInt CEventControl::CountComponentControls() const
    {
    return 0; // return nbr of controls inside this container
    }

// ----------------------------------------------------------------------------
// CEventControl::Draw
// From CCoeControl
// ----------------------------------------------------------------------------
//
void CEventControl::Draw(const TRect& /* aRect */ ) const
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CEventControl::PrepareForFocusLossL
// From CCoeControl
// (may leave)
// ----------------------------------------------------------------------------
//
void CEventControl::PrepareForFocusLossL()
    {
    CCoeControl::PrepareForFocusLossL();
    }

// End of File
