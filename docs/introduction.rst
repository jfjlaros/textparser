Introduction
============

Data is often presented as `delimiter separated values`_ (e.g., CSV, TSV,
...), which makes parsing of these formats a common task.

Here we introduce a lightweight and straightforward method for parsing
delimiter separated files where the user only needs to specify a delimiter
(and optionally a line ending delimiter) and a structure to receive the
parsed data. This structure can be of any basic type, a string or an array.


Motivation
----------

Suppose we want to parse a string containing five integers and store the
result in an array. A straightforward way of doing this would be:

.. code-block:: cpp

    char const line[] = "1, 2, 3, 4, 5";

    int a[5];
    char* endptr = const_cast<char*>(line);
    for (size_t i = 0; i < 5; i++) {
      a[i] = strtol(endptr, &endptr, 10);
      (*endptr) += 2;
    }

If however, we decide that the type of the values should be ``float`` instead
of ``int``, we need to change two lines:

.. code-block:: cpp

    float a[5];                        // This one.
    char* endptr = const_cast<char*>(line);
    for (size_t i = 0; i < 5; i++) {
      a[i] = strtod(endptr, &endptr);  // And this one.
      (*endptr) += 2;
    }

If we need to alternate between the types ``float`` and ``int``, the
structure of the code changes completely:

.. code-block:: cpp

    float a, c, e;
    int b, d;
    char* endptr = const_cast<char*>(line);
    a = strtod(endptr, &endptr);
    (*endptr) += 2;
    b = strtol(endptr, &endptr, 10);
    (*endptr) += 2;
    c = strtod(endptr, &endptr);
    (*endptr) += 2;
    d = strtol(endptr, &endptr, 10);
    (*endptr) += 2;
    e = strtod(endptr, &endptr);

This library aims to provide a more uniform method to solve these problems.
When we look at the example where we want to extract five integers from a
string, the following piece of code is needed:

.. code-block:: cpp

    char const line[] = "1, 2, 3, 4, 5";
    TextParser parser(", ");

    int a[5];
    parser.parseLine("1, 2, 3, 4, 5", a);

If again, we decide that the type of the values should be ``float``, we now
only have to change one line of code:

.. code-block:: cpp

    float a[5];  // This one.
    parser.parseLine("1, 2, 3, 4, 5", a);

Similarly, more complex arrangements like the alternating types are handled
as follows:

.. code-block:: cpp

    float a, c, e;
    int b, d;
    parser.parseLine("1, 2, 3, 4, 5", a, b, c, d, e);


Further Reading
---------------

Please see the :doc:`usage` section for more information about this library.

If this library does not meet your requirements, then perhaps the
`CSV parser for Arduino`_ may be of use.


.. _`delimiter separated values`: https://en.wikipedia.org/wiki/Delimiter-separated_values
.. _`CSV parser for Arduino`: https://github.com/michalmonday/CSV-Parser-for-Arduino
