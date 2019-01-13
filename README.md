#Pojeto ElIS(**E**_ditor de Textos orientado a_ **LI**_nha_**S**)

## Descrição

Um dos primeiros tipos de programas para editar textos eram orientados a linhas, ou seja, editava-se uma linha por vez. Tais editores, denominados de editores orientado a linhas, possuíam uma interface com usuário bem restrita mas, por outro lado, eram bem versáteis e adequados aos terminais textuais típicos da época do surgimento do computador.
Posteriormente, estes editores evoluíram para os chamados editores de página cheia. Mesmo assim, a influência dos primeiros editores de linhas foi tamanha que ainda hoje um dos editores preferidos pela comunidade de programadores, o vi ou vim, ainda utiliza uma sintaxe de comandos bem similar aos antigos editores de linhas.

## Maquina de estados

O programa tera tres estados: '~INSERT~', '~COMMAND~' e '~NORMAL~'.

### Comandos do modo '~COMMAND~':
```
	W [<name>]	|Write. Salva todas as linhas do texto em um arquivo ascii name. O comando sem o fornecimento de um nome simplesmente grava o texto no
	arquivo atual. Se o nome do arquivo atual ainda não foi fornecido o programa deve solicitar um nome ao usuário.
	O <name>	| Open. Lê para a memória todas as linhas de texto do arquivo ascii name. Se o arquivo indicado não existir um novo arquivo vazio name deve ser criado.
	I [n]		|Entra no modo de edição, permitindo a inserção de texto antes da linha 'n'. Se 'n' não é fornecido, o texto é inserido antes da linha atual.
	A [n]		|Entra no modo de edição, permitindo a inserção de texto depois da linha 'n'. Se 'n' não é fornecido, o texto é inserido depois da linha atual.
	M [n]		|Torna 'n' a linha atual. Se 'n' não é fornecido então a última linha do texto passa a ser a atual.
	E [n]		|Edita a linha 'n', posicionando o cursor no final da linha. A edição será básica, suportando apenas o uso do <backspace> para apagar os caracteres da linha.
	D [n [m]]	|Remove linhas 'n' até 'm'. Se apenas 'n' é fornecido, remove-se a linha 'n'. Se nenhum número é fornecido, remove-se a linha atual.
	C [n [m]]	|Copia as linhas 'n' até 'm' para um buffer. Se apenas 'n' é fornecido, copia-se a linha 'n'. Se nenhum número é fornecido, copia-se a linha atual.
	P [n]		|Cola (inserindo) as linhas atualmente armazenada no buffer depois da linha 'n', permanecendo no modo de comando. Se nenhum número é fornecido, as linhas serão coladas logo após a linha atual.
	H 			|Exibe um texto de ajuda, explicando de forma resumida quais são os comandos do programa.
	Q 			|Encerra o programa. Se o texto atual não tiver sido salvo, o programa deve exibir uma mensagem indicando o fato e confirmar a operação.
	<ESC>		|Volta para o modo normal ('~ NORMAL ~').

```

### Comandos do modo '~NORMAL~':
```
	K 		|Navega para a linha de cima, se existir. A linha atual acompanha a movimentação.
	J		|Navega para a linha de baixo, se existir. A linha atual acompanha a movimentação.
	U 		|Desfaz os últimos comandos realizados desde a última gravação do arquivo.
	I 		|Ativa o modo edição ('~ INSERT ~').
	:		|Ativa o modo comando ('~ COMMAND ~').

```
## Compilação
```
	~/elis$ make
```

## Execução sem arquivo
```
	~/elis$ ./elis
```

## Execução com arquivo
```
	~/elis$ ./elis [nome_do_arquivo]
```

## Autor
```
	Lucas Lima Marques de Oliveira( e-mail: l.lima19@hotmail.com )
```