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

struct Term {
    enum class Type : uint8_t {
        CONSTANT,
        VARIABLE
    };

    std::string literal;
    Type type;
};

struct UnaryNode;
struct BinaryNode;
struct QuantificationNode;
struct IdentityNode;
struct PredicationNode;

using Expression = std::variant<
    std::shared_ptr<UnaryNode>,
    std::shared_ptr<BinaryNode>,
    std::shared_ptr<QuantificationNode>,
    std::shared_ptr<IdentityNode>,
    std::shared_ptr<PredicationNode>
>;

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

enum class Quantifier : uint8_t {
    EXISTENTIAL,
    UNIVERSAL
};

struct UnaryNode {
    UnaryNode(Operator op, Expression scope);

    Operator op;
    Expression scope;
};

struct BinaryNode {
    BinaryNode(Operator op, Expression lhs, Expression rhs);

    Operator op;
    Expression lhs;
    Expression rhs;
};

struct QuantificationNode {
    QuantificationNode(Quantifier quantifier, Term variable, Expression scope);

    Quantifier quantifier;
    Term variable;
    Expression scope;
};

struct IdentityNode {
    IdentityNode(Term lhs, Term rhs);

    Term lhs;
    Term rhs;
};

struct PredicationNode {
    PredicationNode(std::string predicate, std::vector<Term> arguments);

    std::string predicate;
    std::vector<Term> arguments;
};

}
