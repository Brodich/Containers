#ifndef LIST 
#define LIST 

template <class T>
class s21_list {
	typedef T						value_type;
	typedef T &						reference;
	typedef const T &				const_reference;
	// typedef ListIterator<T>			iterator;
	// typedef ListConstIterator<T>	const_iterator;
	typedef size_t					size_type;
	

	
	
	private:
		// value_type* element;
		s21_list* next;
		s21_list* prev;
	
		// template <typename T&> value_type;
		// template <typename const T&> reference;

		// template <typename T> value_type;
  
	public:
    		value_type element;
		s21_list(){
            // for(int i = 0; )
            // element = 
            
            // element(new value_type [0]);
            prev = nullptr;
            next = nullptr;
        };
        s21_list(size_type n) {
            // for (int i = 0; i < n; i++) {
                s21_list a;
                s21_list b;
                // a.next = &b;
				this->next = &b;
                b.prev = this;

            // }
            
            // &this 
        };
		// s21_list(size_type n) : element(new value_type [n]) {};
		// s21_list(std::initializer_list<value_type> const &items);
		// s21_list(const s21_list &l);
		// s21_list(s21_list &&l);
		~s21_list() {
            // if (element) free(element);
            // element = nullptr;
        };
		// operator=(s21_list &&l);


		// T front();
		// const_reference back();


};


#endif 
