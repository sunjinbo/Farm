/* ====================================================================
 * File: TouchEventFilter.h
 * Created: 01/18/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef __TOUCHEVENTFILTER_H
#define __TOUCHEVENTFILTER_H

// INCLUDES
#include <e32base.h>
#include <e32std.h>
#include "EventControlObserver.h"

// FORWARD DECLARATIONS
class CEikonEnv;
class CEventControl;
class MEventFilterObserver;

/**
*  CTouchEventFilter
*/
class CTouchEventFilter : public CBase, public MEventControlObserver
    {
public: // Constructors and destructor
    /**
    * Two-phased constructor
    */
    static CTouchEventFilter* NewL( const TRect& aRect, const TSize& aCellSize );

    /**
    * C++ Destructor
    */
    virtual ~CTouchEventFilter();

public: // New functions
    /**
    * Enable keyevent filter
    * @param aEnabled
    * @return void
    */
    void Enable(  const TBool aEnable = ETrue ); 

    /**
    * Check filter state
    * @return ETrue, EFalse
    */
    TBool IsEnabled() const;

    /**
    * Add event observer
    * @param Observer reference
    */
    void AddObserverL( MEventFilterObserver& aObserver );

    /**
    * Remove observer
    * @param Observer reference
    */
   void RemoveObserver( MEventFilterObserver& aObserver );

    /**
    * Notify  observers
    * @param aStart Start position
    * @param aEnd End position
    */
    void NotifyObservers(  const TPoint& aStart, const TPoint& aEnd );

    /**
    * Gets control
    * @return CEventControl reference
    */
    CCoeControl& Control() const;

private: // Constructors
    /**
    * C++ default constructor.
    */
    CTouchEventFilter( const TRect& aRect, const TSize& aCellSize );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

private: // From MEventControlEvent
    /*
    * Callback function
    */
    void EventControlEvent(  const TPoint& aStart, const TPoint& aEnd );

private: //data
    /** Cached pointer to the CEikonEnv singelton instance */
    CEikonEnv* iEikEnv;

    /** Owns: */
    CEventControl* iControl;

    /** */
    TBool iEnabled;

    /** Owns: */
    RPointerArray<MEventFilterObserver> iObservers; 
    
    /**/
    TRect iRect;
    
    /**/
    TSize iCellSize;

    };

#endif // __TOUCHEVENTFILTER_H

// End of File
