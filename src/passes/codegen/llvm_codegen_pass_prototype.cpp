#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <ionir/construct/value.h>
#include <ionir/error_handling/diagnostic.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visit(ionshared::Ptr<Construct> node) {
        /**
         * Only instruct the node to visit this instance and
         * not its children, since they're already visited by
         * the other member methods.
         */
        node->accept(*this);
    }

    void LlvmCodegenPass::visitExtern(ionshared::Ptr<Extern> node) {
        this->requireModule();

        IONIR_PASS_INTERNAL_ASSERT(node->getPrototype() != nullptr)

        llvm::Function *existingExternDefinition =
            (*this->buffers.llvmModule)->getFunction(node->getPrototype()->getId());

        if (existingExternDefinition != nullptr) {
            this->getPassContext()->getDiagnosticBuilder()
                ->bootstrap(diagnostic::externRedefinition);

            throw std::runtime_error("Awaiting new diagnostic buffer checking");
        }

        // Visit the prototype.
        this->visitPrototype(node->getPrototype());

        /**
         * No need to push the resulting function onto the stack; This
         * is done already when visiting the extern's prototype.
         */
    }

    void LlvmCodegenPass::visitPrototype(ionshared::Ptr<Prototype> node) {
        this->requireModule();
        this->requireContext();

        auto argsMap = node->getArgs()->getItems();
        auto &argsNativeMap = argsMap->unwrapConst();

        // Retrieve argument count from the argument vector.
        uint32_t argumentCount = argsMap->getSize();

        // Create the argument buffer vector.
        std::vector<llvm::Type *> llvmArgumentTypes = {};

        // Attempt to retrieve an existing function.
        llvm::Function *llvmFunction = (*this->buffers.llvmModule)->getFunction(node->getId());

        // A function with a matching identifier already exists.
        if (llvmFunction != nullptr) {
            // Function already has a body, disallow re-definition.
            if (llvmFunction->getBasicBlockList().empty()) {
                throw std::runtime_error("Cannot re-define function");
            }
            // If the function takes a different number of arguments, reject.
            else if (llvmFunction->arg_size() != argumentCount) {
                this->getPassContext()->getDiagnosticBuilder()
                    ->bootstrap(diagnostic::functionRedefinitionDiffArgs);

                throw std::runtime_error("Awaiting new diagnostic buffer checking");
            }
        }
        // Otherwise, function will be created.
        else {
            for (const auto &[id, arg] : argsNativeMap) {
                this->visitType(arg.first);
                llvmArgumentTypes.push_back(this->typeStack.pop());
            }

            // Visit and pop the return type.
            this->visitType(node->getReturnType());

            llvm::Type *llvmReturnType = this->typeStack.pop();

            // TODO: Support for infinite arguments and hard-coded return type.
            // Create the function type.
            llvm::FunctionType *llvmFunctionType = llvm::FunctionType::get(
                llvmReturnType,
                llvmArgumentTypes,
                node->getArgs()->getIsVariable()
            );

            // Cast the value to a function, since we know getCallee() will return a function.
            llvmFunction = llvm::dyn_cast<llvm::Function>(
                (*this->buffers.llvmModule)->getOrInsertFunction(node->getId(), llvmFunctionType).getCallee()
            );

            // Set the function's linkage.
            llvmFunction->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
        }

        // Begin processing arguments. Argument count must be the same.
        if (argumentCount != llvmFunction->arg_size()) {
            throw std::runtime_error("Expected argument count to be the same as the function's argument count");
        }

        uint32_t argCounter = 0;
        uint32_t llvmArgCounter = 0;

        // TODO: Simplify method of naming LLVM arguments, as this implementation is inefficient.
        for (const auto &[id, arg] : argsNativeMap) {
            for (auto &llvmArgument : llvmFunction->args()) {
                if (llvmArgCounter == argCounter) {
                    llvmArgument.setName(id);
                    llvmArgCounter = 0;

                    break;
                }

                llvmArgCounter++;
            }

            argCounter++;
        }

        this->valueStack.push(llvmFunction);
    }

    void LlvmCodegenPass::visitFunction(ionshared::Ptr<Function> node) {
        /**
         * This function has already been visited/emitted. This is present
         * because the call instruction requires functions to be present on
         * the local symbol table in order to emit, and if its callee (this node)
         * hasn't yet been emitted, it will emit this function early.
         */
        if (this->symbolTable.contains(node)) {
            return;
        }

        this->requireModule();

        if (!node->verify()) {
            throw std::runtime_error("Function verification failed");
        }
        else if ((*this->buffers.llvmModule)->getFunction(node->getPrototype()->getId()) != nullptr) {
            throw std::runtime_error("A function with the same identifier has been already previously defined");
        }

        // Clear named values.
        this->namedValues.clear();

        // Visit the prototype.
        this->visitPrototype(node->getPrototype());

        // Retrieve the resulting function off the stack.
        llvm::Function *llvmFunction = this->valueStack.popAs<llvm::Function>();

        // Set the function buffer.
        this->buffers.llvmFunction = llvmFunction;

        // Visiting the function body's yields no value to the value stack.
        this->visitFunctionBody(node->getBody());

        // TODO: Verify the resulting LLVM function (through LLVM)?

        this->symbolTable.set(node, llvmFunction);
        this->valueStack.push(llvmFunction);
    }
}
