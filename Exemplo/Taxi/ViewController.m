//
//  ViewController.m
//  Taxi
//
//  Created by Rodrigo Cai on 7/11/16.
//  Copyright © 2016 PagSeguro. All rights reserved.
//

#import "ViewController.h"
#import <PSWalletLib/PSWallet.h>

@interface ViewController () <PSWalletDelegate>
@property PSWallet *psWallet;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    //-- Instancia o PSWallet
    self.psWallet = [[PSWallet alloc] initWithParentViewController:self];
    self.psWallet.delegate = self;
    NSLog(@"PSWallet Version - %@", [self.psWallet version]);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)getMainCard:(id)sender {
    if (self.psWallet) {
        [self.psWallet getMainCard];
    }
}

- (IBAction)openCardList:(id)sender {
    if (self.psWallet) {
        [self.psWallet openCardList];
    }
}

- (IBAction)makePaymentForCartItens:(id)sender {
    if (self.psWallet && ![self.psWallet needLogin]) {
        PSWalletCartItem *i = [[PSWalletCartItem alloc] initWithName:@"Item 0"
                                                               value:@(1.0)
                                                            quantity:1];
        [self.psWallet makePaymentForCartItens:@[i]];
    }
}

- (IBAction)logout:(id)sender {
    if (self.psWallet) {
        [self.psWallet logout];
    }
}


#pragma mark - PSWallet Delegate Methods
//-- Cartão Principal
- (void)psWalletDidFinishGetUserMainCard:(PSWalletCard*)userMainCard{
    PSWalletCard *mainCard = userMainCard;
    
    self.psMainCardBrand.image = mainCard.brandImage;
    self.psMainCardLastDigits.text = mainCard.number;
}

- (void)psWalletDidFailUserMainCardWithError:(NSError *)error{
    NSLog(@"Erro ao obter cartão principal.");
}

//-- Pagamento
- (void)psWalletDidFinishPaymentWithSuccess:(NSDictionary *)success{
    NSLog(@"Transação finalizada com sucesso.");
}

- (void)psWalletDidFailPaymentWithError:(NSError *)error{
     NSLog(@"Erro - %li\nMensagem - %@", (long)error.code, error.userInfo[@"message"]);
}

@end
