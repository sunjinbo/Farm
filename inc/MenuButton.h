/* ====================================================================
 * File: MenuButton.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MENUBUTTON_H
#define C_MENUBUTTON_H

// INCLUDS
#include <coecntrl.h>

// Enums
enum TOrientation
    {
    ENorth,
    ESouth,
    EWest,
    EEast,
    ENortheast,
    ENorthwest,
    ESoutheast,
    ESouthwest,
    ECentre,
    ELastElement
    };

// FORWARD DECLARATIONS
class MButtonObserver;
class CFbsBitGc;
class CPeriodic;
class CBmpUtils;

class CMenuButton : public CCoeControl
    {
public:
    static CMenuButton* NewL(
        MButtonObserver& aObserver,
        CFbsBitGc& aGc, 
        const TRect& aRect );
    virtual ~CMenuButton();

public: // New functions
    void DoDraw();
    void DoEffects();

public: // From CCoeControl
    void Draw();
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private: // Constructor
    void ConstructL(const TRect& aRect);
    CMenuButton(MButtonObserver& aObserver,CFbsBitGc& aGc);

private: // New functions
    static TInt TimerCallback( TAny* aPtr );
    void Start();
    TInt Rand( TInt aRange ) const;
    void Rock();

private: // Data
    MButtonObserver& iObserver;
    CFbsBitGc& iGc;
    CPeriodic* iEffects; // Own
    CBmpUtils* iUtils; // Own
    TInt iRockTimes;
    TOrientation iOrientation;
    TRect iRect;
    };

#endif // C_MENUBUTTON_H

// End of File
