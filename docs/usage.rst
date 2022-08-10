Usage
=====

A ``TextParser`` object is initialised with a delimiter, which can consist of
more than one symbol.

.. code-block:: cpp

    #include <textparser.h>

    TextParser parser(", ");  // Delimiter is a comma followed by a space.

Optionally, an end of line string can be provided when needed.

.. code-block:: cpp

    TextParser parser(", ", "\r\n");  // Strip end of line from strings.

If all fields are of the same type, we can use an array.

.. code-block:: cpp

    int a[5];
    parser.parseLine("1, 2, 3, 4, 5", a);

If the fields have different types, we can use multiple variables.

.. code-block:: cpp

    char a[10];
    int b;
    double c;
    parser.parseLine("one, 2, 3.4", a, b, c);
