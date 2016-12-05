//
//  PSCard.h
//  PSWalletLib
//
//  Created by Rodrigo Cai on 6/22/16.
//  Copyright © 2016 PagSeguro. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface PSWalletCard : NSObject
@property NSString  *brand;
@property UIImage   *brandImage;
@property NSString  *number;

- (instancetype)initWithBrand:(NSString*)brand brandImageCode:(NSString*)brandImageCode number:(NSString*)number;
@end
