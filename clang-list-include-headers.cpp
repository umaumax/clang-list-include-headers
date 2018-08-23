#include <iostream>

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("include-list options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static llvm::cl::extrahelp MoreHelp("\nMore help text...");

// [clang: clang::PPCallbacks Class Reference]( https://clang.llvm.org/doxygen/classclang_1_1PPCallbacks.html )
class PPCallbacksTracker : public PPCallbacks {
 public:
  PPCallbacksTracker() {}
  void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok, llvm::StringRef FileName, bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File, llvm::StringRef SearchPath, llvm::StringRef RelativePath, const clang::Module *Imported) override {
    if (File) {
      if (IsAngled)
        std::cout << "<" << File->getName().str() << ">" << std::endl;
      else
        std::cout << "\"" << File->getName().str() << "\"" << std::endl;
    } else {
      if (IsAngled)
        std::cout << "<" << FileName.str() << ">" << std::endl;
      else
        std::cout << "\"" << FileName.str() << "\"" << std::endl;
    }
  }
};

struct SourceFileHooks : clang::tooling::SourceFileCallbacks {
  SourceFileHooks() {}
  ~SourceFileHooks() override {}
  bool handleBeginSource(clang::CompilerInstance &ci) override {
    ci.getPreprocessor().addPPCallbacks(llvm::make_unique<PPCallbacksTracker>());
    return true;
  }
  void handleEndSource() override {}
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

  MatchFinder Finder;
  SourceFileHooks sf{};
  return Tool.run(newFrontendActionFactory(&Finder, &sf).get());
}
