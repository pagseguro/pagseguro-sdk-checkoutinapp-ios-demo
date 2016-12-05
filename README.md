![ps5.png](https://bitbucket.org/repo/4naLKz/images/1051242651-ps5.png)

## Sobre o Checkout In-App

O objetivo dessa biblioteca do PagSeguro é fornecer um modo de pagamento para o usuário sem que ele saia do seu aplicativo. Através do login ou cadastro de uma conta no PagSeguro e o cadastro de um cartão, o usuário já estará habilitado para realizar pagamentos dentro da app a hora que quiser.

## Instalação

A biblioteca possui dois arquivos:

* `PSWalletLib-Resources.bundle`: possui os arquivos de imagens utilizadas pela biblioteca;
* `PSWalletLib.framework`: é o binário da biblioteca, a partir de onde serão realizada as chamadas.

Para instalar, copie os dois arquivos para o seu projeto no Xcode.

###Frameworks
No projeto faça a importação dos seguintes Frameworks:

* `Accelerate.framework`
* `AudioToolbox.framework`
* `AVFoundation.framework`
* `CoreMedia.framework`
* `MobileCoreServices.framework`
* `SystemConfiguration.framework`

###Flags
Em `Build Settings`, `Other Linker Flags` adicione:

* `-lc++`
* `-ObjC`
* `-all_load`


## Configuração

Para utilizar a biblioteca, primeiro você deve utilizar a classe `AuthorizationLib` para configurar suas informações de acesso:

```objectivec
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
	[[AuthorizationLib sharedManager] setEmail:@"my@email.com" withToken:@"123ABC" appName:@"My App Name"];
	
	return YES;
}
```

Depois, crie uma instância da classe `PSWallet`:

```objectivec
-(void)viewDidLoad{
   	[super viewDidLoad];
	self.psWallet = [[PSWallet alloc] initWithParentViewController:self];
   	self.psWallet.delegate = self;
}
```

Os itens para pagamento e seus respectivos valores são referenciados através da `PSWalletCartItem`:

```objectivec
PSWalletCartItem *item = [[PSWalletCartItem alloc] initWithName:@"Item 0" value:self.value quantity:1];
```

## Utilização

### Requisição do cartão

Os métodos disponíveis para requisitar o cartão que o usuário irá utilizar e exibir na interface do seu aplicativo são os seguintes:

`- (void)getMainCard;`

Retorna o cartão principal do usuário no delegate `psWalletDidFinishGetUserMainCard:`. Esse método irá sempre retornar apenas um cartão ou exibir uma mensagem de erro.

`- (void)openCardList;`

Abre a lista de cartões para o usuário escolher algum ou adicionar um novo cartão.

### Pagamento

`- (void)makePaymentForCartItens:(NSArray*)cartItens;`

O parâmetro `cartItens` é um `NSArray` de objetos do `PSWalletCartItem` com os itens que serão cobrados do usuário. Após realizar a chamada do método, é necessário esperar o retorno em algum dos seguintes delegates para saber o resultado final do pagamento.

Pagamento realizado com sucesso:

`- (void)psWalletDidFinishPaymentWithSuccess:(NSDictionary *_Nullable)success;`

Estutura do objeto de sucesso:

```objectivec
{
     date = "yyyy-MM-dd'T'HH:mm:ss.SSSz";
     status = APPROVED;
     transactionCode = "XXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX";
}
```

Ocorreu algum erro com o pagamento:
	
`- (void)psWalletDidFailPaymentWithError:(NSError *_Nullable)error;`

A propriedade `userInfo` do `NSError` irá retornar um `NSDictionary` com a seguinte estrutura:

```objectivec
{
  message: "Transação cancelada ou recusada"
}
```

### Códigos de Erro
* **1009** - `SESSION_EXPIRED (Sessão expirada, refaça a operação e realize login novamente.)`
* **9000** - `NETWORK_ERROR (Falha de conexão)`
* **9001** - `REFUSED_TRANSACTION_ERROR (Transação cancelada ou recusada)`
* **9002** - `CREATE_TRANSACTION_ERROR (Falha ao criar transação)`
* **9003** - `TIME_OUT_CHECK_TRANSACTION (Timeout verificação status da transação)`
* **9004** - `CHECK_TRANSACTION_ERROR (Falha na verificação da transação)`


### Logout
`- (void)logout;`

Destrói a sessão ativa.

### Verificar a necessidade de login
`- (BOOL)needLogin;`


### Versão
`- (NSString*)version;`

Retorna a versão do framework.

* **

**UOL - O melhor conteúdo**

© 1996-2016 O melhor conteúdo. Todos os direitos reservados.
UNIVERSO ONLINE S/A - CNPJ/MF 01.109.184/0001-95 - Av. Brigadeiro Faria Lima, 1.384, São Paulo - SP - CEP 01452-002 
* **