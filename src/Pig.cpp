/* ====================================================================
 * File: Pig.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Pig.mbg>
#include "Pig.h"
#include "Scene.h"
#include "BmpUtils.h"

// CONSTANS
#if defined( __WINS__ )
_LIT( KPigFileName, "Z:\\resource\\apps\\pig.mbm" );
#else
_LIT( KPigFileName, "\\resource\\apps\\pig.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CPig::NewL
// ----------------------------------------------------------------------------
//
CPig* CPig::NewL(CScene& aScene,const TPoint& aCell)
    {
    CPig* self = new (ELeave) CPig(aScene, aCell );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CPig::~CPig
// ----------------------------------------------------------------------------
//
CPig::~CPig()
    {
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CPig::DoDraw
// ----------------------------------------------------------------------------
//
void CPig::DoDraw()
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
                    iUtils->Bitmap( EMbmPigPig1 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmPigPig1_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmPigPig2 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmPigPig2_mask ),
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
                    iUtils->Bitmap( EMbmPigPig1_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmPigPig1_left_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmPigPig2_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmPigPig2_left_mask ),
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
                    iUtils->Bitmap( EMbmPigPig1_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmPigPig1_right_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmPigPig2_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmPigPig2_right_mask ),
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
// CPig::Type
// ----------------------------------------------------------------------------
//
TLivestockType CPig::Type() const
    {
    return EPigType;
    }

// ----------------------------------------------------------------------------
// CPig::ConstructL
// ----------------------------------------------------------------------------
//
void CPig::ConstructL()
    {
    CLivestock::ConstructL();

    iUtils = CBmpUtils::NewL( 
            KPigFileName,
            EMbmPigPig1,
            EMbmPigLastElement
            );

    }

// ----------------------------------------------------------------------------
// CPig::CPig
// ----------------------------------------------------------------------------
//
CPig::CPig(CScene& aScene,const TPoint& aCell)
    : CLivestock(aScene,aCell )
    { // no implementation required.
    }

// End of File
