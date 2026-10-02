#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> final;

    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();

    while(it1 != s1.end() && it2 != s2.end()) {
        if(*it1 < *it2) {
            it1++;
        }
        else if(*it2 < *it1) {
            it2++;
        }
        else {
            final.insert(*it1);
            it1++;
            it2++;
        }
    }

    return final;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> final;

    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();

    while(it1 != s1.end() && it2 != s2.end()) {
        if(*it1 < *it2) {
            final.insert(*it1);
            it1++;
        }
        else if(*it1 > *it2) {
            final.insert(*it2);
            it2++;
        }
        else {
            final.insert(*it1);
            it1++;
            it2++;
        }
    }

    while(it1 != s1.end()) {
        final.insert(*it1);
        it1++;
    }

    while(it2 != s2.end()) {
        final.insert(*it2);
        it2++;
    }

    return final;
}

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

std::string &ltrim(std::string &s);

std::string &rtrim(std::string &s);

std::string &trim(std::string &s);

#endif