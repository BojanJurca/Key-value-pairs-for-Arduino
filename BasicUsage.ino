#include <WiFi.h>

#include "keyValuePairs.hpp"

void setup () {
    Serial.begin (115200);
    delay (3000);


    // Examples of key-value pairs constructors
    keyValuePairs<int, String> kvp1;                                                          // empty key-value pairs where keys will be integere and values is Strings
    keyValuePairs<int, int> kvp2 ( { {1, 10}, {2, 20}, {3, 30} });                            // constructor of key-value pairs <int, int> from brace enclosed initializer list
    keyValuePairs<int, String> kvp3 = { {4, "four"}, {3, "tree"}, {6, "six"}, {5, "five"} };  // constructor of key-value pairs <int, String> and their initialization from brace enclosed initializer list 
    keyValuePairs<int, String> kvp4 = kvp3;                                                   // copy-constructor


    // Examples of key-valu pairs assignment
    kvp1 = { {5, "five"}, {6, "six"} };
    kvp3 = kvp1;


    // Examples of inserting new key-value pairs
    kvp3.insert ( {7, "seven"} );
    kvp3.insert ( 8, "eight" );


    // Example of finding a value for a given key
    String *strValue = kvp3.find (6);
    if (strValue != NULL) // OK
        Serial.println ("Key found, its value = " + *strValue); 
    else
        Serial.println ("Key not found");

    // when the key is an object (like String) more things can go wrong and more checking is needed
    keyValuePairs<String, int> kvp5 = { {"four", 4}, {"tree", 3}, {"six", 6}, {"five", 5} }; 

    kvp5.clearErrorFlags ();  // clear possible error flags from previous operations
    int *intValue = kvp5.find ("six");
    if (intValue != NULL) // OK
        Serial.println ("Key found, its value = " + String (*intValue)); 
    else {
        // the key probably doesn't exist but we can't be 100% sure that some other error didn't occur
        if (kvp5.errorFlags () & NOT_FOUND)  Serial.println ("Key not found");  
        else {
            Serial.print ("An error occured while searching for the key ");
            // check flags for details
            if (kvp5.errorFlags () & BAD_ALLOC)      Serial.printf ("BAD_ALLOC\n");
            if (kvp5.errorFlags () & NOT_FOUND)      Serial.printf ("NOT_FOUND\n");
            if (kvp5.errorFlags () & NOT_UNIQUE)     Serial.printf ("NOT_UNIQUE\n");
            if (kvp5.errorFlags () & CANT_DO_IT_NOW) Serial.printf ("CANT_DO_IT_NOW\n");
        }
    }


    // Example of deleting key-value pair for a given key
    kvp4.erase (4);


    // Examples of scanning through key-value pairs (in ascending order of keys) with and iterator
    for (auto pair: kvp3)
        Serial.println (String (pair->key) + "-" + pair->value);


    // Finding the first and the last key-value pairs (min and max keys)
    auto firstElement = first_element (kvp3);
    if (firstElement) // check if first element is found (if kvp3 is not empty)
        Serial.printf ("first element (min key) of kvp3 = (%i, %s)\n", (*firstElement)->key, (*firstElement)->value.c_str ());

    auto lastElement = last_element (kvp3);
    if (lastElement) // check if last element is found (if kvp3 is not empty)
        Serial.printf ("last element (max key) of kvp3 = (%i, %s)\n", (*lastElement)->key, (*lastElement)->value.c_str ());


    // Finding min and max key-value pairs (min and max values)
    auto minElement = min_element (kvp3);
    if (minElement) // check if min element is found (if kvp3 is not empty)
        Serial.printf ("min element (min value) of kvp3 = (%i, %s)\n", (*minElement)->key, (*minElement)->value.c_str ());

    auto maxElement = max_element (kvp3);
    if (maxElement) // check if max element is found (if kvp3 is not empty)
        Serial.printf ("max element (max value) of kvp3 = (%i, %s)\n", (*maxElement)->key, (*maxElement)->value.c_str ());


    // Detecting errors that occured in key-value pairs operations
    signed char e = kvp3.insert ( {9, "nine"} );
    if (!e) // OK
        Serial.println ("insert succeeded");
    else {
        // report error or check flags
        Serial.printf ("insert error: ");
        switch (e) {
            case BAD_ALLOC:       Serial.printf ("BAD_ALLOC\n"); break;
            case NOT_FOUND:       Serial.printf ("NOT_FOUND\n"); break;
            case NOT_UNIQUE:      Serial.printf ("NOT_UNIQUE\n"); break;
            case CANT_DO_IT_NOW:  Serial.printf ("CANT_DO_IT_NOW\n"); break;
        }
    }


    // Checking if an error has occurred only once after many key-value pairs operations
    kvp3.clearErrorFlags ();  // clear possible error flags from previous operations
    for (int i = 1000; i < 1100; i++)
        kvp3.insert (i, String (i));

    e = kvp3.errorFlags ();
    if (!e) // OK
        Serial.println ("100 inserts succeeded");
    else {
        Serial.printf ("100 inserts error: ");  // check flags for details
        if (e & BAD_ALLOC)      Serial.printf ("BAD_ALLOC\n");
        if (e & NOT_FOUND)      Serial.printf ("NOT_FOUND\n");
        if (e & NOT_UNIQUE)     Serial.printf ("NOT_UNIQUE\n");
        if (e & CANT_DO_IT_NOW) Serial.printf ("CANT_DO_IT_NOW\n");
    }


                // capacity and speed test
                keyValuePairs<unsigned long, unsigned long> kvp6;
                unsigned long l;
                unsigned long startMillis = millis ();
                for (l = 1; l <= 100000; l++) {
                    if (kvp6.insert ( { l, l } ))
                        break;
                }
                unsigned long endMillis = millis ();
                Serial.printf ("Free heap: %lu, free PSRAM: %lu\n", ESP.getFreeHeap (), ESP.getFreePsram ());
                kvp6.clear ();
                Serial.printf ("Maximum number of keyValuePairs<unsigned long, unsigned long> in the memory is %lu\n", l); // ESP32-S2: heap: 64231, PSRAM: 58197
                Serial.printf ("Average insert time = %lu us\n", (endMillis - startMillis) * 1000 / l);
                Serial.printf ("Free heap: %lu, free PSRAM: %lu\n", ESP.getFreeHeap (), ESP.getFreePsram ());
}

void loop () {

}
