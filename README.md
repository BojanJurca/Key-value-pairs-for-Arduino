# C++ key-value pairs for Arduino (ESP boards)


Key-value pairs library. Internal storage is implemented as balanced binary search for good searching performance.

Error handling (like running out of memory, etc) is also supported. 


Checking error of each function call:

```C++
    keyValuePairs<int, String>::errorCode e = kvp3.insert ( {9, "nine"} );
    if (e == kvp3.OK)
        Serial.println ("insert succeeded");
    else
        Serial.println ("insert error " + String (e));
```

Checking error of multiple operations:

```C++
    for (int i = 1000; i < 1100; i++)
        kvp3.insert (i, String (i));
    if (kvp3.lastErrorCode == kvp3.OK)
        Serial.println ("100 inserts succeeded");
    else {
        Serial.println ("100 inserts error " + String (kvp3.lastErrorCode));
        kvp3.clearLastErrorCode (); // clear lastErrorCode before next operations
    }
```

Checking success of iteration. How can it fail in the first place? At the beginning of iteration an internal stack needs to be constructed in order to iterate to a balanced binary search tree. It there is not enough memory available iteration would fail at this point:

```C++
    for (auto pair: kvp3)
        Serial.println (String (pair.key) + "-" + String (pair.value));
    if (kvp3.lastErrorCode != kvp3.OK) Serial.println ("keyValuePair iteration error " + String (kvp3.lastErrorCode));
    kvp3.clearLastErrorCode (); // clear lastErrorCode before next operations```
