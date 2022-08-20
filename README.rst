Line based text parser.
=======================

.. image:: https://img.shields.io/github/last-commit/jfjlaros/textparser.svg
   :target: https://github.com/jfjlaros/textparser/graphs/commit-activity
.. image:: https://github.com/jfjlaros/textparser/actions/workflows/arduino-package.yml/badge.svg
   :target: https://github.com/jfjlaros/textparser/actions/workflows/arduino-package.yml
.. image:: https://readthedocs.org/projects/arduinotextparser/badge/?version=latest
   :target: https://arduinotextparser.readthedocs.io/en/latest
.. image:: https://img.shields.io/github/release-date/jfjlaros/textparser.svg
   :target: https://github.com/jfjlaros/textparser/releases
.. image:: https://img.shields.io/github/release/jfjlaros/textparser.svg
   :target: https://github.com/jfjlaros/textparser/releases
.. image:: https://www.ardu-badge.com/badge/textparser.svg
   :target: https://www.ardu-badge.com/textparser
.. image:: https://img.shields.io/github/languages/code-size/jfjlaros/textparser.svg
   :target: https://github.com/jfjlaros/textparser
.. image:: https://img.shields.io/github/languages/count/jfjlaros/textparser.svg
   :target: https://github.com/jfjlaros/textparser
.. image:: https://img.shields.io/github/languages/top/jfjlaros/textparser.svg
   :target: https://github.com/jfjlaros/textparser
.. image:: https://img.shields.io/github/license/jfjlaros/textparser.svg
   :target: https://raw.githubusercontent.com/jfjlaros/textparser/master/LICENSE.md

----

This library provides a simple way to parse line based data.

**Features:**

- Easy to use.
- Support for all types of delimiters and line endings.
- Support for arbitrary boolean value notation.
- Support for categorical data.
- Support for integers in any base.
- Tiny overhead compared to dedicated solutions.
- Type safe.

Please see ReadTheDocs_ for the latest documentation.


Quick start
-----------

A ``TextParser`` object is initialised with a delimiter, which can consist of
more than one symbol.

.. code-block:: cpp

    #include <textparser.h>

    TextParser parser(", ");  // Delimiter is a comma followed by a space.

If all fields are of the same type, we can use an array.

.. code-block:: cpp

    int a[5];
    parser.parseLine("1, 2, 3, 4, 5", a);

If the fields have different types, we can use multiple variables.

.. code-block:: cpp

    char a[4];
    int b;
    double c;
    parser.parseLine("one, 2, 3.4, 0x38", a, b, c);


.. _ReadTheDocs: https://arduinotextparser.readthedocs.io
