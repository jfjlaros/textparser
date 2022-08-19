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

Finally, a boolean truth value can be defined to enable text based boolean
parsing.

.. code-block:: cpp

    // Configure boolean text parsing.
    TextParser parser(", ", nullptr, "TRUE");


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

If boolean text parsing is enabled, only an exact string match with the given
truth vale will result in a variable being set to ``true``.

.. code-block:: cpp

    TextParser parser(", ", nullptr, "Yes");
    bool a;
    parser.parseLine("1", a);    // `a` contains `false`.
    parser.parseLine("Yes", a);  // `a` contains `true`.
    parser.parseLine("YES", a);  // `a` contains `false`.


Examples
--------

Please see the demo_ sketch for an example of basic usage and the multilevel_
sketch for a more complicated example.


.. _demo: https://github.com/jfjlaros/textparser/blob/master/examples/demo/demo.ino
.. _multilevel: https://github.com/jfjlaros/textparser/blob/master/examples/multilevel/multilevel.ino
