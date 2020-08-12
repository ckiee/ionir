#include <queue>
#include <ionir/misc/code_writer.h>

namespace ionir {
    void CodeWriter::createModule(ionshared::Ptr<Module> construct) {
        // TODO
    }

    void CodeWriter::createGlobal(ionshared::Ptr<Global> construct) {
        // TODO
    }

    CodeWriter::CodeWriter() : buffer("") {
        //
    }

    std::string CodeWriter::make(ionshared::Ptr<Construct> rootConstruct) const {
        std::queue<ionshared::Ptr<Construct>> queue = {};

        // Push initial items to the queue.
        for (const auto &item : rootConstruct->getChildNodes()) {
            queue.push(item);
        }

        while (!queue.empty()) {
            // TODO: Front or back? Not tested!
            ionshared::Ptr<Construct> item = queue.front();

            queue.pop();

            std::vector<ionshared::Ptr<Construct>> children = item->getChildNodes();

            for (const auto &child : children) {
                queue.push(child);
            }
        }

        return this->getBuffer();
    }

    std::string CodeWriter::getBuffer() const noexcept {
        return this->buffer;
    }

    void CodeWriter::clear() noexcept {
        this->buffer.clear();
    }

    std::string CodeWriter::consumeBuffer() noexcept {
        std::string buffer = this->buffer;

        this->clear();

        return buffer;
    }
}
