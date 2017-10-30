/* ====================================================================
 * File: LivestockBuilder.h
 * Created: 01/20/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_LIVESTOCKBUILDER_H
#define C_LIVESTOCKBUILDER_H

// INCLUDS
#include <e32base.h>
#include "Livestock.hrh"

// FORWARD DECLARATIONS
class CLivestock;
class CScene;

class MLivestockBuilderObserver
    {
public: // callback function
    virtual void NewLivestock( CLivestock* aNewLivestock ) = 0;
    };

class CLivestockBuilder : public CBase
    {
public: // Two phase consturctor and destructor
    static CLivestockBuilder* NewL(CScene& aScene, MLivestockBuilderObserver& aObserver);
    virtual ~CLivestockBuilder();

public: // New functions
    void DoCreate();
    void Start();
    void Stop();

private: // Constructor
    void ConstructL();
    CLivestockBuilder(CScene& aScene, MLivestockBuilderObserver& aObserver);

private: // New functions
    static TInt TimerCallback( TAny* aPtr );
    TInt Rand( TInt aRange ) const;
    CLivestock* CreateLivestockL( TLivestockType aType );
    TPoint RandEntrancePosition() const;

private: // Data
    CScene& iScene;
    MLivestockBuilderObserver& iObserver;
    CPeriodic* iPeriodic; // Own
    };

#endif // C_LIVESTOCKBUILDER_H

// End of File
