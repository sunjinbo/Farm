/* ====================================================================
 * File: Horse.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#include <bitstd.h>
#include <Horse.mbg>
#include "Horse.h"
#include "Scene.h"
#include "BmpUtils.h"

// CONSTANS
#if defined( __WINS__ )
_LIT( KHorseFileName, "Z:\\resource\\apps\\horse.mbm" );
#else
_LIT( KHorseFileName, "\\resource\\apps\\horse.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CHorse::NewL
// ----------------------------------------------------------------------------
//
CHorse* CHorse::NewL(CScene& aScene,const TPoint& aCell)
    {
    CHorse* self = new (ELeave) CHorse(aScene, aCell );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CHorse::~CHorse
// ----------------------------------------------------------------------------
//
CHorse::~CHorse()
    {
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CHorse::DoDraw
// ----------------------------------------------------------------------------
//
void CHorse::DoDraw()
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
                    iUtils->Bitmap( EMbmHorseHorse1 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmHorseHorse1_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmHorseHorse2 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmHorseHorse2_mask ),
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
                    iUtils->Bitmap( EMbmHorseHorse1_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmHorseHorse1_left_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmHorseHorse2_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmHorseHorse2_left_mask ),
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
                    iUtils->Bitmap( EMbmHorseHorse1_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmHorseHorse1_right_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmHorseHorse2_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmHorseHorse2_right_mask ),
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
// CHorse::Type
// ----------------------------------------------------------------------------
//
TLivestockType CHorse::Type() const
    {
    return EHorseType;
    }

// ----------------------------------------------------------------------------
// CHorse::ConstructL
// ----------------------------------------------------------------------------
//
void CHorse::ConstructL()
    {
    CLivestock::ConstructL();
    
    iUtils = CBmpUtils::NewL( 
            KHorseFileName,
            EMbmHorseHorse1,
            EMbmHorseLastElement
            );
    }

// ----------------------------------------------------------------------------
// CHorse::CHorse
// ----------------------------------------------------------------------------
//
CHorse::CHorse(CScene& aScene,const TPoint& aCell)
    : CLivestock(aScene,aCell )
    { // no implementation required.
    }

// End of File
