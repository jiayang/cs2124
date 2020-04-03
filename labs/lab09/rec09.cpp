#include <iostream>
using namespace std;

class PrintedMaterial {
    friend ostream& operator<<(ostream& os, PrintedMaterial print) {
        os << numberOfPages << endl;
        return os;
    }
public:
    PrintedMaterial(unsigned numberOfPages)
        : numberOfPages(numberOfPages) {}
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
        : PrintedMaterial(numPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
        : PrintedMaterial(numPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages)
        : Book(numPages) {}
protected:
private:
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
        : Book(numPages) {}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
    cout << t;
    cout << n;
}
