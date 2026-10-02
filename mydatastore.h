#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <string>
#include <vector>
#include <set>

class MyDataStore : public DataStore
{
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);

    User* getUser(std::string username);

    void addCart(std::string username, Product* p);
    std::vector<Product*> viewCart(std::string username);
    void buyCart(std::string username);

    std::vector<Product*> search(std::vector<std::string>& terms,
                                 int type);

    void dump(std::ostream& ofile);

private:
    std::set<Product*> products_;
    std::set<User*> users_;

    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, User*> userMap_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif