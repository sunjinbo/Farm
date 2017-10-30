/* ====================================================================
 * File: StoneFence.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDS
#include <bitstd.h>
#include <Fence.mbg>
#include "StoneFence.h"
#include "Scene.h"
#include "BmpUtils.h"

// CONSTANS
#if defined( __WINS__ )
_LIT( KFenceFileName, "Z:\\resource\\apps\\fence.mbm" );
#else
_LIT( KFenceFileName, "\\resource\\apps\\fence.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CStoneFence::NewL
// ----------------------------------------------------------------------------
//
CStoneFence* CStoneFence::NewL( CScene& aScene, TPoint aStartCell, TInt aLength )
    {
    CStoneFence* self = new (ELeave) CStoneFence(aScene,aStartCell,aLength);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CStoneFence::~CStoneFence
// ----------------------------------------------------------------------------
//
CStoneFence::~CStoneFence()
    {
    delete iUtils;
    iCells.Close();
    }

// ----------------------------------------------------------------------------
// CStoneFence::DoDraw
// ----------------------------------------------------------------------------
//
void CStoneFence::DoDraw()
    {
    iScene.Gc().SetPenStyle( CGraphicsContext::ENullPen );
    iScene.Gc().SetBrushStyle( CGraphicsContext::ENullBrush );
    
    for ( TInt i = 0; i < iCells.Count(); i++ )
        {
        iScene.Gc().BitBltMasked( 
            iCells[ i ].iTl,
            iUtils->Bitmap( EMbmFenceStone ),
            TRect( TPoint( 0, 0 ), iCells[ i ].Size() ),
            iUtils->Bitmap( EMbmFenceStone_mask ),
            ETrue
            );
        }
    }

// ----------------------------------------------------------------------------
// CStoneFence::PushLeft
// ----------------------------------------------------------------------------
//
void CStoneFence::PushLeft()
    { // we can't move stone fence.
    }

// ----------------------------------------------------------------------------
// CStoneFence::PushRight
// ----------------------------------------------------------------------------
//
void CStoneFence::PushRight()
    { // we can't move stone fence.
    }

// ----------------------------------------------------------------------------
// CStoneFence::ConstructL
// ----------------------------------------------------------------------------
//
void CStoneFence::ConstructL()
    {
    CFence::ConstructL();

    iUtils = CBmpUtils::NewL( 
            KFenceFileName,
            EMbmFenceStone,
            EMbmFenceLastElement
            );
    
    RectForCells( iCells );
    }

// ----------------------------------------------------------------------------
// CStoneFence::CStoneFence
// ----------------------------------------------------------------------------
//
CStoneFence::CStoneFence( CScene& aScene, TPoint aStartCell, TInt aLength )
    : CFence( aScene,aStartCell,aLength )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CStoneFence::RectForCells
// ----------------------------------------------------------------------------
//
void CStoneFence::RectForCells( RArray<TRect>& aCells )
    {
    iCells.Reset();
    RArray<TPoint> cells;
    GetCells( cells );

    TInt vl( iScene.VerticalUnitLength() );
    TInt hl( iScene.HorizontalUnitLength() );
    for ( TInt i = 0; i < cells.Count(); i++ )
        {
        TRect theRect;
        theRect.iTl.iX = cells[i].iX * hl;
        theRect.iTl.iY = cells[i].iY * vl;
        theRect.iBr.iX = ( cells[i].iX + 1 ) * hl;
        theRect.iBr.iY = ( cells[i].iY + 1 )  * vl;
        theRect.Move( iScene.ClientRect().iTl );
        aCells.Append( theRect );
        }

    cells.Close();
    }

// End of File
