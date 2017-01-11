/*
 * CocosBuilder: http://www.cocosbuilder.com
 *
 * Copyright (c) 2011 Viktor Lidholt
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#import <Cocoa/Cocoa.h>
#import "cocos2d.h"
#import "PSMTabBarControl.h"

#import "CHCSVParser.h"

#define kCCBNumCanvasDevices 12

enum {
    kCCBCanvasSizeCustom = 0,
    kCCBCanvasSizeIPhoneLandscape,
    kCCBCanvasSizeIPhonePortrait,
    kCCBCanvasSizeIPhone5Landscape,
    kCCBCanvasSizeIPhone5Portrait,
    kCCBCanvasSizeIPadLandscape,
    kCCBCanvasSizeIPadPortrait,
    kCCBCanvasSizeAndroidXSmallLandscape,
    kCCBCanvasSizeAndroidXSmallPortrait,
    kCCBCanvasSizeAndroidSmallLandscape,
    kCCBCanvasSizeAndroidSmallPortrait,
    kCCBCanvasSizeAndroidMediumLandscape,
    kCCBCanvasSizeAndroidMediumPortrait,
};

enum {
    kCCBBorderDevice = 0,
    kCCBBorderTransparent,
    kCCBBorderOpaque,
    kCCBBorderNone
};

enum {
    kCCBAlignHorizontalCenter,
    kCCBAlignVerticalCenter,
    kCCBAlignLeft,
    kCCBAlignRight,
    kCCBAlignTop,
    kCCBAlignBottom,
    kCCBAlignAcross,
    kCCBAlignDown,
    kCCBAlignSameWidth,
    kCCBAlignSameHeight,
    kCCBAlignSameSize,
};

enum {
    kCCBArrangeBringToFront,
    kCCBArrangeBringForward,
    kCCBArrangeSendBackward,
    kCCBArrangeSendToBack,
};


@class CCBDocument;
@class ProjectSettings;
@class CCBHTTPServer;
@class AssetsWindowController;
@class PlugInManager;
@class ResourceManager;
@class ResourceManagerPanel;
@class ResourceManagerOutlineHandler;
@class CCBGLView;
@class CCBTransparentWindow;
@class CCBTransparentView;
@class WarningsWindow;
@class TaskStatusWindow;
@class CCBPublisher;
@class CCBWarnings;
@class SequencerHandler;
@class SequencerScrubberSelectionView;
@class MainWindow;
@class PlayerConsoleWindow;
@class HelpWindow;
@class APIDocsWindow;
@class MainToolbarDelegate;
@class PlayerConnection;
@class CCBSplitHorizontalView;
@class AboutWindow;
@class ResourceManagerPreviewView;
@class LabelTTFText;

//---jambam 추가
@class UploadResources;
//---

@interface CocosBuilderAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
{
    //---jambam 추가
    UploadResources* pUploadResources;
    NSString* uploadResPath;
    //---
    
    // Panel Views
    IBOutlet NSView* leftPanel;
    IBOutlet NSView* rightPanel;
    IBOutlet NSSegmentedControl *panelVisibilityControl;
    
    // Cocos2D view
    IBOutlet CCBGLView* cocosView;
    IBOutlet NSView* mainView;
    IBOutlet CCBSplitHorizontalView* splitHorizontalView;
    
    // Inspector views
    IBOutlet NSScrollView* inspectorScroll;
    NSView* inspectorDocumentView;
    NSMutableDictionary* currentInspectorValues;
    
    IBOutlet NSToolbar* toolbar;
    MainToolbarDelegate* toolbarDelegate;
    
    // Tabs
    IBOutlet PSMTabBarControl* tabBar;
    NSTabView* tabView;
    
    // Inspector componentes
    IBOutlet NSComboBox* inspectorSpriteName;
    IBOutlet NSTextView* inspectorLabelBMFontString;
    BOOL canEditContentSize;
    BOOL canEditCustomClass;
    
    BOOL lockedScaleRatio;
    
    // Outline view heirarchy
    SequencerHandler* sequenceHandler;
    IBOutlet NSOutlineView* outlineHierarchy;
    IBOutlet SequencerScrubberSelectionView* scrubberSelectionView;
    IBOutlet NSTextField* timeDisplay;
    IBOutlet NSSlider* timeScaleSlider;
    IBOutlet NSScroller* timelineScroller;
    IBOutlet NSScrollView* sequenceScrollView;
    
    // Selections
    NSMutableArray* loadedSelectedNodes;
    NSMutableArray* selectedNodes;
    
    // Menus
    IBOutlet NSMenu* menuCanvasSize;
    IBOutlet NSMenu* menuCanvasBorder;
    IBOutlet NSMenu* menuResolution;
    IBOutlet NSMenu* menuContextKeyframe;
    IBOutlet NSMenu* menuContextKeyframeInterpol;
    IBOutlet NSMenu* menuContextResManager;
    
    IBOutlet NSPopUpButton* menuTimelinePopup;
    IBOutlet NSMenu* menuTimeline;
    IBOutlet NSTextField* lblTimeline;
    
    IBOutlet NSPopUpButton* menuTimelineChainedPopup;
    IBOutlet NSMenu* menuTimelineChained;
    IBOutlet NSTextField* lblTimelineChained;

    CGSize defaultCanvasSizes[kCCBNumCanvasDevices+1];
    IBOutlet NSMenuItem* menuItemStageCentered;
    BOOL defaultCanvasSize;
    
    IBOutlet NSMenuItem* menuItemJSControlled;
    IBOutlet NSMenuItem* menuItemSafari;
    IBOutlet NSMenuItem* menuItemChrome;
    IBOutlet NSMenuItem* menuItemFirefox;
    
    // Resource manager
    ResourceManager* resManager;
    IBOutlet NSView* previewViewContainer;
    NSView* previewView;
    ResourceManagerPreviewView* previewViewOwner;
    IBOutlet NSSplitView* resourceManagerSplitView;
    
    //ResourceManagerPanel* resManagerPanel;
    
    // Project
    ProjectSettings* projectSettings;
    
    // Project display
    IBOutlet NSOutlineView* outlineProject;
    ResourceManagerOutlineHandler* projectOutlineHandler;
    
    // Documents
    NSMutableArray* delayOpenFiles;
    CCBDocument* currentDocument;
    BOOL hasOpenedDocument;
    
    // PlugIns (nodes)
    PlugInManager* plugInManager;
    
    // Guides
    BOOL showGuides;
    BOOL snapToGuides;
    
    // Sticky notes
    BOOL showStickyNotes;
    
    // Transparent window for components on top of cocos scene
    CCBTransparentWindow* guiWindow;
    CCBTransparentView* guiView;
    
    // Warnings
    WarningsWindow* publishWarningsWindow;
    NSString* errorDescription;
    
    // Modal status window
    TaskStatusWindow* modalTaskStatusWindow;
    
    // Player
    PlayerConnection* connection;
    PlayerConsoleWindow* playerConsoleWindow;
    
    // Help window
    HelpWindow* helpWindow;
    APIDocsWindow* apiDocsWindow;
    
    // About window
    AboutWindow* aboutWindow;
    
    // Animation playback
    BOOL playingBack;
    double playbackLastFrameTime;
    
    // JavaScript bindings
    BOOL jsControlled;
    
    //haru - export/import csv 관련 변수들
    CHCSVParser *csvParser;
    NSMutableArray* ttfText_list;
    LabelTTFText* ttfText;
    int nodeSeq;
    BOOL isSearchBreak;
    BOOL isCCBSave;
    
@private
    MainWindow *window;
    
}

@property (assign) IBOutlet MainWindow *window;

@property (nonatomic,readonly) IBOutlet NSOutlineView* outlineProject;


@property (nonatomic,readonly) ResourceManager* resManager;
@property (nonatomic,retain) CCBDocument* currentDocument;
@property (nonatomic,assign) BOOL hasOpenedDocument;
@property (nonatomic,readonly) CCBGLView* cocosView;

@property (nonatomic,assign) BOOL canEditContentSize;
@property (nonatomic,assign) BOOL defaultCanvasSize;
@property (nonatomic,assign) BOOL canEditCustomClass;

@property (nonatomic,readonly) CCNode* selectedNode;

@property (nonatomic,retain) NSArray* selectedNodes;
@property (nonatomic,readonly) NSMutableArray* loadedSelectedNodes;

@property (nonatomic,assign) BOOL showGuides;
@property (nonatomic,assign) BOOL snapToGuides;
@property (nonatomic,assign) BOOL showStickyNotes;

@property (nonatomic,readonly) CCBTransparentView* guiView;
@property (nonatomic,readonly) CCBTransparentWindow* guiWindow;

@property (nonatomic,readonly) IBOutlet NSMenu* menuContextKeyframe;
@property (nonatomic,readonly) IBOutlet NSMenu* menuContextKeyframeInterpol;
@property (nonatomic,readonly) IBOutlet NSMenu* menuContextResManager;
@property (nonatomic,readonly) NSSegmentedControl *panelVisibilityControl;

@property (nonatomic,retain) ProjectSettings* projectSettings;
@property (nonatomic,readonly) PlayerConnection* connection;

@property (nonatomic,copy) NSString* errorDescription;

// Transparent window
- (void) resizeGUIWindow:(NSSize)size;

// PlugIns and properties
@property (nonatomic,readonly) PlugInManager* plugInManager;
- (void) refreshProperty:(NSString*) name;

// Methods
+ (CocosBuilderAppDelegate*) appDelegate;

- (void) updateTimelineMenu;
//---jambam test
//-(void) sequenceHandlerUpdate;
//---
- (void) updateInspectorFromSelection;
- (void) switchToDocument:(CCBDocument*) document;
- (void) closeLastDocument;
- (void) openFile:(NSString*) fileName;
- (void) openJSFile:(NSString*) fileName;
- (void) openJSFile:(NSString*) fileName highlightLine:(int)line;
- (void) resetJSFilesLineHighlight;

//haru - 복사/붙여넣기를 할때, animatableProperties의 SeqID를 현재 SeqID로 업데이트 한다. 모든 자식노드도...
- (void) updateAnimatablePropertiesSeqID:(CCNode*)node;

// Menu options
- (void) dropAddSpriteNamed:(NSString*)spriteFile inSpriteSheet:(NSString*)spriteSheetFile at:(CGPoint)pt parent:(CCNode*)parent;
- (void) dropAddSpriteNamed:(NSString*)spriteFile inSpriteSheet:(NSString*)spriteSheetFile at:(CGPoint)pt;
- (void) dropAddCCBFileNamed:(NSString*)ccbFile at:(CGPoint)pt parent:(CCNode*)parent;

- (IBAction)menuTimelineSettings:(id)sender;

- (IBAction) menuNudgeObject:(id)sender;
- (IBAction) menuMoveObject:(id)sender;

- (IBAction) menuSelectBehind:(id)sender;
- (IBAction) menuDeselect:(id)sender;

- (void) closeProject;
- (IBAction) performClose:(id)sender;

- (BOOL) addCCObject:(CCNode *)obj toParent:(CCNode*)parent atIndex:(int)index;
- (BOOL) addCCObject:(CCNode *)obj toParent:(CCNode*)parent;
- (BOOL) addCCObject:(CCNode*)obj asChild:(BOOL)asChild;
- (void) addPlugInNodeNamed:(NSString*)name asChild:(BOOL) asChild;
- (void) deleteNode:(CCNode*)node isMove:(BOOL)isMove;
- (IBAction) pasteAsChild:(id)sender;
- (IBAction) menuQuit:(id)sender;

- (int) orientedDeviceTypeForSize:(CGSize)size;
- (IBAction)menuEditCustomPropSettings:(id)sender;
- (void) updateStateOriginCenteredMenu;
- (IBAction) menuSetStateOriginCentered:(id)sender;
- (void) updateCanvasBorderMenu;
- (IBAction) menuSetCanvasBorder:(id)sender;
- (IBAction) menuZoomIn:(id)sender;
- (IBAction) menuZoomOut:(id)sender;

//haru - 언어선택시 호출
- (IBAction) selectedLanguage:(id)sender;
//- (void) setLanguageForNode:(CCNode*)node language:(_LanguageType)language;

- (IBAction)menuCreateSmartSpriteSheet:(id)sender;
- (IBAction)menuEditSmartSpriteSheet:(id)sender;

- (IBAction) pressedZoom:(id)sender;
- (IBAction) pressedToolSelection:(id)sender;
- (IBAction) pressedPanelVisibility:(id)sender;

- (IBAction) menuOpenResourceManager:(id)sender;
- (void) reloadResources;
- (IBAction)menuAddStickyNote:(id)sender;
- (IBAction) menuCleanCacheDirectories:(id)sender;
- (IBAction)menuAbout:(id)sender;

// Undo / Redo
- (void) updateDirtyMark;
- (void) saveUndoState;
- (void) saveUndoStateWillChangeProperty:(NSString*)prop;

- (IBAction) undo:(id)sender;
- (IBAction) redo:(id)sender;

- (IBAction) debug:(id)sender;

//haru - 현재 모든 리소스중를 모든 ccb에 검색을 해서 사용중인 리소스인지 확인하는 메뉴
- (IBAction) menuCheckUsingImage:(id)sender;

- (BOOL) searchResourceInCCB:(NSString*) dir subPath:(NSString*) subPath resDict:(NSDictionary*)resDict;
- (void) parseSpriteResource:(NSDictionary*)rootNode resDict:(NSDictionary*)resDict;
- (void) checkResourceList:(NSString*)spriteSheetFileName spriteFileName:(NSString*)spriteFileName resDict:(NSDictionary*)resDict;
- (BOOL) searchAllSpriteResource:(NSString*) dir subPath:(NSString*) subPath resDict:(NSMutableDictionary*)resDict;

//haru - 모든 ccb를 검색해서 누락된 이미지를 리포팅
- (IBAction) menuCheckMissingImage:(id)sender;

- (BOOL) searchMissingResourceInCCB:(NSString*) dir subPath:(NSString*) subPath resDict:(NSDictionary*)resDict missingDict:(NSMutableDictionary*)missingDict;
- (void) parseMissingSpriteResource:(NSString*) filePath rootNode:(NSDictionary*)rootNode resDict:(NSDictionary*)resDict missingDict:(NSMutableDictionary*)missingDict;
- (void) checkMissingResourceList:(NSString*) filePath spriteSheetFileName:(NSString*)spriteSheetFileName spriteFileName:(NSString*)spriteFileName resDict:(NSDictionary*)resDict missingDict:(NSMutableDictionary*)missingDict;


//haru - labelTTF TEXT CSV로 export / import하는 메뉴
- (IBAction) menuExportTextCSV:(id)sender;
- (IBAction) menuImportTextCSV:(id)sender;

//haru - labelTTF TEXT를 CSV로 뽑아주는 함수. 로컬라이징 대응용
- (BOOL) exportCSV:(NSString*) dir subPath:(NSString*) subPath textList:(NSMutableArray*)textList;
- (void) parseLabelTTF:(NSDictionary*)rootNode filePath:(NSString*)filePath textList:(NSMutableArray*)textList;
- (BOOL) importCSV:(NSString*) dir;
- (void) setLabelTTF:(NSDictionary*)rootNode text:(LabelTTFText*) text;

// Publishing & running
- (void) publisher:(CCBPublisher*)publisher finishedWithWarnings:(CCBWarnings*)warnings;
- (IBAction)runProject:(id)sender;
- (IBAction) menuPublishProjectAndRun:(id)sender;
- (IBAction) menuPublishProjectAndRunInBrowser:(id)sender;

//---jambam
- (IBAction) menuPublishProject:(id)sender;
//---

// For warning messages
- (void) modalDialogTitle: (NSString*)title message:(NSString*)msg;

// Modal status messages (progress)
- (void) modalStatusWindowStartWithTitle:(NSString*)title;
- (void) modalStatusWindowFinish;
- (void) modalStatusWindowUpdateStatusText:(NSString*) text;


@end

@interface LabelTTFText : NSObject
{
}

@property (nonatomic, assign) NSString* filePath;
@property (nonatomic, assign) int seq;
@property (nonatomic, assign) NSString* string_en;
@property (nonatomic, assign) NSString* string_kr;
@property (nonatomic, assign) NSString* string_jp;
@property (nonatomic, assign) NSString* string_ch;

@end

@interface SpriteResource : NSObject
{
}

@property (nonatomic, assign) NSString* spriteSheetFileName;
@property (nonatomic, assign) NSString* spriteFileName;
@property (nonatomic, assign) BOOL isExist;

@end

@interface MissingSpriteResource : NSObject
{
}

@property (nonatomic, assign) NSString* ccbFileName;
@property (nonatomic, assign) NSString* spriteSheetFileName;
@property (nonatomic, assign) NSString* spriteFileName;

@end
