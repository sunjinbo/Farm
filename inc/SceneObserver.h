/* ====================================================================
 * File: SceneObserver.h
 * Created: 01/22/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_SCENEOBSERVER_H
#define M_SCENEOBSERVER_H

// INCLUDES
#include <e32std.h>
#include "Livestock.hrh"

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MSceneObserver
    {
public: // New methods
    virtual void Lairage( TLivestockType aType ) = 0;
    virtual void Escape( TLivestockType aType ) = 0;
    virtual void Mixup( TLivestockType aType ) = 0;
    };

#endif // M_SCENEOBSERVER_H

// End of File
