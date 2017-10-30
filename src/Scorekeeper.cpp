/* ====================================================================
 * File: Scorekeeper.cpp
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <fbs.h>
#include <AknUtils.h>
#include <eikenv.h>
#include <Scorekeeper.mbg>
#include "Scorekeeper.h"
#include "FarmConstants.h"
#include "BmpUtils.h"

// CONSTANTS
const TInt KMaxBufferLen = 2;
const TInt KNormalFontHeightInTwips = 85;
const TInt KMaxFontHeightInTwips = 120;
const TInt KEffectsDelayTimeout = 0;
const TInt KEffectsIntervalTimeout = 50000;

#if defined( __WINS__ )
_LIT( KScorekeeperFileName, "Z:\\resource\\apps\\scorekeeper.mbm" );
#else
_LIT( KScorekeeperFileName, "\\resource\\apps\\scorekeeper.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScorekeeper::NewL
// ----------------------------------------------------------------------------
//
CScorekeeper* CScorekeeper::NewL(
        CFbsBitGc& aGc, 
        const TRect& aRect,
        const TSize& aCellSize )
    {
    CScorekeeper* self = new (ELeave) CScorekeeper(aGc);
    CleanupStack::PushL(self);
    self->ConstructL(aRect, aCellSize);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::~CScorekeeper
// ----------------------------------------------------------------------------
//
CScorekeeper::~CScorekeeper()
    {
    if ( iEffects )
        {
        iEffects->Cancel();
        delete iEffects;
        }
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::DoDraw
// ----------------------------------------------------------------------------
//
void CScorekeeper::DoDraw()
    {
    DrawBackground();
    DrawLivestockIcon();
    DrawScorekeeper();
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Clear
// ----------------------------------------------------------------------------
//
void CScorekeeper::Clear()
    {
    for ( TInt i = 0; i < ELivestockLastElement; i++ )
        {
        iValues[ i ] = 0;
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::SetValue
// ----------------------------------------------------------------------------
//
void CScorekeeper::SetValue( TLivestockType aType, TInt aValue )
    {
    iValues[ aType ] = aValue;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Append
// ----------------------------------------------------------------------------
//
void CScorekeeper::Append( TLivestockType aType )
    {
    iValues[ aType ] += 1;
    Start();
    }

// ----------------------------------------------------------------------------
// CScorekeeper::DoEffects
// ----------------------------------------------------------------------------
//
void CScorekeeper::DoEffects()
    { // Do nothing.
    }

// ----------------------------------------------------------------------------
// CScorekeeper::ConstructL
// ----------------------------------------------------------------------------
//
void CScorekeeper::ConstructL(const TRect& aRect, const TSize& aCellSize)
    {
    iRect = aRect;
    iCellSize = aCellSize;
    iHorizMargin = iRect.Width() 
        - iRect.Width() / iCellSize.iWidth * iCellSize.iWidth;
    iVerticalMargin = iRect.Height() 
        - iRect.Height() / iCellSize.iHeight * iCellSize.iHeight;
        
    // For effects
    iEffects = CPeriodic::NewL( CActive::EPriorityStandard );
    iEffects->Cancel();

    iUtils = CBmpUtils::NewL( 
            KScorekeeperFileName,
            EMbmScorekeeperScorekeeper,
            EMbmScorekeeperLastElement
            );
    }

// ----------------------------------------------------------------------------
// CScorekeeper::CScorekeeper
// ----------------------------------------------------------------------------
//
CScorekeeper::CScorekeeper(CFbsBitGc& aGc)
    : iEikEnv( CEikonEnv::Static() ), iGc( aGc )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CScorekeeper::DrawBackground
// ----------------------------------------------------------------------------
//
void CScorekeeper::DrawBackground()
    {
    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc.BitBltMasked( 
                iRect.iTl,
                iUtils->Bitmap( EMbmScorekeeperScorekeeper ),
                TRect( TPoint( 0, 0 ), iRect.Size() ),
                iUtils->Bitmap( EMbmScorekeeperScorekeeper_mask ),
                ETrue
                );
    }

// ----------------------------------------------------------------------------
// CScorekeeper::DrawLivestockIcon
// ----------------------------------------------------------------------------
//
void CScorekeeper::DrawLivestockIcon()
    {
    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );

    for ( TInt i = 0; i < ELivestockLastElement; i++ )
        {
        TRect theRect;
        theRect.iTl.iX = iRect.iTl.iX 
            + KWickiupHoriz[i] * iCellSize.iWidth 
            + iHorizMargin / 2;
        theRect.iTl.iY = iRect.iTl.iY + iVerticalMargin / 2;
        theRect.SetSize( iCellSize );
        iGc.BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmScorekeeperSheep + i * 2 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmScorekeeperSheep_mask + i * 2 ),
                    ETrue
                    );
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::DrawScorekeeper
// ----------------------------------------------------------------------------
//
void CScorekeeper::DrawScorekeeper()
    {
    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc.SetPenColor( KRgbBlack );
    iGc.SetPenStyle( CGraphicsContext::ESolidPen );

    const CFont* font 
        = AknLayoutUtils::FontFromId( EAknLogicalFontSecondaryFont );

    iGc.UseFont( font );

    for ( TInt i = 0; i < ELivestockLastElement; i++ )
        {
        TBuf<KMaxBufferLen> buffer;
        TRect theRect;
        theRect.iTl.iX = iRect.iTl.iX 
            + KWickiupHoriz[i] * iCellSize.iWidth 
            + iHorizMargin / 2;
        theRect.iTl.iY = iRect.iTl.iY 
            + iCellSize.iHeight + iVerticalMargin / 2;
        theRect.SetSize( iCellSize );
        buffer.AppendNum( iValues[i] );
        iGc.DrawText( buffer, theRect, 20, CGraphicsContext::ECenter, 0 );
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::TimerCallback( TAny* aPtr )
    {
    CScorekeeper* self = static_cast<CScorekeeper*> ( aPtr );
    self->DoEffects();
    return 0;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Start
// ----------------------------------------------------------------------------
//
void CScorekeeper::Start()
    {
    if ( iEffects && !iEffects->IsActive() )
        {
        iEffects->Start(
                    KEffectsDelayTimeout,
                    KEffectsIntervalTimeout,
                    TCallBack( TimerCallback, this )
                );
        }
    }

// End of File
