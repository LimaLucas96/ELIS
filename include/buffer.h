#ifndef BUFFER_H
#define BUFFER_H 

#include <string>
#include <stack>
#include <vector>
#include <stdlib.h>

namespace el{

	class buffer
	{
	public:
		buffer(){ /*empty*/ }  // <! Construtor
		
		std::vector<std::string> lines;		// <! Buffer com o o texto do arquivo.
		std::vector<std::string> CopyLines; 	// <! Buffer para as linhas a ser copiadas.
		std::string commandLine;	// <! Buffer para a função COMMAND.
		std::stack< std::vector<std::string> > UndoBuffer;	// <! Buffer para usar o comando UNDO.

		/* <! Função para inserir uma linha no buffer lines.
			@param string a ser inserida na linha.
			@param int para a linha desejada.
		*/
		void insertLine( std::string , int );
		/* <! Função para inserir no fim do buffer lines.
			@param string com os caracteres a ser inseridos.
		*/
		void appendLine( std::string );

		/* <! Remove a linha desejada.
			@param int a linha a ser removida.
		*/
		void removeLine( int );
		/* <! Função para copiar a linha escolhida.
			@param int linha a ser copiada.
		*/
		void CopyLine( int );
		/* <! Função para colar na linha desejada.
			@param int linha a ser colada o buffer.
		*/
		void PasteLine( int );
		
		/* <! Função para copiar uma o texto para o buffer 'UndoBuffer'. */
		void CopyBuffer();
		/* <! Função para Colar uma do buffer 'UndoBuffer' para o buffer lines. */
		void PasteBuffer();
		/* <! Função para limpar o buffer 'UndoBuffer'. */
		void ClearBuffer();

		std::string remTabs( std::string ); // <! remove os TABS do arquivo.
		
	};

	std::string buffer::remTabs( std::string l ){

		int tab = l.find( "\t" );

		if( tab == l.npos ){
			
			return l;

		}else{
			
			return remTabs( l.replace( tab, 1, "    "));

		}
	}

	void buffer::insertLine( std::string l, int n ){

		l = remTabs( l );
		lines.insert( lines.begin() + n, l );
	}

	void buffer::appendLine( std::string l ){

		l = remTabs( l );

		lines.push_back( l );
	}

	void buffer::removeLine( int n ){

		lines.erase( lines.begin() + n );
	}

	void buffer::CopyLine( int n ){

		CopyLines.push_back(lines[n]);

	}

	void buffer::PasteLine( int n ){
		int temp = CopyLines.size();
		for(int i(0);i < temp;i++){
			insertLine(lines[n+i], n+i+1);

			removeLine(n+i);
			insertLine(CopyLines[i],n+i);
		}
	}

	void buffer::CopyBuffer(){
		UndoBuffer.push( lines );
	}

	void buffer::PasteBuffer(){
		if(not UndoBuffer.empty()){
			lines.clear();
			lines = UndoBuffer.top();
			UndoBuffer.pop();
		}
	}

	void buffer::ClearBuffer(){
		while(!UndoBuffer.empty()){
			UndoBuffer.pop();
		}
	}
}

#endif