#ifndef COMPARISON_H
#define COMPARISON_H

#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"

// This stores an individual comparison that is part of a CNF

class Comparison {
    friend class ComparisonEngine;
    friend class CNF;
public:         // TODO restore visibility

    Target operand1;
    int whichAtt1;
    Target operand2;
    int whichAtt2;

    Type attType;

    CompOperator op;


    Comparison();

    //copy constructor
    Comparison(const Comparison &copyMe);

    // print to the screen
    void Print();
};

class Schema;

// This structure encapsulates a sort order for records

class OrderMaker {
    friend class ComparisonEngine;
    friend class CNF;

public:         // TODO restore visibility

    int numAtts;

    int whichAtts[MAX_ANDS];
    Type whichTypes[MAX_ANDS];


    // creates an empty OrdermMaker
    OrderMaker();

    // create an OrderMaker that can be used to sort records
    // based upon ALL of their attributes
    OrderMaker(Schema *schema);

    // print to the screen
    void Print();
};

class Record;

// This structure stores a CNF expression that is to be evaluated
// during query execution

class CNF {
    friend class ComparisonEngine;

public:         // TODO restore the visibility 
    
    // store as a 2d array, for the two dimensions:
    // each 1d array stores <=MAX_ORS * comparisons of the inner OR expression
    // multiple 1d arrays are connected together as the outer AND expression
    Comparison orList[MAX_ANDS][MAX_ORS];

    // records the actual length of each inner OR expression i.e. # of ORs
    int orLens[MAX_ANDS];
    // records the actual length of entire outer AND expression i.e. # of ANDs
    int numAnds;


    // this returns an instance of the OrderMaker class that
    // allows the CNF to be implemented using a sort-based
    // algorithm such as a sort-merge join.  Returns a 0 if and
    // only if it is impossible to determine an acceptable ordering
    // for the given comparison
    int GetSortOrders(OrderMaker &left, OrderMaker &right);

    // print the comparison structure to the screen
    void Print();

    // this takes a parse tree for a CNF and converts it into a 2-D
    // matrix storing the same CNF expression.  This function is applicable
    // specifically to the case where there are two relations involved
    void GrowFromParseTree(struct AndList *parseTree, Schema *leftSchema,
            Schema *rightSchema, Record &literal);

    // version of the same function, except that it is used in the case of
    // a relational selection over a single relation so only one schema is used
    void GrowFromParseTree(struct AndList *parseTree, Schema *mySchema,
            Record &literal);

};

#endif
