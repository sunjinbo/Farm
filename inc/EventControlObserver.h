/* ====================================================================
 * File: EventControlObserver.h
 * Created: 01/18/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef __EVENTCONTROLOBSERVER_H
#define __EVENTCONTROLOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MEventControlObserver
    {
public: // New methods
    virtual void EventControlEvent( const TPoint& aStart, const TPoint& aEnd ) = 0;
    };

#endif // __EVENTCONTROLOBSERVER_H

// End of File
