/* ====================================================================
 * File: Livestock.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32std.h>
#include "Livestock.h"
#include "Scene.h"

// CONSTANTS
const TInt KLivestockDelayTimeout = 0;
const TInt KLivestockDoMoveTimeout = 25000;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CLivestock::~CLivestock
// ----------------------------------------------------------------------------
//
CLivestock::~CLivestock()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CLivestock::Cell
// ----------------------------------------------------------------------------
//
TPoint CLivestock::Cell() const
    {
    return iCell;
    }

// ----------------------------------------------------------------------------
// CLivestock::DoMove
// ----------------------------------------------------------------------------
//
void CLivestock::DoMove()
    {
    switch( iMovement )
        {
        case EMoveBottom:
            {
            if ( HitTest( iHead.iX, iHead.iY + 1 ) )
                {
                iHead.iY += 1;
                }
            else if ( !iScene.HasBarrier( iCell.iX - 1, iCell.iY ) ) // left
                {
                iHead.iX -= ( iScene.HorizontalUnitLength() / 2 );
                iMovement = EMoveBottomLeft;
                }
            else 
                {
                if ( !iScene.HasBarrier( iCell.iX + 1, iCell.iY ) ) // right
                    {
                    iHead.iX += ( iScene.HorizontalUnitLength() / 2 );
                    iMovement = EMoveBottomRight;
                    }
                }
            }
            break;

        case EMoveBottomLeft:
            {
            if ( HitTest( iHead.iX - 1, iHead.iY + 1 ) )
                {
                iHead.iX -= 1;
                iHead.iY += 1;
                }
            else
                {
                if ( !iScene.HasBarrier( iCell.iX, iCell.iY + 1 ) ) // bottom
                        {
                        iHead.iX += ( iScene.HorizontalUnitLength() / 2 );
                        iMovement = EMoveBottom;
                        }
                else
                        {
                        iHead.iX += iScene.HorizontalUnitLength(); // bottom right
                        iMovement = EMoveBottomRight;
                        }
                 }
            }
            break;
            
        case EMoveBottomRight:
            {
            if ( HitTest( iHead.iX + 1, iHead.iY + 1 ) )
                {
                iHead.iX += 1;
                iHead.iY += 1;
                }
            else
                {
                if ( !iScene.HasBarrier( iCell.iX, iCell.iY + 1 ) ) // bottom
                        {
                        iHead.iX -= ( iScene.HorizontalUnitLength() / 2 );
                        iMovement = EMoveBottom;
                        }
                else
                        {
                        iHead.iX -= iScene.HorizontalUnitLength(); // bottom left
                        iMovement = EMoveBottomLeft;
                        }
                }
            }
            break;

        default:
            break;
        }
    
    UpdateCell();
    }

// ----------------------------------------------------------------------------
// CLivestock::Stop
// ----------------------------------------------------------------------------
//
void CLivestock::Stop()
    {
    if ( iPeriodic && iPeriodic->IsActive() )
        {
        iPeriodic->Cancel();
        }
    }

// ----------------------------------------------------------------------------
// CLivestock::Resume
// ----------------------------------------------------------------------------
//
void CLivestock::Resume()
    {
    if ( iPeriodic && !iPeriodic->IsActive() )
        {
        iPeriodic->Start(
                KLivestockDelayTimeout,
                KLivestockDoMoveTimeout,
                TCallBack( TimerCallback, this ) ); 
        }
    }

// ----------------------------------------------------------------------------
// CLivestock::ConstructL
// ----------------------------------------------------------------------------
//
void CLivestock::ConstructL()
    {
/*
    iHead.iX = iScene.ClientRect().iTl.iX 
        + iCell.iX * iScene.VerticalUnitLength() 
        + iScene.VerticalUnitLength() / 2;
    iHead.iY = iScene.ClientRect().iTl.iY
        + ( iCell.iY + 1 ) * iScene.HorizontalUnitLength();
*/

    iHead.iX = iCell.iX * iScene.VerticalUnitLength() 
        + iScene.VerticalUnitLength() / 2;
    iHead.iY = ( iCell.iY + 1 ) * iScene.HorizontalUnitLength();

    iPeriodic = CPeriodic::NewL( CActive::EPriorityUserInput );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KLivestockDelayTimeout,
            KLivestockDoMoveTimeout,
            TCallBack( TimerCallback, this ) ); 
    }

// ----------------------------------------------------------------------------
// CLivestock::CLivestock
// ----------------------------------------------------------------------------
//
CLivestock::CLivestock(CScene& aScene,const TPoint& aCell)
    : iScene( aScene ), 
    iCell( aCell ),
    iMovement( EMoveBottom )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CLivestock::Rect
// ----------------------------------------------------------------------------
//
TRect CLivestock::Rect() const
    {
    TRect theRect;
    switch( iMovement )
        {
        case EMoveBottom:
            {
            theRect.iTl.iX = iHead.iX - iScene.HorizontalUnitLength() / 2;
            theRect.iTl.iY = iHead.iY - iScene.VerticalUnitLength();
            theRect.iBr.iX = iHead.iX + iScene.HorizontalUnitLength() / 2;
            theRect.iBr.iY = iHead.iY;
            }
            break;
        case EMoveBottomLeft:
            {
            theRect.iTl.iX = iHead.iX;
            theRect.iTl.iY = iHead.iY - iScene.VerticalUnitLength();
            theRect.iBr.iX = iHead.iX + iScene.HorizontalUnitLength();
            theRect.iBr.iY = iHead.iY;
            }
            break;
        case EMoveBottomRight:
            {
            theRect.iTl.iX = iHead.iX - iScene.HorizontalUnitLength();
            theRect.iTl.iY = iHead.iY - iScene.VerticalUnitLength();
            theRect.iBr.iX = iHead.iX;
            theRect.iBr.iY = iHead.iY;
            }
            break;
        default:
            break;
        }
    // Adjust the position of livestock to fit client rect.
    TRect clientRect( iScene.ClientRect() );
    theRect.Move( clientRect.iTl );
    return theRect;
    }

// ----------------------------------------------------------------------------
// CLivestock::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CLivestock::TimerCallback( TAny* aPtr )
    {
    CLivestock* self = static_cast<CLivestock*> ( aPtr );
    self->DoMove();
    return 0;
    }


// ----------------------------------------------------------------------------
// CLivestock::HitTest
// ----------------------------------------------------------------------------
//
TBool CLivestock::HitTest( TInt aX, TInt aY ) const
    {
    return !iScene.HasBarrier( CellX( aX ), CellY( aY ) );
    }

// ----------------------------------------------------------------------------
// CLivestock::CellX
// ----------------------------------------------------------------------------
//
TInt CLivestock::CellX( TInt aX ) const
    {
/*
    TInt x = iScene.ClientRect().iTl.iX 
        + aX / iScene.HorizontalUnitLength();
    return x;
*/
    return aX / iScene.HorizontalUnitLength();
    }

// ----------------------------------------------------------------------------
// CLivestock::CellY
// ----------------------------------------------------------------------------
//
TInt CLivestock::CellY( TInt aY ) const
    {
/*
    TInt y = iScene.ClientRect().iTl.iY
        + aY / iScene.VerticalUnitLength();
    return y;
*/
    return aY / iScene.VerticalUnitLength();
    }

// ----------------------------------------------------------------------------
// CLivestock::UpdateCell
// ----------------------------------------------------------------------------
//
void CLivestock::UpdateCell()
    {
    TPoint cell;
    cell.iX = CellX( iHead.iX );
    cell.iY = CellY( iHead.iY );
    if ( cell != iCell )
        {
        iCell = cell;
        iScene.LivestockUpdated( *this );
        }
    }

// End of File
