/*
 * SPDX-FileCopyrightText: 2024-2025 Ramiro Caso <caso.ramiro@conicet.gov.ar>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "expression.hpp"

namespace iif_sadaf::talk::QMLExpression {

UnaryNode::UnaryNode(Operator op, Expression scope)
    : op(op), scope(std::move(scope))
{ }

BinaryNode::BinaryNode(Operator op, Expression lhs, Expression rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs))
{ }

QuantificationNode::QuantificationNode(Quantifier quantifier, Term variable, Expression scope)
    : quantifier(quantifier), variable(std::move(variable)), scope(std::move(scope))
{ }

IdentityNode::IdentityNode(Term lhs, Term rhs)
    : lhs(std::move(lhs)), rhs(std::move(rhs))
{ }

PredicationNode::PredicationNode(std::string predicate, std::vector<Term> arguments)
    : predicate(std::move(predicate)), arguments(std::move(arguments))
{ }

}