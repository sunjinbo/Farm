/* ====================================================================
 * File: Pig.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_PIG_H
#define C_PIG_H

// INCLUDS
#include "Livestock.h"

// FORWARD DECLARATIONS
class CBmpUtils;

class CPig : public CLivestock
    {
public:
    static CPig* NewL(CScene& aScene,const TPoint& aCell);
    virtual ~CPig();

public: // New functions
    virtual void DoDraw();
    virtual TLivestockType Type() const;

private:
    virtual void ConstructL();
    CPig(CScene& aScene,const TPoint& aCell);


private: // Data
    CBmpUtils* iUtils;
    TBool iFirstIcon;
    };

#endif // C_PIG_H

// End of File

