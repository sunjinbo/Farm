/* ====================================================================
 * File: Scene.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Scene.mbg>
#include "Scene.h"
#include "Fence.h"
#include "Livestock.h"
#include "BmpUtils.h"
#include "SceneObserver.h"

// CONSTANTS
const TInt KVerticalUnitNumber = 20;
const TInt KHorizontalUnitNumber = 11;
const TInt KWickiupLivestockVerticalValue =19;
const TInt KWickiupSheepHorizontalValue = 2;
const TInt KWickiupBullHorizontalValue = 4;
const TInt KWickiupPigHorizontalValue = 6;
const TInt KWickiupHorseHorizontalValue = 8;

#if defined( __WINS__ )
_LIT( KSceneFileName, "Z:\\resource\\apps\\scene.mbm" );
#else
_LIT( KSceneFileName, "\\resource\\apps\\scene.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScene::NewL
// ----------------------------------------------------------------------------
//
CScene* CScene::NewL(MSceneObserver& aObserver, CFbsBitGc& aGc, const TRect& aRect)
    {
    CScene* self = new (ELeave) CScene(aObserver,aGc,aRect);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CScene::~CScene
// ----------------------------------------------------------------------------
//
CScene::~CScene()
    {
    ResetAll();
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CScene::Tap
// ----------------------------------------------------------------------------
//
void CScene::Tap( const TPoint& aStart, const TPoint& aEnd )
    {
    RArray<TPoint> tapCells, cells;
    if ( aStart.iX > aEnd.iX )
        {
        GetTapCells( tapCells, aStart, aEnd );
        for ( TInt i = 0; i < iFenceArray.Count(); i++ )
            {
            CFence* fence = iFenceArray[ i ];
            fence->GetCells( cells );
            if ( Intersects( tapCells, cells ) )
                {
                fence->PushLeft();
                break;
                }
            }
        }
    else if ( aStart.iX < aEnd.iX )
        {
        GetTapCells( tapCells, aEnd, aStart );
        for ( TInt i = 0; i < iFenceArray.Count(); i++ )
            {
            CFence* fence = iFenceArray[ i ];
            fence->GetCells( cells );
            if ( Intersects( tapCells, cells ) )
                {
                fence->PushRight();
                break;
                }
            }
        }
       else // aStart.iX == aEnd.iX
        { // do nothing.
        }
    tapCells.Close();
    cells.Close();
    }

// ----------------------------------------------------------------------------
// CScene::HasBarrier
// ----------------------------------------------------------------------------
//
TBool CScene::HasBarrier( TInt aX, TInt aY )
    {
    RArray<TPoint> cells;
    for ( TInt i = 0; i < iFenceArray.Count(); i++ )
        {
        iFenceArray[i]->GetCells( cells );
        for ( TInt j = 0; j < cells.Count(); j++ )
            {
            TPoint temp( cells[ j ] );
            if ( TPoint( aX, aY ) == cells[ j ] )
                {
                cells.Close();
                return ETrue;
                }
            }
        cells.Reset();
        }
    cells.Close();
/*
    for ( TInt j = 0; j < iLivestockArray.Count(); j++ )
        {
        if ( TPoint( aX, aY ) == iLivestockArray[j]->Cell() )
            {
            return ETrue;
            }
        }
*/
    return EFalse;
    }

// ----------------------------------------------------------------------------
// CScene::Gc
// ----------------------------------------------------------------------------
//
CFbsBitGc& CScene::Gc()
    {
    return iGc;
    }

// ----------------------------------------------------------------------------
// CScene::DoDraw
// ----------------------------------------------------------------------------
//
void CScene::DoDraw()
    {
    DrawBackground();
    DrawLivestock();
    DrawFence();
    DrawWickiup();
    //DrawShade();
    }

// ----------------------------------------------------------------------------
// CScene::ClientRect
// ----------------------------------------------------------------------------
//
const TRect& CScene::ClientRect() const
    {
    return iClientRect;
    }

// ----------------------------------------------------------------------------
// CScene::VerticalUnitNumber
// ----------------------------------------------------------------------------
//
TInt CScene::VerticalUnitNumber()
    {
    return KVerticalUnitNumber;
    }

// ----------------------------------------------------------------------------
// CScene::HorizontalUnitNumber
// ----------------------------------------------------------------------------
//
TInt CScene::HorizontalUnitNumber()
    {
    return KHorizontalUnitNumber;
    }

// ----------------------------------------------------------------------------
// CScene::VerticalUnitLength
// ----------------------------------------------------------------------------
//
TInt CScene::VerticalUnitLength()
    {
    return iRect.Height() / KVerticalUnitNumber;
    }

// ----------------------------------------------------------------------------
// CScene::HorizontalUnitLength
// ----------------------------------------------------------------------------
//
TInt CScene::HorizontalUnitLength()
    {
    return iRect.Width() / KHorizontalUnitNumber;
    }

// ----------------------------------------------------------------------------
// CScene::AppendFence
// ----------------------------------------------------------------------------
//
void CScene::AppendFence( CFence* aFence )
    {
    if ( aFence )
        {
        iFenceArray.Append( aFence );
        }
    }

// ----------------------------------------------------------------------------
// CScene::AppendLivestock
// ----------------------------------------------------------------------------
//
void CScene::AppendLivestock( CLivestock* aLivestock )
    {
    if ( aLivestock )
        {
        iLivestockArray.Append( aLivestock );
        }
    }

// ----------------------------------------------------------------------------
// CScene::FenceUpdated
// ----------------------------------------------------------------------------
//
void CScene::FenceUpdated( const CFence& /*aFence*/ )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CScene::LivestockUpdated
// ----------------------------------------------------------------------------
//
void CScene::LivestockUpdated( const CLivestock& aLivestock )
    {
    TPoint theCell( aLivestock.Cell() );
    TLivestockType theType( aLivestock.Type() );
    if ( theCell.iY == KWickiupLivestockVerticalValue )
        {
        // Delete livestock
        TInt index( 0 );
        TRAPD( err, Find( aLivestock, index ) );
        if ( KErrNone == err )
            {
            CLivestock* livestock = iLivestockArray[ index ];
            delete livestock;
            livestock = NULL;
            iLivestockArray.Remove( index );
            iLivestockArray.Compress();
            }

        if ( IsInWickiup( theCell ) )
            {
            if ( iWickiup[theType] == theCell )
                {
                iObserver.Lairage( theType );
                }
            else
                {
                iObserver.Mixup( theType );
                }
            }
        else
            {
            iObserver.Escape( theType );
            }
        }
    }

// ----------------------------------------------------------------------------
// CScene::ResetAll
// ----------------------------------------------------------------------------
//
void CScene::ResetAll()
    {
    iFenceArray.ResetAndDestroy();
    iLivestockArray.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CScene::Stop
// ----------------------------------------------------------------------------
//
void CScene::Stop()
    {
    for ( TInt i = 0; i < iLivestockArray.Count(); i++ )
        {
        iLivestockArray[i]->Stop();
        }
    }

// ----------------------------------------------------------------------------
// CScene::Resume
// ----------------------------------------------------------------------------
//
void CScene::Resume()
    {
    for ( TInt i = 0; i < iLivestockArray.Count(); i++ )
        {
        iLivestockArray[i]->Resume();
        }
    }

// ----------------------------------------------------------------------------
// CScene::SetShade
// ----------------------------------------------------------------------------
//
void CScene::SetShade( TBool aShade )
    {
    if ( iShade != aShade )
        {
        iShade = aShade;
        }
    }

// ----------------------------------------------------------------------------
// CScene::ConstructL
// ----------------------------------------------------------------------------
//
void CScene::ConstructL()
    {
    TInt horizMargin( 0 ), verticalMargin( 0 );
    horizMargin = ( iRect.Width() - HorizontalUnitLength() * HorizontalUnitNumber() ) / 2;
    verticalMargin = ( iRect.Height() - VerticalUnitLength() * VerticalUnitNumber() ) / 2;
    iClientRect.iTl.iX = horizMargin;
    iClientRect.iTl.iY = verticalMargin;
    iClientRect.SetWidth( HorizontalUnitLength() * HorizontalUnitNumber() );
    iClientRect.SetHeight( VerticalUnitLength() * VerticalUnitNumber() );

    iWickiup[ESheepType].iX = KWickiupSheepHorizontalValue;
    iWickiup[ESheepType].iY = KWickiupLivestockVerticalValue;
    iWickiup[ECowType].iX = KWickiupBullHorizontalValue;
    iWickiup[ECowType].iY = KWickiupLivestockVerticalValue;
    iWickiup[EPigType].iX = KWickiupPigHorizontalValue;
    iWickiup[EPigType].iY = KWickiupLivestockVerticalValue;
    iWickiup[EHorseType].iX = KWickiupHorseHorizontalValue;
    iWickiup[EHorseType].iY = KWickiupLivestockVerticalValue;

    iUtils = CBmpUtils::NewL( 
            KSceneFileName,
            EMbmSceneScene,
            EMbmSceneLastElement
            );
    }

// ----------------------------------------------------------------------------
// CScene::CScene
// ----------------------------------------------------------------------------
//
CScene::CScene(MSceneObserver& aObserver,CFbsBitGc& aGc, const TRect& aRect)
    : iObserver( aObserver ), iGc( aGc ), iRect(aRect)
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CScene::DrawBackground
// ----------------------------------------------------------------------------
//
void CScene::DrawBackground()
    {
    /*
    TSize cellSize;
    cellSize.iWidth = iRect.Width() / KHorizontalUnitNumber;
    cellSize.iHeight = iRect.Height() / KVerticalUnitNumber;
    iGc.SetPenStyle( CGraphicsContext::ESolidPen );
    iGc.SetPenColor( KRgbBlack );
    iGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    iGc.SetBrushColor( KRgbGreen );
    iGc.DrawRect( iRect );
    for ( TInt i = 0; i < KHorizontalUnitNumber; i++ )
        for ( TInt j = 0; j < KVerticalUnitNumber; j++ )
        {
        TPoint thePos;
        thePos.iX = iClientRect.iTl.iX + i * cellSize.iWidth;
        thePos.iY = iClientRect.iTl.iY + j * cellSize.iHeight;
        iGc.DrawRect( TRect( thePos, cellSize ) );
        }
    */
    iGc.BitBltMasked( 
        iRect.iTl,
        iUtils->Bitmap( EMbmSceneScene ),
        TRect( TPoint( 0, 0 ), iRect.Size() ),
        iUtils->Bitmap( EMbmSceneScene_mask ),
        ETrue
        );
    }

// ----------------------------------------------------------------------------
// CScene::DrawWickiup
// ----------------------------------------------------------------------------
//
void CScene::DrawWickiup()
    {
    iGc.SetBrushColor( KRgbRed );
    iGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    iGc.SetPenColor( KRgbBlack );
    iGc.SetPenStyle( CGraphicsContext::ESolidPen );

    for ( TInt i = 0; i < ELivestockLastElement; i++ )
        {
        TInt x = iClientRect.iTl.iX + iWickiup[i].iX * HorizontalUnitLength();
        TInt y = iClientRect.iTl.iY + ( iWickiup[i].iY - 1 ) * VerticalUnitLength();
        TSize size( HorizontalUnitLength(), VerticalUnitLength() );
        iGc.DrawRect( TRect( TPoint( x, y ), size ) );
        }
    }

// ----------------------------------------------------------------------------
// CScene::DrawFence
// ----------------------------------------------------------------------------
//
void CScene::DrawFence()
    {
    for ( TInt i = 0; i < iFenceArray.Count(); i++ )
        {
        iFenceArray[i]->DoDraw();
        }
    }

// ----------------------------------------------------------------------------
// CScene::DrawLivestock
// ----------------------------------------------------------------------------
//
void CScene::DrawLivestock()
    {
    for ( TInt i = 0; i < iLivestockArray.Count(); i++ )
        {
        iLivestockArray[i]->DoDraw();
        }
    }

// ----------------------------------------------------------------------------
// CScene::DrawShade
// ----------------------------------------------------------------------------
//
void CScene::DrawShade()
    {
    if ( iShade )
        {
        iGc.SetPenStyle( CGraphicsContext::ENullPen );
        iGc.SetBrushStyle( CGraphicsContext::ENullBrush );
        TRect theRect( RectForShade() );
        iGc.BitBltMasked( 
                theRect.iTl,
                iUtils->Bitmap( EMbmSceneShade ),
                TRect( TPoint( 0, 0 ), theRect.Size() ),
                iUtils->Bitmap( EMbmSceneShade_mask ),
                ETrue
                );
        }
    }

// ----------------------------------------------------------------------------
// CScene::GetTapCells
// ----------------------------------------------------------------------------
//
void CScene::GetTapCells( RArray<TPoint>& aCells, const TPoint& aStart, const TPoint& aEnd )
    {
    TPoint origin( Min( aStart.iX, aEnd.iX ), Min( aStart.iY, aEnd.iY ) );
    TPoint origin2( Max( aStart.iX, aEnd.iX ), Max( aStart.iY, aEnd.iY ) );
    /*Transfer integer to  double to keep decimal digits*/
    TReal x1 = (TReal)( aStart.iX );
    TReal y1 = (TReal)( aStart.iY );
    TReal x2 = (TReal)( aEnd.iX );
    TReal y2 = (TReal)( aEnd.iY );
    TReal a = ( y2 - y1 ) / ( x2 - x1 );
    TReal32 b = ( x2 * y1 - x1 * y2 ) / ( x2 - x1 );
    for ( TInt i = origin.iX; i < origin2.iX + 1; i++ )
        for ( TInt j = origin.iY; j <  origin2.iY + 1; j++ )
            {
            if ( Abs( j - a * i - b ) < 1 )
                {
                aCells.Append( TPoint( i, j ) );
                }
            }
    }

// ----------------------------------------------------------------------------
// CScene::Intersects
// ----------------------------------------------------------------------------
//
TBool CScene::Intersects( const RArray<TPoint>& aFirst, const RArray<TPoint>& aSecond ) const
        {
        for ( TInt i = 0; i < aFirst.Count(); i++ )
            for ( TInt j = 0; j < aSecond.Count(); j ++ )
                {
                if ( aFirst[ i ] == aSecond[ j ] )
                    {
                    return ETrue;
                    }
                }
        return EFalse;
        }

// ----------------------------------------------------------------------------
// CScene::Find
// ----------------------------------------------------------------------------
//
TInt CScene::Find( const CLivestock& aLivestock, TInt& aIndex ) const
        {
        for ( TInt i = 0; i < iLivestockArray.Count(); i++ )
            {
            if ( iLivestockArray[i] == &aLivestock )
                {
                aIndex = i;
                return KErrNone;
                }
            }
        return KErrNotFound;
        }

// ----------------------------------------------------------------------------
// CScene::IsInWickiup
// ----------------------------------------------------------------------------
//
TBool CScene::IsInWickiup( const TPoint& aLivestockCell ) const
        {
        for ( TInt i = 0; i < ELivestockLastElement; i++ )
            {
            if ( iWickiup[ i ] == aLivestockCell )
                {
                return ETrue;
                }
            }
        return EFalse;
        }

// ----------------------------------------------------------------------------
// CScene::RectForShade
// ----------------------------------------------------------------------------
//
TRect CScene::RectForShade() const
    {
    TRect theRect;
    theRect.iTl = iRect.iTl;
    theRect.SetWidth( iRect.Width() );
    TInt height = iRect.Height() / KVerticalUnitNumber * 2;
    theRect.SetHeight( height );
    return theRect;
    }

// End of File
