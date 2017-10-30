/* ====================================================================
 * File: Cow.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDES
#include <bitstd.h>
#include <Cow.mbg>
#include "Cow.h"
#include "Scene.h"
#include "BmpUtils.h"

// CONSTANS
#if defined( __WINS__ )
_LIT( KCowFileName, "Z:\\resource\\apps\\cow.mbm" );
#else
_LIT( KCowFileName, "\\resource\\apps\\cow.mbm" );
#endif // __WINS__


// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CCow::NewL
// ----------------------------------------------------------------------------
//
CCow* CCow::NewL(CScene& aScene,const TPoint& aCell)
    {
    CCow* self = new (ELeave) CCow(aScene, aCell );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CCow::~CCow
// ----------------------------------------------------------------------------
//
CCow::~CCow()
    {
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CCow::DoDraw
// ----------------------------------------------------------------------------
//
void CCow::DoDraw()
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
                    iUtils->Bitmap( EMbmCowCow1 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmCowCow1_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmCowCow2 ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmCowCow2_mask ),
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
                    iUtils->Bitmap( EMbmCowCow1_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmCowCow1_left_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmCowCow2_left ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmCowCow2_left_mask ),
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
                    iUtils->Bitmap( EMbmCowCow1_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmCowCow1_right_mask ),
                    ETrue
                    );
                }
            else
                {
                iScene.Gc().BitBltMasked( 
                    theRect.iTl,
                    iUtils->Bitmap( EMbmCowCow2_right ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iUtils->Bitmap( EMbmCowCow2_right_mask ),
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
// CCow::Type
// ----------------------------------------------------------------------------
//
TLivestockType CCow::Type() const
    {
    return ECowType;
    }

// ----------------------------------------------------------------------------
// CCow::ConstructL
// 2nd phase construction
// ----------------------------------------------------------------------------
//
void CCow::ConstructL()
    {
    CLivestock::ConstructL();
    

    iUtils = CBmpUtils::NewL( 
            KCowFileName,
            EMbmCowCow1,
            EMbmCowLastElement
            );
    
    }

// ----------------------------------------------------------------------------
// CCow::CCow
// ----------------------------------------------------------------------------
//
CCow::CCow(CScene& aScene,const TPoint& aCell)
    : CLivestock(aScene,aCell )
    { // no implementation required.
    }

// End of File
