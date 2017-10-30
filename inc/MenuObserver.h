/* ====================================================================
 * File: MenuObserver.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_MENUOBSERVER_H
#define M_MENUOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MMenuObserver
    {
public: // New methods
    virtual void HandleMenuItemL( TInt aMenuItem ) = 0;
    };

#endif // M_MENUOBSERVER_H

// End of File
