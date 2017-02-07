![ps5.png](https://bitbucket.org/repo/4naLKz/images/1051242651-ps5.png)

# Guia de Integração #
* **
**Biblioteca iOS PagSeguro UOL - Checkout in App Manual de Uso**

* **
**Histórico de Versões**                                                                                      
- 0.0.1 : **Versão inicial**  - 13/07/2016
- 0.0.2 : **Atualização do SDK**  - 06/02/2017

* **

**Copyright**

Todos os direitos reservados. O UOL é uma marca comercial do UNIVERSO ONLINE S / A. O logotipo do UOL é uma marca comercial do UNIVERSO ONLINE S / A. Outras marcas, nomes, logotipos e marcas são de propriedade de seus respectivos proprietários.
As informações contidas neste documento pertencem ao UNIVERSO ONLINE S/A. Todos os direitos reservados. UNIVERSO ONLINE S/A. - Av. Faria Lima, 1384, 6º andar, São Paulo / SP, CEP 01452-002, Brasil.
O serviço PagSeguro não é, nem pretende ser comparável a serviços financeiros oferecidos por instituições financeiras ou administradoras de cartões de crédito, consistindo apenas de uma forma de facilitar e monitorar a execução das transações de comércio eletrónico através da gestão de pagamentos. Qualquer transação efetuada através do PagSeguro está sujeita e deve estar em conformidade com as leis da República Federativa do Brasil.
Aconselhamos que você leia os termos e condições cuidadosamente.

* **

**Aviso Legal**

O UOL não oferece garantias de qualquer tipo (expressas, implícitas ou estatutárias) com relação às informações nele contidas. O UOL não assume nenhuma responsabilidade por perdas e danos (diretos ou indiretos), causados por erros ou omissões, ou resultantes da utilização deste documento ou a informação contida neste documento ou resultantes da aplicação ou uso do produto ou serviço aqui descrito. O UOL reserva o direito de fazer qualquer tipo de alterações a quaisquer informações aqui contidas sem aviso prévio.

* **

**Visão Geral**

A biblioteca Checkout in App tem como foco auxiliar desenvolvedores que desejam prover em seus aplicativos toda a praticidade e segurança fornecida pelo PagSeguro no segmento de pagamentos móveis através de smartphones e tablets. Para ajudar a entender como a biblioteca pode ser utilizada, apresentamos o seguinte cenário:

• Cenário Exemplo: Solução de pagamentos com Checkout in App. A empresa X desenvolve um aplicativo para seus clientes permitindo-os efetuar pagamento de serviços prestados ou itens (produtos) vendidos. Neste cenário o aplicativo da empresa X faz uso da biblioteca PagSeguro "Checkout in App" autorizando a Library com a sua conta PagSeguro (E-mail vendedor e Token referente da conta). Os clientes da empresa X que utilizam o aplicativo para realizar o pagamento em um ambiente seguro para autenticação do usuário utilizando uma conta PagSeguro (usuário comprador). Após autenticação o usuário do aplicativo da empresa X poderá realizar pagamentos utilizando sua conta PagSeguro(usuário comprador). A empresa X receberá os pagamentos em sua conta PagSeguro configurada como vendedor na Lib Checkout in App.

* **

**Conceitos Básicos**

Antes de fazer uso da biblioteca é importante que o desenvolvedor realize alguns procedimentos básicos, além de assimilar alguns conceitos importantes para o correto funcionamento de sua aplicação. É necessário ter em mãos o token da conta PagSeguro que será configurado como vendedor (Seller), tal token pode ser obtido no ibanking do PagSeguro. (Vide tópico abaixo).

* **

-Observação: Por favor, enviar e-mail para: checkoutinapp@uol.com.br , informando seu e-mail vendedor para que possamos liberar a funcionalidade para seu usuário.

* **

**Obtendo Token da conta PagSeguro**

Para realizar transações utilizando a biblioteca é necessária uma conta PagSeguro. Caso não tenha uma Acesse: www.pagseguro.com.br.
Com a conta PagSeguro criada é necessário ter o Token da conta que será utilizada na configuração como vendedor na Library Checkout in App.

OBTENDO TOKEN DA CONTA PAGSEGURO PARA INTEGRAÇÃO COM API's

Na pagina do ibanking do PagSeguro em sua conta:

1- Click na guia **"Minha Conta"**;

2- No Menu lateral clique em **"Preferências"**;

3- Pressione o botão **"Gerar Token"**;

4- Armazene esse **TOKEN** em algum lugar pois iremos utilizá-lo a seguir nesse guia de integração.

* **
## **1 - Instalação** ##

**Obs: Os trechos utilizados nesta documentação foram retirados da aplicação de exemplo disponível nesse repositório.**


A biblioteca possui dois arquivos:

* `PSWalletLib-Resources.bundle`: possui os arquivos de imagens utilizadas pela biblioteca;

* `PSWalletLib.framework`: é o binário da biblioteca, a partir de onde serão realizada as chamadas.

Para instalar, copie os dois arquivos para o seu projeto no Xcode.

* **
## **2 - Configuração do info.plist** ##

Adicionar a liberação para segurança de tráfego de dados

```html

<key>NSAppTransportSecurity</key>
<dict>
<key>NSAllowsArbitraryLoads</key>
<true/>
</dict>
```

* **
## **3 - Adicionar os frameworks padrões** ##

No projeto faça a importação dos seguintes Frameworks:

* `Accelerate.framework`
* `AudioToolbox.framework`
* `AVFoundation.framework`
* `CoreMedia.framework`
* `MobileCoreServices.framework`
* `SystemConfiguration.framework`

* **
## **4 - Configurações do projeto** ##

Targets -> Build Settingns -> Header Search Paths

Adicionar :
* $(PROJECT_DIR)/PSWalletLib.framework/Headers

* **

Targets -> Build Settingns -> Other Linker Flags

Adicionar:
* -lc++
* -ObjC
* -all_load

* **
## **5 - Configurações AppDelegate** ##

Antes de utilizar os demais métodos da biblioteca é de extrema importância passar as configurações para inicialização da Lib Checkout in App.

Configuração de inicialização da Lib:

• (NSString) Email (E-mail da conta que será utilizado como vendedor);

• (NSString) withToken (Token da conta que será utilizado como vendedor, foi explicado anteriormente nessa documentação como obter esse token);

• (NSString) appName (Nome do aplicativo);

```objective-c

#import "AuthorizationLib.h"

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)
launchOptions {

    [[AuthorizationLib sharedManager] setEmail:@"exemplo@bol.com.br" 
    withToken:@"10291902189212891289"
    appName:@"App Name"];

return YES;
}
```

* **
## **6 - Configurações ViewController** ##

* Importar a classe PSWallet
```objective-c
#import "PSWallet.h"
```
* **
* Injetar PSWalletDelegate como delegate da classe.
```objective-c

@interface VTViewController : UIViewController <PSWalletDelegate>
```
* **
* Criar uma instância da classe PSWallet
```objective-c

@property PSWallet *psWallet;
```
* **
* Imagem para mostrar bandeira do cartão 
```objective-c

@property (weak, nonatomic) IBOutlet UIImageView *mainCardBrandImageView;
```
* **
* Mostrar os últimos dígitos do cartão 
```objective-c

@property (weak, nonatomic) IBOutlet UILabel *mainCardLastDigitsLabel;
```
* **
* Botão para selecionar o cartão principal
```objective-c

@property (weak, nonatomic) IBOutlet UIButton *mainCardButton;
```
* **
* Campo texto para informar o valor do pagamento 

```objective-c

@property (weak, nonatomic) IBOutlet UITextField *paymentValueTextField;
```
* **
* Objeto que contém o cartão principal 

```objective-c
@property PSWalletCard *userMainCard;

```
* **
* Métodos executados pelo controlador da classe UIViewController

```objective-c

-(void)viewDidLoad{
//-- Library
    if (!self.psWallet) {
        self.psWallet = [[PSWallet alloc] initWithParentViewController:self];
        self.psWallet.delegate = self;
    }
}

- (void)viewDidAppear:(BOOL)animated{
    if (self.psWallet) {
        if ([self.psWallet needLogin]) {
            [self clearUserMainCard];
        }
    }
}
```
* **
* Método getMainCard retornar o cartão principal do usuário no delegate “psWalletDidFinishGetUserMainCard”, este método sempre retornara apenas um cartão ou uma mensagem de erro. 
```objective-c

- (IBAction)getMainCardTouched:(UIButton *)sender {
    if (self.psWallet) {
        [self.psWallet getMainCard];
    }
}
```
* **
* Abre a lista de cartões para o usuário escolher algum ou adicionar um novo cartão.
```objective-c

- (IBAction)openCardList:(UIButton *)sender {
    [self.psWallet openCardList];
}
```
* **
* Logout app 
```objective-c

- (IBAction)doLogout:(UIButton *)sender {
    [self clearUserMainCard];
    [self.psWallet logout];
}
```
* **
* Método para pagamento após ter selecionado um cartão 

```objective-c
- (IBAction)makePaymentTouched:(id)sender {
    if (self.userMainCard) {
    //-- START PAYMENT
        NSNumber * value =    [NSNumber numberWithFloat:1.00] ;

        PSWalletCartItem *item = [[PSWalletCartItem alloc] initWithName:@"Item 0" 
        value:value quantity:1];

        [self.psWallet makePaymentForCartItens:@[item]]; 
    }
}


- (void)setupMainCardWithCard:(PSWalletCard*)userMainCard{
    if (userMainCard != nil) {
        self.mainCardBrandImageView.image = userMainCard.brandImage;
        self.mainCardLastDigitsLabel.text = userMainCard.number;
        self.mainCardButton.selected = YES;
        self.mainCardLastDigitsLabel.textColor = [UIColor whiteColor];
    }
}

- (void)clearUserMainCard{
    self.userMainCard = nil;
    self.mainCardBrandImageView.image = nil;
    self.mainCardLastDigitsLabel.text = @"";
    self.mainCardButton.selected = NO;
    self.mainCardLastDigitsLabel.textColor = [UIColor blackColor];
}

- (void)userMainCardSelected:(BOOL)selected{
    self.mainCardButton.selected = selected;
    self.mainCardLastDigitsLabel.textColor = selected ? 
    [UIColor whiteColor] : [UIColor blackColor];
}

#pragma mark - PSWalletDelegate

- (void)psWalletDidFinishGetUserMainCard:(PSWalletCard *)userMainCard{
    if (userMainCard.number==nil) {
        [self clearUserMainCard];
    }else{
        self.userMainCard = userMainCard;
    [self setupMainCardWithCard:userMainCard];
    }
}

- (void)psWalletDidFailUserMainCardWithError:(NSError *)error{
    self.userMainCard = nil;
}

```

* **
**Código de Erros**

Abaixo seguem os códigos de erro que podem ser retornados pela biblioteca:

**1009** - SESSION_EXPIRED (Sessão expirada, refaça a operação e realize login novamente.);

**9000** - NETWORK_ERROR (Falha de conexão);

**9001** - REFUSED_TRANSACTION_ERROR (Transação cancelada ou recusada);

**9002** - CREATE_TRANSACTION_ERROR (Falha ao criar transação);

**9003** - TIME_OUT_CHECK_TRANSACTION (Timeout verificação status da transação);

**9004** - CHECK_TRANSACTION_ERROR (Falha na verificação da transação);

**9005** - TIME_OUT_CHECK_TRANSACTION_VALIDATOR (Timeout verificação status da transação validadora);

* **

**UOL - O melhor conteúdo**

© 1996-2017 O melhor conteúdo. Todos os direitos reservados.
UNIVERSO ONLINE S/A - CNPJ/MF 01.109.184/0001-95 - Av. Brigadeiro Faria Lima, 1.384, São Paulo - SP - CEP 01452-002 
<hr>
