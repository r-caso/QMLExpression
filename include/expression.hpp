/*
 * SPDX-FileCopyrightText: 2024-2025 Ramiro Caso <caso.ramiro@conicet.gov.ar>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace iif_sadaf::talk::QMLExpression {

/**
 * @brief Represents a term in a QML expression.
 */
struct Term {
    /**
     * @brief Enum representing the type of term.
     */
    enum class Type : uint8_t {
        CONSTANT,
        VARIABLE
    };

    std::string literal; /**< The string representation of the term. */
    Type type;           /**< The type of the term (constant or variable). */
};

struct UnaryNode;
struct BinaryNode;
struct QuantificationNode;
struct IdentityNode;
struct PredicationNode;

/**
 * @brief Represents a generic QML expression using a variant type.
 */
using Expression = std::variant<
    std::shared_ptr<UnaryNode>,
    std::shared_ptr<BinaryNode>,
    std::shared_ptr<QuantificationNode>,
    std::shared_ptr<IdentityNode>,
    std::shared_ptr<PredicationNode>
>;

/**
 * @brief Enum representing logical and modal operators.
 */
enum class Operator : uint8_t {
    NEGATION,
    CONJUNCTION, DISJUNCTION,
    CONDITIONAL, CONDITIONAL_MATERIAL, CONDITIONAL_STRICT,
    BICONDITIONAL,
    ACTUALITY,
    NECESSITY, POSSIBILITY,
    EPISTEMIC_NECESSITY, EPISTEMIC_POSSIBILITY,
    DEONTIC_NECESSITY, DEONTIC_POSSIBILITY,
    NORMAL_NECESSITY, NORMAL_POSSIBILITY,
};

/**
 * @brief Enum representing quantifiers in QML.
 */
enum class Quantifier : uint8_t {
    EXISTENTIAL,
    UNIVERSAL
};

/**
 * @brief Represents a unary QML formula.
 */

struct UnaryNode {
    UnaryNode(Operator op, Expression scope);

    Operator op;
    Expression scope;
};

/**
 * @brief Represents a binary QML formula.
 */
struct BinaryNode {
    BinaryNode(Operator op, Expression lhs, Expression rhs);

    Operator op;
    Expression lhs;
    Expression rhs;
};

/**
 * @brief Represents a quantified QML formula.
 */
struct QuantificationNode {
    QuantificationNode(Quantifier quantifier, Term variable, Expression scope);

    Quantifier quantifier;
    Term variable;
    Expression scope;
};

/**
 * @brief Represents an identity atomic formula.
 */
struct IdentityNode {
    IdentityNode(Term lhs, Term rhs);

    Term lhs;
    Term rhs;
};

/**
 * @brief Represents a predicative atomic formula.
 */
struct PredicationNode {
    PredicationNode(std::string predicate, std::vector<Term> arguments);

    std::string predicate;
    std::vector<Term> arguments;
};

}
