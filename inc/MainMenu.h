/* ====================================================================
 * File: MainMenu.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MAINMENU_H
#define C_MAINMENU_H

// INCLUDS
#include <coecntrl.h>

// FORWARD DECLARATIONS
class MMenuObserver;
class CFbsBitGc;
class CPeriodic;
class TResourceReader;
class CBmpUtils;

const TInt KMaxItemLen = 20;

class TMenuItem
    {
public: // New function
    static TInt Compare( const TMenuItem& aFirst, const TMenuItem& aSecond );
public: // Member Data
    TInt iItemId;
    TBuf<KMaxItemLen> iText;
    };

class CMainMenu : public CCoeControl
    {
public:
    static CMainMenu* NewL(
            MMenuObserver& aObserver,
            CFbsBitGc& aGc, 
            const TRect& aRect );
    virtual ~CMainMenu();

public: // New functions
    void DoDraw();
    TInt Append( const TMenuItem& aItem );
    TInt Remove( TInt aItemId );
    TInt Count() const;
    const TMenuItem& At( TInt aIndex ) const;
    void Start();
    void DoEffects();
    void ConstructFromResourceL( TResourceReader& aReader );

public: // From CCoeControl
    void Draw();
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private: // Constructor
    void ConstructL(const TRect& aRect);
    CMainMenu(MMenuObserver& aObserver,CFbsBitGc& aGc);

private: // New functions
    void ProcessPressedL( const TPoint& aPosition );
    void Sort();
    static TInt TimerCallback( TAny* aPtr );

private: // Data
    MMenuObserver& iObserver;
    CFbsBitGc& iGc;
    RArray<TMenuItem> iMenuItems;
    CPeriodic* iEffects; // Own
    CBmpUtils* iUtils;
    TRect iRect;
    };

#endif // C_MAINMENU_H

// End of File
