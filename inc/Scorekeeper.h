/* ====================================================================
 * File: Scorekeeper.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCOREKEEPER_H
#define C_SCOREKEEPER_H

// INCLUDS
#include "Livestock.hrh"

// FORWARD DECLARATIONS
class CFbsBitGc;
class CEikonEnv;
class CBmpUtils;

class CScorekeeper : public CBase
    {
public:
    static CScorekeeper* NewL(
        CFbsBitGc& aGc, 
        const TRect& aRect,
        const TSize& aCellSize );
    virtual ~CScorekeeper();

public: // New functions
    void DoDraw();
    void Clear();
    void SetValue( TLivestockType aType, TInt aValue );
    void Append( TLivestockType aType );
    void DoEffects();

private: // Constructor
    void ConstructL(const TRect& aRect, const TSize& aCellSize);
    CScorekeeper(CFbsBitGc& aGc);

private: // New functions
    void DrawBackground();
    void DrawLivestockIcon();
    void DrawScorekeeper();
    static TInt TimerCallback( TAny* aPtr );
    void Start();

private: // Data
    CEikonEnv* iEikEnv;
    CFbsBitGc& iGc;
    TRect iRect;
    TSize iCellSize;
    TInt iHorizMargin;
    TInt iVerticalMargin;
    TInt iValues[ELivestockLastElement];
    CPeriodic* iEffects; // Own
    CBmpUtils* iUtils; // Own
    };

#endif // C_SCOREKEEPER_H

// End of File
