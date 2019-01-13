#ifndef EDITOR_H
#define EDITOR_H 

#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "buffer.h"

namespace el{
    class editor
    {
    private:
        int x;      // <! Posição do cursor na linha.
        int y;      // <! Posição do cursor na coluna.

        int commandX;   // <! Posição do cursor no modo ~COMMAND~.
        
        int i_inicial; // <! Scroll da tela na posição da Tela.

        char mode; // <! Modo da maquina de estados.

        el::buffer* buff;       // <! Ponteiro para a classe Buffer.
        std::string status;     // <! String para a mensagem da barra de status.
        std::string File;       // <! Nome do arquivo.

        /* <! Função para mover o cursor para cima.*/
        void moveUp();
        /* <! Função para mover o cursor para baixo.*/
        void moveDown();
        /* <! Função para mover o cursor para a esquerda.*/
        void moveLeft();
        /* <! Função para mover o cursor para a direita.*/
        void moveRight();

        // Função para deletar linha atual do cursor.
        void DeleteLine(){ buff->removeLine(y+i_inicial); }
        /* <! Função para deletar uma linha passada na entrada.
            @param i linha a ser deletada.
        */
        void DeleteLine( int i ){ buff->removeLine(i); }
        
        /* <! Abre arquivo.
            @param string com o nome do arquivo.
        */
        void openFile( std::string );
        /* <! Salva o arquivo Atual. */
        void savefile();
        /* <! Salva o arquivo.
            @param string com o nome do arquivo.
        */
        void savefile( std::string );

        /* <! Função do modo ~COMMAND~ para salvar. */
        void white();
        /* <! Função do modo ~COMMAND~ para abrir o arquivo. */
        void open();
        /* <! Função do modo ~COMMAND~ para inserir antes da linha desejada. */
        void insert();
        /* <! Função do modo ~COMMAND~ para inserir depois da linha desejada. */
        void applend();
        /* <! Função do modo ~COMMAND~ para Modifica a linha escolhida. */
        void modify();

        /* <! Função do modo ~COMMAND~ para editar a linha escolhida. */
        void edit();
        /* <! Função do modo ~COMMAND~ para Deleta linha desejada. */
        void Delete();
        /* <! Função do modo ~COMMAND~ para copiar uma ou mais linhas. */
        void Copy();
        /* <! Função do modo ~COMMAND~ para Colar uma ou mais linhas. */
        void Paste();
        /* <! Função do modo ~COMMAND~ para abrir o arquivo help.txt. */
        void help();
        /* <! Função do modo ~COMMAND~ para Sair do programa elis. */
        void quit();

    public:
        editor();       // <! Construtor
        editor( std::string );  // <! Construtor

        char getMode(){ return mode; } // <! Função para retornar estado.
        
        /* <! Checa a entrada dos caracteres. */
        void Input( int );
        /* <! Printa na tela o corpo do arquivo. */
        void PrintBuffer();
        /* <! Printa no fim da tela a barra de status. */
        void PrintStatusLine();
        /* <! Atualiza o status do programa. */
        void UpdateStatus();
    };


    editor::editor(){
        x = 5;      // <! Posição minima do cursor na linha.
        y = 0;      // <! Posição minima do cursor na tela.
        i_inicial = 0;    // <! Auxiliar para o scroll da tela.
        commandX = 0;   // <! Posicao do cursor na linha de comando no modo '~COMMAND~'.
        mode = 'n';     // <! inicia o ELIS no modo '~NORMAL~'.

        File = "";      // <! Nome do arquivo em branco.

        status = "~NORMAL~"; 

        buff = new el::buffer();    // <! constroi a classe buffer.
        buff->appendLine("");       // <! adiciona uma linha para aparecer na tela.
    }

    editor::editor( std::string fn ){

        x = 5;
        y = 0;
        i_inicial = 0;
        commandX = 0;
        mode = 'n';

        status = "~NORMAL~";
        File = fn;

        buff = new el::buffer();

        openFile( fn );     // <! Abre o arquivo passado como entrada.
    }

    void editor::UpdateStatus(){

        switch( mode ){
            case 'n': status = "~NORMAL~"; break;
            case 'i': status = "~INSERT~"; break;
            case ':': status = "~COMMAND~"; break;
            case 'H': status = "~HELP~"; break;      // <! Modo para exibir o manual do ELIS.
            case 'q': break;      // <! Modo para sair do programa.
            case 'Q': break;      // <! Modo para exibir a confirmação de saida do programa.
        }
    }

    void editor::Input( int c ){
        // Verifica se a entrada é uma KEY de direção para o cursor.
        switch( c ){
            case KEY_LEFT: moveLeft(); return;
            case KEY_RIGHT: moveRight(); return;
            case KEY_UP: moveUp(); return;
            case KEY_DOWN: moveDown(); return;
        }
        // Verifica qual o modo da maquina de estados.
        switch ( mode ){
            //Modo '~NORMAL~'.
            case 'n':
                switch(c){
                    // Troca o modo para '~INSERT~'.
                    case 'I':
                    case 'i': buff->CopyBuffer(); mode = 'i'; status = "~INSERT~"; break;
                    case 'j':case 'J': moveUp(); return;      // <! Move o crusor para cima usando a tecla 'J'.
                    case 'k':case 'K': moveDown(); return;    // <! Move o cursor para baixo usando a tecla 'K';
                    case 'u':case 'U': buff->PasteBuffer(); return;    // <! Executa o UNDO.
                    case ':':mode = ':'; status = "~COMMAND~"; break;  // <! Muda o modo para '~COMMAND~'.
                }
                break;
            // Modo '~COMMAND~'.
            case ':':
                // Verifica qual tecla foi clicada pelo usuario.
                switch(c){
                    case 27://<ESC>
                        mode = 'n'; // <! Retorna para o modo '~NORMAL~';
                        break;
                    // Tecla 'ENTER'.
                    case 10:
                    case KEY_ENTER:
                        // Verifica qual comando foi digitado pelo usuario.
                        switch(buff->commandLine[0]){
                            //White.
                            case 'w':
                            case 'W':
                                white();
                                break;
                            //Open
                            case 'o':
                            case 'O':
                                open();
                                break;
                            // Modify.
                            case 'm':
                            case 'M':
                                modify();
                                break;
                            // Edit.
                            case 'e':
                            case 'E':
                                edit();
                                break;
                            // Delete
                            case 'd':
                            case 'D':
                                Delete();
                                break;
                            // Copy
                            case 'c':
                            case 'C':
                                Copy();
                                break;
                            // Paste
                            case 'p':
                            case 'P':
                                Paste();
                                break;
                            //Help
                            case 'h':
                            case 'H':
                                help();
                                break;
                            // Insert
                            case 'i':
                            case 'I':
                                insert();
                                break;
                            //Applend
                            case 'a':
                            case 'A':
                                applend();
                                break;
                            //Quit
                            case 'q':
                            case 'Q':
                                quit();
                                break;
                            // Se o comando foi invalido ele so limpa a linha de comando e não executa nada.
                            default:
                                buff->commandLine.clear();
                                break;
                        }
                        commandX = 0; // <! volta o cursor para o inicio da linha de comando.
                        break;
                    //Delete / Backspace.
                    case 127:
                    case KEY_BACKSPACE:
                        if(commandX > 0){
                            buff->commandLine.erase(--commandX,1); // <! Apaga o ultimo caracter digitado.
                        }
                        break;
                    //Digita na linha de comando.
                    default:
                        buff->commandLine.insert(commandX,1,char(c)); //insere o caracter no Buffer da linha de comando.
                        commandX++;// <! move o cursor um caracter.
                        break;
                }
                break;
            // Modo '~INSERT~'.
            case 'i':
                // Verifica qual tecla foi clicada pelo usuario.
                switch( c ){
                    case 27://<ESC>
                        mode = 'n';  // <! Retorna para o Modo '~NORMAL~'.
                        break;
                    // Delete / Backspace
                    case 127:
                    case KEY_BACKSPACE:
                        // Se o cursor estiver no inicio da linha, ele remove uma linha
                        if( x == 5 && y > 0 ){
                            
                            x = buff->lines[y - 1+i_inicial].length()+5;

                            buff->lines[y - 1 + i_inicial] += buff->lines[y+i_inicial];

                            DeleteLine();
                            moveUp();
                        // Se o cursor estiver dentro da linha, remove um caracter.
                        }else if(x > 5){
                            --x;
                            buff->lines[y+i_inicial].erase(x-5,1);
                        }
                        break;
                    //Delete Caractere a frente.
                    case KEY_DC:
                        if( x == buff->lines[y+i_inicial].length()+5 && y != (buff->lines.size() - 1) ){
                            buff->lines[y+i_inicial] += buff->lines[y+1+i_inicial];
                            DeleteLine(y+1+i_inicial);
                        }else{
                            buff->lines[y+i_inicial].erase(x-5,1);
                        }
                        break;
                    //tecla 'ENTER'.
                    case KEY_ENTER:
                    case 10:
                        // Verifica se o cursor esta no meio da linha
                        if( x < buff->lines[y+i_inicial].length()+5){
                            //se tiver, move a parte depois do cursor para a linha seguinte.
                            buff->insertLine(buff->lines[y+i_inicial].substr( x-5, buff->lines[y+i_inicial].length() - (x-5)), y+1+i_inicial);
                            buff->lines[y+i_inicial].erase(x-5,buff->lines[y+i_inicial].length() - x+5);
                        //se Estiver no fim da linha
                        }else{
                            // Adiciona mais uma linha em branco.
                            buff->insertLine("",y+1+i_inicial);
                        }

                        x = 5; // <! o cursor vai para o inicio da linha seguinte.
                        moveDown(); // <! move o crusor para baixo.
                        break;
                        //Tecla Tab.
                    case KEY_BTAB:
                    case KEY_CTAB:
                    case KEY_STAB:
                    case KEY_CATAB:
                    case 9: //TAB
                        buff->lines[y+i_inicial].insert( x, 4, ' ');// <! adicona 4 espaços
                        x += 4; // <! move o cursor para frente 4 vezes.
                        break;
                    //Adiciona uma letra para o Buffer de texto.
                    default:
                        buff->lines[y+i_inicial].insert(x-5,1,char(c));
                        x++;
                        break;
                }
                break;
            //Modo '~HELP~'
            case 'H':
                switch(c){
                    case 27://<ESC>
                        buff->PasteBuffer(); // <! volta para o texto original.
                        File="";
                        x=5;
                        y=0;
                        i_inicial=0;
                        mode ='n'; // <! volta para o modo '~NORMAL~'.
                        break;
                }
                break;
            // Modo 'Aviso de arquivo não salvo'.
            case 'Q':
                switch(c){
                    //Se o usuario clicar 'y', sai do programa.
                    case 'y':
                    case 'Y':
                        mode = 'q';
                        break;
                    // Se usuario clicar 'n', ele retorna para o modo '~NORMAL~'.
                    case 'n':
                    case 'N':
                        mode = 'n';
                        break;
                }
                break;
            //Qualquer outro modo retorna para o modo normal.
            default:
                mode = 'n';
                break;
        }
    }

    void editor::moveLeft(){
        if( x-1 >= 5 ){
            x--;
            move(y,x);
        }
    }

    void editor::moveRight(){
        //move o crusor ate o fim da linha ou ate o fim da tela.
        if( x-5 < COLS && x-5 < buff->lines[y+i_inicial].length() ){
            x++;
            move(y,x);
        }
    }

    void editor::moveUp(){
        if( y-1 >= 0 ){
            y--;
        }
        if( x >= buff->lines[y+i_inicial].length() ){
            x = buff->lines[y+i_inicial].length()+5;
        }
        move( y , x );
    }

    void editor::moveDown(){
        if( y+1 < LINES-1 && y+1+i_inicial < buff->lines.size() ){
            y++;
        }
        if( x >= buff->lines[y+i_inicial].length() ){
            x = buff->lines[y+i_inicial].length()+5;
        }

        move( y , x );
    }

    void editor::PrintBuffer(){
        // Printa na tela o texto ate o fim da tela  - 1.
        for( int i(0); i < LINES-1; i++ ){
            // se o cursor estiver no fim da tela e ainda tiver texto a ser exibido,
            // faz o scroll para baixo.
            if(y == LINES-2 && i< buff->lines.size()){
                i_inicial++;
                y --;
            }
            // se o cursor estiver no topo da tela e ainda tiver texto,
            //  faz o scroll para cima.
            if(y == 0 && i_inicial>0){ i_inicial --; y++; }
            // Se tiver acabado o texto, mas ainda tem espaco na tela, coloca o sinal '~'.
            if( i+i_inicial >= buff->lines.size()){
                mvprintw( i , 0 , "~");
                
            }
            // Se ainda tive texto, coloca o texto do Buffer na tela.
            else{
                int temp = i_inicial + i;
                std::string n = std::to_string(temp);
                //Coloca o numero da linha.
                mvprintw(i , 0, n.c_str());
                clrtoeol(); // <! da um flush
                // Coloca o texto do Buffer na tela.
                mvprintw( i , 5 , buff->lines[i+i_inicial].c_str() );

                
            }
            clrtoeol();
        }
        move( y,x );// <! move o cursor.
    }

    void editor::PrintStatusLine(){
        // Se estiver no modo de aviso de saida.
        if( mode == 'Q'){
            attron( A_REVERSE );
            attron (A_BOLD);
            mvprintw( LINES-1, 0, "Arquivo não salvo, deseja continuar [y/n]: " );
            clrtoeol();
            attroff(A_REVERSE);
            attroff(A_BOLD);
        }
        // Se tiver no modo aviso de 'arquivo sem nome'.
        else if(mode == 'I'){
            attron( A_REVERSE );

            mvprintw( LINES-1, 0, "Arquivo sem nome" );
            clrtoeol();
            attroff(A_REVERSE);
        // Se tiver nos demais modos, coloca na tela o status e o nome do arquivo.
        }else{
            attron( A_BLINK );
            attron( A_BOLD );

            mvprintw( LINES-1, 0, status.c_str() );
            clrtoeol();
            // Se o arquivo não foi salvo, coloca um '+' antes do nome do arquivo.
            if(not buff->UndoBuffer.empty()){
                mvprintw( LINES-1, COLS - File.length()-1, "+" );
            clrtoeol();
            }
            // coloca na tela o nome do arquivo.
            mvprintw( LINES-1, COLS - File.length(), File.c_str() );
            clrtoeol();

            attroff(A_BLINK);
            attroff(A_BOLD);
        }

        // Se tiver no modo comando exibe a linha de comando.
        if(getMode() == ':'){
            mvprintw( LINES-1, 10, ": " );
            mvprintw( LINES-1, 12, buff->commandLine.c_str() );
        }
    }

    void editor::openFile( std::string fn ){

        File = fn;

        buff->lines.clear();
        std::ifstream file( fn.c_str() );

        if( file.is_open() ){
            
            while( not file.eof() ){
                std::string temp;

                std::getline( file, temp );
                buff->appendLine( temp );
            }
        }else{
            std::ofstream f(fn.c_str());
            f.close();
            buff->appendLine( "" );
        }

        y = 0;
        x = 5;
    }

    void editor::savefile(){
        if( File == "" ){
            mode = 'I';
            return;
        }
        std::ofstream f(File.c_str());
        if(f.is_open()){
            for(int i(0);i<buff->lines.size();i++){
                f << buff->lines[i] << std::endl;
            }
            buff->ClearBuffer();
        }
        f.close();
    }

    void editor::savefile( std::string fn ){
        if(File == ""){
            File = fn.c_str();
        }

        std::ofstream f(fn.c_str());
        if(f.is_open()){
            for(int i(0);i<buff->lines.size();i++){
                f << buff->lines[i] << std::endl;
            }
            
            buff->ClearBuffer();
        }
        f.close();
    }

    void editor::white(){
        buff->commandLine.erase(0,1);
        if(buff->commandLine.size()>1){
            savefile(buff->commandLine);
            mode = 'n';
        }else{
            savefile();
        }
        buff->commandLine.clear();
    }

    void editor::open(){
        buff->ClearBuffer();
        buff->commandLine.erase(0,1);
        
        if(buff->commandLine.size()>1){                  
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }

            openFile( buff->commandLine );
        }
        buff->commandLine.clear();
        mode = 'n';
    }

    void editor::insert(){
        buff->CopyBuffer();
        if(buff->commandLine.size() > 1){

            buff->commandLine.erase(0,1);
                            
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }
            int n = atoi(&buff->commandLine[0]);
            if(n < buff->lines.size()){
                y = n - 1;
            }
        }else{
            y-=1;
        }
        buff->commandLine.clear();
        mode = 'i';
    }

    void editor::applend(){
        buff->CopyBuffer();
        if(buff->commandLine.size() > 1){

            buff->commandLine.erase(0,1);
                            
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }
            int n = atoi(&buff->commandLine[0]);
                        
            if(n + 1 == buff->lines.size() ){
                buff->insertLine("",n+1);
            }

            y = n + 1;
            x = 5;
        }else{
            if(y + 1 == buff->lines.size() ){
                buff->insertLine("",y+1);
            }
            y+=1;
            x = 5;
        }
        buff->commandLine.clear();
        mode = 'i';
    }

    void editor::modify(){
        buff->commandLine.erase(0,1);
        if(buff->commandLine.size() > 1){
                                
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }

            int linha = atoi( &buff->commandLine[0] );
            i_inicial = 0;
            y = linha; 
            if( linha > LINES-2 ){
                i_inicial = linha - (LINES-2);
                y = LINES - 2;
            }
        }
        else{
            int linha = buff->lines.size();
            y = buff->lines.size()-1; 
                                
            if( linha > LINES-2 ){
                i_inicial = linha - (LINES-2);
                y = LINES-3;
            }

        }
        x = 5;
        buff->commandLine.clear();
        mode = 'n';
    }

    void editor::edit(){
        buff->CopyBuffer();
        buff->commandLine.erase(0,1);
        if(buff->commandLine.size() > 1){
                                
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }

            int linha = atoi( &buff->commandLine[0] );
            if(linha < buff->lines.size()){
                i_inicial = 0;
                y = linha; 
                if( linha > LINES-2 ){
                    i_inicial = linha - (LINES-2);
                    y = LINES - 2;
                }
            }
        }

        x = buff->lines[y+i_inicial].length()+5;
        buff->commandLine.clear();
        mode = 'i';
    }

    void editor::Delete(){
        buff->CopyBuffer();
        buff->commandLine.erase(0,1);
                                
        if(buff->commandLine.size() > 1 ){
            int n;
            int m = 0;
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }

            n = atoi( &buff->commandLine[0] );
            if(n < buff->lines.size()){
                if(buff->commandLine.size() > 1){
                    m = atoi( &buff->commandLine[2] );
                }

                if(m>0){

                    for(int i(0);i <= m-n;i++){
                        DeleteLine(n);
                    }
                }else{
                    DeleteLine(n);
                }
            }
        }else{
            DeleteLine(y+i_inicial);
        }

        buff->commandLine.clear();
        mode = 'n';
    }

    void editor::Copy(){
        buff->CopyLines.clear();
        buff->commandLine.erase(0,1);
                                
        if(buff->commandLine.size() > 1){
            int n;
            int m = 0;
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }

            n = atoi( &buff->commandLine[0] );
            if(n < buff->lines.size()){
                if(buff->commandLine.size() > 1){
                    m = atoi( &buff->commandLine[2] );
                }

                if(m>0){

                    for(/**/;n <= m;n++){
                        buff->CopyLine(n);
                    }
                }else{
                    buff->CopyLine(n);
                }
            }
        }else{
            buff->CopyLine(y+i_inicial);
        }

        buff->commandLine.clear();
        mode = 'n';
    }

    void editor::Paste(){
        buff->CopyBuffer();
        buff->commandLine.erase(0,1);
                                
        if(buff->commandLine.size() > 1){
            int n;
            while(buff->commandLine[0] == ' '){
                buff->commandLine.erase(0,1);
            }

            n = atoi( &buff->commandLine[0] );
            if(n < buff->lines.size()){
                if(n+1 >= buff->lines.size() ){
                    buff->insertLine("",n+1);
                }
                buff->PasteLine(n+1);
            }
        }else{
            if(y+i_inicial+1 >= buff->lines.size() ){
                buff->insertLine("",y+i_inicial+1);
            }
            buff->PasteLine(y+i_inicial+1);
        }
        buff->commandLine.clear();
    }

    void editor::help(){
        buff->CopyBuffer();
                                
        openFile("doc/help.txt");
                                
        buff->commandLine.clear();
        mode = 'H';
    }

    void editor::quit(){
        if(not buff->UndoBuffer.empty()){
            mode = 'Q';
        }else{
            mode = 'q';
        }
        buff->commandLine.clear();
    }
}
#endif
