/* ====================================================================
 * File: TouchEventFilter.cpp
 * Created: 01/18/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <eikenv.h>
#include "TouchEventFilter.h"
#include "EventControl.h"
#include "EventFilterObserver.h"

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// ----------------------------------------------------------------------------
// CTouchEventFilter::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTouchEventFilter* CTouchEventFilter::NewL( const TRect& aRect, const TSize& aCellSize )
    {
    CTouchEventFilter* self = new (ELeave) CTouchEventFilter( aRect, aCellSize );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::~CTouchEventFilter
// C++ Destructor
// -----------------------------------------------------------------------------
//
CTouchEventFilter::~CTouchEventFilter()
    {
    if ( iControl )
        {
        delete iControl;         
        } // iControl

    // Do not delete references
    iObservers.Reset();
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::Enable
// Enable/disable filtering
// -----------------------------------------------------------------------------
//
void CTouchEventFilter::Enable( const TBool aEnable )
    {
    iEnabled = aEnable;
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::IsEnabled
// Get state
// -----------------------------------------------------------------------------
//
TBool CTouchEventFilter::IsEnabled() const
    {
    return iEnabled;
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::AddObserverL
// Add observer refernce to array
// (exported, may leave)
// ----------------------------------------------------------------------------
//
void CTouchEventFilter::AddObserverL( MEventFilterObserver& aObserver )
    {
    iObservers.AppendL( &aObserver );
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::RemoveObserver
// Remove observer refernce from array
// (exported)
// ----------------------------------------------------------------------------
//
void CTouchEventFilter::RemoveObserver( MEventFilterObserver& aObserver )
    {
    const TInt count = iObservers.Count();
    for ( TInt i = ( count - 1 ); i >= 0; i-- )
        {
        MEventFilterObserver* observer = iObservers[ i ];
        if ( &aObserver == observer )
            {
            iObservers.Remove( i );
            }
        }
    }


// ----------------------------------------------------------------------------
// CEventFilter::NotifyObservers
// Notify observers
// ----------------------------------------------------------------------------
//
void CTouchEventFilter::NotifyObservers(  const TPoint& aStart, const TPoint& aEnd )
    {
    const TInt count = iObservers.Count();
    for ( TInt i = 0; i < count; i++ )
        {
        MEventFilterObserver* observer = iObservers[ i ];
        observer->EventFilterEvent( aStart, aEnd );
        } // i
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::Control
// ----------------------------------------------------------------------------
//
CCoeControl& CTouchEventFilter::Control() const
    {
    return ( *iControl );
    }

// ----------------------------------------------------------------------------
// CTouchEventFilter::CTouchEventFilter
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTouchEventFilter::CTouchEventFilter( const TRect& aRect, const TSize& aCellSize )
    : iEikEnv( CEikonEnv::Static() ), iEnabled( EFalse ), iRect( aRect ), iCellSize( aCellSize )
    { // no implementation required
    }

// -----------------------------------------------------------------------------
// CTouchEventFilter::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTouchEventFilter::ConstructL()
    {
    iControl = CEventControl::NewL( *this  );
    }

// -----------------------------------------------------------------------------
// CTouchEventFilter::EventControlEvent
// -----------------------------------------------------------------------------
//
void CTouchEventFilter::EventControlEvent(  const TPoint& aStart, const TPoint& aEnd )
    {
    if ( iRect.Contains( aStart ) && iRect.Contains( aEnd ) )
        {
        TPoint start, end;
        start.iX = ( aStart.iX - iRect.iTl.iX ) / iCellSize.iWidth;
        start.iY = ( aStart.iY - iRect.iTl.iY ) / iCellSize.iHeight;
        end.iX = ( aEnd.iX - iRect.iTl.iX ) / iCellSize.iWidth;
        end.iY = ( aEnd.iY - iRect.iTl.iY ) / iCellSize.iHeight;
        if ( start.iX != end.iX )
            {
            NotifyObservers( start, end );
            }
        }
    }

//  End of File
