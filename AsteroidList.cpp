#include <galaxy-explorer/AsteroidList.hpp>

/* Default Constructor
 */ 
AsteroidListItem::AsteroidListItem() {
    this -> next = nullptr;
    this -> data = nullptr;
}
/* Constructor 1 creates a new Asteroid
 * and sets its data to the data of 
 * Asteroid a
 */
AsteroidListItem::AsteroidListItem(Asteroid a) {    
    this -> next = nullptr;
    this -> data = new Asteroid( a.getID(), a.getMass(), a.getHealth(),
            a.getCurrentHitbox(), a.getVelocity() );
}
/* Destructor deletes data which was previously 
 * dynamically allocated.
 */
AsteroidListItem::~AsteroidListItem() {
    delete this -> data;
}
/* The object head is invoking the constructor of
 * AsteroidListItem and being initialized therefore
 * an empty constructor will suffice since we do not
 * need to initialize anything else 
 */
AsteroidList::AsteroidList()
{
}
/*Copy Constructor
 */ 
AsteroidList::AsteroidList(const AsteroidList& src)
{
    /*empties the list if it already contains something
     */
    clear(); 
    pushFront ( src.begin() -> getData() );
    AsteroidListItem *curr = head.getNext();
    const AsteroidListItem *temp = src.begin() -> getNext();
    while(temp != nullptr) {
        insertAfter( curr, temp -> getData() );
        curr = curr -> getNext();
        temp = temp -> getNext();
    }
}
/* Destructor invokes the clear function 
 * and deletes all the AstroidLisItem 
 * allocated dynamically
 */
AsteroidList::~AsteroidList() {
    clear();
}
/* Creates a new AstroidListItem and makes it's
 * next point to head's next. It also makes head's
 * next point to the newly created object;
 */
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem *obj = new AsteroidListItem( e );
        obj -> setNext( head.getNext() );
        head.setNext( obj );    
}

Asteroid& AsteroidList::front() {
    return head.getNext() -> getData();
}


const Asteroid& AsteroidList::front() const {
    if(head.getNext() == nullptr)
        return *(const Asteroid*)nullptr;
    return head.getNext() -> getData();
}

bool AsteroidList::isEmpty() const {
    if ( head.getNext() == nullptr )
	return true;
    return false;
}

int AsteroidList::size() const {
    if(head.getNext() == nullptr)
        return 0;
    const AsteroidListItem *temp = head.getNext();
    int size = 0 ;
    while( temp->getNext() != NULL ){
        size++;
        temp = temp->getNext();
    }
    size++;
    return size;
}

AsteroidListItem* AsteroidList::beforeBegin() {
        return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
        return &head;
}

AsteroidListItem* AsteroidList::begin() {
    if( head.getNext() == nullptr )
	return nullptr;
    else
        return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
    if( head.getNext() == nullptr )
	return nullptr;
    else
        return head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    if( head.getNext() == nullptr )
        return nullptr;
    else{
        AsteroidListItem *temp = head.getNext();
        while( temp-> getNext() != nullptr ){
            temp = temp -> getNext();
        }
        return temp;
    }
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    if( head.getNext() == nullptr )
	return nullptr;
    else{
        const AsteroidListItem *temp = head.getNext();
         while( temp -> getNext() != nullptr ){
            temp = temp -> getNext();
        }
    return temp;
    }
}

AsteroidListItem* AsteroidList::end() {
    return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    if( head.getNext() == nullptr )
       return prev;
    AsteroidListItem *temp = head.getNext();
    AsteroidListItem *last = nullptr;
    while( temp -> getNext() != nullptr && temp != prev ){
       temp = temp->getNext();
    }
    /* Now temp is pointing to the AsteroidListItem after 
     * which 'e' has to be added
     */ 
    if( temp -> hasNext() )
       last = temp -> getNext();
    AsteroidListItem *item = new AsteroidListItem( e );
    temp -> setNext( item );
    if( last == nullptr )
       item -> setNext( nullptr );
    else
        item -> setNext( last );
    return item;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    if( head.getNext() == nullptr )
        return prev;
    AsteroidListItem *temp = head.getNext();
    AsteroidListItem *last = nullptr;
    while( temp -> getNext()!= nullptr && temp != prev ){
        temp = temp -> getNext();
    }
    /* Now temp is pointing to the AsteroidListItem after 
     * which the list 'others' has to be added
     */ 
    if( temp -> hasNext() )
        last = temp -> getNext();
    const AsteroidListItem *item = others.begin();
    while( item != nullptr ){
        AsteroidListItem* obj = new AsteroidListItem( item -> getData() );
        temp -> setNext( obj );
        temp = temp -> getNext();
        item = item -> getNext();
    }
    if( last == nullptr )
        temp -> setNext( nullptr );
    else
        temp -> setNext( last );
    return temp;  
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    if( !prev -> hasNext() )
	return nullptr;
    else{
        AsteroidListItem *temp = head.getNext();
        while( temp != prev ){
           temp = temp -> getNext();
        } 
        temp -> setNext( temp -> getNext() -> getNext() );
        delete temp -> getNext();
    }
}

void AsteroidList::clear() {
    AsteroidListItem *temp = head.getNext();
        while( temp != NULL){
            AsteroidListItem* curr = temp;
            temp = temp -> getNext();
            delete curr;
        }
    head.setNext( nullptr );
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    /*empties the list if it already contains something
     */
    clear();
    if( src.head.getNext() != nullptr ){
        pushFront( src.begin() -> getData() );
        AsteroidListItem *curr = head.getNext();
        const AsteroidListItem *temp = src.begin() -> getNext();
        while( temp !=  nullptr ) {
            insertAfter( curr, temp -> getData() );
            curr = curr -> getNext();
            temp = temp -> getNext();
        }
    }
}

