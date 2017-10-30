/* ====================================================================
 * File: FarmAppView.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <coemain.h>
#include <AknUtils.h>
#include <StringLoader.h>
#include <f32file.h>
#include <Farm.rsg>
#include "FarmAppView.h"
#include "Farm.pan"
#include "Scene.h"
#include "TouchEventFilter.h"
#include "Scorekeeper.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "Rollpacker.h"
#include "Stopwatch.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 50000;
_LIT( KFarmResourceFile, "\\resource\\apps\\farm.rsc" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFarmFactory::NewL
// Standard construction sequence
// ----------------------------------------------------------------------------
//
CFarmAppView* CFarmAppView::NewL(const TRect& aRect)
    {
    CFarmAppView* self = CFarmAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::NewLC
// ----------------------------------------------------------------------------
//
CFarmAppView* CFarmAppView::NewLC(const TRect& aRect)
    {
    CFarmAppView* self = new (ELeave) CFarmAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CFarmAppView
// ----------------------------------------------------------------------------
//
CFarmAppView::CFarmAppView()
    : iCoeEnv( *CCoeEnv::Static() ), iAudioOn( ETrue )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::~CFarmAppView
// ----------------------------------------------------------------------------
//
CFarmAppView::~CFarmAppView()
    {
    Stop(); // iPeriodic
    ReleaseBmpBuffer();
    delete iScene;
    delete iFactory;
    delete iEventFilter;
    delete iLivestockBuilder;
    delete iScorekeeper;
    delete iMenuButton;
    delete iStopwatch;
    delete iMainMenu;
    delete iRollpacker;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ConstructL
// ----------------------------------------------------------------------------
//
void CFarmAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    CreateBmpBufferL();

    iScene = CScene::NewL( *this, *iBmpBufferContext, aRect );

    iFactory = CFarmFactory::NewL( *this, *iScene );
    iFactory->Next();

    iLivestockBuilder = CLivestockBuilder::NewL( *iScene, *this );

    TSize cellSize( 
        iScene->HorizontalUnitLength(), 
        iScene->VerticalUnitLength() 
        );

    TRect rect;
    rect.iTl = TPoint( aRect.iTl.iX, aRect.Height() - cellSize.iHeight * 2 );
    rect.iBr = aRect.iBr;
    iScorekeeper = CScorekeeper::NewL( *iBmpBufferContext, rect, cellSize );
    iScorekeeper->Clear();

    iEventFilter = CTouchEventFilter::NewL( aRect, cellSize );
    iEventFilter->AddObserverL( *this );
    iEventFilter->Enable();

    iPeriodic = CPeriodic::NewL( CActive::EPriorityLow );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KDoDelayTimeout,
            KDoFrameUpdateTimeout,
            TCallBack( TimerCallback, this ) 
            );

    // Creates main menu
    CreateMainMenuL( EMainMenuStart );

    // Enable Drag Events.
    EnableDragEvents();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Draw
// Draw this application's view to the screen
// ----------------------------------------------------------------------------
//
void CFarmAppView::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context 
    CWindowGc& gc = SystemGc();
    
    // Gets the control's extent
    TRect rect = Rect();

    // Clears the screen
    gc.Clear(rect);
    }

// ----------------------------------------------------------------------------
// CFarmFactory::SizeChanged
// ----------------------------------------------------------------------------
//
void CFarmAppView::SizeChanged()
    {
    TRAP_IGNORE( CreateBmpBufferL() );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CFarmAppView::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( iMenuButton && iMenuButton->Rect().Contains( aPointerEvent.iPosition ) )
        {
        iMenuButton->HandlePointerEventL( aPointerEvent );
        return;
        }
    if ( iMainMenu && iMainMenu->Rect().Contains( aPointerEvent.iPosition ) )
        {
        iMainMenu->HandlePointerEventL( aPointerEvent );
        return;
        }
    if ( iRollpacker && iRollpacker->Rect().Contains( aPointerEvent.iPosition )  )
        {
        iRollpacker->HandlePointerEventL( aPointerEvent );
        return;
        }
    iEventFilter->Control().HandlePointerEventL( aPointerEvent );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CountComponentControls
// ----------------------------------------------------------------------------
//
TInt CFarmAppView::CountComponentControls() const
    {
    TInt count( 0 );
    if ( iMenuButton )
        {
        count++;
        }
    if ( iMainMenu )
        {
        count++;
        }
    if ( iRollpacker )
        {
        count++;
        }
    return count;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ComponentControl
// ----------------------------------------------------------------------------
//
CCoeControl* CFarmAppView::ComponentControl(TInt aIndex) const
    {
    __ASSERT_ALWAYS( aIndex == 0, Panic( EFarmBasicUi ) );
    if ( iMenuButton )
        return iMenuButton;
    if ( iMainMenu )
        return iMainMenu;
    if ( iRollpacker )
        return iRollpacker;
    return NULL;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::EventFilterEvent
// ----------------------------------------------------------------------------
//
void CFarmAppView::EventFilterEvent( const TPoint& aStart, const TPoint& aEnd )
    {
    iScene->Tap( aStart, aEnd );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::NewLivestock
// ----------------------------------------------------------------------------
//
void CFarmAppView::NewLivestock( CLivestock* aNewLivestock )
    {
    iScene->AppendLivestock( aNewLivestock );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Lairage
// ----------------------------------------------------------------------------
//
void CFarmAppView::Lairage( TLivestockType aType )
    {
    iScorekeeper->Append( aType );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Escape
// ----------------------------------------------------------------------------
//
void CFarmAppView::Escape( TLivestockType /*aType*/ )
    {
    // no matter what kinds of livestock was escaped
    // we all need to restart our game.
    CreateMainMenuL( EMainMenuRestart );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Mixup
// ----------------------------------------------------------------------------
//
void CFarmAppView::Mixup( TLivestockType /*aType*/ )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::HandleClickedL
// ----------------------------------------------------------------------------
//
void CFarmAppView::HandleClickedL()
    {
    if ( iMenuButton )
        {
        delete iMenuButton;
        iMenuButton = NULL;
        }
    
    if ( iStopwatch )
        {
        iTimeout = iStopwatch->Timeout();
        delete iStopwatch;
        iStopwatch = NULL;
        }

    CreateMainMenuL( EMainMenuResume );
    iLivestockBuilder->Stop();
    iScene->Stop();
    iScene->SetShade( EFalse );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::HandleMenuItemL
// ----------------------------------------------------------------------------
//
void CFarmAppView::HandleMenuItemL( TInt aMenuItem )
    {
    switch( aMenuItem )
        {
        case EFarmMenuStart:
            DoStartL();
            break;

        case EFarmMenuResume:
            DoResumeL();
            break;

        case EFarmMenuRestart:
            DoRestartL();
            break;

        case EFarmMenuAudioOn:
            DoAudioOnL();
            break;
        case EFarmMenuAudioOff:
            DoAudioOffL();
            break;

        case EFarmMenuRecord:
            // Do nothing for a being time.
            break;

        case EFarmMenuHelp:
            DoHelpL();
            break;

        case EFarmMenuQuit:
            {
            CEikAppUi* appUi 
                = static_cast<CEikAppUi*>( iCoeEnv.AppUi() );
            appUi->HandleCommandL( EEikCmdExit );
            }
            break;

        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CFarmFactory::FinishedL
// ----------------------------------------------------------------------------
//
void CFarmAppView::FinishedL()
    {
    delete iRollpacker;
    iRollpacker = NULL;

    iMainMenu = CMainMenu::NewL( *this, *iBmpBufferContext, MainMenuRect() );
    iMainMenu->SetContainerWindowL( *this );

    switch( iFirstItemId )
        {
        case EFarmMenuStart:
            CreateMainMenuL( EMainMenuStart );
            break;
        case EFarmMenuResume:
            CreateMainMenuL( EMainMenuResume );
            break;
        case EFarmMenuRestart:
            CreateMainMenuL( EMainMenuRestart );
            break;
        case EFarmMenuAudioOn:  // flowthru
        case EFarmMenuAudioOff: // flowthru
        case EFarmMenuRecord: // flowthru
        case EFarmMenuHelp: // flowthru
        case EFarmMenuQuit: // flowthru
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ExpiredL
// ----------------------------------------------------------------------------
//
void CFarmAppView::ExpiredL()
    {
    iFactory->Done();
    iFactory->Next();
    iStopwatch->SetLevel( iLevel );
    iStopwatch->SetTimeout( iTimeout );
    iStopwatch->Start();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Updated
// ----------------------------------------------------------------------------
//
void CFarmAppView::Updated()
    {
    iLevel = iFactory->Id();
    iTimeout = iFactory->Timeout();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::EndedL
// ----------------------------------------------------------------------------
//
void CFarmAppView::EndedL()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CFarmAppView::CreateBmpBufferL()
    {
    // If double buffer resouces has been created, 
    // release them at first.
    ReleaseBmpBuffer();

    // Create double buffer bitmap
    iBmpBuffer = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBmpBuffer->Create( Size(), EColor16MU ) );

    // Create double buffer graphics context
    iBmpBufferDevice = CFbsBitmapDevice::NewL( iBmpBuffer );
    User::LeaveIfError( iBmpBufferDevice->CreateContext( iBmpBufferContext ) );
    iBmpBufferContext->SetPenStyle( CGraphicsContext::ESolidPen );
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CFarmAppView::ReleaseBmpBuffer()
    {
    delete iBmpBufferContext;
    iBmpBufferContext = NULL;
    delete iBmpBufferDevice;
    iBmpBufferDevice = NULL;
    delete iBmpBuffer;
    iBmpBuffer = NULL;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Stop
// ----------------------------------------------------------------------------
//
void CFarmAppView::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;   
        }
    }

// ----------------------------------------------------------------------------
// CFarmFactory::DoFrame
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    DoDraw();
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBmpBuffer );
    Window().EndRedraw();
    DeactivateGc();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CFarmAppView::TimerCallback( TAny* aPtr )
    {
    CFarmAppView* self = static_cast<CFarmAppView*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::DoDraw
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoDraw()
    {
    iScene->DoDraw();
    iScorekeeper->DoDraw();

    if ( iMenuButton )
        iMenuButton->DoDraw();
    if ( iStopwatch )
        iStopwatch->DoDraw();
    if ( iMainMenu )
        iMainMenu->DoDraw();
    if ( iRollpacker )
        iRollpacker->DoDraw();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::MenuButtonRect
// ----------------------------------------------------------------------------
//
TRect CFarmAppView::MenuButtonRect() const
    {
    TRect clientRect( Rect() ), theRect;
    TSize margin;
    TInt horizLen( iScene->HorizontalUnitLength() );
    TInt vertLen( iScene->VerticalUnitLength() );
    TInt horizNbr( iScene->HorizontalUnitNumber() );
    TInt vertNbr( iScene->VerticalUnitNumber() );
    margin.iWidth = clientRect.Width() - horizLen * horizNbr;
    margin.iHeight = clientRect.Height() - vertLen * vertNbr;

    theRect.iTl.iX = clientRect.iBr.iX 
        - horizLen * 2
        - margin.iWidth / 2;
    theRect.iTl.iY = clientRect.iTl.iY
        - margin.iHeight / 2;

    theRect.SetSize( TSize( horizLen * 2, vertLen * 2 ) );

    return theRect;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::MainMenuRect
// ----------------------------------------------------------------------------
//
TRect CFarmAppView::MainMenuRect() const
    {
    TRect theRect, clientRect( Rect() );
    theRect.iTl.iX = clientRect.Width() / 3;
    theRect.iTl.iY = clientRect.Height() / 3;
    theRect.SetWidth( clientRect.Width() / 3 );
    theRect.SetHeight( clientRect.Height() / 3 );
    return theRect;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::AboutRect
// ----------------------------------------------------------------------------
//
TRect CFarmAppView::AboutRect() const
    {
    TRect theRect, clientRect( Rect() );
    theRect.iTl.iX = clientRect.iTl.iX;
    theRect.iTl.iY = clientRect.Height() / 4;
    theRect.SetWidth( clientRect.Width() );
    theRect.SetHeight( clientRect.Height() / 4 );
    return theRect;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::StopwatchRect
// ----------------------------------------------------------------------------
//
TRect CFarmAppView::StopwatchRect() const
    {
    TRect clientRect( Rect() ), theRect;
    TSize margin;
    TInt horizLen( iScene->HorizontalUnitLength() );
    TInt vertLen( iScene->VerticalUnitLength() );
    TInt horizNbr( iScene->HorizontalUnitNumber() );
    TInt vertNbr( iScene->VerticalUnitNumber() );
    margin.iWidth = clientRect.Width() - horizLen * horizNbr;
    margin.iHeight = clientRect.Height() - vertLen * vertNbr;

    theRect.iTl.iX = clientRect.iTl.iX + margin.iWidth / 2;
    theRect.iTl.iY = clientRect.iTl.iY + margin.iHeight / 2;

    theRect.SetSize( TSize( horizLen * 4, vertLen * 2 ) );

    return theRect;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CreateMainMenuL
// ----------------------------------------------------------------------------
//
void CFarmAppView::CreateMainMenuL( TMainMenuState aState )
    {
    delete iMainMenu;
    iMainMenu = NULL;
    iMainMenu = CMainMenu::NewL( *this, *iBmpBufferContext, MainMenuRect() );
    iMainMenu->SetContainerWindowL( *this );

    RFs& fs = iCoeEnv.FsSession();
    TFileName fileName( KFarmResourceFile );
    TInt err = CompleteWithAppPath( fileName );
    if ( err != KErrNotSupported )
        {
        User::LeaveIfError( err );
        }

    // Get the exact filename of the resource file
    BaflUtils::NearestLanguageFile( fs, fileName );

    // Check if the resource file exists or not
    if ( ! BaflUtils::FileExists( fs, fileName ) )
        {
        User::Leave( KErrNotFound );
        }

    TInt offset( 0 );
    TRAP( err, offset = iCoeEnv.AddResourceFileL( fileName ) );

    TResourceReader reader;

    switch( aState )
        {
        case EMainMenuStart:
            iCoeEnv.CreateResourceReaderLC( reader, R_FARM_MAINMENU_START );
            break;
        case EMainMenuResume:
            iCoeEnv.CreateResourceReaderLC( reader, R_FARM_MAINMENU_RESUME );
            break;
        case EMainMenuRestart:
            iCoeEnv.CreateResourceReaderLC( reader, R_FARM_MAINMENU_RESTART );
            break;
        default:
            break;
        }
    iMainMenu->ConstructFromResourceL( reader );

    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( offset );

    TMenuItem audioItem;
    HBufC* audioText( NULL );
    if ( !iAudioOn )
        {
        audioText = StringLoader::LoadLC( R_FARM_MAINMENU_AUDIO_ON );
        audioItem.iText.Append( *audioText );
        audioItem.iItemId = EFarmMenuAudioOn;
        User::LeaveIfError( iMainMenu->Append( audioItem ) );
        CleanupStack::PopAndDestroy();
        audioText = NULL;
        }
    else
        {
        audioText = StringLoader::LoadLC( R_FARM_MAINMENU_AUDIO_OFF );
        audioItem.iText.Append( *audioText );
        audioItem.iItemId = EFarmMenuAudioOff;
        User::LeaveIfError( iMainMenu->Append( audioItem ) );
        CleanupStack::PopAndDestroy();
        audioText = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CFarmFactory::DoStartL
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoStartL()
    {
    delete iMainMenu;
    iMainMenu = NULL;

    iMenuButton = 
        CMenuButton::NewL( *this, *iBmpBufferContext, MenuButtonRect() );
    iMenuButton->SetContainerWindowL( *this );

    iStopwatch = CStopwatch::NewL( *this, *iBmpBufferContext, StopwatchRect() );
    iStopwatch->SetLevel( iLevel );
    iStopwatch->SetTimeout( iTimeout );
    iStopwatch->Start();

    //iScene->SetShade( ETrue );

    iLivestockBuilder->Start();
    
    }

// ----------------------------------------------------------------------------
// CFarmFactory::DoResumeL
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoResumeL()
    {
    delete iMainMenu;
    iMainMenu = NULL;

    iMenuButton = 
        CMenuButton::NewL( *this, *iBmpBufferContext, MenuButtonRect() );
    iMenuButton->SetContainerWindowL( *this );

    iStopwatch = CStopwatch::NewL( *this, *iBmpBufferContext, StopwatchRect() );
    iStopwatch->SetLevel( iLevel );
    iStopwatch->SetTimeout( iTimeout );
    iStopwatch->Start();
    
    iScene->Resume();
    //iScene->SetShade( ETrue );

    iLivestockBuilder->Start();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::DoRestartL
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoRestartL()
    {
    /*
    delete iMainMenu;
    iMainMenu = NULL;
    
    iMenuButton = 
        CMenuButton::NewL( *this, *iBmpBufferContext, MenuButtonRect() );
    iMenuButton->SetContainerWindowL( *this );

    iStopwatch = CStopwatch::NewL( *this, *iBmpBufferContext, StopwatchRect() );
    iStopwatch->SetLevel( iLevel );
    iStopwatch->SetTimeout( iTimeout );
    iStopwatch->Start();
    iScene->Resume();
    iLivestockBuilder->Start();
    */
    }

// ----------------------------------------------------------------------------
// CFarmAppView::DoAudioOnL
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoAudioOnL()
    {
    iAudioOn = EFalse;
    TMenuItem menuItem;
    menuItem.iItemId = EFarmMenuAudioOff;
    HBufC* text = StringLoader::LoadLC( R_FARM_MAINMENU_AUDIO_OFF );
    menuItem.iText.Append( *text );
    iMainMenu->Remove( EFarmMenuAudioOn );
    User::LeaveIfError( iMainMenu->Append( menuItem ) );
    CleanupStack::PopAndDestroy();
    text = NULL;
    }

// ----------------------------------------------------------------------------
// CFarmAppView::DoAudioOffL
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoAudioOffL()
    {
    iAudioOn = ETrue;
    TMenuItem menuItem;
    menuItem.iItemId = EFarmMenuAudioOn;
    HBufC* text = StringLoader::LoadLC( R_FARM_MAINMENU_AUDIO_ON );
    menuItem.iText.Append( *text );
    iMainMenu->Remove( EFarmMenuAudioOff );
    User::LeaveIfError( iMainMenu->Append( menuItem ) );
    CleanupStack::PopAndDestroy();
    text = NULL;
    }

// ----------------------------------------------------------------------------
// CFarmAppView::DoHelpL
// ----------------------------------------------------------------------------
//
void CFarmAppView::DoHelpL()
    {
    iFirstItemId = (TFarmMenuIds)iMainMenu->At( 0 ).iItemId;
    delete iMainMenu;
    iMainMenu = NULL;
    iRollpacker = 
        CRollpacker::NewL( *iBmpBufferContext, AboutRect() );
    iRollpacker->SetContainerWindowL( *this );
    iRollpacker->SetObserver( this );

    HBufC* title = StringLoader::LoadLC( R_FARM_HELP_TITLE );
    iRollpacker->AddTextL( *title );
    CleanupStack::PopAndDestroy(); // title
    title = NULL;

    HBufC* about = StringLoader::LoadLC( R_FARM_HELP_ABOUT );
    iRollpacker->AddTextL( *about );
    CleanupStack::PopAndDestroy(); // about
    about = NULL;

    HBufC* contents = StringLoader::LoadLC( R_FARM_HELP_CONTENTS );
    iRollpacker->AddTextL( *contents );
    CleanupStack::PopAndDestroy(); // contents
    contents = NULL;

    HBufC* caution = StringLoader::LoadLC( R_FARM_HELP_CAUTION );
    iRollpacker->AddTextL( *caution );
    CleanupStack::PopAndDestroy(); // caution
    caution = NULL;

    iRollpacker->Start();
    }

// End of File
