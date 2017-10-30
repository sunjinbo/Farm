/* ====================================================================
 * File: MenuButton.cpp
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <fbs.h>
#include <e32math.h>
#include <MenuButton.mbg>
#include "MenuButton.h"
#include "ButtonObserver.h"
#include "BmpUtils.h"

// CONSTANTS
const TInt KMaxRockTimes = 16;
const TInt KRockDelayTimeout = 0;
const TInt KRockIntervalTimeout = 50000;

#if defined( __WINS__ )
_LIT( KMenuButtonFileName, "Z:\\resource\\apps\\menubutton.mbm" );
#else
_LIT( KMenuButtonFileName, "\\resource\\apps\\menubutton.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CEventControl::NewL
// ----------------------------------------------------------------------------
//
CMenuButton* CMenuButton::NewL(
    MButtonObserver& aObserver,
    CFbsBitGc& aGc, 
    const TRect& aRect )
    {
    CMenuButton* self = new (ELeave) CMenuButton(aObserver,aGc);
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CMenuButton::~CMenuButton
// ----------------------------------------------------------------------------
//
CMenuButton::~CMenuButton()
    {
    if ( iEffects )
        {
        iEffects->Cancel();
        delete iEffects;
        }
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CMenuButton::DoDraw
// ----------------------------------------------------------------------------
//
void CMenuButton::DoDraw()
    {
    iGc.SetPenStyle( CGraphicsContext::ENullPen );
    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc.BitBltMasked( 
                iRect.iTl,
                iUtils->Bitmap( EMbmMenubuttonBtn ),
                TRect( TPoint( 0, 0 ), iRect.Size() ),
                iUtils->Bitmap( EMbmMenubuttonBtn_mask ),
                ETrue
                );
    }

// ----------------------------------------------------------------------------
// CMenuButton::DoDraw
// ----------------------------------------------------------------------------
//
void CMenuButton::DoEffects()
    {
    --iRockTimes;
    if ( iRockTimes <= 0 )
        {
        TRAP_IGNORE( iObserver.HandleClickedL() );
        }
    else
        {
        Rock();
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::Draw
// ----------------------------------------------------------------------------
//
void CMenuButton::Draw()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CMenuButton::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CMenuButton::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Up:
            Start();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::ConstructL
// ----------------------------------------------------------------------------
//
void CMenuButton::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iRect = aRect;

    iUtils = CBmpUtils::NewL( 
            KMenuButtonFileName,
            EMbmMenubuttonBtn,
            EMbmMenubuttonLastElement
            );

    // For effects
    iEffects = CPeriodic::NewL( CActive::EPriorityStandard );
    iEffects->Cancel();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CMenuButton::CMenuButton
// ----------------------------------------------------------------------------
//
CMenuButton::CMenuButton(MButtonObserver& aObserver,CFbsBitGc& aGc)
    : iObserver( aObserver ), iGc( aGc ), iOrientation( ECentre )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CMenuButton::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CMenuButton::TimerCallback( TAny* aPtr )
    {
    CMenuButton* self = static_cast<CMenuButton*> ( aPtr );
    self->DoEffects();
    return 0;
    }

// ----------------------------------------------------------------------------
// CMenuButton::Start
// ----------------------------------------------------------------------------
//
void CMenuButton::Start()
    {
    if ( iEffects && !iEffects->IsActive() )
        {
        iRockTimes = KMaxRockTimes;
        iEffects->Start(
                    KRockDelayTimeout,
                    KRockIntervalTimeout,
                    TCallBack( TimerCallback, this )
                );
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::Rand
// ----------------------------------------------------------------------------
//
TInt CMenuButton::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CMenuButton::Rock
// ----------------------------------------------------------------------------
//
void CMenuButton::Rock()
    {
    switch ( iOrientation )
        {
        case ENorth:
            iRect.Move( 0, -2 );
            iOrientation = ECentre;
            break;
        case ESouth:
            iRect.Move( 0, 2 );
            iOrientation = ECentre;
            break;
        case EWest:
            iRect.Move( -2, 0 );
            iOrientation = ECentre;
            break;
        case EEast:
            iRect.Move( 2, 0 );
             iOrientation = ECentre;
            break;
        case ENortheast:
            iRect.Move( 2, -2 );
            iOrientation = ECentre;
            break;
        case ENorthwest:
            iRect.Move( -2, -2);
            iOrientation = ECentre;
            break;
        case ESoutheast:
            iRect.Move( 2, 2 );
            iOrientation = ECentre;
            break;
        case ESouthwest:
            iRect.Move( -2, 2 );
            iOrientation = ECentre;
            break;
        case ECentre:
            iRect = Rect();
            iOrientation = (TOrientation)Rand(ELastElement);
            break;
        default:
            break;
        }
    }

// End of File
