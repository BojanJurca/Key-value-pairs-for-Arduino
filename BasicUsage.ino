#include <WiFi.h>

#include "keyValuePairs.h"

void setup () {
    Serial.begin (115200);

    // constructor of key-value pairs from brace enclosed initializer list
    keyValuePairs<int, String> kvp1 = { {4, "four"}, {3, "tree"}, {6, "six"}, {5, "five"} };

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
    keyValuePairs<int, String>::errorCode e = kvp3.insert ( {9, "nine"} );
    if (e == kvp3.OK)
        Serial.println ("insert succeeded");
    else
        Serial.println ("insert error " + String (e));
    
    // or checking errors of multiple operations:
    for (int i = 1000; i < 1100; i++)
        kvp3.insert (i, String (i));
    if (kvp3.lastErrorCode == kvp3.OK)
        Serial.println ("100 inserts succeeded");
    else {
        Serial.println ("100 inserts error " + String (kvp3.lastErrorCode));
        kvp3.clearLastErrorCode (); // clear lastErrorCode before next operations
    }

    // Checking success of iteration. Why would it fail? At the beginning of iteration
    // an internal stack needs to be constructed in order to iterate to balanced binary
    // search tree. It there is not enough memory avalilable iteration would fail.
    Serial.println ("--- kvp3 = ---");
    for (auto pair: kvp3)
        Serial.println (String (pair.key) + "-" + String (pair.value));
    if (kvp3.lastErrorCode != kvp3.OK) Serial.println ("keyValuePair iteration error " + String (kvp3.lastErrorCode));
    kvp3.clearLastErrorCode (); // clear lastErrorCode before next operations
}

void loop () {

}
