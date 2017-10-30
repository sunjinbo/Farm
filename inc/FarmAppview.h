/* ====================================================================
 * File: FarmAppView.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __FARM_APPVIEW_H__
#define __FARM_APPVIEW_H__

// INCLUDE FILES
#include <coecntrl.h>
#include "Farm.hrh"
#include "EventFilterObserver.h"
#include "LivestockBuilder.h"
#include "FarmFactory.h"
#include "SceneObserver.h"
#include "ButtonObserver.h"
#include "MenuObserver.h"
#include "RollpackerObserver.h"
#include "StopwatchObserver.h"

// FORWARD DECLARATIONS
class CScene;
class CTouchEventFilter;
class CLivestock;
class CScorekeeper;
class CMenuButton;
class CMainMenu;
class CRollpacker;
class CStopwatch;
class CCoeEnv;

/*! 
  @class CFarmAppView
  
  @discussion An instance of the Application View object for the Farm 
  example application
  */
class CFarmAppView : public CCoeControl, 
    public MEventFilterObserver, 
    public MLivestockBuilderObserver,
    public MSceneObserver,
    public MButtonObserver,
    public MMenuObserver,
    public MRollpackerObserver,
    public MStopwatchObserver,
    public MFactoryObserver
    {
public:

/*!
  @function NewL
   
  @discussion Create a CFarmAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CFarmAppView
  */
    static CFarmAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CFarmAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CFarmAppView
  */
    static CFarmAppView* NewLC(const TRect& aRect);


/*!
  @function ~CFarmAppView
  
  @discussion Destroy the object and release all memory objects
  */
    virtual  ~CFarmAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CFarmAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  
    void SizeChanged();

    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    TInt CountComponentControls() const;

    CCoeControl* ComponentControl(TInt aIndex) const;

public: // From MEventFilterObserver
    void EventFilterEvent(  const TPoint& aStart, const TPoint& aEnd );

public: // From MLivestockBuilderObserver
    void NewLivestock( CLivestock* aNewLivestock );

public: // From MSceneObserver
    void Lairage( TLivestockType aType );
    void Escape( TLivestockType aType );
    void Mixup( TLivestockType aType );

public: // From MButtonObserver
    void HandleClickedL();

public: // From MMenuObserver
    void HandleMenuItemL( TInt aMenuItem );

public: // From MRollpackerObserver
    void FinishedL();

public: // From MStopwatchObserver
    void ExpiredL();

public: // From MFactoryObserver
    void Updated();
    void EndedL();

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CFarmAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CFarmAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CFarmAppView();

private: // New functions
    
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    void Stop();
    void DoFrame();
    static TInt TimerCallback( TAny* aPtr );
    void DoDraw();
    TRect MenuButtonRect() const;
    TRect MainMenuRect() const;
    TRect AboutRect() const;
    TRect StopwatchRect() const;
    enum TMainMenuState
        {
        EMainMenuStart,
        EMainMenuResume,
        EMainMenuRestart
        };
    void CreateMainMenuL( TMainMenuState aState );
    void DoStartL();
    void DoResumeL();
    void DoRestartL();
    void DoAudioOnL();
    void DoAudioOffL();
    void DoHelpL();

private: // Member data
    CCoeEnv& iCoeEnv;
    CPeriodic* iPeriodic; // Own
    CFbsBitmap* iBmpBuffer; // Own
    CFbsBitmapDevice* iBmpBufferDevice; // Own
    CFbsBitGc* iBmpBufferContext; // Own
    CScene* iScene; // Own
    CFarmFactory* iFactory; // Own
    CTouchEventFilter* iEventFilter; // Own
    CLivestockBuilder* iLivestockBuilder; // Own
    CScorekeeper* iScorekeeper; // Own
    CMenuButton* iMenuButton; // Own
    CStopwatch* iStopwatch; // Own
    CMainMenu* iMainMenu; // Own
    CRollpacker* iRollpacker; // Own
    TBool iAudioOn;
    TInt iTimeout;
    TInt iLevel;
    TFarmMenuIds iFirstItemId;
    };

#endif // __FARM_APPVIEW_H__

// End of File
