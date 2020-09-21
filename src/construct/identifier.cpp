#include <ionir/passes/pass.h>
namespace ionir {
    Identifier::Identifier(std::string name, std::vector<std::string> scopePath) :
        Construct(ConstructKind::Identifier),
        ionshared::Named(std::move(name)),
        scopePath(std::move(scopePath)) {
        //
    }

    Identifier::operator std::string() const {
        std::stringstream stream;

        for (const auto &scopePath : this->scopePath) {
            // TODO: Avoid having it hard-coded.
            stream << scopePath << "::";
        }

        stream << this->getName();

        return stream.str();
    }

    std::string Identifier::operator*() const {
        return this->operator std::string();
    }

    void Identifier::accept(Pass &visitor) {
        visitor.visitIdentifier(this->dynamicCast<Identifier>());
    }

    std::vector<std::string> Identifier::getScopePath() const noexcept {
        return this->scopePath;
    }

    void Identifier::setScopePath(std::vector<std::string> scopePath) noexcept {
        this->scopePath = std::move(scopePath);
    }
}
