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
		return NULL;
	}
	return contents;	
}

unsigned char* osLoadImageFile(const char* fileName, unsigned int* width, unsigned int *height) {
	NSString* fileNameString = [NSString stringWithCString:fileName length:strlen(fileName)];		
	CGImageRef image;
	CGContextRef imageContext;
	GLubyte *imageData;
	size_t	w, h;
	
	image = [UIImage imageNamed:fileNameString].CGImage;
	
	if (image) {
		w = CGImageGetWidth(image);
		h = CGImageGetHeight(image);
		*width = w;
		*height = h;
		NSLog(@"Image w:%d h:%d", w, h);
		imageData = (GLubyte *) malloc(w * h * 4);
		imageContext = CGBitmapContextCreate(imageData, w, h, 8, w * 4, CGImageGetColorSpace(image), kCGImageAlphaPremultipliedLast);
		CGContextDrawImage(imageContext, CGRectMake(0.0, 0.0, (CGFloat)w, (CGFloat)h), image);
		CGContextRelease(imageContext);
		return imageData;
	}
	else {	
		*width = 0;
		*height = 0;
		return NULL;
	}	
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
		
		[self setMultipleTouchEnabled:TRUE];
		
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
	app->onMouseDown(touchPos.x, touchPos.y, [touches count]);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	CGPoint touchPos = [[touches anyObject] locationInView:self];
	app->onMouseMove(touchPos.x, touchPos.y, [touches count]);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	CGPoint touchPos = [[touches anyObject] locationInView:self];
	app->onMouseMove(touchPos.x, touchPos.y, [touches count]);
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
