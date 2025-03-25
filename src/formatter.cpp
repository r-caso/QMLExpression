/*
 * SPDX-FileCopyrightText: 2024-2025 Ramiro Caso <caso.ramiro@conicet.gov.ar>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "formatter.hpp"

#include <format>
#include <unordered_map>

namespace iif_sadaf::talk::QMLExpression {

namespace {
    const std::unordered_map<Operator, std::string> operatorToString = {
        { Operator::NEGATION, "¬"},
        { Operator::CONJUNCTION, "∧"},
        { Operator::DISJUNCTION, "∨"},
        { Operator::CONDITIONAL, "→"},
        { Operator::CONDITIONAL_MATERIAL, "⊃"},
        { Operator::BICONDITIONAL, "↔"},
        { Operator::NECESSITY, "□"},
        { Operator::POSSIBILITY, "⋄"},
        { Operator::EPISTEMIC_NECESSITY, "Must "},
        { Operator::EPISTEMIC_POSSIBILITY, "Might "},
        { Operator::DEONTIC_NECESSITY, "Ought "},
        { Operator::DEONTIC_POSSIBILITY, "May "},
        { Operator::NORMAL_NECESSITY, "Normally "},
        { Operator::NORMAL_POSSIBILITY, "Sometimes "},
    };

    const std::unordered_map<Quantifier, std::string> quantifierToString = {
        { Quantifier::UNIVERSAL, "∀" },
        { Quantifier::EXISTENTIAL, "∃" },
    };
}

/**
 * @brief Formats a unary node as a string.
 * @param expr Shared pointer to a UnaryNode.
 * @return The formatted string representation.
 */
std::string Formatter::operator()(std::shared_ptr<UnaryNode> expr) const
{
    if (expr->op == Operator::NEGATION && std::holds_alternative<std::shared_ptr<IdentityNode>>(expr->scope)) {
        std::string prejacent = std::visit(Formatter(), expr->scope);
        const std::string::size_type pos = prejacent.find('=');
        prejacent.replace(pos, 1, "≠");
        return prejacent;
    }

    return std::format("{}{}"
                      , operatorToString.at(expr->op)
                      , std::visit(Formatter(), expr->scope)
    );
}

/**
 * @brief Formats a binary node as a string.
 * @param expr Shared pointer to a BinaryNode.
 * @return The formatted string representation.
 */
std::string Formatter::operator()(std::shared_ptr<BinaryNode> expr) const
{
    return std::format("({} {} {})"
                      , std::visit(Formatter(), expr->lhs)
                      , operatorToString.at(expr->op)
                      , std::visit(Formatter(), expr->rhs)
    );
}

/**
 * @brief Formats a quantification node as a string.
 * @param expr Shared pointer to a QuantificationNode.
 * @return The formatted string representation.
 */
std::string Formatter::operator()(std::shared_ptr<QuantificationNode> expr) const
{
    return std::format("{}{} {}"
                      , quantifierToString.at(expr->quantifier)
                      , expr->variable.literal
                      , std::visit(Formatter(), expr->scope)
    );
}

/**
 * @brief Formats a predication node as a string.
 * @param expr Shared pointer to a PredicationNode.
 * @return The formatted string representation.
 */
std::string Formatter::operator()(std::shared_ptr<PredicationNode> expr) const
{
    std::string argument_list;

    for (const Term& arg : expr->arguments) {
        argument_list += arg.literal + ", ";
    }

    argument_list.resize(argument_list.size() - 2);

    return std::format("{}({})"
                      , expr->predicate
                      , argument_list
    );
}

/**
 * @brief Formats an identity node as a string.
 * @param expr Shared pointer to an IdentityNode.
 * @return The formatted string representation.
 */
std::string Formatter::operator()(std::shared_ptr<IdentityNode> expr) const
{
    return std::format("{} = {}"
                      , expr->lhs.literal
                      , expr->rhs.literal
    );
}

/**
 * @brief Formats a generic QML expression as a string.
 * @param expr The expression to format.
 * @return The formatted string representation.
 */
std::string format(const Expression& expr)
{
    return std::visit(Formatter(), expr);
}

}