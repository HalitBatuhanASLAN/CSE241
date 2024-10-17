# Part A;
# Time Class - Header File

This document contains the header file (`Time.h`) for the `Time` class, which models a basic time system in hours and minutes. The class provides several functionalities, such as printing the time, modifying time values, and comparing two time objects.

## Class Overview
The `Time` class allows for:
- Storing and manipulating time in hours and minutes.
- Printing the time in `hh:mm` format.
- Comparing two `Time` objects for equality or to see if one is earlier than the other.
- Adding minutes to a `Time` object.
- Error handling for invalid time inputs (can be handled in the implementation file).

## Class Members

### Private Data Members
- `int hour`: Represents the hour part of the time.
- `int minutes`: Represents the minute part of the time.

### Public Member Functions
1. **Constructor**:
    - `Time(int h = 0, int m = 0);`
    - Initializes a `Time` object with default values of `00:00`, or user-provided values.
2. **print_time()**:
    - Displays the time in `hh:mm` format.
3. **set_min(int m)**:
    - Sets the minutes for the `Time` object.
4. **set_hour(int h)**:
    - Sets the hour for the `Time` object.
5. **get_min()**:
    - Returns the current minutes value of the `Time` object.
6. **get_hour()**:
    - Returns the current hour value of the `Time` object.
7. **is_equal(Time &t)**:
    - Compares two `Time` objects for equality.
8. **is_earlier(Time &t)**:
    - Checks if the current `Time` object is earlier than another `Time` object.
9. **add_minute(int minute)**:
    - Adds a specified number of minutes to the `Time` object.

# Part B;

# Time Class - Implementation File

This document contains the implementation file (`Time.cpp`) for the `Time` class. The file defines all the member functions declared in the `Time.h` header file, providing actual functionality such as setting time values, comparing time objects, and adding minutes.

## Implementation Overview
The `Time` class is designed to:
- Store time in hours and minutes.
- Provide methods for setting and retrieving the time values.
- Support printing time in a formatted manner (`hh:mm`).
- Compare two time objects for equality or to check if one is earlier than the other.
- Add minutes to a time object and handle any overflow in minutes to hours.
