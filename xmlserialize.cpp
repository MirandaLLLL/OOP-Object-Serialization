#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "tinyxml2.h"

#pragma once
//delete pointer
#define SAFE_DELETE(pRet) if(pRet != NULL) {delete pRet;pRet = NULL;}
//check whether key in xml subsistent£¬structure of xml is known£¬if isn't subsistent£¬withdrawal immediatly
#define KEY_IS_NULL(key) if(key == nullptr){printf("%s is not found\n",#key);exit(-1);}

class Std_pair;
class Std_pair
{
public:
    std::string num;
    Std_pair(const std::string& num) :num(num) {}
};


class Serialization
{
public:
    std::string num;
    std::vector<Std_pair> vStd_pairs;

public:
    Serialization(const std::string& num) : num(num) {}
    Serialization() {}


    /**
     *  Serialize a member of this class to a fixed XML file
     */
    template<typename T>
    int serializeXML(T& doc, const std::string& fileName)
    {
        //head of xml
        const char* declaration = R"(<?xml version="1.0" encoding="UTF-16"?>)";

        //Parses a string into a DOM object
        doc.Parse(declaration);

        //new a key
        //serialize std::string name;
        auto roof = doc.NewElement("serialization");
        auto keyserialization = doc.NewElement("num");

        //insert value
        keyserialization->InsertEndChild(doc.NewText(num.c_str()));

        //insert</>
        roof->InsertEndChild(keyserialization);
        doc.InsertEndChild(roof);

        //serialize std::vector<vstd_pairs> vstd_pairs;
        for (auto std_pairs : vStd_pairs)
        {
            auto keyStd_pair = doc.NewElement("std_pairs");
            roof->InsertEndChild(keyStd_pair);
            auto keyStd_pairNum = doc.NewElement("num");
            keyStd_pairNum->InsertEndChild(doc.NewText(std_pairs.num.c_str()));
            keyStd_pair->InsertEndChild(keyStd_pairNum);

        }
        //save as xml file
        return doc.SaveFile(fileName.c_str());
    }
};