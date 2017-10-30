/* ====================================================================
 * File: FarmApplication.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __FARM_APPLICATION_H__
#define __FARM_APPLICATION_H__

// INCLUDS
#include <aknapp.h>


/*! 
  @class CFarmApplication
  
  @discussion An instance of CFarmApplication is the application part of the AVKON
  application framework for the Farm example application
  */
class CFarmApplication : public CAknApplication
    {
public:  // from CAknApplication

/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CAknApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __FARM_APPLICATION_H__

// End of File
