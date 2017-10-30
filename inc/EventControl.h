/* ====================================================================
 * File: EventControl.h
 * Created: 01/18/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef __EVENTCONTROL_H
#define __EVENTCONTROL_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CCoeAppUi;
class MEventControlObserver;

// CLASS DECLARATION
class CEventControl : public CCoeControl
    {
public:  // Constructors and destructor
    /**
    * Two-phased constructor.
    * @param aObserver
    * @return
    */
    static CEventControl* NewL( MEventControlObserver& aObserver );

    /**
    * C++ destructor
    */
    virtual ~CEventControl();

public: // from MEikCommandObserver
    /**
    *
    * @param aCommand
    */
    void ProcessCommandL( TInt aCommand );

private: // Constructor
    /**
    *  C++ default constructor.
    */
    CEventControl( MEventControlObserver& aObserver );

    /**
    *  default constructor
    */
    void ConstructL();

private: // From CCoeControl

    /**
    * @param aPointerEvent
    * @return void
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
    * 
    * @param aKeyEvent
    * @param aType
    * @return EKeyWasConsumed, or EKeyWasNotConsumed
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, 
            TEventCode aType 
           );

    /**
    * Return number of controls
    * @param None
    * @return void
    */
    TInt CountComponentControls() const;

    /**
    * Return control by given index
    * @param None
    * @return void
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * Draw given rectancge
    * @param aRect
    * @return void
    */
    void Draw( const TRect& aRect ) const;        

    /**
    * -
    * @return void
    */
    void PrepareForFocusLossL();

private: // Data
    /** */
    MEventControlObserver& iObserver;

    /** */
    CCoeAppUi* iAppUi;
    
    /** */
    TPoint iStart;
    };

#endif // __EVENTCONTROL_H

// End of File
