# QML Expression

An implementation of Abstract Syntax Trees for formulas of Quantified Modal Logic.

This library has been developed as part of my work as a Researcher at [IIF/SADAF/CONICET](https://iif.conicet.gov.ar/?lan=en) and as member of the [Talk Group](https://talk-group.org/).

## Description

This library is designed to work as an interface between parser libraries and semantic evaluation libraries. The general description of this intended architecture is:

![Intended parser-evaluator architecture](parser_evaluator_architecture.png)

## Overview

The QMLExpression library has two main components:

- an expression library that defined `Expression` objects
- a convenience formatting library, that defines a `Formatter` visitor for `Expression` objects

`Expression` objects are `std::variant` objects with any of the following possible values:

- a `std::shared_ptr` to a `UnaryNode`
- a `std::shared_ptr` to a `BinaryNode`
- a `std::shared_ptr` to a `QuantificationNode`
- a `std::shared_ptr` to an `IdentityNode`
- a `std::shared_ptr` to a `PredicationNode`

You can check the declarations [here](include/expression.hpp). There you will find as well a `Term` class for the singular terms of the language, which may be of type `Term::Type::VARIABLE` or `Term::Type::CONSTANT`.

The `Formatter` visitor produces `std::string` representations of the provided `Expression` objects.

## Directory structure

```
/
├── include/           # Public headers
└── src/               # Implementation files
```

## Build and install

Clone the repository:
```bash
git clone git@github.com:r-caso/QMLExpression.git
```

### Prerequisites

- C++23 compatible compiler
- CMake 3.22 or newer

### Building

In order to build the library, navigate to the QMLExpression project root folder, and do the following:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
You can use `cmake .. -DCMAKE_BUILD_TYPE=Relase` for a Release build, and `cmake .. -DCMAKE_BUILD_TYPE=Debug` for a Debug build.

### Installing

To install the QMLExpression as a system library:
```bash
cmake --install .
```
If you want to install it to a different location (non-system library), then specify the desired path:
```bash
cmake --install . --prefix /path/to/library_dir
```

## Usage

### Inclusion in other CMake projects

To use the library in another project, you need to add the following line to the `CMakeLists.txt` of the project using the library:

```cmake
find_package(QMLExpression REQUIRED)
```
If you have installed the QMLExpression library in a non-standard path, you will need to tell CMake, either through the command line:
```bash
cmake [directory containing CMakeLists.txt] -DCMAKE_PREFIX_PATH=/path/to/QMLExpression
```
or by adding the corresponding key-value pair to the `cacheVariables` section of CMakePresets.json:
```
{
	...
	"cacheVariables" : {
		...
		"CMAKE_PREFIX_PATH": "/path/to/QMLExpression"
		...
	}
	...
}
```
Then, you need to link the library to your target:
```cmake
target_link_libraries(your_target [PUBLIC|PRIVATE]
    QMLExpression::QMLExpression
    # other libraries
)
```

### Declaring and formatting

The different components of the QMLExpression library can be accessed through the following include directive:
```c++
#include <QMLExpression/expression.hpp>
#include <QMLExpression/formatter.hpp>
```
Alternatively, you may include both components with a single header:
```c++
#include <QMLExpression/QMLExpression.hpp>
```

#### Introducing `Expression` objects

A few examples:
```c++
// constructing Term objects for use in building ASTs
namespace QExpr = iif_sadaf::talk::QMLExpression;

const QExpr::Term x("x", QExpr::Term::Type::VARIABLE);
const QExpr::Term y("y", QExpr::Term::Type::VARIABLE);
const QExpr::Term a("a", QExpr::Term::Type::CONSTANT);
```

```c++
// constructing the variants

const auto predication1 = std::make_shared<QExpr::PredicationNode>(
	"F",
	std::vector<QExpr::Term>{x}
);

const auto predication2 = std::make_shared<QExpr::PredicationNode>(
	"G",
	std::vector<QExpr::Term>{x, a}
);

const auto disjunction = std::make_shared<QExpr::BinaryNode>(
	QExpr::Operator::DISJUNCTION,
	predication1,
	predication2
);

const auto negation = std::make_shared<QExpr::UnaryNode>(
	QExpr::Operator::NEGATION,
	disjunction
);

const auto universal = std::make_shared<QExpr::QuantificationNode>(
	QExpr::Quantifier::UNIVERSAL,
	x,
	predication1
);
```

```c++
// turning the variants into Expression objects

const QExpr::Expression negation_expr(negation);
const QExpr::Expression universal_expr(negation);
```

#### Formatting `Expression` objects

A formatter visitor for `Expression` objects is provided as well, with the purpose of being a quick way of rendering any `Expression` object as a QML formula. This visitor can be accessed directly:
```c++
const std::string formula = std::visit(QExpr::Formatter(), expr);
```
It can also be accessed through the `format()` convenience function:
```c++
const std::string formula = QExpr::formt(expr);
```

## Contributing

Contributions are more than welcome. If you want to contribute, please do the following:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature-name`.
3. Make your changes.
4. Push your branch: `git push origin feature-name`.
5. Create a pull request.

## License
This project is licensed under the [BSD-3-Clause](LICENSE).
