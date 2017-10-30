/* ====================================================================
 * File: Fence.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Fence.h"
#include "Scene.h"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFence::~CFence
// ----------------------------------------------------------------------------
//
CFence::~CFence()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CFence::GetCells
// ----------------------------------------------------------------------------
//
void CFence::GetCells( RArray<TPoint>& aCells )
    {
    aCells.Reset();
    aCells.Append( iStartCell );
    for ( TInt i = 1; i < iLength; i++ )
        {
        switch( iState )
            {
            case EVertical:
                {
                aCells.Append( TPoint( iStartCell.iX, iStartCell.iY + i ) );
                }
                break;
            case EInclinedLeft:
                {
                aCells.Append( TPoint( iStartCell.iX - i, iStartCell.iY + i ) );
                }
                break;
            case EInclinedRight:
                {
                aCells.Append( TPoint( iStartCell.iX + i, iStartCell.iY + i ) );
                }
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CFence::ConstructL
// ----------------------------------------------------------------------------
//
void CFence::ConstructL()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CFence::CFence
// ----------------------------------------------------------------------------
//
CFence::CFence( CScene& aScene, const TPoint& aStartCell, TInt aLength )
    : iScene( aScene ), 
    iStartCell( aStartCell ), 
    iLength( aLength ), 
    iState( EVertical )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CFence::Rect
// ----------------------------------------------------------------------------
//
TRect CFence::Rect() const
    {
    TRect theRect( 0,0,0,0 );
    TInt verticalUnitLength( iScene.VerticalUnitLength() );
    TInt horizontalUnitLength( iScene.HorizontalUnitLength() );

    switch( iState )
        {
        case EVertical:
            {
            theRect.iTl.iX = iStartCell.iX * verticalUnitLength;
            theRect.iTl.iY = iStartCell.iY * horizontalUnitLength;
            theRect.iBr.iX = theRect.iTl.iX + verticalUnitLength;
            theRect.iBr.iY = theRect.iTl.iY + horizontalUnitLength * iLength;
            }
            break;
        case EInclinedLeft:
            {
            theRect.iTl.iX = ( iStartCell.iX - iLength + 1 ) * verticalUnitLength;
            theRect.iTl.iY = iStartCell.iY * horizontalUnitLength;
            theRect.iBr.iX = theRect.iTl.iX + verticalUnitLength * iLength;
            theRect.iBr.iY = theRect.iTl.iY + horizontalUnitLength * iLength;
            }
            break;
        case EInclinedRight:
            {
            theRect.iTl.iX = iStartCell.iX * verticalUnitLength;
            theRect.iTl.iY = iStartCell.iY * horizontalUnitLength;
            theRect.iBr.iX = theRect.iTl.iX + verticalUnitLength * iLength;
            theRect.iBr.iY = theRect.iTl.iY + horizontalUnitLength * iLength;
            }
            break;
        default:
            break;
        }
    // Adjust the position of fence to fit client rect.
    TRect clientRect( iScene.ClientRect() );
    theRect.Move( clientRect.iTl );
    return theRect;
    }

// End of File
