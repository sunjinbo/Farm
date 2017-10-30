/* ====================================================================
 * File: Rollpacker.cpp
 * Created: 01/26/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <fbs.h>
#include <AknUtils.h>
#include <eikenv.h>
#include "Rollpacker.h"
#include "RollpackerObserver.h"

// CONSTANTS
const TInt KScorllDelayTimeout = 0;
const TInt KScorllUpdateTimeout = 1000000;
const TInt KTextItemListCranularity = 10;
const TInt KScrollUnavailableIndex = -1;
const TInt KScrollUnavailableValue = -1;
const TInt KScrollinitializeValue = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CRollpacker::NewL
// ----------------------------------------------------------------------------
//
CRollpacker* CRollpacker::NewL( CFbsBitGc& aGc, const TRect& aRect )
    {
    CRollpacker* self = new (ELeave) CRollpacker( aGc );
    CleanupStack::PushL (self );
    self->ConstructL (aRect);
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CRollpacker::~CRollpacker
// ----------------------------------------------------------------------------
//
CRollpacker::~CRollpacker()
    {
    iPeriodic->Cancel();
    delete iPeriodic;
    iTextArray.ResetAndDestroy();
    iTextArray.Close();
    }

// ----------------------------------------------------------------------------
// CRollpacker::AddTextItemL
// ----------------------------------------------------------------------------
//
void CRollpacker::AddTextL( const TDesC& aText )
    {
    AppendL( aText );
    // Start();
    }

// ----------------------------------------------------------------------------
// CRollpacker::Clear
// ----------------------------------------------------------------------------
//
void CRollpacker::Clear()
    {
    iTextArray.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CRollpacker::Start
// ----------------------------------------------------------------------------
//
void CRollpacker::Start()
    {
    InitializeScroll();
    iPeriodic->Cancel();
    iPeriodic->Start(
                KScorllDelayTimeout,
                KScorllUpdateTimeout,
                TCallBack( TimerCallback, this ) );
    }

// ----------------------------------------------------------------------------
// CRollpacker::DoDraw
// ----------------------------------------------------------------------------
//
void CRollpacker::DoDraw()
    {
    TRgb itemColor( KRgbBlack );
    iGc.SetPenStyle( CGraphicsContext::ESolidPen );
    iGc.SetPenColor( itemColor );
    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    const CFont* font 
        = AknLayoutUtils::FontFromId( ELatinBold17 );
     iGc.UseFont( font );

    HBufC* textItem( NULL );
    TInt height = Rect().Height() / KScrollLineNumber;
    TInt width = Rect().Width();
    TPoint topLeft( Rect().iTl );
    for ( TInt i = 0; i < KScrollLineNumber; ++i )
        {
        if ( iScrollCabinet[ i ] != KScrollUnavailableIndex )
            {
            TRect rect( topLeft, TSize( width, height ) );
            TInt baseline = 
                ( rect.Height() + font->HeightInPixels() ) / 2;
            textItem = iTextArray[ iScrollCabinet[ i ] ];
            iGc.DrawText( *textItem, rect, baseline, CGraphicsContext::ECenter, 0 );
            }
        topLeft.iY += height;
        }
    }

// ----------------------------------------------------------------------------
// CRollpacker::SetObserver
// ----------------------------------------------------------------------------
//
void CRollpacker::SetObserver( MRollpackerObserver* aObserver )
    {
    if ( aObserver && aObserver != iObserver )
        {
        iObserver = aObserver;
        }
    }

// ----------------------------------------------------------------------------
// CRollpacker::Draw
// ----------------------------------------------------------------------------
//
void CRollpacker::Draw(const TRect& /*aRect*/) const
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CRollpacker::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CRollpacker::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
        case TPointerEvent::EDrag:
            break;
        case TPointerEvent::EButton1Up:
            iObserver->FinishedL();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CRollpacker::CRollpacker
// ----------------------------------------------------------------------------
//
CRollpacker::CRollpacker( CFbsBitGc& aGc )
    : iGc( aGc ), iTextArray( KTextItemListCranularity )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CRollpacker::ConstructL
// ----------------------------------------------------------------------------
//
void CRollpacker::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);
    
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CRollpacker::Stop
// ----------------------------------------------------------------------------
//
void CRollpacker::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        }
    }

// ----------------------------------------------------------------------------
// CRollpacker::DoScroll
// ----------------------------------------------------------------------------
//
void CRollpacker::DoScroll()
    {
    if ( iHeadIndex == KScrollUnavailableIndex
        && iTailIndex == KScrollUnavailableIndex
        && iHeadValue == KScrollUnavailableValue )
        { 
        // It's the first step of scrolling text item.
        iHeadIndex = KScrollLineNumber - 1;
        iTailIndex = KScrollLineNumber - 1;
        iHeadValue = KScrollinitializeValue;
        }
    else
        { 
        // other scroll steps
        if ( --iScrollStep )
            {
            if ( --iCabinetStep )
                {
                iHeadIndex--;
                }
            else
                {
                iHeadValue++;
                }

            if ( KScrollLineNumber  >= iScrollStep )
                {
                iTailIndex--;
                }
            }
        else
            { // Running out of scroll steps, restart again.
            Start();
            }
        }
    UpdateCabinetArray();
    }

// ----------------------------------------------------------------------------
// CRollpacker::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CRollpacker::TimerCallback( TAny* aPtr )
    {
    CRollpacker* self = static_cast<CRollpacker*> ( aPtr );
    self->DoScroll();
    return 0;
    }

// ----------------------------------------------------------------------------
// CRollpacker::InitializeScroll
// ----------------------------------------------------------------------------
//
void CRollpacker::InitializeScroll()
    {
    iHeadIndex = KScrollUnavailableIndex;
    iTailIndex =  KScrollUnavailableIndex;
    iHeadValue = KScrollUnavailableValue;
    iScrollStep = KScrollLineNumber + iTextArray.Count();
    iCabinetStep = KScrollLineNumber;
    UpdateCabinetArray();
    }

// ----------------------------------------------------------------------------
// CRollpacker::UpdateCabinetArray
// ----------------------------------------------------------------------------
//
void CRollpacker::UpdateCabinetArray()
    {
    for ( TInt i = 0; i < KScrollLineNumber; ++i )
        {
        if ( ( i >= iHeadIndex ) && ( i <= iTailIndex ) )
            {
            iScrollCabinet[ i ] = iHeadValue + i - iHeadIndex;    
            }
        else
            {
            iScrollCabinet[ i ] = KScrollUnavailableIndex;    
            }
        }
    }

// ----------------------------------------------------------------------------
// CRollpacker::AppendL
// ----------------------------------------------------------------------------
//
void CRollpacker::AppendL( const TDesC& aText )
    {
    TPtrC ptr( aText );
    const TChar KLf( '\n' );
    const TInt pos = aText.Locate( KLf );

    HBufC* txt( NULL );
    if ( pos != KErrNotFound )
        {
        ptr.Set( aText.Ptr(), pos );
        txt = HBufC::NewL( ptr.Length() );
        TPtr txtPtr( txt->Des() );
        txtPtr.Copy( ptr );
        iTextArray.Append( txt );
        }
    else
        {
        if ( aText.Length() != 0 )
            {
            txt = HBufC::NewL( aText.Length() );
            TPtr txtPtr( txt->Des() );
            txtPtr.Copy( aText );
            iTextArray.Append( txt );
            }
        }

    if ( pos != KErrNotFound )
        {
        ptr.Set( &aText.Ptr()[ pos + 1 ], aText.Length() - pos - 1 );

        AppendL( ptr ); // Recursive call
        }
    }

// End of File
