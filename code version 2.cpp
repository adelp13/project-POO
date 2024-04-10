#include <iostream>
#include <vector>
#include <string.h>
#include <list>
#include <set>
#include <map>
#include <typeinfo>
using namespace std;

class contestNotFound: public exception {
public:
    const char * what () const throw() {return "Contest has not been found\n";};
};

class alreadyParticipated: public exception {
public:
    const char * what () const throw() {return "You can participate in a contest just once!\n";};
};

class contestNotApproved: public exception {
public:
    const char * what () const throw() {return "Contest has not been approved!\n";};
};

class valueNumberOutOfRange: public exception{
public:
    const char *what () const throw() {return "Value not allowed!\n";}
};

class valueStringOutOfRange: public exception{
public:
    const char *what () const throw() {return "String cannot be longer than 20!\n";}
};

class contestNameAlreadyUsed: public exception{
public:
    const char *what () const throw() {return "2 contests cannot have the same name!\n";}
};

template <typename X> //functie template care se asigura ca valorile citite de la tastatura se afla intr-un anumit range, altfel arunca exceptii
void verify(X a, bool &verified, int length){
    try {
        if(a < 0 || a > length)
            throw valueNumberOutOfRange();
        verified = 1;
    }
    catch(valueNumberOutOfRange& v){
        cout << v.what();
        verified = 0;
    }
    return;
}

template <>
void verify(int a, bool &verified, int length){
    try{
        if (a < 0 || a > length)
            throw valueNumberOutOfRange();
        verified = 1;
    }
    catch(valueNumberOutOfRange& v){
        cout << v.what();
        verified = 0;
    }
    return;
}

template <>
void verify(float a, bool &verified, int length){
    try{
        if (a < 0 || a > length)
            throw valueNumberOutOfRange();
        verified = 1;
    }
    catch(valueNumberOutOfRange& v){
        cout << v.what();
        verified = 0;
    }
    return;
}
template <>
void verify(string a, bool &verified, int length){
    try{
        if (a.length() > length)
            throw valueStringOutOfRange();
        verified = 1;
    }
    catch(valueStringOutOfRange& v){
        cout << v.what();
        verified = 0;
    }
    return;
}

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
    bool verified;
    cout << "question: ";
    do{
        in >> obj.qs;
        verify(obj.qs, verified, 20);
    }while(!verified);
    cout << "answer: ";
    do{
        in >> obj.answer;
        verify(obj.answer, verified, 20);
    }while(!verified);
    cout << "difficulty(1-10): ";
    do{
        in >> obj.difficulty;;
        verify(obj.difficulty, verified, 10);
    }while(!verified);
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
    string contestName; //numele concursului trebuie sa fie unic
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
    void update() { //functie de update nevirtuala, folosita prin dynamic cast
        bool verified;
        cout << "What do you want to modify?\n";
        cout << "1-contest name   2-date  3-duration\n";
        int command;
        cin >> command;
        switch(command){
            case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                cout << "new value: ";
                int name;
                do{
                    cin >> name;
                    verify(name, verified, 30);
                }while(!verified);
                this->duration = name;
                break;}
            default:{
                cout << "undetected command";
            }
        }

    };
    void participate();
    virtual void showPrize() = 0; //functie virtuala care afiseaza bunurile alocate pt un concurs, in functie de numarul maxim de castigatori pt fiecare tip de concurs
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
    virtual ~Contest();
};
//destructor:
Contest::~Contest(){
     if (!this->questionList.empty()){
        this->questionList.clear();
    }
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
    out << "Contest name: " << C1.contestName << '\n';
    out << "Date of contest: " << C1.date << '\n';
    for (int i = 0; i < C1.questionList.size(); i++)
        out << "Question number " << i + 1 << ":\n" <<  C1.questionList[i] << '\n';
    out << "Duration of contest: " << C1.duration << " minutes\n";
    return out;
}
//overload >> operator:
istream& operator >>(istream& in, Contest& C1){
    cout << "Contest name: ";
    bool verified;
    do{
        in >> C1.contestName;
        verify(C1.contestName, verified, 20);
    }while(!verified);
    cout << "Date of contest: ";
    do{
        in >> C1.date;
        verify(C1.date, verified, 20);
    }while(!verified);
    if (!C1.questionList.empty()){
        C1.questionList.clear();
    }
    cout << "1-Add question    2-Stop\n";
    int command;
    while(cin >> command && command != 2){
        C1.questionList.push_back(*(new Question()));
        in >> C1.questionList.back();
    }
    cout << "Duration of contest(minutes): ";
    do{
        in >> C1.duration;
        verify(C1.duration, verified, 30);
    }while(!verified);
    return in;
}

//methods:
void Contest::participate(){ //punctajul se calculeaza de fapt prin raportul dintre punctajul maxim posibil si punctajul obtinut. punctajul maxim posibil este suma punctelor
    //pt fiecare intrebare
    double score = 0,  punctaj_maxim = 0;
    bool verified;
    string ans;
    for (int i = 0; i < questionList.size(); i++){
        cout << "Question number " << i + 1 << ": " << questionList[i].getQuestion() << "  answer: ?\n";
        punctaj_maxim += questionList[i].getDifficulty();
        do{
            cin >> ans;
            verify(ans, verified, 20);
        }while(!verified);
        if (ans == questionList[i].getAnswer()){
            cout << "correct answer!\n";
            score += questionList[i].getDifficulty();
        }
        else{
            cout << "wrong answer! correct answer is: " << questionList[i].getAnswer() <<'\n';
        }
    }
    cout << "final score: " << (score/punctaj_maxim) * 100 << '\n';
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
    bool verified;
    do{
        in >> this->contestName;
        verify(this->contestName, verified, 20);
    }while(!verified);
    cout << "Date of contest: ";
    do{
        in >> this->date;
        verify(this->date, verified, 20);
    }while(!verified);
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
    do{
        in >> this->duration;
        verify(this->duration, verified, 30);
    }while(!verified);
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

    friend istream& operator >>(istream& in, ContestPrizeMoney& C1){
        bool verified;
        in >> (Contest&)C1;
        cout << "Prize value(euro): ";
        do{
            in >> C1.prizeValue;
            verify(C1.prizeValue, verified, 100);
        }while(!verified);
        return in;
    }

    friend ostream& operator <<(ostream& out, const ContestPrizeMoney& C1){
        out << (Contest&)C1;
        out << "Prize value: " << C1.prizeValue << " euro\n";
        return out;
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
        bool verified;
        cin >> command;
        switch(command){
            case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                cout << "new value: ";
                int name;
                do{
                    cin >> name;
                    verify(name, verified, 30);
                }while(!verified);
                this->duration = name;
                break;}
            case 4:{
                cout << "Current value is " << this->prizeValue << '\n';
                cout << "new value: ";
                float name;
                do{
                    cin >> name;
                    verify(name, verified, 100);
                }while(!verified);
                this->prizeValue = name;
                break;}
            default:{
                cout << "undetected command";
            }
        }

    }
    void showPrize() {
        cout << this->numberOfWinners() * this->prizeValue << " euro\n";
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

    friend istream& operator >>(istream& in, ContestPrizeItems& C1){
        bool verified;
        in >> (Contest&)C1;
        cout << "Item prize: ";
        do{
            in >> C1.itemName;
            verify(C1.itemName, verified, 20);
        }while(!verified);
        return in;
    }

    friend ostream& operator <<(ostream& out, const ContestPrizeItems& C1){
        out << (Contest&)C1;
        out << "Item prize: " << C1.itemName;
        return out;
    }
    //methods:
    void update() {
        cout << "What do you want to modify?\n";
        cout << "1-contest name   2-date  3-duration  4-item name\n";
        int command;
        cin >> command;
        bool verified;
        switch(command){
             case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                cout << "new value: ";
                int name;
                do{
                    cin >> name;
                    verify(name, verified, 30);
                }while(!verified);
                this->duration = name;
                break;}
            case 4:{
                cout << "Current value is " << this->itemName << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 30);
                }while(!verified);
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
    void showPrize() {
        cout << this->numberOfWinners() << " x " << this->itemName << "\n";
    }
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

ContestPrizeItems::ContestPrizeItems(const ContestPrizeItems& obj):Contest(obj){
    this->itemName = obj.itemName;
}

ContestPrizeItems& ContestPrizeItems::operator =(const ContestPrizeItems& obj){
    if(this != &obj){
        this->Contest::operator=(obj);
        this->itemName = obj.itemName;
    }
    return *this;
}

//methods:
istream& ContestPrizeItems::read(istream& in){
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
    int choosePrice; //winners will receive both type of prices, or they will have to choose one of them (money/item)
public://constructors:
    ContestBothPrizes();
    ContestBothPrizes(string contestName, string date, const vector<Question>&  questionList, int duration, float prizeValue, string itemName, int choosePrice);
    ContestBothPrizes(const ContestBothPrizes&);
    // operator:
    friend ostream& operator <<(ostream& out , const ContestBothPrizes& C1){
        out << (Contest&)C1;
        out << "Prize value: " << C1.prizeValue << " euro\n";
        out << "Item prize: " << C1.itemName << "\n";
        if (C1.choosePrice) out << "Winners must choose between a " << C1.itemName << " and " << C1.prizeValue << " euro\n";
        else out << "Winners will receive both the " << C1.itemName << " and " << C1.prizeValue << " euro\n";
        return out;
    }

    friend istream& operator >>(istream& in, ContestBothPrizes& C1){
        bool verified;
        in >> (Contest&)C1;
        cout << "Prize value(euro): ";
        do{
            in >> C1.prizeValue;
            verify(C1.prizeValue, verified, 100);
        }while(!verified);
        cout << "Item prize: ";
        do{
            in >> C1.itemName;
            verify(C1.itemName, verified, 20);
        }while(!verified);
        cout << "Do winners choose their prize?[0/1]: ";
        do{
            in >> C1.choosePrice;
            verify(C1.choosePrice, verified, 1);
        }while(!verified);
        cout << '\n';
        return in;
    }
    ContestBothPrizes& operator =(const ContestBothPrizes&);
    //methods:
    void update() {
        cout << "What do you want to modify?\n";
        cout << "1-contest name   2-date  3-duration  4-prize value  5-item name  6-do winners choose their price?\n";
        int command;
        cin >> command;
        bool verified;
        switch(command){
            case 1:{
                cout << "Current value is " << this->contestName << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->contestName = name;
            break;}
            case 2:{
                cout << "Current value is " << this->date << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->date = name;
            break;}
            case 3:{
                cout << "Current value is " << this->duration << '\n';
                int name;
                cout << "new value: ";
                do{
                    cin >> name;
                    verify(name, verified, 30);
                }while(!verified);
                this->duration = name;
                break;}
            case 4:{
                cout << "Current value is " << this->prizeValue << '\n';
                cout << "new value: ";
                int name;
                do{
                    cin >> name;
                    verify(name, verified, 100);
                }while(!verified);
                this->prizeValue = name;
                break;}
            case 5:{
                cout << "Current value is " << this->itemName << '\n';
                cout << "new value: ";
                string name;
                do{
                    cin >> name;
                    verify(name, verified, 20);
                }while(!verified);
                this->itemName = name;
            break;}
            case 6:{
                cout << "Current value is " << this->choosePrice << '\n';
                cout << "new value: ";
                int name;
                do{
                    cin >> name;
                    verify(name, verified, 1);
                }while(!verified);
                this->choosePrice = name;
            break;}
            default:{
                cout << "undetected command\n";
            }
        }
    }

    void showPrize() {
        cout << this->numberOfWinners() * this->prizeValue << " euro    and     ";
        cout << this->numberOfWinners() << " x " << this->itemName << "\n";
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
   //aaaaa virtual ~ContestBothPrizes(){}
};
//constructors:
ContestBothPrizes::ContestBothPrizes(){
    this->choosePrice = 0;
    //cout << "ContestBothPrizes\n";
}

ContestBothPrizes::ContestBothPrizes(string contestName, string date, const vector<Question>&  questionList, int duration,
                float prizeValue, string itemName, int choosePrice):Contest(contestName, date, questionList, duration),
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
    int winnersNo;
    int approved;

public:
    ContestData(){
        contest = NULL;
        winnersNo = 0;
        approved = 0;
    };

    ContestData(const ContestData &obj){
        this->winnersNo = obj.winnersNo;
        this->approved = obj.approved;

        if (obj.contest != NULL){
            if (typeid(ContestPrizeMoney) == typeid(*obj.contest))
                this->contest = new ContestPrizeMoney(dynamic_cast<ContestPrizeMoney&>(*obj.contest));
            if (typeid(ContestPrizeItems) == typeid(*obj.contest))
                this->contest = new ContestPrizeItems(dynamic_cast<ContestPrizeItems&>(*obj.contest));
            if (typeid(ContestBothPrizes) == typeid(*obj.contest))
                this->contest = new ContestBothPrizes(dynamic_cast<ContestBothPrizes&>(*obj.contest));
        }
        else
            this->contest = NULL;
    }

    ContestData& operator=(const ContestData &obj){
        if (this != &obj){
            if(this->contest != NULL){
                delete this->contest;
                this->contest = NULL;
            }
            if(obj.contest != NULL){
                if (typeid(ContestPrizeMoney) == typeid(*obj.contest))
                    this->contest = new ContestPrizeMoney(dynamic_cast<ContestPrizeMoney&>(*obj.contest));
                else if (typeid(ContestPrizeItems) == typeid(*obj.contest))
                    this->contest = new ContestPrizeItems(dynamic_cast<ContestPrizeItems&>(*obj.contest));
                else if (typeid(ContestBothPrizes) == typeid(*obj.contest))
                    this->contest = new ContestBothPrizes(dynamic_cast<ContestBothPrizes&>(*obj.contest));
            }
            this->winnersNo = obj.winnersNo;
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
                in >> *(dynamic_cast<ContestPrizeMoney*>(obj.contest));
            break;}
            case 2:{
                obj.contest = new ContestPrizeItems();
                in >> dynamic_cast<ContestPrizeItems&>(*obj.contest);
            break;}
            case 3:{
                obj.contest = new ContestBothPrizes();
            break;}
        }
        if (typeid(ContestBothPrizes) == typeid(*obj.contest))
            in >> dynamic_cast<ContestBothPrizes&>(*obj.contest);
        cout << "Has the contest been approved? [0/1] ";
        bool verified;
        do{
            in >> obj.approved;
            verify(obj.approved, verified, 1);
        }while(!verified);
        return in;
    }

    friend ostream& operator <<(ostream& out, const ContestData& obj){
        out << "Contest:\n";
        if(typeid(ContestPrizeMoney) == typeid(*obj.contest))
              out << dynamic_cast<ContestPrizeMoney&>(*obj.contest);
        if(typeid(ContestPrizeItems) == typeid(*obj.contest))
              out << dynamic_cast<ContestPrizeItems&>(*obj.contest);
        if(typeid(ContestBothPrizes) == typeid(*obj.contest))
              out << dynamic_cast<ContestBothPrizes&>(*obj.contest);

        //out << "Number of competitors who won: " << obj.winnersNo << '\n';
        if (obj.approved) out << "Contest approved\n";
        else out << "Contest not approved\n";
        return out;
    }
    Contest* getContest() {return this->contest;}
    int getApproved() {return this->approved;}
    int getWinnersNo() {return this->winnersNo;}
    void incrementWinnersNo() {this->winnersNo++;}
    void setWinnersNo(int winnersNo) {this->winnersNo = winnersNo;}
    virtual ~ContestData(){
        if(this->contest != NULL){
            delete this->contest;
            this->contest = NULL;
        }
    };
};

class OnlinePlatform { //clasa de tip singletone, reprezinta site ul pe care sunt inregsitrate atat concursurile, cat si participantii
private:
    static OnlinePlatform *entity;
    static int instanceNumber;
    list <ContestData> contestsList;
    set <string> participants; //retin numele candidtatilor care au participat macar o data la un concurs
    map <pair<string, string>, int> contestsResults; //stocheaza participarile, astfel ca un concurent nu poate participa la acelasi concurs de mai multe oriF
    OnlinePlatform() = default; //cand sterg un concurs sterg din map toate participarile; //functie de calculat punctajul mediu al unui participant
    OnlinePlatform(const OnlinePlatform&) = delete;
    OnlinePlatform& operator=(OnlinePlatform&) = delete;
    //daca nu se afla in set concurentul il adaugam;
public:
    static OnlinePlatform* getInstance(){
        instanceNumber++;
        if(!entity)
            entity = new OnlinePlatform();
        return entity;
    }
    void showContestByIndex();
    void addContest();
    void displayContestsList();
    void deleteContestByIndex();
    void calculateWinners();
    void contestWithMaximumNumberOfWinners();
    void updateContest();
    void addParticipant();
    void contestsWonNo();
    void displayData();

    template<typename X> void calculateWorth();
    //template <ContestBothPrizes> void calculateWorth(){};
    void startApp(){
        int contCounter = 0;
        bool displayMenu = true;
        int counterDisplay = 0;
        while(displayMenu){
            if (counterDisplay > 10000) counterDisplay = 0;
            int command;
            if (counterDisplay % 3 == 0){
                cout << "1 - Show a contest by index  ";
                cout << "2 - Add Contest  ";
                cout << "3 - Display list of contests  ";
                cout << "4 - Delete Contest  ";

                cout << "\n5-Functionalities";
                cout << "\n6-Update a contest by index:\n";
                cout << "\t\t\t\t ***STOP COMMAND: 0***\n";
            }
            cin >> command;
            counterDisplay++;
            switch (command){
                case 1:{
                    entity->showContestByIndex();
                break;}
                case 2:{
                    entity->addContest();
                break;}
                case 3:{
                    entity->displayContestsList();
                break;}
                case 4:{
                    entity->deleteContestByIndex();
                break;}
                case 5:{
                    cout << " 1-Calculate possible number of winners for a contest and type of contest\n";
                    cout << " 2-Show list of contests with the maximum possible number of winners\n";
                    cout << " 3-Show how many contests have been approved   ";
                    cout << " 4-Participate in a contest\n";
                    cout << " 5-Add a participant\n";
                    cout << " 6-Find how many contests each participant won\n";
                    cout << " 7-Display resources allocated for each type of contest\n";
                    int instr;
                    cin >> instr;
                    switch (instr){
                        case 1:{
                            entity->calculateWinners();
                        break;}
                        case 2:{
                            entity->contestWithMaximumNumberOfWinners();
                        break;}
                        case 3:{
                            int cnt = 0;
                            for (auto i = contestsList.begin(); i != contestsList.end(); i++){
                                if ((*i).getApproved())
                                    cnt++;
                            }
                            cout << "Contests approved: " << cnt << " from " << contestsList.size() << '\n';
                        break;}
                        case 4:{
                            int index;
                            cout << "index of contest: ";
                            cin >> index;
                            index -= 1;
                            if (index < 0 || index >= contestsList.size()) cout << "Index invalid\n";
                            else{
                                auto i = contestsList.begin();
                                for(i; i != contestsList.end() && index > 0; i++, index--);
                                 (*(*i).getContest()).participate();
                            }
                        break;}
                        case 5: {
                            entity->addParticipant();
                        break;}
                        case 6: {
                            entity->contestsWonNo();
                        break;}
                        case 7: {
                            entity->displayData();
                        break;}
                        default:{
                    cout << "\n Undetected command\n";
                        break;}
                    }
                break;}
                case 6:{
                    entity->updateContest();
                break;}
                case 0:{
                    displayMenu = false;
                break;}
                default:{
                    cout << "\n Undetected command";
                }
            }
        }
    }
    ~OnlinePlatform(){
        instanceNumber--;
        if(!instanceNumber)
            if(entity){
                delete entity;
        }
    }
};
OnlinePlatform* OnlinePlatform::entity = 0;
int OnlinePlatform::instanceNumber = 0;

void OnlinePlatform::displayData() {
    int command;
    cout << "Type of contest: ";
    cout << "1-Contests with prize in money    2-Contests who offers items as prize    3-Contests with both types of prizes   4-All\n";
    cin >> command;
    switch(command){
        case 1:{
            calculateWorth<ContestPrizeMoney>();
        break;}
        case 2:{
             calculateWorth<ContestPrizeItems>();
        break;}
        case 3:{
            calculateWorth<ContestBothPrizes>();
        break;}
        case 4:{
            calculateWorth<ContestPrizeMoney>();
            calculateWorth<ContestPrizeItems>();
            calculateWorth<ContestBothPrizes>();
        break;}
        default:{
            cout << "undetected command\n";
        break;}
    };
}
void OnlinePlatform::contestsWonNo() { //pentru fiecare concurs exista un numar maxim posibil de castigatori si se vor alege oricare concurenti dintre cei care au obtinut mai mult de 70 de puncte
    for(auto i : participants){ //pentru fiecare participant vedem la ce concursuri a participat
        //string prize;
        //int prizeInMoney;
        int contestsWon = 0;
        for (auto j = contestsResults.begin(); j != contestsResults.end(); j++){
            if (i == (*j).first.first){
                for (auto k = contestsList.begin(); k != contestsList.end(); k++){
                    if ((*k).getContest()->getContestName() == (*j).first.second ){
                        if ((*k).getWinnersNo() < (*k).getContest()->numberOfWinners() && (*j).second > 70){ //verificam daca numarul de persoane care au castigat este mai mic decat numarul permis de castigatori pt acest concurs
                            (*k).incrementWinnersNo();
                            contestsWon++;
                            //addToPrize(prize, prizeInMoney, (*k)->getContest)
                        }
                    }
                }
            }
        }
        cout << i << " has won: " << contestsWon << " contest(s)\n";
    }
     for (auto k = contestsList.begin(); k != contestsList.end(); k++){
        (*k).setWinnersNo(0);
    }
}

template<typename X> void OnlinePlatform::calculateWorth(){ //metoda membra template care calculeaza pentru unul din cele 3 tipuri de contest valuarea bunurilor alocate
    for (auto i = contestsList.begin(); i != contestsList.end(); i++)
    {
        if(typeid(X) == typeid( *((*i).getContest()) )){ //daca concursul curent este de tipul cautat ii afisam premiile
            dynamic_cast<X&>(*((*i).getContest())).showPrize();
        }
    }
}

void OnlinePlatform::addParticipant() {
    bool verified;
    string participant;
    cout << "participant name: ";
    do{
        cin >> participant;
        verify(participant, verified, 20);
    }while(!verified);
    participants.insert(participant); //fiind un set, daca incerc sa adaug de 2 ori acelasi participant nu se va adauga de 2 ori
    cout << "contest name: ";
    string contest_name;
    do{
        cin >> contest_name;
        verify(contest_name, verified, 20); // se va citi valoarea pana cand utilizatorul introduce o valoare corecta
    }while(!verified);
    try{
        bool contestFound = false;
        for (auto i = contestsList.begin(); i != contestsList.end() && contestFound == 0; i++){
            if (((*i).getContest())->getContestName() == contest_name){
                contestFound = true;
                if ((*i).getApproved() == 0) {
                    throw contestNotApproved();
                }
            }
        }
        if (!contestFound)
            throw contestNotFound();
    }
    catch(contestNotFound& cnf){
        cout << cnf.what();
        return;
    }
    catch(contestNotApproved& cna){
        cout << cna.what();
        return;
    }
    bool contestFound = false;
    int score;
    cout << "score obtained: ";
    do{
        cin >> score;
        verify(score, verified, 100);
    }while(!verified);
    try{
        for(auto I : contestsResults)
        if (I.first.first == participant && I.first.second == contest_name)
            throw alreadyParticipated();
        contestsResults.insert({make_pair(participant, contest_name), score});
    }
    catch(alreadyParticipated& ap){
        cout << ap.what();
        return;
    }

}
void OnlinePlatform::updateContest(){
    int index;
    cout << "index of contest: ";
    cin >> index;
    index -= 1;
    if (index < 0 || index >= contestsList.size()) cout << "Index invalid\n";
    else{
        auto i = contestsList.begin();
        for(i; i != contestsList.end() && index > 0; i++, index--);
        if(typeid(ContestPrizeMoney) == typeid( *((*i).getContest()) ))
              dynamic_cast<ContestPrizeMoney&>(*((*i).getContest())).update();
        if(typeid(ContestPrizeItems) == typeid( *((*i).getContest()) ))
              dynamic_cast<ContestPrizeItems&>(*((*i).getContest())).update();
        if(typeid(ContestBothPrizes) == typeid( *((*i).getContest()) ))
              dynamic_cast<ContestBothPrizes&>(*((*i).getContest())).update();
    }
}

void OnlinePlatform::contestWithMaximumNumberOfWinners(){
    if (contestsList.size() == 0) cout << "There are no contests registered\n";
    else{
        vector <Contest*> maxWinners;
        int nrMax = 0;
        for (auto i = contestsList.begin(); i != contestsList.end(); i++){
            int currentWinners = (*i).getContest()->numberOfWinners();
                if (currentWinners > nrMax){
                    nrMax = currentWinners;
                    maxWinners.clear();
                    maxWinners.push_back((*i).getContest());
                }
                else if(currentWinners == nrMax){
                    maxWinners.push_back((*i).getContest());
                }
        }
        cout << "Biggest number of winners: " << nrMax << '\n';
        cout << "Number of contests: " <<  maxWinners.size() << '\n';
        for (int i = 0; i < maxWinners.size(); i++)
            cout << "Contest number " << i + 1 << '\n' << *maxWinners[i] << '\n';
    }
}
void OnlinePlatform::calculateWinners(){
    int index;
    cout << "index of contest: ";
    cin >> index;
    index -= 1;
    if (index < 0 || index >= contestsList.size()) cout << "Index invalid\n";
    else{
        auto i = contestsList.begin();
        for(i; i != contestsList.end() && index > 0; i++, index--);
        cout << "Number of winners: " << (*i).getContest()->numberOfWinners() << '\n';
        cout << "Type of prize: ";
        int caz = (*i).getContest()->type();
        if (caz == 1) cout << "money\n";
        if (caz == 2) cout << "items from store\n";
        if (caz == 3) cout << "money and an item\n";
    }
}
void OnlinePlatform::addContest(){
    ContestData O;
    cin >> O;
    try{
        for (auto i = contestsList.begin(); i != contestsList.end(); i++){ //verificam daca mai exista concursuri cu numele acesta
            if ((*i).getContest()->getContestName() == O.getContest()->getContestName())
                throw contestNameAlreadyUsed();
        }
        contestsList.push_back(O);
    }
    catch(contestNameAlreadyUsed& cna){
        cout << cna.what();
    }
}

void OnlinePlatform::displayContestsList(){
    auto i = contestsList.begin();
    for(i; i != contestsList.end(); i++)
        cout << *i << endl;
}

void OnlinePlatform::deleteContestByIndex(){
    int index;
    cout << "index of object: ";
    cin >> index;
    index -= 1;
    if (index < 0 || index >= contestsList.size()) cout << "Index invalid\n";
    else{
        auto i = contestsList.begin();
        for(i; i != contestsList.end() && index > 0; i++, index--);
        contestsList.erase(i);
    }
}
void OnlinePlatform::showContestByIndex(){
    cout << "index of object: ";
    int index;
    cin >> index;
    index -= 1;
    if (index < 0 || index >= contestsList.size()) cout << "Index invalid\n";
    else{
        auto i = contestsList.begin();
        for(i; i != contestsList.end() && index > 0; i++, index--);
        cout << *i << endl;
    }
}
int main()
{
    OnlinePlatform* p = p->getInstance();
    p->startApp(); //pornim meniul

    return 0;
}
