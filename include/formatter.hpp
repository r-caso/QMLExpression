/*
 * SPDX-FileCopyrightText: 2024-2025 Ramiro Caso <caso.ramiro@conicet.gov.ar>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "expression.hpp"

#include <string>

namespace iif_sadaf::talk::QMLExpression {

struct Formatter {
	std::string operator()(std::shared_ptr<UnaryNode> expr) const;
	std::string operator()(std::shared_ptr<BinaryNode> expr) const;
	std::string operator()(std::shared_ptr<QuantificationNode> expr) const;
	std::string operator()(std::shared_ptr<PredicationNode> expr) const;
	std::string operator()(std::shared_ptr<IdentityNode> expr) const;
};

std::string format(const Expression& expr);

}
