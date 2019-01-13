#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>
#include <iterator>

using size_type = size_t;

namespace ls{
template<typename T>
	
	/* <! Consists in the implementation of a double linked list using classes. */
	class list
	{
		private:
			/* <! Contains nodes previous, next adresses and it`s data. */
			struct Node{
				T data;     //<! Data field
				Node *prev; //<! Pointer to the previous node in the list.
				Node *next; //<! Pointer to the next node in the list.

				// <! basic constructor
				Node(const T & d = T(), Node * p = nullptr, Node * n = nullptr ):
				data(d),prev(p),next(n){ /*empty*/ }
			};

		public:
			/* <! A simple const_iterator class. */
			class const_iterator{
				public:

					typedef const T& const_reference;
					typedef Node* pointer;

					typedef std::ptrdiff_t difference_type;
					typedef std::forward_iterator_tag iterator_categoty;

					/* <! Default const_iterator initializer. */
					const_iterator() = default;

					/* <! Default const_iterator deferencier.
						@return value of it.
					*/
					const_reference operator*()const;
					/* <! Overload on the ++it operator.
						@return const_iterator in the it+1.
					*/
					const_iterator & operator++();   // ++it;
					/* <! Overload on the it++ operator.
						@return const_iterator in the it+1.
					*/
					const_iterator operator++(int);  // it++;
					/* <! Overload on the --it operator. 
						@return const_iterator in the it-1.
					*/
					const_iterator & operator--();   // --it;
					/* <! Overload on the it-- operator.
						@return const_iterator in the it-1.
					 */
					const_iterator operator--(int);  // it--;
					
					/* <! Overload on the it + add operator. 
						@param add int value.
						@return const_iterator in new position.
					*/
					const_iterator & operator+(int add);
					/* <! Overload on the it = rhs operator. */
					const_iterator* operator=(const const_iterator &rhs);
					/* <! Overload on the it - sub operator. 
						@param sub int value.
						@return const_iterator in new position.
					*/
					const_iterator & operator-(int sub);

					pointer operator->(){ return current; }

					/* <! Overload on the it == operator. 
						@param rhs other const_iterator.
						@return True if the const_iterators id iqual. False otherwise.
					*/
					bool operator== (const const_iterator &rhs) const;

					/* <! Overload on the it != operator. 
						@param rhs other const_iterator.
						@return True if the const_iterators is different. False otherwise.
					*/
					bool operator!= (const const_iterator &rhs) const;

				protected:
					pointer current;
					const_iterator(Node *p):current(p){ /*empty*/ };

					friend class list<T>;
			};

			class iterator : public const_iterator{
				public:

					typedef const T& const_reference;
					typedef T& reference;
					typedef Node* pointer;

					typedef std::forward_iterator_tag iterator_categoty;
					typedef std::ptrdiff_t difference_type;

					iterator() : const_iterator() { /*empty*/ }

					/* <! Default iterator deferencier.
						@return value of it.
					*/
					const_reference operator* () const;
					/* <! Default iterator deferencier.
						@return value of it.
					*/
					reference operator* ();
					
					/* <! Overload on the it + add operator. 
						@param add int value.
						@return iterator in new position.
					*/
					iterator & operator+(int add);
					
					/* <! Overload on the it - sub operator. 
						@param sub int value.
						@return iterator in new position.
					*/
					iterator & operator-(int sub);


					iterator& operator=(const iterator &rhs);

					/* <! Overload on the ++it operator.
						@return iterator in the it+1.
					*/
					iterator & operator++();

					/* <! Overload on the it++ operator.
						@return iterator in the it+1.
					*/
					iterator operator++(int);

					/* <! Overload on the it-- operator.
						@return iterator in the it-1.
					 */
					iterator & operator--();

					/* <! Overload on the it + add operator. 
						@param add int value.
						@return iterator in new position.
					*/
					iterator operator--(int);
					pointer operator->(){return this->current;}

					/* <! Overload on the it == operator. 
						@param rhs other iterator.
						@return True if the iterators id iqual. False otherwise.
					*/
					bool operator== (const iterator &rhs) const;

					/* <! Overload on the it != operator. 
						@param rhs other iterator.
						@return True if the iterators is different. False otherwise.
					*/
					bool operator!= (const iterator &rhs) const;

				protected:
					iterator (Node *p) : const_iterator(p){ /*empty*/ };

					friend class list<T>;
			};

			// [I] SPECIAL MEMBERS
			list();
			
			/* <! Constructs the list with default inserted instances.
				@param cont of the tipe size_type.
			*/
			explicit list(size_type cont);

			/* <! constructs the list with the contents of the range [first,last).
				@param first pointer first the range.
				@param last The pointer last the range.
			*/
			template<typename InputIt>
			list( InputIt, InputIt );

			/* <! Copy constructs. Constructs the list with the deep copy of other.
				@param other The other list.
			*/
			list( const list & );

			/* <! Cosntructs the list with the contents of the initializer list ilist. */
			list( std::initializer_list<T> );

			/* <! Destructs the list. */
			~list();

			/* <! Copy assigment operator. 
				@param other The other operator the type list.
			*/
			list & operator= ( const list & );

			/* <! Replaces the contents with those identified by initializer list.
				@param ilist.
			*/ 
			list & operator= ( std::initializer_list<T> );

			//[II] ITERATORS
			/* <! A normal iterator to begin of the list. 
				@return A iterator with the begin position.
			*/
			iterator begin();
			/* <! A constant iterator to the begin of the list.
				@return A constant iterator with the begin position.
			*/
			const_iterator cbegin() const;

			/* <! A normal iterator to the end of the list.
				@return A iterator with the end position.
			*/
			iterator end();

			/* <! A Constant iterator to the end of the list.
				@return A constant iterator with the end position.
			*/
			const_iterator cend() const;

			//[III] CAPACITY

			/* <! Return the number of elements in the list. */
			int size() const;
			/* <! Return True if the list is empty; Return False otherwise. */
			bool empty() const;

			//[IV] MODIFIERS

			/* <! Remove all elements in the list. */
			void clear();
			
			/* <! Returns the object at the begin of the list. */
			const T & front() const;
			
			/* <! Returns the object at the end of the list. */
			T & back();
			
			/* <! Returns the object at the end of the list. */
			const T & back() const;

			/* <! Add a value to the front of the list.
				@param const T& value : value to be added to the list.
			*/
			void push_front ( const T & value );

			/* <! Add a value to the end of the list.
				@param const T& value : Value to be added to the list.
			*/
			void push_back (const T & value );

			/* <! Remove the Object at the begin of the list. */
			void pop_front ();

			/* <! Remove the object at the end of the list. */
			void pop_back ();

			/* <! Replaces the content of the list with copies of values. 
				@param const T& value : The value to be added of the list.
			*/
			void assign (const T & value);

			//[IV-a] MODIFIERS WITH ITERATORS

			/* <! Replaces the contents of the list with copies of the elements in the range [first,last).
				@param InItr first : Pointer to the frist of the range.
				@param InItr last : Pointer to the last of the range.
			*/
			template< typename InItr>
			void assign(InItr first, InItr last);

			/* <! Replaces the contents of the list with elements from the initializer list ilist.
				@param std::initializer_list ilist : initializer list of elements.
			*/
			void assign(std::initializer_list<T> ilist);

			/* <! Adds values into the list before the position given.
				@param const_iterator itr : Constant iterator with the position.
				@param const T& value : The value to be added to the list.
				@return The iterator with the position after the value.
			*/
			iterator insert( const_iterator itr, const T & value );

			/* <! Insert elements from the range [first; last) before position given.
				@param iterator pos : Iterator with the position.
				@param InItr first : Pointer to the first of the range.
				@param InItr last : Pointer to the last of the range.
				@return The iterator with the position after the ranger add.
			*/
			template<typename InItr>
			iterator insert( iterator pos,InItr first, InItr last );

			/* <! Insert elements from the initializer list before the position give.
				@param const_iterator pos : Constant iterator with the positon.
				@param std::initializer_list ilist : initializer list to be added.
				@return The iterator with the position after the initializer list.
			*/
			iterator insert( const_iterator pos, std::initializer_list<T> ilist );

			/* <! Removes the object at positions given.
				@param const_iterator pos : Constant iterator with the position.
				@preturn Iterator before position pos.
			*/
			iterator erase( const_iterator itr );

			/* <! Removes the objects on the range [first; last).
				@param iterator first : iterator to the first of the range.
				@param iterator last : iterator to the last of the range.
				@return iterator before position first.
			*/
			iterator erase( iterator first, iterator last );

			/* <! Search for a value in the list.
				@param const T& value : Object to be searched for.
				@return The constant iterator in the position of the object. Return the position end if the object is not in the list.
			*/
			const_iterator find( const T & value ) const; 
			iterator next(iterator, const T & value);

			bool operator==(const list &rhs);
			bool operator!=(const list &rhs);

			friend std::ostream& operator<<(std::ostream &os_,const list<T> &v);		

		private:
			int m_size;
			Node *m_head;
			Node *m_tail;
	};

	//=======================================================================================

	//CONST_ITERATOR

	template<typename T>
	const T& list<T>::const_iterator::operator*(void) const{
		return current->data;
	}

	template<typename T>
	typename list<T>::const_iterator & list<T>::const_iterator::operator++(void){
		this->current = this->current->next;
		return *this;
	}

	template<typename T>
	typename list<T>::const_iterator list<T>::const_iterator::operator++(int){
		auto aux = this->current;
		this->current = this->current->next;

		return aux;
	}

	template<typename T>
	typename list<T>::const_iterator & list<T>::const_iterator::operator--(void){
		this->current = this->current->prev;
		return *this;
	}

	template<typename T>
	typename list<T>::const_iterator list<T>::const_iterator::operator--(int){
		auto aux = this->current;
		this->current = this->current->prev;

		return aux;
	}

	template<typename T>
	bool list<T>::const_iterator::operator==( const list<T>::const_iterator &rhs) const{
		return this->current == rhs.current;
	}

	template<typename T>
	bool list<T>::const_iterator::operator!=( const list<T>::const_iterator &rhs) const{
		return this->current != rhs.current;
	}

	template<typename T>
	typename list<T>::const_iterator & list<T>::const_iterator::operator+(int add){
		for( int i = 0; i < add; ++i ){
			if( this->current == nullptr ){ /*empty*/ }
			this->current = this->current->next;
		}
		return *this;
	}
	
	template<typename T>
	typename list<T>::const_iterator* list<T>::const_iterator::operator=(const list<T>::const_iterator &rhs){
		this->current = rhs.current;
	}

	template<typename T>
	typename list<T>::const_iterator & list<T>::const_iterator::operator-(int sub){
		for( int i = 0; i < sub; ++i ){
			if( this->current == nullptr ){	/*empty*/ }
			this->current = this->current->prev;
		}
		return *this;
	}

	//=======================================================================================

	//ITERATOR
	template<typename T>
	const T &list<T>::iterator::operator*() const{
		return this->current->data;
	}

	template<typename T>
	T &list<T>::iterator::operator*(){
		return this->current->data;
	}

	template<typename T>
	typename list<T>::iterator & list<T>::iterator::operator+(int add){
		for( int i = 0; i < add; ++i ){
			if( this->current == nullptr ){ /*empty*/ }
			this->current = this->current->next;
		}
		return *this;
	}

	template<typename T>
	typename list<T>::iterator & list<T>::iterator::operator-(int sub){
		for( int i = 0; i < sub; ++i ){
			if( this->current == nullptr ){	/*empty*/ }
			this->current = this->current->prev;
		}
		return *this;
	}

	template<typename T>
	typename list<T>::iterator& list<T>::iterator::operator=(const list<T>::iterator &rhs){
		this->current = rhs.current;
		return *this;
	} 

	template<typename T>
	typename list<T>::iterator &list<T>::iterator::operator++(){
		this->current = this->current->next;
		return *this;
	}

	template<typename T>
	typename list<T>::iterator list<T>::iterator::operator++(int){
		auto temp = this->current;
		this->current = this->current->next;

		return temp;
	}

	template<typename T>
	typename list<T>::iterator &list<T>::iterator::operator--(){
		this->current = this->current->prev;
		return *this;
	}

	template<typename T>
	typename list<T>::iterator list<T>::iterator::operator--(int){
		auto temp = this->current;
		this->current = this->current->prev;

		return temp;
	}

	template<typename T>
	bool list<T>::iterator::operator==(const list<T>::iterator &rhs) const{
		return this->current == rhs.current;
	}

	template<typename T>
	bool list<T>::iterator::operator!=( const list<T>::iterator &rhs) const{
		return this->current != rhs.current;
	}

	//=======================================================================================

	//SPECIAL MEMBERS 
	template<typename T>
	list<T>::list(){
		
		m_size = 0;
		m_head = new Node();
		m_tail = new Node();
		m_head->next = m_tail;
		m_tail->prev = m_head;
	}

	template<typename T>
	list<T>::list( size_type count ){
		m_size = 0;
		m_head = new Node();
		m_tail = new Node();
		m_head->next = m_tail;
		m_tail->prev = m_head;

		for(auto i(0); i < count; i++){
			push_back(i);
		}
	}

	template<typename T>
	template<typename InputIt>
	list<T>::list(InputIt first, InputIt last){
		m_size = 0;
		m_head = new Node();
		m_tail = new Node();
		m_head->next = m_tail;
		m_tail->prev = m_head;

		for(auto i(first); i != last; i++){
			push_back(*i);
		}
	}

	template<typename T>
	list<T>::list(const list &other){
		m_size = 0;
		m_head = new Node();
		m_tail = new Node();
		m_head->next = m_tail;
		m_tail->prev = m_head;
		
		for(auto i(other.cbegin()); i != other.cend(); i++){
			push_back(*i);
		}	
	}

	template<typename T>
	list<T>::list(std::initializer_list<T> ilist){
		m_size = 0;
		m_head = new Node();
		m_tail = new Node();
		m_head->next = m_tail;
		m_tail->prev = m_head;

		for(auto &i : ilist){
			push_back(i);
		}
	}

	template<typename T>
	list<T>::~list(){
		Node *temp = m_head;

		while (temp != m_tail){
			temp = temp->next;

			if(temp->prev != m_head){
				delete temp->prev;
			}
		}

		delete m_head;
		delete m_tail;
	}

	template<typename T>
	list<T> &list<T>::operator=( const list &other ){
		if(m_size != 0){
			clear();

			m_size = 0;
			m_head = new Node();
			m_tail = new Node();
			m_head->next = m_tail;
			m_tail->prev = m_head;	
		}

		for(auto i(other.cbegin()); i != other.cend(); i++){
			push_back(*i);
		}

		return *this;
	}

	template<typename T>
	list<T> & list<T>::operator= (std::initializer_list<T> ilist){
		if(m_size != 0){
			clear();

			m_size = 0;
			m_head = new Node();
			m_tail = new Node();
			m_head->next = m_tail;
			m_tail->prev = m_head;	
		}

		for(auto &i : ilist){
			push_back(i);
		}

		return *this;
	}

	//=======================================================================================

	//ITERATORS
	template<typename T>
	typename ls::list<T>::iterator ls::list<T>::begin(void){
		return list<T>::iterator(this->m_head->next);
	}

	template<typename T>
	typename ls::list<T>::const_iterator ls::list<T>::cbegin(void) const{
		return list<T>::const_iterator(this->m_head->next);
	}

	template<typename T>
	typename ls::list<T>::iterator ls::list<T>::end(void){
		return list<T>::iterator(this->m_tail);
	}

	template<typename T>
	typename list<T>::const_iterator ls::list<T>::cend(void) const{
		return list<T>::const_iterator(this->m_tail);
	}

	//=======================================================================================

	//CAPACITY
	template<typename T>
	int list<T>::size() const{
		return m_size;
	}

	template<typename T>
	bool list<T>::empty() const{
		return (m_head->next == m_tail) && (m_tail->prev == m_head);
	}

	//=======================================================================================

	//MODIFIERS
	template<typename T>
	void list<T>::clear(void){
		erase(begin(),end());

		m_size = 0;
	}

	template<typename T>
	const T & list<T>::front(void) const{
		return m_head->next->data;
	}

	template<typename T>
	T & list<T>::back(void){
		return m_tail->prev->data;
	}

	template<typename T>
	const T & list<T>::back(void) const{
		return m_tail->prev->data;
	} 

	template<typename T>
	void list<T>::push_front( const T & value ){

		Node *temp = new Node(value, m_head,m_head->next);

		m_head->next->prev = temp;
		m_head->next = temp;
		m_size ++;
	}

	template<typename T>
	void list<T>::push_back( const T & value ){
		Node *temp = new Node(value,m_tail->prev, m_tail);
		m_tail->prev->next = temp;
		m_tail->prev = temp;

		m_size ++;
	}

	template<typename T>
	void list<T>::pop_back(void){
		erase(m_tail->prev);
	}

	template<typename T>
	void list<T>::pop_front(void){
		erase(this->m_head->next);
	}

	template<typename T>
	void list<T>::assign( const T & value ){
		for(auto i(begin()); i != end(); i++){
			*i = value;
		}
	}

	//=======================================================================================

	//MODIFIERS WITH ITERATORS
	template<typename T>
	template<typename InItr>
	void list<T>::assign(InItr first, InItr last){
		if(m_size != 0){
			clear();
		}

		insert(begin(), first, last);
	}

	template<typename T>
	void list<T>::assign( std::initializer_list<T> ilist ){
		if(m_size != 0){
			clear();
		}

		insert(begin(), ilist.begin(), ilist.end());
	}

	template<typename T>
	typename list<T>::iterator list<T>::insert( list<T>::const_iterator itr, const T & value ){
		Node *temp = new Node(value, itr.current->prev,itr.current );

		m_size ++;
		itr.current->prev->next = temp;
		itr.current->prev = temp;

		return temp;
	}

	template<typename T>
	template<typename InItr>
	typename list<T>::iterator list<T>::insert( list<T>::iterator pos, InItr first, InItr last ){
		list<T>::iterator temp(pos);
		int size (0);

		for(auto i(first); i != last; ++i){
			temp = list<T>::insert(pos,*i);
			size++;
		}

		if(temp == begin()){
			return temp;
		}else{
			return temp - size + 1;
		}
	}

	template<typename T>
	typename list<T>::iterator list<T>::insert( list<T>::const_iterator pos, std::initializer_list<T> ilist ){
		list<T>::iterator temp;
		int size = ilist.size();

		for(auto i(ilist.begin()); i != ilist.end(); i++){
			temp = insert(pos,*i);
		}

		if(temp == begin()){
			return temp;
		}else{
			return temp - size + 1;
		}
	}

	template<typename T>
	typename list<T>::iterator list<T>::erase( list<T>::const_iterator itr ){
		auto temp = list<T>::iterator(itr.current->next);
		if(itr != end()){
			itr.current->next->prev = itr.current->prev;
			itr.current->prev->next = itr.current->next;
			delete itr.current;
		}

		m_size --;

		return temp;
	}

	template<typename T>
	typename list<T>::iterator list<T>::erase( list<T>::iterator first, list<T>::iterator last ){
		list<T>::iterator temp = erase(first);

		while( temp != last ){
			temp = erase(temp);
		}

		return temp;
	}

	template<typename T>
	typename list<T>::const_iterator list<T>::find( const T & value ) const{
		Node *temp = m_head;

		while (temp != m_tail){

			if(temp->data == value){
				return list<T>::const_iterator(temp);
			}

			temp = temp->next;
		}

		return list<T>::const_iterator(temp);
	}

	template<typename T>
	typename list<T>::iterator list<T>::next(list<T>::iterator first, const T& value){
		return list<T>::iterator(first + value);
	}

	template<typename T>
	bool list<T>::operator==(const list &rhs){
		if( this->m_size != rhs.m_size ) return false;
		for( int i = 0; i < m_size; i++ ){
			if( *(cbegin() + i) != *(rhs.cbegin() + i) ) return false;
		}
		return true;
	}

	template <typename T>
	bool list<T>::operator!=( const list &rhs ){
	/* Function implementation {{{*/
		if ((*this) == rhs) return false;
		return true;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream &os_, list<T> &v){
		for(auto i(v.cbegin());i != v.cend(); i++){
			os_ << *i << ' ';
		}

		return os_;
	}
}

#endif