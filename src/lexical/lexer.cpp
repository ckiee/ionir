#define IONIR_MATCH_INDEX_MATCHED 0
#define IONIR_MATCH_INDEX_CAPTURED 1
#define IONIR_LEXER_INDEX_DEFAULT 0

#include <ionir/lexical/lexer.h>

namespace ionir {
    Lexer::Lexer(const std::string &input)
        : input(input), length(input.length()), index(IONIR_LEXER_INDEX_DEFAULT), simpleIds(TokenConst::getSortedSimpleIds()), complexIds(TokenConst::getComplexIds()) {
        // Input string must contain at least one character.
        if (!this->length || this->length < 1) {
            throw std::invalid_argument("Input must be a string with one or more character(s)");
        }
    }

    char Lexer::getChar() const noexcept {
        // Return null character if reached end of input.
        if (!this->hasNext()) {
            return '\0';
        }

        // Otherwise, return the corresponding character.
        return this->input[this->index];
    }

    std::string Lexer::getCharAsString() const noexcept {
        return std::string(1, this->getChar());
    }

    size_t Lexer::getLength() const noexcept {
        return this->length;
    }

    size_t Lexer::setIndex(size_t index) noexcept {
        // Index cannot be negative.
        if (index < 0) {
            index = 0;
        }
            // Keep index within bounds.
        else if (index >= this->length) {
            index = this->length;
        }

        this->index = index;

        return this->index;
    }

    size_t Lexer::skip(size_t amount) {
        return this->setIndex(this->index + amount);
    }

    MatchResult Lexer::matchExpression(MatchOpts opts) {
        MatchResult result = {
            false
        };

        // Substring from the current index to get the viable matching string.
        std::string input = this->input.substr(this->index);
        std::smatch match;

        // If successful, return a new token with different value and kind.
        if (std::regex_search(input, match, opts.regex)) {
            // If applicable, match should contain both matched value (at index 0) and a captured value (at index 1).
            if (opts.expectCapturedValue && match.size() < 2) {
                throw std::runtime_error("Successful regex match may not contain a captured value");
            }

            int index = opts.expectCapturedValue
                ? IONIR_MATCH_INDEX_CAPTURED
                : IONIR_MATCH_INDEX_MATCHED;

            // Extract the matched or captured value from the match.
            std::string value = match[index];

            /**
             * Since std::regex_search() returns true if any match
             * is found, regardless of its position in the input
             * string, it must be assured that the captured value
             * is actually positioned at the beginning of the input
             * string, otherwise in certain cases it may lead to some
             * tokens being skipped. For example, when parsing a valid
             * token, 'A', if after the value of such token in the input
             * string is located another valid token, 'B', and its rule
             * is processed first, then token 'B' would take precedence
             * when it should not. Additionally, use the matched value
             * index instead of the captured value, because patterns such
             * as literal character and string capture values while skipping
             * certain characters.
             */
            if (!ionshared::Util::stringStartsWith(input, match[IONIR_MATCH_INDEX_MATCHED])) {
                // Return default result at this point.
                return result;
            }

            // Finalize result's properties.
            result.success = true;
            result.matchedValue = match[IONIR_MATCH_INDEX_MATCHED];

            // Set the result's captured value property if applicable.
            if (opts.expectCapturedValue) {
                result.capturedValue = match[IONIR_MATCH_INDEX_CAPTURED];
            }

            // Modify the input token (since it was passed by reference).
            opts.token = Token(opts.tokenKind, value, opts.token.getStartPosition());

            // Skip the matched value's length (never the captured one).
            this->skip(result.matchedValue->length());

            // Return the successful, modified result.
            return result;
        }

        // Return default result, which indicates failure.
        return result;
    }

    void Lexer::processWhitespace() {
        // TODO: Any way to omit 'match' since it's not actually being used?
        // Ignore whitespace.
        std::smatch match;
        std::string subject = this->getCharAsString();

        while (std::regex_search(subject, match, Regex::whitespace) && this->hasNext()) {
            this->skip();
            subject = this->getCharAsString();
        }
    }

    size_t Lexer::getIndex() const noexcept {
        return this->index;
    }

    void Lexer::begin() {
        this->index = IONIR_LEXER_INDEX_DEFAULT;
    }

    bool Lexer::hasNext() const {
        return this->index < this->length;
    }

    std::optional<Token> Lexer::tryNext() {
        // No more possible tokens to retrieve.
        if (!this->hasNext()) {
            return std::nullopt;
        }

        // First, ignore all whitespace if applicable.
        this->processWhitespace();

        // No more possible tokens to retrieve.
        if (!this->hasNext()) {
            return std::nullopt;
        }

        // Set the initial Token buffer as Unknown.
        Token token = Token(TokenKind::Unknown, this->getCharAsString(), this->index);

        // Abstract the Token's value for easier access.
        std::string tokenValue = token.getValue();

        // Begin by testing against all simple until a possible match is found.
        for (const auto &pair : this->simpleIds) {
            // Test the first letter of the subject to continue.
            if (tokenValue[0] == pair.first[0]) {
                /**
                 * Produce a Regex instance to match the exact value of the
                 * simple identifier. It is important that the initial value
                 * is escaped of any Regex special characters.
                 */
                std::regex regex = ionshared::Util::createPureRegex(pair.first);

                /**
                 * If the match starts with an identifier character, ensure that
                 * the token's value ends with a non-identifier character.
                 */
                if (std::regex_match(tokenValue, Regex::identifier)) {
                    // Ensure the requirement of a non-identifier character at the end is met.
                    std::string requirementInput = this->input.substr(this->index);
                    bool postCharacterRequirement = std::regex_search(requirementInput, std::regex("^" + pair.first + "(?:\\s|\\W|$)"));

                    if (!postCharacterRequirement) {
                        continue;
                    }
                }

                MatchResult matchResult = this->matchExpression(MatchOpts{
                    token,
                    pair.second,
                    regex
                });

                if (matchResult.success) {
                    // Reduce the position.
                    // TODO: Causing problems, works when commented HERE.
                    //this.SetPosition(this.Position - token.Value.Length - pair.Key.Length);

                    // Skim the last character off.
                    token = Token(token.getKind(), pair.first, token.getStartPosition());

                    // Return the token, no need to skip its value.
                    return token;
                }
            }
        }

        // No simple was matched, proceed to test complex.
        for (const auto &pair : this->complexIds) {
            MatchResult matchResult = this->matchExpression(MatchOpts{
                token,
                pair.second,
                pair.first,
                true
            });

            // If it matches, return the token (already modified by the matchExpression function).
            if (matchResult.success) {
                return token;
            }
        }

        // At this point the token was not identified. Skip over any captured value.
        this->skip(tokenValue.length());

        // Return the default token. The token kind defaults to Unknown.
        return token;
    }

    std::string Lexer::getInput() const noexcept {
        return this->input;
    }

    std::vector<Token> Lexer::scan() {
        // Reset index to avoid carrying over previous information.
        this->begin();

        // TODO: Should be a list, then converted to a vector?
        std::vector<Token> tokens = {};

        std::optional<Token> token;

        while (this->hasNext()) {
            token = this->tryNext();

            // No more tokens to process.
            if (!token.has_value()) {
                break;
            }
            // Display a warning if the token's type is unknown.
            else if (token->getKind() == TokenKind::Unknown) {
                // TODO: Issue warning instead of plain std::cout.
                std::cout << "Warning: Unknown token encountered" << std::endl;
            }

            // Append the token to the result.
            tokens.push_back(*token);
        }

        return tokens;
    }
}
