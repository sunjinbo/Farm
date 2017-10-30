/* ====================================================================
 * File: Scene.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCENE_H
#define C_SCENE_H

// INCLUDS
#include <e32base.h>
#include "Livestock.hrh"

// FORWARD DECLARATIONS
class CFbsBitGc;
class CFence;
class CLivestock;
class CBmpUtils;
class MSceneObserver;


class CScene : public CBase
    {
public:
    static CScene* NewL(MSceneObserver& aObserver, CFbsBitGc& aGc, const TRect& aRect);
    virtual ~CScene();

public: // New functions
    void Tap( const TPoint& aStart, const TPoint& aEnd );
    TBool HasBarrier( TInt aX, TInt aY );
    CFbsBitGc& Gc();
    void DoDraw();
    const TRect& ClientRect() const;
    TInt VerticalUnitNumber();
    TInt HorizontalUnitNumber();
    TInt VerticalUnitLength();
    TInt HorizontalUnitLength();
    void AppendFence( CFence* aFence );
    void AppendLivestock( CLivestock* aLivestock );
    void FenceUpdated( const CFence& aFence );
    void LivestockUpdated( const CLivestock& aLivestock );
    void ResetAll();
    void Stop();
    void Resume();
    void SetShade( TBool aShade );

private:
    void ConstructL();
    CScene(MSceneObserver& aObserver, CFbsBitGc& aGc, const TRect& aRect);

private: // New functions
    void DrawBackground();
    void DrawWickiup();
    void DrawFence();
    void DrawLivestock();
    void DrawShade();
    void GetTapCells( RArray<TPoint>& aCells, const TPoint& aStart, const TPoint& aEnd );
    TBool Intersects( const RArray<TPoint>& aFirst, const RArray<TPoint>& aSecond ) const;
    TInt Find( const CLivestock& aLivestock, TInt& aIndex ) const;
    TBool IsInWickiup( const TPoint& aLivestockCell ) const;
    TRect RectForShade() const;

private: // Data
    MSceneObserver& iObserver;
    CFbsBitGc& iGc;
    RPointerArray<CFence> iFenceArray;
    RPointerArray<CLivestock> iLivestockArray;
    CBmpUtils* iUtils;
    TRect iRect;
    TRect iClientRect;
    TPoint iWickiup[ELivestockLastElement];
    TBool iShade;
    };

#endif // C_SCENE_H

// End of File
