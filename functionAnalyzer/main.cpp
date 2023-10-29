#include "ast.h"
#include "tokenizer.h"

int main(int argc, char const *argv[])
{
    std::string str = "14 + sin(274 - sqrt(374 - cos(129)) - 738) - 40 +3 - sqrt(2 , sqrt(329 +29383 - sqrt(9339 + sqrt(3939))))";
    std::vector<std::string> tokens = tokenizeExpression(str);

    //prova
    std::cout << "\n---TOKENIZATION START---" << std::endl;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens[i] << std::endl;
    }
    std::cout << "---TOKENIZATION END---\n" << std::endl;

    std::cout << "Building AST..." << std::endl;
    AST * ast = buildAST(tokens);
    std::cout << "printAST called:" << std::endl;
    ast->printAST();
    std::cout << std::endl;

    FunctionNode* mostNestedFunction = findMostNestedFunction(ast->getRoot());
    std::cout << "\nMost Nested Function: " << mostNestedFunction->getFunction();
    std::cout << "(";
    for (size_t i = 0; i < mostNestedFunction->getArgs().size(); i++)
    {
        printNode(mostNestedFunction->getArgs()[i]);
    }
    std::cout << ")\n" << std::endl;

    std::vector<FunctionNode*> functionsInOrder;
    collectFunctions(ast->getRoot(), functionsInOrder);
    std::reverse(functionsInOrder.begin(), functionsInOrder.end());

    std::cout << "Approaching AST from innermost function to outermost function:" << std::endl;
    for(const auto& function : functionsInOrder){
        std::cout << function->getFunction() << "(";
        for (size_t i = 0; i < function->getArgs().size(); i++)
        {
            if(i>=1) std::cout << " , ";
            printNode(function->getArgs()[i]);
        }
        
        std::cout << ")" << std::endl;
    }

    return 0;
}