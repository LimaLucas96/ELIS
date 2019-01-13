#include <ncurses.h>
#include <string>

#include "../include/editor.h"

/* <! Função para iniciar o NCurses. */
void curses_init(){
    initscr();      // <! inicia NCurses.
    noecho();       // <! entada de caracter
    cbreak();       // <! Remove buffer e printa imediatamente na tela o caracter.

    keypad(stdscr,true);  // <! autoriza a entrada de KEYS.
}

int main(int argc, char const *argv[])
{    
    el::editor ed;  //Constroi a Classe editor.

    std::string fn = ""; 
    //verfica se foi passado um arquivo na linha de comando.
    if( argc > 1 ){
        
        fn = argv[1];
        ed = el::editor(fn); //constroi uma Classe com o segundo contrutor
    }else{
        ed = el::editor();
    }

    curses_init(); //inicia o ncurses.

    while( ed.getMode() != 'q' ){ //enquanto o maquina de estado não for 'q' faça:
        ed.UpdateStatus();  // <! atualiza o status do programa.
        ed.PrintStatusLine();   // <! Pinta a barra de estado.

        ed.PrintBuffer();       // <! Printa o texto do arquivo.

        int input = getch();    // <! Recebe o caracter de digitado pelo usuario.

        ed.Input( input );      // <! Le o caracter digitado.
        
    }

    refresh();    // <! atualiza o ncurses.
    endwin();     // <! redefine o terminal para fechar o ncurses.

    return 0;
}
