
#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
};

class Brass : public Instrument {
public:
    Brass(unsigned mouthpieceSize) :mouthpieceSize(mouthpieceSize){}

    void makeSound() const override {
        cout << "To make a sound... blow on a mouthpiece of size "
             << mouthpieceSize << endl;
    }
private:
    unsigned mouthpieceSize;
};

class String : public Instrument {
public:
    String(unsigned freq) : freq(freq) {}

    void makeSound() const override {
        cout << "To make a sound... bow a string with pitch "
             << freq << endl;
    }
private:
    unsigned freq;
};

class Percussion : public Instrument {
public:
    Percussion() {}

    void makeSound() const override {
        cout << "To make a sound... hit me!" << endl;
    }
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned mouthSize) : Brass(mouthSize) {}

    void play() const override {
        cout << "Toot";
    }
};

class Trombone : public Brass {
public:
    Trombone(unsigned mouthSize) : Brass(mouthSize) {}

    void play() const override {
        cout << "Blat";
    }
};

class Violin : public String {
public:
    Violin(unsigned freq) : String(freq) {}
    
    void play() const override {
        cout << "Screech";
    }
};

class Cello : public String {
public:
    Cello(unsigned freq) : String(freq) {}
    
    void play() const override {
        cout << "Squawk";
    }
};

class Drum : public Percussion {
public:
    Drum() {}
    
    void play() const override {
        cout << "Boom";
    }
};

class Cymbal : public Percussion {
public:
    Cymbal() {}
    
    void play() const override {
        cout << "Crash";
    }
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }

    void play() const {
        if (instr != nullptr) {
            instr->play();
        }
    }
private:
    Instrument* instr;
};

class MILL {
public:
    void receiveInstr(Instrument& instr) {
        //instr.makeSound();
        for (size_t i = 0; i < instruments.size(); ++i) {
            if (instruments[i] == nullptr) {
                instruments[i] = &instr;
                return;
            }
        }
        instruments.push_back(&instr);
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < instruments.size(); ++i) {
            if (instruments[i] != nullptr) {
                Instrument* ptr = instruments[i];
                instruments[i] = nullptr;
                return ptr;
            }
        }
        return nullptr;
    }

    void dailyTestPlay() const {
        for (Instrument const* instr : instruments) {
            if (instr != nullptr) {
                instr->makeSound();
            }
        }
    }
    
private:
    vector<Instrument*> instruments;
};

class Orch {
public:
    void addPlayer(Musician& player) {
        musicians.push_back(&player);
    }

    void play() const {
        for (Musician const* player : musicians) {
            player->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> musicians;
};
    
// PART ONE
/*int main() {

    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;
}
*/
