//
//  EAGLView.m
//  DMA
//
//  Created by vorg on 2009-10-06.
//  Copyright 2009 Vorg. All rights reserved.
//

#import "GLView.h"
#import "GLApp.h"
#import "DirectMemoryAccess.h"

GLApp* app;

EAGLContext* context;
CAEAGLLayer* eaglLayer;

float osGetTime() {
	static double startTime = CFAbsoluteTimeGetCurrent();
	return CFAbsoluteTimeGetCurrent() - startTime;
}

void osRenderbufferStorage() {	
	[context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
}

void osPresentRenderbuffer() {
	[context presentRenderbuffer:GL_RENDERBUFFER];
}

extern const char* osLoadTextFile(const char* fileName) {
	NSString* fileNameString = [NSString stringWithCString:fileName length:strlen(fileName)];		
	NSString *filePathString = [[NSBundle mainBundle] pathForResource:[fileNameString stringByDeletingPathExtension] ofType:[fileNameString pathExtension]];  	
	const char* contents = (const char*)[[NSString stringWithContentsOfFile:filePathString encoding:NSUTF8StringEncoding error:nil] UTF8String];
	if (!contents) {
		NSLog(@"Failed to load file %s", fileName);
	}
	//[fileNameString release];
	//[filePathString release];
	return contents;	
}

unsigned char* osLoadImageFile(const char* fileName) {
	NSString* fileNameString = [NSString stringWithCString:fileName length:strlen(fileName)];		
	CGImageRef image;
	CGContextRef imageContext;
	GLubyte *imageData;
	size_t	width, height;
	
	image = [UIImage imageNamed:fileNameString].CGImage;
	
	if (image) {
		width = CGImageGetWidth(image);
		height = CGImageGetHeight(image);
		imageData = (GLubyte *) malloc(width * height * 4);
		imageContext = CGBitmapContextCreate(imageData, width, height, 8, width * 4, CGImageGetColorSpace(image), kCGImageAlphaPremultipliedLast);
		CGContextDrawImage(imageContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), image);
		CGContextRelease(imageContext);
	}
	else {
		NSLog(@"Failed to load file %s", fileName);
		return NULL;
	}
	return imageData;
}

@implementation GLView
+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
		eaglLayer = (CAEAGLLayer*)self.layer;
		eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		[EAGLContext setCurrentContext: context];
		
		//app = new GLApp();
		app = new DirectMemoryAccess();
		app->init();
		app->update();
		
		animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0)) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
		//NSString* fileName = @"basic.glsl";
//		NSString *filePath = [[NSBundle mainBundle] pathForResource:[fileName stringByDeletingPathExtension] ofType:[fileName pathExtension]];  
//		NSLog(@"%@", filePath);
//		NSString* str = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:nil];
//		NSLog(@"%@", str);
    }
    return self;
}


- (void)drawRect:(CGRect)rect {
    app->update();
}

- (void) drawView:(id)sender {
	app->update();	
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	CGPoint touchPos = [[touches anyObject] locationInView:self];
	app->onMouseDown(touchPos.x, touchPos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	CGPoint touchPos = [[touches anyObject] locationInView:self];
	app->onMouseMove(touchPos.x, touchPos.y);
}


- (void)dealloc {
	app->dispose();

	if ([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
	}	 
	
	[context release];
	context = nil;
	
	delete app;
    [super dealloc];
}


@end
