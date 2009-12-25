//
//  EAGLView.h
//  DMA
//
//  Created by vorg on 2009-10-06.
//  Copyright 2009 Vorg. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface GLView : UIView {	
	NSTimer* animationTimer;
}

- (void) drawView:(id)sender;

@end
