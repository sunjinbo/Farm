/* ====================================================================
 * File: Stopwatch.cpp
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <StringLoader.h>
#include <fbs.h>
#include <eikenv.h>
#include <Farm.rsg>
#include <Stopwatch.mbg>
#include "Stopwatch.h"
#include "StopwatchObserver.h"
#include "BmpUtils.h"

// CONSTANTS
const TInt KMaxBufferLen = 25;
const TInt KStopwatchTimeout = 1000000; // 1 second

#if defined( __WINS__ )
_LIT( KStopwatchFileName, "Z:\\resource\\apps\\stopwatch.mbm" );
#else
_LIT( KStopwatchFileName, "\\resource\\apps\\stopwatch.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CStopwatch::NewL
// ----------------------------------------------------------------------------
//
CStopwatch* CStopwatch::NewL(
        MStopwatchObserver& aObserver,
        CFbsBitGc& aGc, 
        const TRect& aRect )
    {
    CStopwatch* self = new (ELeave) CStopwatch(aObserver,aGc);
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CStopwatch::~CStopwatch
// ----------------------------------------------------------------------------
//
CStopwatch::~CStopwatch()
    {
    Cancel();
    delete iLevelText;
    delete iTimeoutText;
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CStopwatch::SetLevel
// ----------------------------------------------------------------------------
//
void CStopwatch::SetLevel( TInt aLevel )
    {
    if ( !IsActive() )
        {
        iLevel = aLevel;
        }
    }

// ----------------------------------------------------------------------------
// CStopwatch::SetTimeout
// ----------------------------------------------------------------------------
//
void CStopwatch::SetTimeout( TInt aTimeout )
    {
    if ( !IsActive() )
        {
        iTimeout = aTimeout;
        }
    }

// ----------------------------------------------------------------------------
// CStopwatch::Start
// ----------------------------------------------------------------------------
//
void CStopwatch::Start()
    {
    if ( !IsActive() )
        {
        CTimer::After( KStopwatchTimeout );
        }
    }

// ----------------------------------------------------------------------------
// CStopwatch::Stop
// ----------------------------------------------------------------------------
//
void CStopwatch::Stop()
    {
    if ( IsActive() )
        {
        DoCancel();
        }
    }

// ----------------------------------------------------------------------------
// CStopwatch::Timeout
// ----------------------------------------------------------------------------
//
TInt CStopwatch::Timeout() const
    {
    return iTimeout;
    }

// ----------------------------------------------------------------------------
// CStopwatch::DoDraw
// ----------------------------------------------------------------------------
//
void CStopwatch::DoDraw()
    {
    iGc.SetPenStyle( CGraphicsContext::ENullPen );
    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc.BitBltMasked( 
            iRect.iTl,
            iUtils->Bitmap( EMbmStopwatchStopwatch ),
            TRect( TPoint( 0, 0 ), iRect.Size() ),
            iUtils->Bitmap( EMbmStopwatchStopwatch_mask ),
            ETrue
            );

    iGc.SetPenColor( KRgbBlack );
    iGc.SetPenStyle( CGraphicsContext::ESolidPen );
    iGc.UseFont( iEikEnv->AnnotationFont() );
    
    TRect theRect;
    // Draws level
    theRect.iTl = iRect.iTl;
    theRect.SetSize( TSize( iRect.Width(), iRect.Height() / 2 ) );
    theRect.Shrink( 4, 0 );
    
    TBuf<KMaxBufferLen> levelBuffer;
    levelBuffer.Append( *iLevelText );
    levelBuffer.AppendNum( iLevel );
    iGc.DrawText( levelBuffer, theRect, 30, CGraphicsContext::ELeft, 0 );

    // Draws timeout
    theRect.iTl.iX = iRect.iTl.iX;
    theRect.iTl.iY = iRect.iTl.iY + iRect.Height() / 2;
    theRect.SetSize( TSize( iRect.Width(), iRect.Height() / 2 ) );
    theRect.Shrink( 4, 0 );

    TBuf<KMaxBufferLen> timeoutBuffer;
    timeoutBuffer.Append( *iTimeoutText );
    timeoutBuffer.AppendNum( iTimeout );
    iGc.DrawText( timeoutBuffer, theRect, 30, CGraphicsContext::ELeft, 0 );
    }

// ----------------------------------------------------------------------------
// CStopwatch::ConstructL
// ----------------------------------------------------------------------------
//
void CStopwatch::ConstructL(const TRect& aRect)
    {
    CTimer::ConstructL();
    iRect = aRect;
    iLevelText = StringLoader::LoadL( R_FARM_STOPWATCH_LEVEL );
    iTimeoutText = StringLoader::LoadL( R_FARM_STOPWATCH_TIMEOUT );

    iUtils = CBmpUtils::NewL( 
            KStopwatchFileName,
            EMbmStopwatchStopwatch,
            EMbmStopwatchLastElement
            );
    }

// ----------------------------------------------------------------------------
// CStopwatch::CStopwatch
// ----------------------------------------------------------------------------
//
CStopwatch::CStopwatch(MStopwatchObserver& aObserver,CFbsBitGc& aGc)
    : CTimer( EPriorityUserInput ),
    iObserver( aObserver ),
    iEikEnv( CEikonEnv::Static() ), 
    iGc( aGc )
    {
    CActiveScheduler::Add( this );
    }

// ----------------------------------------------------------------------------
// CStopwatch::RunL
// ----------------------------------------------------------------------------
//
void CStopwatch::RunL()
    {
    if ( iStatus == KErrNone )
        {
        if ( iTimeout > 0 )
            {
             --iTimeout;
            CTimer::After( KStopwatchTimeout );
            }
        else
            {
            DoCancel();
            iObserver.ExpiredL();
            }
        }
    }

// ----------------------------------------------------------------------------
// CStopwatch::DoCancel
// ----------------------------------------------------------------------------
//
void CStopwatch::DoCancel()
    {
    CTimer::DoCancel(); 
    }

// End of File
