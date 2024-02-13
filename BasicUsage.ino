#include <WiFi.h>

#include "keyValuePairs.hpp"

void setup () {
    Serial.begin (115200);

    // constructor of key-value pairs from brace enclosed initializer list
    keyValuePairs<int, String> kvp1 = { {4, "four"}, {3, "tree"}, {6, "six"}, {5, "five"} };

    for (auto pair: kvp1)
        Serial.println (String (pair.key) + "-" + String (pair.value));

    // copy-constructor
    keyValuePairs<int, String> kvp2 = kvp1;

    // key-valu pairs assignment
    keyValuePairs<int, String> kvp3;
    kvp3 = kvp2;

    // insert new pair
    kvp3.insert ( {7, "seven"} );
    // or
    kvp3.insert ( 8, "eight" );

    // find a value for given key
    String *value = kvp3.find (3);
    if (value == NULL) {
        if (kvp3.lastErrorCode == kvp3.BAD_ALLOC) Serial.println ("Out of memory");         // only if key is of type String and find parameter could not be constructed doe to lack of memory
        else                                      Serial.println ("Key not found");
    }
    else                                          Serial.println ("Key found, its value = " + *value);

    // delete a pair identified by the key
    kvp3.erase (4);

    // scan key-value pairs in accending (sorted) order
    Serial.println ("--- kvp3 = ---");
    for (auto pair: kvp3)
        Serial.println (String (pair.key) + "-" + String (pair.value));

    // checking error of each function call:
    int e = kvp3.insert ( {9, "nine"} );
    if (e == kvp3.OK)
        Serial.println ("insert succeeded");
    else
        Serial.printf ("insert error: %s\n", kvp3.errorCodeText (e));
    
    // or checking errors of multiple operations:
    for (int i = 1000; i < 1100; i++)
        kvp3.insert (i, String (i));

    if (kvp3.lastErrorCode == kvp3.OK)
        Serial.println ("100 inserts succeeded");
    else {
        Serial.printf ("100 inserts error: %s\n", kvp3.errorCodeText (kvp3.lastErrorCode));
        kvp3.clearLastErrorCode (); // clear lastErrorCode before next operations
    }

    // find min (max) values
    Serial.println ("--- min_element, max_element ---");
    auto minElement = min_element (kvp3);
    if (minElement) // check if min element is found (if kvp3 is not empty)
        Serial.printf ("min element (min value) of kvp3 = (%i, %s)\n", (*minElement).key, (*minElement).value.c_str ());
    auto maxElement = max_element (kvp3);
    if (maxElement) // check if max element is found (if kvp3 is not empty)
        Serial.printf ("max element (max value) of kvp3 = (%i, %s)\n", (*maxElement).key, (*maxElement).value.c_str ());


    // find first (last) keys
    Serial.println ("--- first_element, last_element ---");
    auto firstElement = first_element (kvp3);
    if (firstElement) // check if first element is found (if kvp3 is not empty)
        Serial.printf ("first element (min key) of kvp3 = (%i, %s)\n", (*firstElement).key, (*firstElement).value.c_str ());

    auto lastElement = last_element (kvp3);
    if (lastElement) // check if last element is found (if kvp3 is not empty)
        Serial.printf ("last element (max key) of kvp3 = (%i, %s)\n", (*lastElement).key, (*lastElement).value.c_str ());

}

void loop () {

}
