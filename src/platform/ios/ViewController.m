//
//  ViewController.m
//  ISBench
//
//  Created by Konrad Kołakowski on 14.09.2018.
//  Copyright © 2018 One Minute Games. All rights reserved.
//

#import "ViewController.h"

#import "platform.h"
#import "platform_ios.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UITextView *terminalTextView;
@property (weak, nonatomic) IBOutlet UIButton *startButton;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.startButton.layer.cornerRadius = 8.0;
}

- (IBAction)startBenchmarking:(id)sender {
    self.terminalTextView.text = [NSString string]; // "clear" terminal
    
    ios_terminal_text_view = self.terminalTextView;
    
    self.startButton.enabled = FALSE;
    
    // start on a separate thread to keep UI active
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
        bench_main(0, NULL);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            self.startButton.enabled = TRUE;
        });
    });
}

@end
