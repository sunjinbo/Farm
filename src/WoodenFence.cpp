/* ====================================================================
 * File: WoodenFence.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Fence.mbg>
#include "WoodenFence.h"
#include "Scene.h"
#include "BmpUtils.h"

// CONSTANTS
const TInt KWoodeFenceLength = 2;
const TInt KAutoRecoveryDelayTimeout = 5000000;
const TInt KAutoRecoveryTimeout = 0;
#if defined( __WINS__ )
_LIT( KFenceFileName, "Z:\\resource\\apps\\fence.mbm" );
#else
_LIT( KFenceFileName, "\\resource\\apps\\fence.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CWoodenFence::NewL
// ----------------------------------------------------------------------------
//
CWoodenFence* CWoodenFence::NewL( CScene& aScene,TPoint aStartCell)
    {
    CWoodenFence* self = new (ELeave) CWoodenFence(aScene,aStartCell);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CWoodenFence::~CWoodenFence
// ----------------------------------------------------------------------------
//
CWoodenFence::~CWoodenFence()
    {
    delete iUtils;
    if ( iPeriodic )
        {
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CWoodenFence::DoDraw
// ----------------------------------------------------------------------------
//
void CWoodenFence::DoDraw()
    {
    iScene.Gc().SetPenStyle( CGraphicsContext::ENullPen );
    iScene.Gc().SetBrushStyle( CGraphicsContext::ENullBrush );
    
    TRect theRect( Rect() );
    switch( iState )
        {
        case EVertical:
            iScene.Gc().BitBltMasked( 
                theRect.iTl,
                iUtils->Bitmap( EMbmFenceWooden ),
                TRect( TPoint( 0, 0 ), theRect.Size() ),
                iUtils->Bitmap( EMbmFenceWooden_mask ),
                ETrue
                );
            break;
        case EInclinedLeft:
            iScene.Gc().BitBltMasked( 
                theRect.iTl,
                iUtils->Bitmap( EMbmFenceWooden_left ),
                TRect( TPoint( 0, 0 ), theRect.Size() ),
                iUtils->Bitmap( EMbmFenceWooden_left_mask ),
                ETrue
                );
            break;
        case EInclinedRight:
            iScene.Gc().BitBltMasked( 
                theRect.iTl,
                iUtils->Bitmap( EMbmFenceWooden_right ),
                TRect( TPoint( 0, 0 ), theRect.Size() ),
                iUtils->Bitmap( EMbmFenceWooden_right_mask ),
                ETrue
                );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CWoodenFence::DoRecovery
// ----------------------------------------------------------------------------
//
void CWoodenFence::DoRecovery()
    {
    iState = EVertical;
    iPeriodic->Cancel();
    }

// ----------------------------------------------------------------------------
// CWoodenFence::PushLeft
// ----------------------------------------------------------------------------
//
void CWoodenFence::PushLeft()
    {
    switch( iState )
        {
        case EVertical:
            {
            iState = EInclinedLeft;
            Start();
            }
            break;
        case EInclinedLeft:
            break;
        case EInclinedRight:
            {
            iState = EVertical;
            iPeriodic->Cancel();
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CWoodenFence::PushRight
// ----------------------------------------------------------------------------
//
void CWoodenFence::PushRight()
    {
    switch( iState )
        {
        case EVertical:
            {
            iState = EInclinedRight;
            Start();
            }
            break;
        case EInclinedLeft:
            {
            iState = EVertical;
            iPeriodic->Cancel();
            }
            break;
        case EInclinedRight:
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CWoodenFence::ConstructL
// ----------------------------------------------------------------------------
//
void CWoodenFence::ConstructL()
    {
    CFence::ConstructL();
    
    iUtils = CBmpUtils::NewL( 
            KFenceFileName,
            EMbmFenceStone,
            EMbmFenceLastElement
            );
    
    iPeriodic = 
        CPeriodic::NewL( CActive::EPriorityStandard );
    }

// ----------------------------------------------------------------------------
// CWoodenFence::CWoodenFence
// ----------------------------------------------------------------------------
//
CWoodenFence::CWoodenFence(CScene& aScene,TPoint aStartCell)
    : CFence(aScene,aStartCell,KWoodeFenceLength )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CWoodenFence::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CWoodenFence::TimerCallback( TAny* aPtr )
    {
    CWoodenFence* self = static_cast<CWoodenFence*> ( aPtr );
    self->DoRecovery();
    return 0;
    }

// ----------------------------------------------------------------------------
// CWoodenFence::Start
// ----------------------------------------------------------------------------
//
void CWoodenFence::Start()
    {
    iPeriodic->Cancel();
    iPeriodic->Start(
                KAutoRecoveryDelayTimeout,
                KAutoRecoveryTimeout,
                TCallBack( TimerCallback, this )
                 );
    }

// End of File
