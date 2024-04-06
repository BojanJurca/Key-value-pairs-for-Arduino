# Key-value pairs for Arduino (ESP boards)


This is an in-memory key-value pairs library. Internal storage is implemented as balanced binary search tree for good performance. 


### Examples of key-value pairs constructors

```C++
vector<String> v1;                          // empty vector of Strings
vector<int> v2 ( { 100, 200, 300, 400 } );  // constructor of vector of integers from brace enclosed initializer list
vector<int> v3 = { 500, 600, 700, 800 };    // constructor of vector of integers and its initialization from brace enclosed initializer list
vector<int> v4 = v3;                        // copy-constructor
```

### Examples of key-value pairs assignment

```C++
v2 = { 3, 2, 1 };                           // assignment from brace enclosed initializer list
v3 = v2;                                    // assignemnt from another vector
```


### Examples of inserting new key-value pair

```C++
kvp3.insert ( {7, "seven"} );
kvp3.insert ( 8, "eight" );
```


### Examples of searching for value that belongs to a given key

```C++
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
```


### Example of deleting key-value pair for a given key

```C++
kvp4.erase (4);
```


### Examples of scanning through key-value pairs (in ascending order of keys)

```C++
for (auto pair: kvp3)
    Serial.println (String (pair->key) + "-" + pair->value);
```


### Finding the first and the last key-vlue pairs (min and max keys)

```C++
auto firstElement = first_element (kvp3);
if (firstElement) // check if first element is found (if kvp3 is not empty)
    Serial.printf ("first element (min key) of kvp3 = (%i, %s)\n", (*firstElement)->key, (*firstElement)->value.c_str ());

auto lastElement = last_element (kvp3);
if (lastElement) // check if last element is found (if kvp3 is not empty)
    Serial.printf ("last element (max key) of kvp3 = (%i, %s)\n", (*lastElement)->key, (*lastElement)->value.c_str ());
```


### Finding min and max key-value pairs (min and max values)

```C++
auto minElement = min_element (kvp3);
if (minElement) // check if min element is found (if kvp3 is not empty)
    Serial.printf ("min element (min value) of kvp3 = (%i, %s)\n", (*minElement)->key, (*minElement)->value.c_str ());

auto maxElement = max_element (kvp3);
if (maxElement) // check if max element is found (if kvp3 is not empty)
    Serial.printf ("max element (max value) of kvp3 = (%i, %s)\n", (*maxElement)->key, (*maxElement)->value.c_str ());
```


### Detecting errors that occured in key-value pairs operations

```C++
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
```


### Checking if an error has occurred only once after many key-value pairs operations

```C++
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

```
