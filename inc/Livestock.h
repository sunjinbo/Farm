/* ====================================================================
 * File: Livestock.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_LIVESTOCK_H
#define C_LIVESTOCK_H

// INCLUDS
#include <e32base.h>
#include "Livestock.hrh"

// FORWARD DECLARATIONS
class CScene;

class CLivestock : public CBase
    {
public:
    virtual ~CLivestock();

public: // New functions
    virtual void DoDraw() = 0;
    virtual TLivestockType Type() const = 0;

public:
    TPoint Cell() const;
    void DoMove();
    void Stop();
    void Resume();

protected:
    virtual void ConstructL();
    CLivestock(CScene& aScene, const TPoint& aCell);

protected:
    TRect Rect() const;

private: // New functions
    static TInt TimerCallback( TAny* aPtr );
    TBool HitTest( TInt aX, TInt aY ) const;
    TInt CellX( TInt aX ) const;
    TInt CellY( TInt aY ) const;
    void UpdateCell();

protected: // Data
    CScene& iScene;
    TPoint iCell;
    TPoint iHead;
    enum TMovement
        {
        EMoveBottom,
        EMoveBottomLeft,
        EMoveBottomRight
        };
    TMovement iMovement;
    CPeriodic* iPeriodic;
    };

#endif // C_LIVESTOCK_H

// End of File