#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class Customer {
private:
    static int counterIdCustomer;
    const int idCustomer;
    string lastName;
    string firstName;
    string email;
    int fidelityPoints;
    bool madeReview;
    int reviewAspectsNo;
    string* reviewAspect;
    int* satisfactionScore;
public: //constructors:
    Customer();
    Customer(string lastName, string firstName, string email, int fidelityPoints, bool madeReview, int reviewAspectsNo, string* reviewAspect, int* satisfactionScore);
    Customer(const Customer& Obj);
    Customer(string lastName, string firstName, string email, int fidelityPoints);
    Customer(string lastName, string firstName, string email);
    //operators:
    Customer& operator=(const Customer& Obj);
    friend ostream& operator <<(ostream& out, const Customer& C1);
    friend istream& operator >>(istream& in, Customer& C1);
    bool operator ==(const Customer& C);
    bool operator <=(const Customer& C);
    string operator [] (int a);
    operator string();
    operator int();
    Customer& operator --();
    Customer operator --(int);
    Customer operator +(int a);
    friend Customer operator +(int a, Customer C);
    Customer operator +(const Customer &C);
    Customer operator -(int a);
    friend Customer operator -(int a, Customer C);
    Customer operator -(const Customer &C);
    //getters:
    int static getCounterIdCustomer(){return counterIdCustomer;}
    const int getIdCustomer(){return this->idCustomer;}
    string getLastName(){return this->lastName;}
    string getFirstName(){return this->firstName;}
    string getEmail(){return this->email;}
    int getFidelityPoints(){return this->fidelityPoints;}
    bool getMadeReview(){return this->madeReview;}
    int getReviewAspectsNo(){return this->reviewAspectsNo;}
    const string* getReviewAspect(){return this->reviewAspect;}
    const int* getSatisfactionScore(){return this->satisfactionScore;}
    //setters:
    void setLastName(string lastName){this->lastName = lastName;}
    void setFirstName(string firstName){this->firstName = firstName;}
    void setEmail(string email){this->email = email;}
    void setFidelityPoints(int fidelityPoints){this->fidelityPoints = fidelityPoints;}
    void setMadeReview(bool madeReview){this->madeReview = madeReview;}
    void setReviewAspectsNo(int reviewAspectsNo){this->reviewAspectsNo = reviewAspectsNo;}
    void setReviewAspect(string* reviewAspect);
    void setSatisfactionScore(int* satisfactionScore);

    ~Customer();
};
//operator -:
Customer Customer::operator -(const Customer &C){
    Customer aux(*this);
    aux.fidelityPoints = abs(aux.fidelityPoints - C.fidelityPoints);
    return aux;
}
Customer operator -(int a, Customer C){
    Customer aux(C);
    aux.fidelityPoints = abs(aux.fidelityPoints - a);
    return aux;
}
Customer Customer::operator -(int a){
    Customer aux(*this);
    aux.fidelityPoints = abs(aux.fidelityPoints - a);
    return aux;
}
//operator +:
Customer Customer::operator +(const Customer &C){
    Customer aux(*this);
    aux.fidelityPoints += C.fidelityPoints;
    return aux;
}
Customer operator +(int a, Customer C){
    Customer aux(C);
    aux.fidelityPoints += a;
    return aux;
}
Customer Customer::operator +(int a){
    Customer aux(*this);
    aux.fidelityPoints += a;
    return aux;
}
//overload -- operator:
Customer Customer::operator --(int){
    Customer aux(*this);
    if (this->reviewAspect == NULL){
        cout << "Customer didn't make a review\n";
        return aux;
    }
    if (this->reviewAspectsNo == 1){
        delete [] this->reviewAspect;
        delete [] this->satisfactionScore;
        this->reviewAspect = NULL;
        this->satisfactionScore = NULL;
        this->reviewAspectsNo = 0;
        this->madeReview = 0;
        return aux;
    }
    if (aux.reviewAspect != NULL){
        delete [] aux.reviewAspect;
        delete [] aux.satisfactionScore;
        aux.reviewAspectsNo--;
        aux.reviewAspect = new string[aux.reviewAspectsNo];
        aux.satisfactionScore = new int[aux.reviewAspectsNo];
        for (int i = 0; i < aux.reviewAspectsNo; i++){
            aux.reviewAspect[i] = this->reviewAspect[i];
            aux.satisfactionScore[i] = this->satisfactionScore[i];
        }
    }
    Customer aux2(*this);
    *this = aux;
    return aux2;
}
Customer& Customer::operator --(){
    if (this->reviewAspect == NULL){
        cout << "Customer didn't make a review\n";
        return *this;
    }
    if (this->reviewAspectsNo == 1){
        delete [] this->reviewAspect;
        delete [] this->satisfactionScore;
        this->reviewAspect = NULL;
        this->satisfactionScore = NULL;
        this->reviewAspectsNo = 0;
        this->madeReview = 0;
        return *this;
    }
    Customer aux(*this);
    if (aux.reviewAspect != NULL){
        delete [] aux.reviewAspect;
        delete [] aux.satisfactionScore;
        aux.reviewAspectsNo--;
        aux.reviewAspect = new string[aux.reviewAspectsNo];
        aux.satisfactionScore = new int[aux.reviewAspectsNo];
        for (int i = 0; i < aux.reviewAspectsNo; i++){
            aux.reviewAspect[i] = this->reviewAspect[i];
            aux.satisfactionScore[i] = this->satisfactionScore[i];
        }
    }
    *this = aux;
    return *this;
}
//cast operator:
Customer::operator string(){
    return this->lastName;
}
Customer::operator int(){
    return this->fidelityPoints;
}
//index operator:
string Customer::operator [] (int a){
    if (this->reviewAspect == NULL)
        throw runtime_error("Customer did not make any review");
    if (a < 0 || a >= this->reviewAspectsNo)
        throw runtime_error("invalid index");
    else
        return this->reviewAspect[a];
}
//<= operator:
bool Customer::operator <=(const Customer& Obj){
    return this->fidelityPoints <= Obj.fidelityPoints;
}
// == operator:
bool Customer::operator ==(const Customer& Obj){
    if (this->lastName != Obj.lastName) return 0;
    if (this->firstName != Obj.firstName) return 0;
    if (this->email != Obj.email) return 0;
    if (this->fidelityPoints != Obj.fidelityPoints) return 0;
    if (this->email != Obj.email) return 0;
    if (this->fidelityPoints != Obj.fidelityPoints) return 0;
    if (this->madeReview != Obj.madeReview) return 0;
    if (this->reviewAspectsNo != Obj.reviewAspectsNo) return 0;
    for(int i = 0; i < Obj.reviewAspectsNo; i++){
        if (this->reviewAspect[i] != Obj.reviewAspect[i]) return 0;
        if (this->satisfactionScore[i] != Obj.satisfactionScore[i]) return 0;
    }
    return 1;
}
//constructor without parameters:
Customer::Customer():idCustomer(counterIdCustomer++){
    lastName = "anonimus";
    firstName = "anonimus";
    email = "notfound";
    fidelityPoints = 0;
    madeReview = false;
    reviewAspectsNo = 0;
    reviewAspect = NULL;
    satisfactionScore = NULL;
}
//full constructor:
Customer::Customer(string lastName, string firstName, string email, int fidelityPoints, bool madeReview, int reviewAspectsNo, string* reviewAspect,
                    int* satisfactionScore):idCustomer(counterIdCustomer++){
    this->lastName = lastName;
    this->firstName = firstName;
    this->email = email;
    this->fidelityPoints = fidelityPoints;
    this->email = email;
    this->fidelityPoints = fidelityPoints;
    this->madeReview = madeReview;
    this->reviewAspectsNo = reviewAspectsNo;
    this->reviewAspect = new string[reviewAspectsNo];
    this->satisfactionScore = new int[reviewAspectsNo];
    for(int i = 0; i < reviewAspectsNo; i++){
        this->reviewAspect[i] = reviewAspect[i];
        this->satisfactionScore[i] = satisfactionScore[i];
    }
}
//partial constructors:
Customer::Customer(string lastName, string firstName, string email, int fidelityPoints):idCustomer(counterIdCustomer++){
    this->lastName = lastName;
    this->firstName = firstName;
    this->email = email;
    this->fidelityPoints = fidelityPoints;
    this->madeReview = 0;
    this->reviewAspectsNo = 0;
    this->reviewAspect = NULL;
    this->satisfactionScore = NULL;
}
Customer::Customer(string lastName, string firstName, string email):idCustomer(counterIdCustomer++){
    this->lastName = lastName;
    this->firstName = firstName;
    this->email = email;
    this->fidelityPoints = 0;
    this->madeReview = 0;
    this->reviewAspectsNo = 0;
    this->reviewAspect = NULL;
    this->satisfactionScore = NULL;
}
//copy constructor:
Customer::Customer(const Customer& Obj):idCustomer(counterIdCustomer++){
    this->lastName = Obj.lastName;
    this->firstName = Obj.firstName;
    this->email = Obj.email;
    this->fidelityPoints = Obj.fidelityPoints;
    this->email = Obj.email;
    this->fidelityPoints = Obj.fidelityPoints;
    this->madeReview = Obj.madeReview;
    this->reviewAspectsNo = Obj.reviewAspectsNo;
    this->reviewAspect = new string[reviewAspectsNo];
    this->satisfactionScore = new int[reviewAspectsNo];
    for(int i = 0; i < Obj.reviewAspectsNo; i++){
        this->reviewAspect[i] = Obj.reviewAspect[i];
        this->satisfactionScore[i] = Obj.satisfactionScore[i];
    }
}
//overload = operator:
Customer& Customer::operator=(const Customer& Obj){
    if(this != &Obj){
        if(this->satisfactionScore != NULL)
        {
            delete[] this->satisfactionScore;
            this->satisfactionScore = NULL;
        }
        if(this->reviewAspect != NULL)
        {
            delete[] this->reviewAspect;
            this->reviewAspect = NULL;
        }
        this->lastName = Obj.lastName;
        this->firstName = Obj.firstName;
        this->email = Obj.email;
        this->fidelityPoints = Obj.fidelityPoints;
        this->madeReview = Obj.madeReview;
        this->reviewAspectsNo = Obj.reviewAspectsNo;
        this->reviewAspect = new string[Obj.reviewAspectsNo];
        this->satisfactionScore = new int[Obj.reviewAspectsNo];
        for(int i = 0; i < Obj.reviewAspectsNo; i++){
            this->reviewAspect[i] = Obj.reviewAspect[i];
            this->satisfactionScore[i] = Obj.satisfactionScore[i];
        }
    }
    return *this;
}


//overload << operator:
ostream& operator <<(ostream& out, const Customer& C1)
{
    out << "last name: " << C1.lastName << '\n';
    out << "first name: " << C1.firstName << '\n';
    out << "email adress: " << C1.email << '\n';
    out << "fidelity points: " << C1.fidelityPoints << '\n';
    if (C1.madeReview){
        out << "the customer offer a review evaluating " << C1.reviewAspectsNo << " criteria" << '\n';
        for (int i = 0; i < C1.reviewAspectsNo; i++){
            out << "criteria number " << i+1 << " : " << C1.reviewAspect[i];
            out << "\tnumber of stars: ";
            for (int j = 0; j < C1.satisfactionScore[i]; j++)
                out << "* ";
            out << '\n';
        }
        out << "\n\n";
    }
    else{
        out << "the customer did not make a review " << "\n\n";
    }
    return out;
}
//overload >> operator;
istream& operator >>(istream& in, Customer& C1)
{
    cout << "last name: ";
    in >> C1.lastName;
    cout << "first name: ";
    in >> C1.firstName;
    cout << "email adress: ";
    in >> C1.email;
    cout << "fidelity points: ";
    in >> C1.fidelityPoints;
    cout << "did the customer offer a review? [0/1] ";
    in >> C1.madeReview;
    if (C1.reviewAspect != NULL){
        delete[] C1.reviewAspect;
    }
    if (C1.satisfactionScore != NULL){
        delete[] C1.satisfactionScore;
    }
    C1.reviewAspectsNo = 0;
    if (C1.madeReview){
        cout << "How many criteria did the customer evaluate in the review? ";
        in >> C1.reviewAspectsNo;
        C1.reviewAspect = new string[C1.reviewAspectsNo];
        C1.satisfactionScore = new int[C1.reviewAspectsNo];
        for (int i = 0; i < C1.reviewAspectsNo; i++){
            cout << "criteria number " << i + 1 << ": ";
            in >> C1.reviewAspect[i];
            cout << "number of stars: ";
            in >> C1.satisfactionScore[i];
        }
    }
    return in;
}
//setters:
void Customer::setSatisfactionScore(int* satisfactionScore){
    if (this->satisfactionScore != NULL){
        delete [] this->satisfactionScore;
        this->satisfactionScore = NULL;
    }
    this->satisfactionScore = new int[this->reviewAspectsNo];
    for (int i = 0; i < this->reviewAspectsNo; i++)
        this->satisfactionScore[i] = satisfactionScore[i];
}
void Customer::setReviewAspect(string* reviewAspect){
    if (this->reviewAspect != NULL){
        delete [] this->reviewAspect;
        this->reviewAspect = NULL;
    }
    this->reviewAspect = new string[this->reviewAspectsNo];
    for (int i = 0; i < this->reviewAspectsNo; i++)
        this->reviewAspect[i] = reviewAspect[i];
}
//destructor:
Customer::~Customer(){
    if(this->reviewAspect != NULL){
        delete[] this->reviewAspect;
        this->reviewAspect = NULL;
    }
    if(this->satisfactionScore != NULL){
        delete[] this->satisfactionScore;
        this->satisfactionScore = NULL;
    }
}

class Advertisement;
class Item {
private:
    static int counterIdItem;
    const int idItem;
    float price;
    bool inStock;
    bool warranty;
    char* itemType;//TV, mobile phone, laptop etc

public:
    Item(); //constructor without parameters
    Item(float price, bool inStock, bool warranty, char* itemType); //full constructor
    Item(const Item& Obj); //copy constructor

    Item(float price, char* itemType); //it is not in stock and it does not have warranty
    Item(float price, char* itemType, bool inStock); //it can be in stock but it does not have warranty

    //operators:
    Item& operator=(const Item& Obj); //overload = operator
    friend ostream& operator <<(ostream& out, const Item& I1);
    friend istream& operator >>(istream& out, Item& I1);
    bool operator == (const Item &I);
    bool operator > (const Item &I);
    Item& operator ++();
    Item operator ++(int);
    Item operator +(const Item &I);
    Item operator +(float);
    Item operator *(float);
    friend Item operator *(float a, Item);
    friend Item operator +(float a, Item);
    friend Advertisement operator +(const Advertisement& obj, const Item& I);
    friend Advertisement operator +(const Item& I, const Advertisement& obj);
    friend Advertisement operator -(const Advertisement& obj, const Item& I);
    friend Advertisement operator -(const Item& I, const Advertisement& obj);
    operator float();
    //getters:
    static int getCounterIdItem(){return counterIdItem;}
    const int getIdItem(){return this->idItem;}
    float getPrice(){return this->price;}
    bool getInStock(){return this->inStock;}
    bool getWarranty(){return this->warranty;}
    char* getItemType(){return this->itemType;}
    //setters:
    void setPrice(float price){this->price = price;}
    void setInStock(bool inStock){this->inStock = inStock;}
    void setWarranty(bool warranty){this->warranty = warranty;}
    void setItemType(char* itemType);

    ~Item(){
        if(this->itemType != NULL)
        {
            delete[] this->itemType;
            this->itemType = NULL;
        }
    }//destructor
};

//constructor without parameteres:
Item::Item():idItem(counterIdItem++){
    price = 0;
    inStock = false;
    warranty = false;
    itemType = new char[strlen("unavailable") + 1];
    strcpy(itemType, "unavailable");
}
//full constructor:
Item::Item(float price, bool inStock, bool warranty, char* itemType):idItem(counterIdItem++){
    this->price = price;
    this->inStock = inStock;
    this->warranty = warranty;
    this->itemType = new char[strlen(itemType) + 1];
    strcpy(this->itemType, itemType);
}
//copy constructor:
Item::Item(const Item& Obj):idItem(counterIdItem++){
    this->price = Obj.price;
    this->inStock = Obj.inStock;
    this->warranty = Obj.warranty;
    this->itemType = new char[strlen(Obj.itemType) + 1];
    strcpy(this->itemType, Obj.itemType);
}
//partial constructors:
Item::Item(float price, char* itemType):idItem(counterIdItem++){
    this->price = price;
    inStock = 0;
    warranty = 0;
    this->itemType = new char[strlen(itemType) + 1];
    strcpy(this->itemType, itemType);
}
Item::Item(float price, char* itemType, bool inStock):idItem(counterIdItem++){
    this->price = price;
    this->inStock = inStock;
    this->warranty = 0;
    this->itemType = new char[strlen(itemType) + 1];
    strcpy(this->itemType, itemType);
}
//overload = operator:
Item& Item::operator=(const Item& Obj){
    if(this != &Obj){
        if(this->itemType != NULL)
        {
            delete[] this->itemType;
            this->itemType = NULL;
        }
        this->price = Obj.price;
        this->inStock = Obj.inStock;
        this->warranty = Obj.warranty;
        this->itemType = new char[strlen(Obj.itemType) + 1];
        strcpy(this->itemType, Obj.itemType);
    }
    return *this;
}
//overload << operator:
ostream& operator <<(ostream& out, const Item& I1){
    //out << "id item: " << I1.idItem<< '\n';
    out << "price: " << I1.price<< '\n';
    if (!I1.inStock)
        out << "not ";
    out << "in stock" << '\n';
    if (!I1.warranty)
        out << "warranty is not available" << '\n';
    else
        out << "warranty available" << '\n';
    out << "item type: " << I1.itemType << '\n';
    return out;
}
//overload >> operator:
istream& operator >>(istream& in, Item& I1){
    cout << "price: ";
    in >> I1.price;
    cout << "is the item in stock? [0/1] ";
    in >> I1.inStock;
    cout << "does the item have warranty? [0/1] ";
    in >> I1.warranty;
    char item[30];
    cout << "item type: ";
    in >> item;
    if (I1.itemType != NULL){
        delete[] I1.itemType;
    }
    I1.itemType = new char[strlen(item) + 1];
    strcpy(I1.itemType, item);
    return in;
}
// overload == operator:
bool Item::operator ==(const Item& I)
{
    if (this->price != I.price)
        return 0;
    if (this->inStock != I.inStock)
        return 0;
    if (this->warranty != I.warranty)
        return 0;
    if (strcmp(this->itemType, I.itemType) != 0)
        return 0;
    return 1;
}
//setter:
void Item::setItemType(char* itemType){
    if (this->itemType != NULL){
        delete [] this->itemType;
        this->itemType = NULL;
    }
    this->itemType = new char[strlen(itemType) + 1];
    strcpy(this->itemType, itemType);
}
//overload ++ operator pre and post:
Item& Item::operator ++(){
    this->price++;
    return *this;
}
Item Item::operator ++(int){
    Item aux(*this);
    this->price++;
    return aux;
}
//overload + operator:
Item Item::operator +(const Item &I){
    Item aux(*this);
    aux.price = this->price + I.price;
    aux.inStock = this->inStock && I.inStock;
    return aux;
}
Item Item::operator +(float a){
    Item aux(*this);
    aux.price = this->price + a;
    return aux;
}
Item operator +(float a, Item obj){
    Item aux(obj);
    aux.price = aux.price + a;
    return aux;
}
//overload * operator:
Item Item::operator *(float a){
    Item aux(*this);
    aux.price = this->price * a;
    return aux;
}
Item operator *(float a, Item obj){
    Item aux(obj);
    aux.price = aux.price * a;
    return aux;
}
//cast operator:
Item::operator float(){
    return this->price;
}
//overload > operator:
bool Item::operator >(const Item& I){
    return strcmp(this->itemType, I.itemType) > 0;
}

/// ////////////////////////////////////A D V E R T I S E M E N T///////////////////////////////////////////////////////////////////
class Advertisement{
private:
    static int counterIdAdvertisement;
    const int idAdvertisement;
    int runningTime; //in seconds
    int channelsNo; //number of tv channels where it will appear
    int itemsNo;
    Item* items;
    string* channels;
    int viewsNo;
public:
    //constructors:
    Advertisement();
    Advertisement(int runningTime, int channelsNo, string* channels, int itemsNo, Item* items, int viewsNo);
    Advertisement(const Advertisement& Obj);
    Advertisement(int runningTime, int channelsNo, string* channels, int itemsNo, Item* items); //it did not make any views yet, but it doeas appear on TV;
    Advertisement(int runningTime, int itemsNo, Item* items); //it does not appear on any channels
    //operators:
    Advertisement& operator=(const Advertisement& Obj);
    friend ostream& operator <<(ostream& out, const Advertisement& A1);
    friend istream& operator >>(istream& out, Advertisement& A1);
    bool operator == (const Advertisement& Obj);
    bool operator > (const Advertisement& Obj);
    operator int()const;
    Item operator [] (int a);
    Advertisement& operator ++();
    Advertisement operator ++(int);
    Advertisement operator +(const Advertisement &A);
    Advertisement operator -(const Advertisement &A);
    friend Advertisement operator +(const Advertisement& A, const Item& I);
    friend Advertisement operator +(const Item& I, const Advertisement& A);
    friend Advertisement operator -(const Advertisement& A, const Item& I);
    friend Advertisement operator -(const Item& I, const Advertisement& A);
    //getters:
    int static getCounterIdAdvertisement(){return counterIdAdvertisement;}
    const int getIdAdvertisement(){return this->idAdvertisement;}
    int getRunningTime(){return this->runningTime;}
    int getChannelsNo(){return this->channelsNo;}
    int getItemsNo(){return this->itemsNo;}
    const Item* getItems(){return this->items;}
    const string* getChannels(){return this->channels;}
    int getViewsNo(){return this->viewsNo;}
    //setters:
    void setRunningTime(int runningTime){this->runningTime = runningTime;}
    void setChannelsNo(int channelsNo){this->channelsNo = channelsNo;}
    void setItemsNo(int itemsNo){this->itemsNo = itemsNo;}
    void setItems(Item* items);
    void setChannels(string* channels);
    void setViewsNo(int viewsNo){this->viewsNo = viewsNo;}
    //destructor:
    ~Advertisement(){
        if(this->channels != NULL){
            delete[] this->channels;
            this->channels = NULL;}
        if(this->items != NULL){
            delete[] this->items;
            this->items = NULL;}
    };
};
// - operator:
Advertisement Advertisement::operator -(const Advertisement& obj){//items that are only in the first advertisement
    Advertisement aux(*this), aux2(*this);
    if (aux.items != NULL)
        delete [] aux.items;
    if (aux2.items != NULL)
        delete [] aux2.items;
    aux2.items = new Item[this->itemsNo];
    aux2.itemsNo = 0;
    for (int i = 0; i < this->itemsNo; i++){
        bool foundInObj = 0;
        for (int j = 0; j < obj.itemsNo && foundInObj == 0; j++){
            if (this->items[i] == obj.items[j])
                foundInObj = 1;
        }
        if (!foundInObj){
            aux2.items[aux2.itemsNo] = this->items[i];
            aux2.itemsNo++;
        }
    }
    aux.items = new Item[aux2.itemsNo];
    aux.itemsNo = aux2.itemsNo;
    for (int i = 0; i < aux.itemsNo; i++){
         aux.items[i] = aux2.items[i];
    }
    return aux;
}

Advertisement operator-(const Item& I, const Advertisement& obj){
    bool itemFound = false;
    int indexItem;
    Advertisement aux(obj);
    for (int i = 0; i < obj.itemsNo && itemFound == false; i++)
        if (obj.items[i] == I){
            indexItem = i;
            itemFound = true;
        }
    if (itemFound == false) return aux;
    if (aux.items != NULL)
        delete [] aux.items;
    aux.itemsNo--;
    aux.items = new Item[aux.itemsNo];
    for (int i = 0; i < indexItem; i++){
        aux.items[i] = obj.items[i];
    }
    for (int i = indexItem + 1; i <= aux.itemsNo; i++){
        aux.items[i - 1] = obj.items[i];
    }
    return aux;
}

Advertisement operator-(const Advertisement& obj, const Item& I){
    bool itemFound = false;
    int indexItem;
    Advertisement aux(obj);
    for (int i = 0; i < obj.itemsNo && itemFound == false; i++)
        if (obj.items[i] == I){
            indexItem = i;
            itemFound = true;
        }
    if (itemFound == false) return aux;
    if (aux.items != NULL)
        delete [] aux.items;
    aux.itemsNo--;
    aux.items = new Item[aux.itemsNo];
    for (int i = 0; i < indexItem; i++){
        aux.items[i] = obj.items[i];
    }
    for (int i = indexItem + 1; i <= aux.itemsNo; i++){
        aux.items[i - 1] = obj.items[i];
    }
    return aux;
}

// + operator:
Advertisement Advertisement::operator +(const Advertisement& obj){
    Advertisement aux(*this);
    if (aux.items != NULL)
        delete [] aux.items;
    aux.items = new Item[aux.itemsNo + obj.itemsNo];
    for (int i = 0; i < this->itemsNo; i++)
        aux.items[i] = this->items[i];
    for (int i = 0; i < obj.itemsNo; i++)
        aux.items[i + this->itemsNo] = obj.items[i];
    aux.itemsNo += obj.itemsNo;
    return aux;
}
Advertisement operator +(const Item& I, const Advertisement& obj){
    Advertisement aux(obj);
    if (aux.items != NULL)
        delete [] aux.items;
    aux.items = new Item[aux.itemsNo + 1];
    for (int i = 0; i < obj.itemsNo; i++)
        aux.items[i] = obj.items[i];
    aux.items[obj.itemsNo] = I;
    aux.itemsNo++;
    return aux;
}

Advertisement operator +(const Advertisement& obj, const Item& I){
    Advertisement aux(obj);
    if (aux.items != NULL)
        delete [] aux.items;
    aux.items = new Item[aux.itemsNo + 1];
    for (int i = 0; i < obj.itemsNo; i++)
        aux.items[i] = obj.items[i];
    aux.items[obj.itemsNo] = I;
    aux.itemsNo++;
    return aux;
}
// ++ operator:
Advertisement& Advertisement::operator ++(){
    this->viewsNo++;
    return *this;
}
Advertisement Advertisement::operator ++(int){
    Advertisement aux(*this);
    this->viewsNo++;
    return aux;
}
//index operator:
Item Advertisement::operator [] (int a){
    if(this->items == NULL)
        throw runtime_error("There aren't any items");
    if(a < 0 || a >= this->itemsNo)
        throw runtime_error("invalid index");
    else
        return this->items[a];
}
//cast operator:
Advertisement::operator int()const{
    return this->runningTime;
}
//overload > operator:
bool Advertisement::operator >(const Advertisement& Obj){
   return this->runningTime > Obj.runningTime;
}
//overload == operator:
bool Advertisement::operator ==(const Advertisement& Obj){
    if (this->runningTime != Obj.runningTime) return 0;
    if (this->channelsNo != Obj.channelsNo) return 0;
    for(int i = 0; i < Obj.channelsNo; i++)
        if (this->channels[i] != Obj.channels[i]) return 0;
    if (this->itemsNo != Obj.itemsNo) return 0;
    for(int i = 0; i < Obj.itemsNo; i++)
        if (this->items[i] != Obj.items[i]) return 0;
    if (this->viewsNo != Obj.viewsNo) return 0;
    return 1;
}
//constructor without parameters:
Advertisement::Advertisement():idAdvertisement(counterIdAdvertisement++){
    runningTime = 0;
    channelsNo = 0;
    channels = NULL;
    itemsNo = 0;
    items = NULL;
    viewsNo = 0;
}
//full constructor:
Advertisement::Advertisement(int runningTime, int channelsNo, string* channels, int itemsNo, Item* items, int viewsNo):idAdvertisement(counterIdAdvertisement++){
    this->runningTime = runningTime;
    this->channelsNo = channelsNo;
    this->channels = new string[channelsNo];
    for(int i = 0; i < channelsNo; i++)
        this->channels[i] = channels[i];
    this->itemsNo = itemsNo;
    this->items = new Item[itemsNo];
    for(int i = 0; i < itemsNo; i++)
        this->items[i] = items[i];
    this->viewsNo = viewsNo;
}
//copy constructor:
Advertisement::Advertisement(const Advertisement &Obj):idAdvertisement(counterIdAdvertisement++){
    this->runningTime = Obj.runningTime;
    this->channelsNo = Obj.channelsNo;
    this->channels = new string[Obj.channelsNo];
    for(int i = 0; i < Obj.channelsNo; i++)
        this->channels[i] = Obj.channels[i];
    this->itemsNo = Obj.itemsNo;
    this->items = new Item[Obj.itemsNo];
    for(int i = 0; i < Obj.itemsNo; i++)
        this->items[i] = Obj.items[i];
    this->viewsNo = Obj.viewsNo;
}
//partial constructors:
Advertisement::Advertisement(int runningTime, int itemsNo, Item* items):idAdvertisement(counterIdAdvertisement++){
    this->runningTime = runningTime;
    this->viewsNo = 0;
    this->channelsNo = 0;
    this->channels = NULL;
    this->itemsNo = itemsNo;
    this->items = new Item[itemsNo];
    for(int i = 0; i < itemsNo; i++)
        this->items[i] = items[i];
}

Advertisement::Advertisement(int runningTime, int channelsNo, string* channels, int itemsNo, Item* items):idAdvertisement(counterIdAdvertisement++){
    this->runningTime = runningTime;
    this->channelsNo = channelsNo;
    this->channels = new string[channelsNo];
    for(int i = 0; i < channelsNo; i++)
        this->channels[i] = channels[i];
    this->itemsNo = itemsNo;
    this->items = new Item[itemsNo];
    for(int i = 0; i < itemsNo; i++)
        this->items[i] = items[i];
    viewsNo = 0;
}
//overload = operator:
Advertisement& Advertisement::operator=(const Advertisement& Obj){
    if(this != &Obj){
        if(this->channels != NULL)
        {
            delete[] this->channels;
            this->channels = NULL;
        }
        if(this->items != NULL)
        {
            delete[] this->items;
            this->items = NULL;
        }
        this->runningTime = Obj.runningTime;
        this->channelsNo = Obj.channelsNo;
        this->channels = new string[Obj.channelsNo];
        for(int i = 0; i < Obj.channelsNo; i++)
            this->channels[i] = Obj.channels[i];
        this->itemsNo = Obj.itemsNo;
        this->items = new Item[Obj.itemsNo];
        for(int i = 0; i < Obj.itemsNo; i++)
            this->items[i] = Obj.items[i];
        this->viewsNo = Obj.viewsNo;
    }
    return *this;
}
//overload << operator:
ostream& operator <<(ostream& out, const Advertisement& A1){
    //out << "id advertisement: " << A1.idAdvertisement << '\n';
    out << "running time: " << A1.runningTime << '\n';
    out << "number of TV channels where the advertisement appeared: " << A1.channelsNo << '\n';
    for (int i = 0; i < A1.channelsNo; i++)
        out << "-channel number" << i+1 << " : " << A1.channels[i] << '\n';
    out << "number of items appearing in the advertisement: " << A1.itemsNo << '\n';
    for (int i = 0; i < A1.itemsNo; i++)
        out << "-item number " << i+1 << " : " << A1.items[i] << '\n';
    out << "number of views: " << A1.viewsNo << '\n';
    return out;
}
//overload >> operator:
istream& operator >>(istream& in, Advertisement& A1){
    cout << "running time: ";
    in >> A1.runningTime;
    cout << "number of TV channels where the advertisement appeared: ";
    in >> A1.channelsNo;
    if (A1.channels != NULL){
        delete[] A1.channels;
    }
    if (A1.items != NULL){
        delete[] A1.items;
    }
    A1.channels = new string[A1.channelsNo];
    for (int i = 0; i < A1.channelsNo; i++){
        cout << "-channel number" << i + 1 << " : ";
        in >> A1.channels[i];
    }
    cout << "number of items appearing in the advertisement: ";
    in >> A1.itemsNo;
    A1.items = new Item[A1.itemsNo];
    for (int i = 0; i < A1.itemsNo; i++){
        cout << "-item number" << i + 1 << " : ";
        in >> A1.items[i];
    }
    cout << "number of views: ";
    in >> A1.viewsNo;
    cout << '\n';
    return in;
}
//setters:
void Advertisement::setChannels(string* channels){
    if (this->channels != NULL){
        delete [] this->channels;
        this->channels = NULL;
    }
    this->channels = new string[this->channelsNo];
    for (int i = 0; i < this->channelsNo; i++)
        this->channels[i] = channels[i];
}
void Advertisement::setItems(Item* items){
    if (this->items != NULL){
        delete [] this->items;
        this->items = NULL;
    }
    this->items = new Item[this->itemsNo];
    for (int i = 0; i < this->itemsNo; i++)
        this->items[i] = items[i];
}

///counters:
int Item::counterIdItem = 0;
int Customer::counterIdCustomer = 0;
int Advertisement::counterIdAdvertisement = 0;

///  /////////////////////// D I A M A N T ////////////////////////////////////////
class Question{
private:
    string qs;
    string answer;
    int difficulty; //on a scale from 1 to 10, proportional with points given per correct answer
public://constructors:
    Question();
    Question(string qs, string answer, int difficulty);
    Question(const Question&);
    // = operator:
    Question& operator =(const Question&);
    // >> and << operator:
    friend istream& operator >>(istream&, Question&);
    friend ostream& operator <<(ostream&, const Question&);
    //getters and setters:
    int getDifficulty() {return this->difficulty;}
    string getQuestion() {return  this->qs;}
    string getAnswer(){return this->answer;}
    void setDifficulty(int difficulty){this->difficulty = difficulty;}
    void setQuestion(string qs)  {this->qs = qs;}
    void setAnswer(string answer) {this->answer = answer;}
    //destructor:
    ~Question(){};
};
//constructors:
Question::Question(){
    qs = "unavailable";
    answer = "unavailable";
    difficulty = 0;
}

Question::Question(string qs, string answer, int difficulty){
    this->qs = qs;
    this->answer = answer;
    this->difficulty = difficulty;
}

Question::Question(const Question& obj){
    this->qs = obj.qs;
    this->answer = obj.answer;
    this->difficulty = obj.difficulty;
}
 // = operator:
Question& Question::operator = (const Question& obj){
    if (this != &obj){
        this->qs = obj.qs;
        this->answer = obj.answer;
        this->difficulty = obj.difficulty;
    }
    return *this;
}

istream& operator >>(istream& in, Question& obj){
    cout << "question: ";
    in >> obj.qs;
    cout << "answer: ";
    in >> obj.answer;
    cout << "difficulty(1-10): ";
    in >> obj.difficulty;
    return in;
}

ostream& operator <<(ostream& out, const Question& obj){
    out << "Question: " << obj.qs << '\n';
    out << "Answer: " << obj.answer << '\n';
    out << "Difficulty: " << obj.difficulty << '\n';
    return out;
}

class Interface{
public:
    virtual ostream& write(ostream&) const = 0;
    virtual istream& read(istream&) = 0;
};

class Contest: public Interface{
protected:
    string contestName;
    string date;
    vector<Question> questionList;
    int duration; //in minutes
public: //constructors:
    Contest();
    Contest(string contestName, string date, const vector<Question>&  questionList, int duration);
    Contest(const Contest& Obj);
    //operators:
    Contest& operator=(const Contest& Obj);
    friend ostream& operator <<(ostream& out, const Contest& C1);
    friend istream& operator >>(istream& out, Contest& C1);
    //methods:
    virtual int numberOfWinners() = 0;
    ostream& write(ostream& out) const;
    istream& read(istream& in);
    virtual int type() = 0;
    virtual void update() = 0;
    void participate();
    //getters:
    string getContestName(){return this->contestName;}
    string getDate(){return this->date;}
    int getDuration(){return this->duration;}
    const vector<Question> getQuestionList(){return this->questionList;}
    //setters:
    void setContestName(string contestName){this->contestName = contestName;}
    void setDate(string date){this->date = date;}
    int setDuration(int duration){this->duration = duration;}
    /*virtual void setItemName(string){};
    virtual void setPrizeValue(float){};
    virtual void setChoosePrice(bool){};
    virtual string getItemName(){};
    virtual float getPrizeValue(){};
    virtual bool getChoosePrice(){};*/
    //destructor:
    virtual ~Contest(){};
};//constructors:
Contest::Contest(){
    contestName = "notfound";
    date = "unavailable";
    questionList = {};
    duration = 0;
    //cout << "Contest\n";
}

Contest::Contest(string contestName, string date, const vector<Question>& questionList, int duration){
    this->contestName = contestName;
    this->date = date;
    this->questionList = questionList;
    this->duration = duration;
}
//copy constructor:
Contest::Contest(const Contest &obj){
    this->contestName = obj.contestName;
    this->date = obj.date;
    this->questionList = obj.questionList;
    this->duration = obj.duration;
}
//overload = operator:
Contest& Contest::operator=(const Contest& obj){
    if(this != &obj){
        this->contestName = obj.contestName;
        this->date = obj.date;
        this->questionList = obj.questionList;
        this->duration = obj.duration;
    }
    return *this;
}
//overload << operator:
ostream& operator <<(ostream& out, const Contest& C1){
    return C1.write(out);
}
//overload >> operator:
istream& operator >>(istream& in, Contest& C1){
    return C1.read(in);
}

//methods:
void Contest::participate(){
    int score = 0;
    string ans;
    for (int i = 0; i < questionList.size(); i++){
        cout << "Question number " << i + 1 << ": " << questionList[i].getQuestion() << "  answer: ?\n";
        cin >> ans;
        if (ans == questionList[i].getAnswer()){
            cout << "correct answer!\n";
            score += questionList[i].getDifficulty();
        }
        else{
            cout << "wrong answer! correct answer is: " << questionList[i].getAnswer() <<'\n';
        }
    }
    cout << "final score: " << score << '\n';
}

ostream& Contest::write(ostream& out) const{
    out << "Contest name: " << this->contestName << '\n';
    out << "Date of contest: " << this->date << '\n';
    for (int i = 0; i < this->questionList.size(); i++)
        out << "Question number " << i + 1 << ":\n" <<  this->questionList[i] << '\n';
    out << "Duration of contest: " << this->duration << " minutes\n";
    return out;
}

istream& Contest::read(istream& in) {
    cout << "Contest name: ";
    in >> this->contestName;
    cout << "Date of contest: ";
    in >> this->date;
    if (!this->questionList.empty()){
        this->questionList.clear();
    }
    cout << "1-Add question    2-Stop\n";
    int command;
    while(cin >> command && command != 2){
        this->questionList.push_back(*(new Question()));
        in >> this->questionList.back();
    }
    cout << "Duration of contest(minutes): ";
    in >> this->duration;
    return in;
}


class ContestPrizeMoney: virtual public Contest{
protected:
    float prizeValue;
public://constructors:
    ContestPrizeMoney();
    ContestPrizeMoney(string contestName, string date, const vector<Question>&  questionList, int duration, float prizeValue);
    ContestPrizeMoney(const ContestPrizeMoney&);// operators:
    ContestPrizeMoney& operator =(const ContestPrizeMoney&);
    friend ostream& operator <<(ostream& out, const ContestPrizeMoney& C1){
        return C1.write(out);
    }
    friend istream& operator >>(istream& in, ContestPrizeMoney& C1){
        return C1.read(in);
    }
    //methods:
    int numberOfWinners(){
        int nrWinners = 0;
        for (int i = 0; i < this->questionList.size(); i++)
            nrWinners += this->questionList[i].getDifficulty();
        return nrWinners * 3;
    }
    void update() {
        cout << "What do you want to modify?\n";
        cout << "1-contest name   2-date  3-duration  4-prize value\n";
        int command;
        cin >> command;
        switch(command){
            case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                cout << "new value: ";
                int name;
                cin >> name;
                this->duration = name;
                break;}
            case 4:{
                cout << "Current value is " << this->prizeValue << '\n';
                cout << "new value: ";
                float name;
                cin >> name;
                this->prizeValue = name;
                break;}
            default:{
                cout << "undetected command";
            }
        }

    }
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    int type() {return 1;}
    /*float getPrizeValue(){return prizeValue;}
    void setPrizeValue(float prizeValue){this->prizeValue = prizeValue;}*/
    //destructor:
    virtual ~ContestPrizeMoney(){};
};//constructors:
ContestPrizeMoney::ContestPrizeMoney(): Contest(){
    this->prizeValue = 0;
    //cout << "ContestPrizeMoney\n";
}

ContestPrizeMoney::ContestPrizeMoney(string contestName, string date, const vector<Question>&  questionList,
                    int duration, float prizeValue):Contest(contestName, date, questionList, duration){
    this->prizeValue = prizeValue;
}

ContestPrizeMoney::ContestPrizeMoney(const ContestPrizeMoney& obj):Contest(obj){
    this->prizeValue = obj.prizeValue;
}

ContestPrizeMoney& ContestPrizeMoney::operator =(const ContestPrizeMoney& obj){
    if(this != &obj){
        this->Contest::operator=(obj);
        this->prizeValue = obj.prizeValue;
    }
    return *this;
}

//methods:
istream& ContestPrizeMoney::read(istream& in){
    this->Contest::read(in);
    cout << "Prize value(euro): ";
    in >> this->prizeValue;
    return in;
}

ostream& ContestPrizeMoney::write(ostream& out) const{
    this->Contest::write(out);
    out << "Prize value: " << this->prizeValue << " euro\n";
    return out;
}

class ContestPrizeItems: virtual public Contest{
protected:
    string itemName;
public://constructors:
    ContestPrizeItems();
    ContestPrizeItems(string contestName, string date, const vector<Question>&  questionList, int duration, string itemName);
    ContestPrizeItems(const ContestPrizeItems&);// operators:
    ContestPrizeItems& operator =(const ContestPrizeItems&);
    friend ostream& operator <<(ostream& out, const ContestPrizeItems& C1){
        return C1.write(out);
    }
    friend istream& operator >>(istream& in, ContestPrizeItems& C1){
        return C1.read(in);
    }
    //methods:
    void update() {
        cout << "What do you want to modify?\n";
        cout << "1-contest name   2-date  3-duration  4-item name\n";
        int command;
        cin >> command;
        switch(command){
            case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                cout << "new value: ";
                int name;
                cin >> name;
                this->duration = name;
                break;}
            case 4:{
                cout << "Current value is " << this->itemName << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->itemName = name;
                break;}
            default:{
                cout << "undetected command";
            }
        }
    }
    int numberOfWinners(){
        int nrWinners = 0;
        for (int i = 0; i < this->questionList.size(); i++)
            nrWinners += this->questionList[i].getDifficulty();
        return nrWinners * 2;
    }
    istream& read(istream& in);
    ostream& write(ostream& out) const;
    int type() {return 2;}
    /*string getItemName(){return itemName;}
    void setItemName(string itemName){this->itemName = itemName;} */
    //destructor:
    virtual ~ContestPrizeItems(){};
};//constructors:
ContestPrizeItems::ContestPrizeItems(): Contest(){
    this->itemName = "unavailable";
    //cout << "ContestPrizeItems\n";
}

ContestPrizeItems::ContestPrizeItems(string contestName, string date, const vector<Question>&  questionList,
                    int duration, string itemName):Contest(contestName, date, questionList, duration){
    this->itemName = itemName;
}

ContestPrizeItems::ContestPrizeItems(const ContestPrizeItems& obj):Contest(obj) {
    this->itemName = obj.itemName;
}

ContestPrizeItems& ContestPrizeItems::operator =(const ContestPrizeItems& obj) {
    if(this != &obj) {
        this->Contest::operator=(obj);
        this->itemName = obj.itemName;
    }
    return *this;
}

//methods:
istream& ContestPrizeItems::read(istream& in) {
    this->Contest::read(in);
    cout << "Item prize: ";
    in >> this->itemName;
    return in;
}

ostream& ContestPrizeItems::write(ostream& out) const{
    this->Contest::write(out);
    out << "Item prize: " << this->itemName;
    return out;
}

class ContestBothPrizes: public ContestPrizeItems, public ContestPrizeMoney {
private:
    bool choosePrice; //winners will receive both type of prices, or they will have to choose one of them (money/item)
public://constructors:
    ContestBothPrizes();
    ContestBothPrizes(string contestName, string date, const vector<Question>&  questionList, int duration, float prizeValue, string itemName, bool choosePrice);
    ContestBothPrizes(const ContestBothPrizes&);
    // operator:
    friend ostream& operator <<(ostream& out, const ContestBothPrizes& C1){
        return C1.write(out);
    }
    friend istream& operator >>(istream& in, ContestBothPrizes& C1){
        return C1.read(in);
    }
    ContestBothPrizes& operator =(const ContestBothPrizes&);
    //methods:
    void update() {
        cout << "What do you want to modify?\n";
        cout << "1-contest name   2-date  3-duration  4-prize value  5-item name  6-do winners choose their price?\n";
        int command;
        cin >> command;
        switch(command){
            case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                cout << "new value: ";
                int name;
                cin >> name;
                this->duration = name;
                break;}
            case 4:{
                cout << "Current value is " << this->prizeValue << '\n';
                cout << "new value: ";
                int name;
                cin >> name;
                this->prizeValue = name;
                break;}
            case 5:{
                cout << "Current value is " << this->itemName << '\n';
                cout << "new value: ";
                string name;
                cin >> name;
                this->itemName = name;
            break;}
            case 6:{
                cout << "Current value is " << this->choosePrice << '\n';
                cout << "new value: ";
                bool name;
                cin >> name;
                this->choosePrice = name;
            break;}
            default:{
                cout << "undetected command\n";
            }
        }
    }
    int numberOfWinners(){
        if (this->choosePrice == 0)
            return ContestPrizeMoney::numberOfWinners()*2;
        else return ContestPrizeMoney::numberOfWinners() + ContestPrizeItems::numberOfWinners();
    }
    ostream& write(ostream& out) const;
    istream& read(istream& in);
    int type() {return 3;}

    /*bool getChoosePrice(){return choosePrice;}
    void setChoosePrice(bool choosePrice){this->choosePrice = choosePrice;}*/
    virtual ~ContestBothPrizes(){}
};
//constructors:
ContestBothPrizes::ContestBothPrizes(){
    this->choosePrice = 0;
    //cout << "ContestBothPrizes\n";
}

ContestBothPrizes::ContestBothPrizes(string contestName, string date, const vector<Question>&  questionList, int duration,
                float prizeValue, string itemName, bool choosePrice):Contest(contestName, date, questionList, duration),
                ContestPrizeMoney(contestName, date, questionList, duration, prizeValue),
                ContestPrizeItems(contestName, date, questionList, duration, itemName){
    this->choosePrice = choosePrice;
}

ContestBothPrizes::ContestBothPrizes(const ContestBothPrizes& obj):Contest(obj), ContestPrizeMoney(obj), ContestPrizeItems(obj){
    this->choosePrice = obj.choosePrice;
}
// = operator:
ContestBothPrizes& ContestBothPrizes::operator =(const ContestBothPrizes& obj){
    if (this != &obj){
        Contest::operator=(obj);
        ContestPrizeMoney::operator=(obj);
        ContestPrizeItems::operator=(obj);
        this->choosePrice = obj.choosePrice;
    }
    return *this;
}
//methods:
ostream& ContestBothPrizes::write(ostream& out) const{
    Contest::write(out);
    out << "Prize value: " << this->prizeValue << " euro\n";
    out << "Item prize: " << this->itemName << "\n";
    if (this->choosePrice) out << "Winners must choose between a " << this->itemName << " and " << this->prizeValue << " euro\n";
    else out << "Winners will receive both the " << this->itemName << " and " << this->prizeValue << " euro\n";
    return out;
}
istream& ContestBothPrizes::read(istream& in){
    Contest::read(in);
    cout << "Prize value(euro): ";
    in >> this->prizeValue;
    cout << "Item prize: ";
    in >> this->itemName;
    cout << "Do winners choose their prize?[0/1]: ";
    in >> this->choosePrice;
    cout << '\n';
    return in;
}

class ContestData{
private:
    Contest* contest;
    int registeredCompetitors;
    bool approved;
public:
    ContestData(){
        contest = NULL;
        registeredCompetitors = 0;
        approved = 0;
    };
    ContestData(const ContestData &obj){
        this->contest = obj.contest;
        this->registeredCompetitors = obj.registeredCompetitors;
        this->approved = obj.approved;
    }
    ContestData& operator=(const ContestData &obj){
        if (this != &obj){
            this->contest = obj.contest;
            this->registeredCompetitors = obj.registeredCompetitors;
            this->approved = obj.approved;
        }
        return *this;
    }
    friend istream& operator >>(istream& in, ContestData& obj){
        cout << "1-Contest with prize in money    2-Contest who offers items as prize    3-Contest with both types of prizes    ";
        int c;
        cin >> c;
        switch(c){
            case 1:{
                obj.contest = new ContestPrizeMoney();
            break;}
            case 2:{
                obj.contest = new ContestPrizeItems();
            break;}
            case 3:{
                obj.contest = new ContestBothPrizes();
            break;}
        }
        in >> *obj.contest;
        cout << "How many people have already registered? ";
        in >> obj.registeredCompetitors;
        cout << "Has the contest been approved? [0/1] ";
        in >> obj.approved;
        return in;
    }

    friend ostream& operator <<(ostream& out, const ContestData& obj){
        out << "Contest:\n" << *obj.contest << '\n';
        out << "Number of competitors already registered: " << obj.registeredCompetitors << '\n';
        if (obj.approved) out << "Contest approved\n";
        else out << "Contest not approved\n";
        return out;
    }
    Contest* getContest() {return this->contest;}
    bool getApproved() {return this->approved;}
};

int main()
{
    ///lists of objects:
    Advertisement advertisementsList[100];
    ContestData contestsList[100];
    Item itemsList[100];
    Customer customersList[100];
    vector <Contest*> Participations;
    int advCounter = 0, contCounter = 0, itemCounter = 0, customerCounter = 0;
    bool displayMenu = true;
    int counterDisplay = 0;
    while(displayMenu){
        if (counterDisplay > 10000) counterDisplay = 0;
        int command;
        if (counterDisplay % 3 == 0){
            cout << "\n Show by index:   ";
            cout << "1-Advertisement  ";
            cout << "2-Contest  ";
            cout << "3-Item  ";
            cout << "4-Customer\n";

            cout << " Add:      ";
            cout << "11-Advertisement  ";
            cout << "12-Contest  ";
            cout << "13-Item  ";
            cout << "14-Customer";

            cout << "\n Display list:   ";
            cout << "21-Advertisement  ";
            cout << "22-Contest  ";
            cout << "23-Item  ";
            cout << "24-Customer\n";

            cout << " Delete:   ";
            cout << "31-Advertisement  ";
            cout << "32-Contest  ";
            cout << "33-Item  ";
            cout << "34-Customer";

            cout << "\n 40-Functionalities";
            cout << "\n 41-Update:\n";
            cout << "\t\t\t\t ***STOP COMMAND: 0***\n";
        }
        cin >> command;
        counterDisplay++;
        switch (command){
            case 1:{
                cout << "index of object: ";
                int index;
                cin >> index;
                index -= 1;
                if (index < 0 || index >= advCounter) cout << "Index invalid\n";
                else{
                    cout << advertisementsList[index];
                }
            break;}
            case 2:{
                cout << "index of object: ";
                int index;
                cin >> index;
                index -= 1;
                if (index < 0 || index >= contCounter) cout << "Index invalid\n";
                else{
                    cout << contestsList[index];
                }
            break;}
             case 3:{
                cout << "index of object: ";
                int index;
                cin >> index;
                index -= 1;
                if (index < 0 || index >= itemCounter) cout << "Index invalid\n";
                else{
                    cout << itemsList[index];
                }
            break;}
             case 4:{
                cout << "index of object: ";
                int index;
                cin >> index;
                index -= 1;
                if (index < 0 || index >= customerCounter) cout << "Index invalid\n";
                else{
                    cout << customersList[index];
                }
            break;}
            case 11:{
                Advertisement O;
                cin >> O;
                advertisementsList[advCounter++] = O;
            break;}
            case 12:{
                ContestData O;
                cin >> O;
                contestsList[contCounter++] = O;
            break;}
           case 13:{
                Item O;
                cin >> O;
                itemsList[itemCounter++] = O;
            break;}
            case 14:{
                Customer O;
                cin >> O;
                customersList[customerCounter++] = O;
            break;}
            case 21:{
                for (int i = 0; i < advCounter; i++)
                    cout << "Object " << i + 1 << ":\n" << advertisementsList[i] << '\n';
            break;}
            case 22:{
                for (int i = 0; i < contCounter; i++)
                    cout << "Object " << i + 1 << ":\n" << contestsList[i] << '\n';
            break;}
            case 23:{
                for (int i = 0; i < itemCounter; i++)
                    cout << "Object " << i + 1 << ":\n" << itemsList[i] << '\n';
            break;}
            case 24:{
                for (int i = 0; i < customerCounter; i++)
                    cout << "Object " << i + 1 << ":\n" << customersList[i] << '\n';
            break;}
            case 31:{
                int index;
                cout << "index of object: ";
                cin >> index;
                index -= 1;
                if (index < 0 || index >= advCounter) cout << "Index invalid\n";
                else{
                    for (int i = index; i < advCounter - 1; i++)
                        advertisementsList[i] = advertisementsList[i + 1];
                    advCounter--;
                }
            break;}
            case 32:{
                int index;
                cout << "index of object: ";
                cin >> index;
                index -= 1;
                if (index < 0 || index >= contCounter) cout << "Index invalid\n";
                else{
                    for (int i = index; i < contCounter - 1; i++)
                        contestsList[i] = contestsList[i + 1];
                    contCounter--;
                }
            break;}
            case 33:{
                int index;
                cout << "index of object: ";
                cin >> index;
                index -= 1;
                if (index < 0 || index >= itemCounter) cout << "Index invalid\n";
                else{
                    for (int i = index; i < itemCounter - 1; i++)
                        itemsList[i] = itemsList[i + 1];
                    itemCounter--;
                }
            break;}
            case 34:{
                int index;
                cout << "index of object: ";
                cin >> index;
                index -= 1;
                if (index < 0 || index >= customerCounter) cout << "Index invalid\n";
                else{
                    for (int i = index; i < customerCounter - 1; i++)
                        customersList[i] = customersList[i + 1];
                    customerCounter--;
                }
            break;}
            case 40:{
                cout << " 1-Show how many advertisements have a number of views between 2 given values\n";
                cout << " 2-Show how many items of a given type are in stock    ";
                cout << " 3-Show the average review points for a given criterion\n";
                cout << " 4-Show the average price for items of a given type  ";
                cout << " 5-Calculate number of winners for a contest and type of contest\n";
                cout << " 6-Show list of contests with the maximum number of winners\n";
                cout << " 7-Show how many contests have been approved   ";
                cout << " 8-Participate in a contest\n";
                int instr;
                cin >> instr;
                switch (instr){
                    case 1:{
                        int views1, views2, advertisementsNo = 0;
                        cout << "number of views 1: ";
                        cin >> views1;
                        cout << "number of views 2: ";
                        cin >> views2;
                        if (views1 > views2)
                            swap(views1, views2);
                        for (int i = 0; i < advCounter; i++)
                            if (advertisementsList[i].getViewsNo() >= views1 && advertisementsList[i].getViewsNo() <= views2)
                                advertisementsNo++;
                        cout << "number of advertisements: " << advertisementsNo << '\n';
                    break;}
                    case 2:{
                        char type[30];
                        cout << "item type: ";
                        cin >> type;
                        int itemsNo = 0; //number of items in stock
                        for (int i = 0; i < itemCounter; i++)
                        {
                            if(itemsList[i].getInStock() && strcmp(itemsList[i].getItemType(), type) == 0)
                                itemsNo++;
                        }
                        cout << "item type :" << type << "   number of items in stock: " << itemsNo << '\n';
                    break;}
                    case 3:{
                        string criterion;
                        float avgStars = 0;
                        int criterionCnt = 0; //how many customers evaluated this criterion
                        cout << "criterion: ";
                        cin >> criterion;
                        for (int i = 0; i < customerCounter; i++)
                        {
                            bool criterionFound = false;
                            if (customersList[i].getMadeReview() == false)
                                    continue;
                            const string* criteria = customersList[i].getReviewAspect();
                            const int* stars = customersList[i].getSatisfactionScore();
                            for (int j = 0; j < customersList[i].getReviewAspectsNo() && !(criterionFound); j++)
                                if (criteria[j] == criterion){
                                    criterionFound = true;
                                    criterionCnt++;
                                    avgStars += stars[j];
                                }
                        }
                        if (criterionCnt == 0)
                            cout << "This criterion has not been evaluated by any customer\n";
                        else{
                            avgStars /= (float)criterionCnt;
                            cout << "average rating: " << avgStars << '\n';
                        }
                    break;}
                    case 4:{
                        char type[30];
                        cout << "item type: ";
                        cin >> type;
                        float price = 0;
                        float itemsNr = 0;
                        Item aux;
                        for (int i = 0; i < itemCounter; i++){
                            if(strcmp(itemsList[i].getItemType(), type) == 0){
                                aux = aux + itemsList[i];
                                itemsNr++;
                            }
                        }
                        aux = aux * (1/itemsNr);
                        price = (float)aux;
                        cout << "item type :" << type << "   averagePrice: " << price << '\n';
                    break;}
                    case 5:{
                        int index;
                        cout << "index of contest: ";
                        cin >> index;
                        index -= 1;
                        if (index < 0 || index >= contCounter) cout << "Index invalid\n";
                        else{
                            cout << "Number of winners: " << contestsList[index].getContest()->numberOfWinners() << '\n';
                            cout << "Type of prize: ";
                            int caz = contestsList[index].getContest()->type();
                            if (caz == 1) cout << "money\n";
                            if (caz == 2) cout << "items from store\n";
                            if (caz == 3) cout << "money and an item\n";
                        }
                    break;}
                    case 6:{
                        if (contCounter == 0) cout << "There are no contests registered\n";
                        else{
                            vector <Contest*> maxWinners;
                            int nrMax = 0;
                            for (int i = 0; i < contCounter; i++){
                                int currentWinners = contestsList[i].getContest()->numberOfWinners();
                                if (currentWinners > nrMax){
                                    nrMax = currentWinners;
                                    maxWinners.clear();
                                    maxWinners.push_back(contestsList[i].getContest());
                                }
                                else if(currentWinners == nrMax){
                                    maxWinners.push_back(contestsList[i].getContest());
                                }
                            }
                            cout << "Biggest number of winners: " << nrMax << '\n';
                            cout << "Number of contests: " <<  maxWinners.size() << '\n';
                            for (int i = 0; i < maxWinners.size(); i++)
                                cout << "Contest number " << i + 1 << '\n' << *maxWinners[i] << '\n';
                        }
                    break;}
                    case 7:{
                        int cnt = 0;
                        for (int i = 0; i < contCounter; i++){
                            if (contestsList[i].getApproved())
                                cnt++;
                        }
                        cout << "Contests approved: " << cnt << " from " << contCounter << '\n';
                    break;}
                    case 8:{
                        int index;
                        cout << "index of contest: ";
                        cin >> index;
                        index -= 1;
                        if (index < 0 || index >= contCounter) cout << "Index invalid\n";
                        else{
                             (*(contestsList[index].getContest())).participate();
                        }
                    break;}
                    default:{
                cout << "\n Undetected command\n";
                    break;}
                }
            break;}
            case 41:{
                cout << " 1-Add item to advertisement     ";
                cout << " 2-Delete item from advertisement\n";
                cout << " 3-Change an item\t\t ";
                cout << " 4-Add fidelity points to customer ";
                cout << " 5-Delete last review criterion from customer\n";
                cout << " 6-Update a contest by index\n";
                int instruction;
                cin >> instruction;
                switch (instruction){
                    case 1:{
                    int index;
                    cout << "index of advertisement: ";
                    cin >> index;
                    index -= 1;
                    if (index < 0 || index >= advCounter) cout << "Index invalid\n";
                    else{
                        cin >> itemsList[itemCounter++];
                        advertisementsList[index] = advertisementsList[index] + itemsList[itemCounter - 1];
                        }
                    break;}
                    case 2:{
                        int index;
                        cout << "index of advertisement: ";
                        cin >> index;
                        index -= 1;
                        if (index < 0 || index >= advCounter) cout << "Index invalid\n";
                        else{
                            int indexI;
                            cout << "index of item: ";
                            cin >> indexI;
                            indexI--;
                            if (indexI < 0 || index >= advertisementsList[index].getItemsNo()) cout << "Index invalid\n";
                            else{
                                    Item I = advertisementsList[index][indexI];
                                    advertisementsList[index] = advertisementsList[index] - I;
                                }
                            }
                    break;}
                    case 3:{
                        int index;
                        cout << "index of item: ";
                        cin >> index;
                        index -= 1;
                        if (index < 0 || index >= itemCounter) cout << "Index invalid\n";
                        else{
                            cout << "change:    1-price    2-availabity(in stock/not in stock)";
                            int choice;
                            cin >> choice;
                            switch (choice){
                                case 1:{
                                    float a;
                                    cout << "Value to be added: ";
                                    cin >> a;
                                    itemsList[index] = a + itemsList[index];
                                    cout << "Now the item price is: " << (float)itemsList[index] << '\n';
                                break;}
                                case 2:{
                                    bool stock;
                                    cout << "In stock[0/1]: ";
                                    cin >> stock;
                                    itemsList[index].setInStock(stock);
                                break;}
                                default:{
                                    cout << "\n Undetected command";
                                }
                            }
                        }
                    break;}
                    case 4:{
                        int index;
                        cout << "customer index: ";
                        cin >> index;
                        index -= 1;
                        if (index < 0 || index >= customerCounter) cout << "Index invalid\n";
                        else{
                            int points;
                            cout << "bonus fidelity points: ";
                            cin >> points;
                            customersList[index] = points + customersList[index];
                        }
                    break;}
                    case 5:{
                        int index;
                        cout << "customer index: ";
                        cin >> index;
                        index--;
                        if (index < 0 || index >= customerCounter) cout << "Index invalid\n";
                        else --customersList[index];
                    break;}
                    case 6:{
                        int index;
                        cout << "index of contest: ";
                        cin >> index;
                        index -= 1;
                        if (index < 0 || index >= contCounter) cout << "Index invalid\n";
                        else{
                            contestsList[index].getContest()->update();
                        }
                    break;}
                    default:{
                        cout << "\n Undetected command";
                    }
                }

            break;}
            case 0:{
                displayMenu = false;
            break;}
            default:{
                cout << "\n Undetected command";
            }
        }
    }
    return 0;
}



