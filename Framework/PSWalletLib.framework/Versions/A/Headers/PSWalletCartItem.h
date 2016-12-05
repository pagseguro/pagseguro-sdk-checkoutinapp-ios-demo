//
//  PSWalletCartItem.h
//  PSWalletLib
//
//  Created by Rodrigo Cai on 6/27/16.
//  Copyright © 2016 PagSeguro. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PSWalletCartItem : NSObject
@property NSString      *itemName;
@property NSNumber      *itemValue;
@property NSInteger     itemQuantity;

- (id)initWithName:(NSString *)name value:(NSNumber*)value quantity:(NSInteger)quantity;
@end
