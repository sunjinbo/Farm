/* ====================================================================
 * File: Sheep.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Sheep.mbg>
#include "Sheep.h"
#include "Scene.h"
#include "BmpUtils.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KSheepFileName, "Z:\\resource\\apps\\sheep.mbm" );
#else
_LIT( KSheepFileName, "\\resource\\apps\\sheep.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CSheep::NewL
// ----------------------------------------------------------------------------
//
CSheep* CSheep::NewL(CScene& aScene,const TPoint& aCell)
    {
    CSheep* self = new (ELeave) CSheep(aScene, aCell );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CSheep::~CSheep
// ----------------------------------------------------------------------------
//
CSheep::~CSheep()
    {
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CSheep::DoDraw
// ----------------------------------------------------------------------------
//
void CSheep::DoDraw()
    {
    iScene.Gc().SetPenStyle( CGraphicsContext::ENullPen );
    iScene.Gc().SetBrushStyle( CGraphicsContext::ENullBrush );
    
    TRect theRect( Rect() );
    
    switch( iMovement )
        {
        case EMoveBottom:
            {
            if ( iFirstIcon )
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmSheepSheep1 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmSheepSheep1_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmSheepSheep2 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmSheepSheep2_mask ),
                    ETrue
                    );
                }
            }
            break;
        case EMoveBottomLeft:
            {
            if ( iFirstIcon )
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmSheepSheep1_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmSheepSheep1_left_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmSheepSheep2_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmSheepSheep2_left_mask ),
                    ETrue
                    );
                }
            }
            break;
        case EMoveBottomRight:
            {
            if ( iFirstIcon )
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmSheepSheep1_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmSheepSheep1_right_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmSheepSheep2_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmSheepSheep2_right_mask ),
                    ETrue
                    );
                }
            }
            break;
        default:
            break;
        }
    
    iFirstIcon = !iFirstIcon;
    }

// ----------------------------------------------------------------------------
// CSheep::Type
// ----------------------------------------------------------------------------
//
TLivestockType CSheep::Type() const
    {
    return ESheepType;
    }

// ----------------------------------------------------------------------------
// CSheep::ConstructL
// ----------------------------------------------------------------------------
//
void CSheep::ConstructL()
    {
    CLivestock::ConstructL();

    iUtils = CBmpUtils::NewL( 
            KSheepFileName,
            EMbmSheepSheep1,
            EMbmSheepLastElement
            );
    
    }

// ----------------------------------------------------------------------------
// CSheep::CSheep
// ----------------------------------------------------------------------------
//
CSheep::CSheep(CScene& aScene,const TPoint& aCell)
    : CLivestock(aScene,aCell )
    { // no implementation required.
    }

// End of File
