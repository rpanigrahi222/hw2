#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    set<Product*>::iterator pit;

    for(pit = products_.begin(); pit != products_.end(); ++pit) {
        delete *pit;
    }

    set<User*>::iterator uit;

    for(uit = users_.begin(); uit != users_.end(); ++uit) {
        delete *uit;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.insert(p);

    set<string> words = p->keywords();

    set<string>::iterator it;

    for(it = words.begin(); it != words.end(); ++it) {
        string word = convToLower(*it);
        keywordMap_[word].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    users_.insert(u);

    string username = convToLower(u->getName());

    userMap_[username] = u;
}

User* MyDataStore::getUser(string username)
{
    username = convToLower(username);

    map<string, User*>::iterator it = userMap_.find(username);

    if(it == userMap_.end()) {
        return NULL;
    }

    return it->second;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> results;

    if(terms.size() == 0) {
        return results;
    }

    set<Product*>* current = NULL;

    for(unsigned int i = 0; i < terms.size(); ++i) {

        string term = convToLower(terms[i]);

        map<string, set<Product*> >::iterator mit =
            keywordMap_.find(term);

        if(mit == keywordMap_.end()) {

            if(type == 0) {
                return results;
            }
            else {
                continue;
            }
        }

        if(current == NULL) {

            current = new set<Product*>(mit->second);

        }
        else {

            set<Product*>* next =
                new set<Product*>(mit->second);

            set<Product*> combined;

            if(type == 0) {
                combined = setIntersection(*current, *next);
            }
            else {
                combined = setUnion(*current, *next);
            }

            delete current;
            delete next;

            current = new set<Product*>(combined);
        }
    }

    if(current != NULL) {

        set<Product*>::iterator it;

        for(it = current->begin(); it != current->end(); ++it) {
            results.push_back(*it);
        }

        delete current;
    }

    return results;
}

void MyDataStore::addCart(string username, Product* p)
{
    username = convToLower(username);

    carts_[username].push_back(p);
}

vector<Product*> MyDataStore::viewCart(string username)
{
    username = convToLower(username);

    return carts_[username];
}

void MyDataStore::buyCart(string username)
{
    username = convToLower(username);

    User* user = getUser(username);

    if(user == NULL) {
        return;
    }

    vector<Product*>& cart = carts_[username];

    unsigned int i = 0;

    while(i < cart.size()) {

        Product* p = cart[i];

        if(p->getQty() > 0 &&
           user->getBalance() >= p->getPrice()) {

            user->deductAmount(p->getPrice());

            p->subtractQty(1);

            cart.erase(cart.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;

    set<Product*>::iterator pit;

    for(pit = products_.begin();
        pit != products_.end();
        ++pit) {

        (*pit)->dump(ofile);
    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    set<User*>::iterator uit;

    for(uit = users_.begin();
        uit != users_.end();
        ++uit) {

        (*uit)->dump(ofile);
    }

    ofile << "</users>" << endl;
}