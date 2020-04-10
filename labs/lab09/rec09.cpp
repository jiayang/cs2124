#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
    friend ostream& operator<<(ostream& os, const PrintedMaterial& print) {
        os << print.numberOfPages << endl;
        return os;
    }
public:
    PrintedMaterial(unsigned numberOfPages)
        : numberOfPages(numberOfPages) {}
    virtual void displayNumPages() const = 0;
protected:
    unsigned getNumberOfPages() const {
        return numberOfPages;
    }
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
        : PrintedMaterial(numPages) {}

    void displayNumPages() const override {
        cout << getNumberOfPages() << endl;
    }
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
        : PrintedMaterial(numPages) {}
    
    void displayNumPages() const override {
        cout << getNumberOfPages() << endl;
    }
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages)
        : Book(numPages) {}

    void displayNumPages() const {
		cout << "Pages: ";
		cout << getNumberOfPages();
		cout << "Index pages: ";
		cout << numOfIndexPages << endl; 
	}
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
        : Book(numPages) {}

    
    void displayNumPages() const override {
        cout << getNumberOfPages() << endl;
    }
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& pm) {
    pm.displayNumPages();
}


// tester/modeler code
int main()
{
	TextBook t(1);
	Novel n(2);
	Magazine m(3);

    cout << t;
    cout << n;

    vector<PrintedMaterial*> prints;
    prints.push_back(&t);
    prints.push_back(&n);
    prints.push_back(&m);

    for (PrintedMaterial* print : prints) {
        displayNumberOfPages(*print);
    }
}
