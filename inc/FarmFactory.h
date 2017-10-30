/* ====================================================================
 * File: FarmFactory.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_FARMFACTORY_H
#define C_FARMFACTORY_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class TResourceReader;
class CScene;
class CFarmLevel;
class CCoeEnv;

class MFactoryObserver
    {
public:
    virtual void Updated() = 0;
    virtual void EndedL() = 0;
    };

class CFarmFactory : public CBase
    {
public:
    static CFarmFactory* NewL(MFactoryObserver& aObserver, CScene& aScene);
    virtual ~CFarmFactory();

public: // New functions
    void Next();
    void Restore();
    void Done();
    TInt Id() const;
    TInt Score() const;
    TInt Bonus() const;
    TInt Timeout() const;

private:
    void ConstructL();
    CFarmFactory(MFactoryObserver& aObserver,CScene& aScene);

private:
    void ReadLevelL( TResourceReader& aReader );
    void Sort();

private: // Data
    CCoeEnv& iCoeEnv;
    MFactoryObserver& iObserver;
    CScene& iScene;
    RPointerArray<CFarmLevel> iFarmLevelArray;
    TInt iCurrentLevel;
    TInt iResFileOffset;
    };

#endif // C_FARMFACTORY_H

// End of File
