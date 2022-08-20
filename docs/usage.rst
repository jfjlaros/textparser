Usage
=====

A ``TextParser`` object is initialised with a delimiter, which can consist of
more than one symbol.

.. code-block:: cpp

    #include <textparser.h>

    // Delimiter is a comma followed by a space.
    TextParser parser(", ");

Optionally, an end of line string can be provided when needed.

.. code-block:: cpp

    // Strip end of line from strings.
    TextParser parser(", ", "\r\n");


Uniform types
-------------

If all fields are of the same type, we can use an array.

.. code-block:: cpp

    int a[5];
    parser.parseLine("1, 2, 3, 4, 5", a);

If the values should be of type ``float`` instead of ``int``, we simply
change the type of the receiving array.

.. code-block:: cpp

    float a[5];
    parser.parseLine("1, 2, 3, 4, 5", a);


Non-uniform types
-----------------

If the fields have different types, we can use multiple variables.

.. code-block:: cpp

    char a[4];
    int b;
    double c;
    parser.parseLine("one, 2, 3.4", a, b, c);


Boolean types
-------------

By default, integers are used to represent boolean values.

.. code-block:: cpp

    bool a;
    parser.parseLine("0", a);    // `a` contains `false`.
    parser.parseLine("1", a);    // `a` contains `true`.
    parser.parseLine("314", a);  // `a` contains `true`.

For text to boolean conversion, we first need to define a global string that
contains the truth value.

.. code-block:: cpp

    char const truth[] = "Yes";  // This needs to be a global string.

This string can then be used to create a variable of type ``Bool``.

.. code-block:: cpp

    Bool<truth> a;
    parser.parseLine("1", a);    // `a.value` contains `false`.
    parser.parseLine("Yes", a);  // `a.value` contains `true`.
    parser.parseLine("YES", a);  // `a.value` contains `false`.


Categorical data
----------------

For categorical data, we need to define a global zero terminated list of
labels.

.. code-block:: cpp

    char const* labels[] = {"red", "green", "blue", nullptr};

These labels can then be used to create a variable of type ``Category``.

.. code-block:: cpp

    Category<int, labels> a;
    parser.parseLine("red", a);     // `a.value` contains 0.
    parser.parseLine("blue", a);    // `a.value` contains 2.
    parser.parseLine("yellow", a);  // `a.value` contains -1.


Integers in other bases
-----------------------

Integers in arbitrary bases are supported via the `Number` type.

.. code-block:: cpp

    Number<int, 16> a;  // Hexadecimal number.
    Number<int, 2> a;   // Binary number.
    parser.parseLine("0x1f, 101001", a, b);


Examples
--------

Please see the demo_ sketch for an example of basic usage.


.. _demo: https://github.com/jfjlaros/textparser/blob/master/examples/demo/demo.ino
