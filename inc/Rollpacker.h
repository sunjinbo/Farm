/* ====================================================================
 * File: Rollpacker.h
 * Created: 01/26/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ROLLPACKER_H
#define C_ROLLPACKER_H

// INCLUDE FILES
#include <coecntrl.h>

// CONSTANTS
const TInt KScrollLineNumber = 7;

// FORWARD DECLARATIONS
class MRollpackerObserver;

// CLASS DECLARATION
/**
* CRollpacker class
*
*/
class CRollpacker : public CCoeControl
    {
public: // Constructor and Destructor
    static CRollpacker* NewL( CFbsBitGc& aGc, const TRect& aRect );
    virtual ~CRollpacker();

public: // New function
    void AddTextL( const TDesC& aText );
    void Clear();
    void Start();
    void DoDraw();
    void SetObserver( MRollpackerObserver* aObserver );

public: // From CCoeControl
    void Draw(const TRect& aRect) const;
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

protected: // Constructor
    CRollpacker( CFbsBitGc& aGc );
    void ConstructL( const TRect& aRect );

private: // New function
    void Stop();
    void DoScroll();
    static TInt TimerCallback( TAny* aPtr );
    void InitializeScroll();
    void UpdateCabinetArray();
    void AppendL( const TDesC& aText );

protected: // Data members
    CFbsBitGc& iGc;
    MRollpackerObserver* iObserver; // Not own
    RPointerArray<HBufC> iTextArray;
    CPeriodic* iPeriodic; // Own
    TFixedArray<TInt, KScrollLineNumber> iScrollCabinet;
    TInt iHeadIndex;
    TInt iTailIndex;
    TInt iHeadValue;
    TInt iScrollStep;
    TInt iCabinetStep;
    };

#endif // C_ROLLPACKER_H

// End of File
