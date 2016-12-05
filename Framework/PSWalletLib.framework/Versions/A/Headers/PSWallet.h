//
//  PSWallet.h
//  PSWalletLib
//
//  Created by Rodrigo Cai on 6/22/16.
//  Copyright © 2016 PagSeguro. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "PSWalletCard.h"
#import "AuthorizationLib.h"
#import "PSWalletCartItem.h"

/*
 1009 - SESSION_EXPIRED (Sessão expirada, refaça a operação e realize login novamente.);
 9000 - NETWORK_ERROR (Falha de conexão);
 9001 - REFUSED_TRANSACTION_ERROR (Transação cancelada ou recusada);
 9002 - CREATE_TRANSACTION_ERROR (Falha ao criar transação);
 9003 - TIME_OUT_CHECK_TRANSACTION (Timeout verificação status da transação);
 9004 - CHECK_TRANSACTION_ERROR (Falha na verificação da transação);
*/

@protocol PSWalletDelegate <NSObject>
@optional
- (void)psWalletDidFinishGetUserMainCard:(PSWalletCard *_Nullable)userMainCard;
- (void)psWalletDidFailUserMainCardWithError:(NSError *_Nullable)error;

- (void)psWalletDidFinishPaymentWithSuccess:(NSDictionary *_Nullable)success;
- (void)psWalletDidFailPaymentWithError:(NSError *_Nullable)error;
@end

@interface PSWallet : NSObject
NS_ASSUME_NONNULL_BEGIN
@property id<PSWalletDelegate> _Nullable delegate;
@property UIColor *_Nullable navigationBarColor;

- (void)getMainCard;
- (void)openCardList;
- (void)makePaymentForCartItens:(NSArray*)cartItens;
- (void)logout;
- (BOOL)needLogin;
- (NSString*)version;
-(void)updateUserMainCard;

- (instancetype)initWithParentViewController:(UIViewController*)parentViewController;


NS_ASSUME_NONNULL_END
@end
