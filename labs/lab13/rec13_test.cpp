// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

//task 9
void print_list(const list<int>& lst) {
    for (list<int>::const_iterator i = lst.begin(); i != lst.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

//task 10
void print_list_ranged(const list<int>& lst) {
    for (int elem : lst) {
        cout << elem << " ";
    }
    cout << endl;
}

//task 11
void print_with_auto(const list<int>& lst) {
    for (auto i = lst.begin(); i != lst.end(); ++++i) {
        cout << *i << " ";
    }
    cout << endl;
}

//task 12
list<int>::const_iterator find_item(const list<int>& lst, int n) {
    for (list<int>::const_iterator i = lst.begin(); i != lst.end(); ++i) {
        if (*i == n) {
            return i;
        }
    }
    return lst.end();
}

//task 13
auto find_auto(const list<int>& lst, int n) {
    for (auto i = lst.begin(); i != lst.end(); ++i) {
        if (*i == n) {
            return i;
        }
    }
    return lst.end();
}

//task 15
bool is_even(int n) {
    return !(n & 1);
}

//task 16
struct IsEven {
    bool operator() (int n) {
        return !(n & 1);
    }
};

//task 19
auto ourFind(const list<int>::iterator& begin, const list<int>::iterator& end, int n) {
    for (auto i = begin; i != end; ++i) {
        if (*i == n) {
            return i;
        }
    }
    return end;
}

//task 20
template <typename T, typename Q>
auto ourFindTemplate(const T& begin, const T& end, Q elem) {
    for (auto i = begin; i != end; ++i) {
        if (*i == elem) {
            return i;
        }
    }
    return end;
} 

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> a{0,1,2,6,7,3,4,5};
    for (int elem : a) {
        cout << elem << " ";
    }
    
    
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";

    list<int> lst(a.begin(),a.end());
    for (int elem : lst) {
        cout << elem << " ";
    }
    
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(a.begin(),a.end());
    for (int elem : a) {
        cout << elem << " ";
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < a.size(); i +=2) {
        cout << a[i] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";

    // for (size_t i = 0; i < lst.size(); i += 2) {
    //     cout << lst[i] << " ";
    // }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator i = a.begin(); i != a.end(); i+=2) {
        cout << *i << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";

    for (list<int>::iterator i = lst.begin(); i != lst.end(); ++++i) {
        cout << *i << " ";
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (int elem : lst) {
        cout << elem << " ";
    }
        
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    print_list(lst);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    print_list_ranged(lst);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    print_with_auto(lst);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";

    cout << *find_item(lst, 2) << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *find_auto(lst,2) << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(lst.begin(),lst.end(), 2) << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << *find_if(lst.begin(), lst.end(), is_even) << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    cout << *find_if(lst.begin(), lst.end(), IsEven()) << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    cout << *find_if(lst.begin(), lst.end(), [] (int n) {return !(n&1);}) << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[lst.size()];
    copy(lst.begin(), lst.end(), arr);
    for (size_t i = 0; i < lst.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(lst.begin(), lst.end(), 2) << endl;
    cout << (ourFind(lst.begin(), lst.end(), 123) == lst.end()) << endl; 
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFindTemplate(lst.begin(), lst.end(), 2) << endl;
    cout << (ourFindTemplate(lst.begin(), lst.end(), 123) == lst.end()) << endl; 
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs("text.txt");
    if (!ifs) {
        exit(1);
    }
    vector<string> words;
    string s;
    while (ifs >> s) {
        if (find(words.begin(),words.end(),s) == words.end()) {
            words.push_back(s);
        }
    }
    ifs.close();
    cout << words.size() << endl;
    // for (const string& word : words) {
    //     cout << word << ", ";
    // }
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> setWords;
    ifstream ifss("text.txt");
    if (!ifss) {
        exit(1);
    }
    while (ifss >> s) {
        setWords.insert(s);
    }
    ifss.close();
    cout << setWords.size() << endl;
    // for (const string& word : setWords) {
    //     cout << word << ", ";
    // }
    
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    ifstream ifsMap("text.txt");
    if (!ifsMap) {
        exit(1);
    }
    int i = 0;
    while (ifsMap >> s) {
        wordMap[s].push_back(i);
        ++i;
    }
    ifsMap.close();
    cout << wordMap.size() << endl;
    for (const pair<string, vector<int>>& p : wordMap) {
        cout << p.first << ": ";
        for (const int& n : p.second) {
            cout << n << ", ";
        }
        cout << endl;
    }
    cout << "=======\n";
}
